#!/usr/bin/env fish

set -l BUILD_DIR src/build_msvc
set -l COMPDB "$BUILD_DIR/compile_commands.json"

set -l REPORT_DIR reports
set -l FILTERED_COMPDB "$REPORT_DIR/compile_commands.filtered.json"

set -l CPPCHECK_DIR "$REPORT_DIR/cppcheck"
set -l CLANG_TIDY_DIR "$REPORT_DIR/clang_tidy"
set -l CPPCHECK_HTML_DIR "$CPPCHECK_DIR/html"

if not test -f "$COMPDB"
    echo "error: $COMPDB not found"
    exit 1
end

mkdir -p "$REPORT_DIR"
mkdir -p "$CPPCHECK_DIR"
mkdir -p "$CLANG_TIDY_DIR"
mkdir -p "$CPPCHECK_HTML_DIR"

echo "==> Filtering compilation database..."

jq '
    map(
        select(
            (.file | contains("/sdk/") | not)
            and
            (.file | contains("/src/3rd_party/") | not)
            and
            (.file | contains("/_deps/") | not)
        )
    )
' "$COMPDB" >"$FILTERED_COMPDB"

or begin
    echo "error: failed to filter compile_commands.json"
    exit 1
end

echo "==> Running Cppcheck..."

cppcheck \
    --project="$FILTERED_COMPDB" \
    -j (nproc) \
    --enable=warning,style,performance,portability \
    --inconclusive \
    --xml \
    --xml-version=2 \
    --output-file="$CPPCHECK_DIR/report.xml" 2>"$CPPCHECK_DIR/stderr.txt"

or begin
    echo "error: cppcheck failed"
    exit 1
end

echo "==> Generating Cppcheck HTML report..."

cppcheck-htmlreport \
    --file="$CPPCHECK_DIR/report.xml" \
    --report-dir="$CPPCHECK_HTML_DIR" \
    --source-dir=src

or begin
    echo "error: failed to generate HTML report"
    exit 1
end

echo "==> Running clang-tidy..."

set -l COMPDB_BACKUP "$COMPDB.bak"

cp "$COMPDB" "$COMPDB_BACKUP"
or begin
    echo "error: failed to back up compile_commands.json"
    exit 1
end

function restore_compdb --on-event fish_exit
    if test -f "$COMPDB_BACKUP"
        mv -f "$COMPDB_BACKUP" "$COMPDB"
    end
end

cp "$FILTERED_COMPDB" "$COMPDB"
or begin
    echo "error: failed to replace compile_commands.json"
    exit 1
end

./run-clang-tidy.py \
    -p "$BUILD_DIR" \
    -j (nproc)

set -l tidy_status $status

mv -f "$COMPDB_BACKUP" "$COMPDB"
functions -e restore_compdb

if test $tidy_status -ne 0
    echo "error: clang-tidy failed"
    exit $tidy_status
end

echo
echo "Reports written to:"
echo "  XML:  $CPPCHECK_DIR/report.xml"
echo "  HTML: $CPPCHECK_HTML_DIR/index.html"
echo "  Log:  $CPPCHECK_DIR/stderr.txt"
