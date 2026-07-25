#!/usr/bin/env fish

set -l BUILD_DIR src/build_msvc
set -l COMPDB "$BUILD_DIR/compile_commands.json"
set -l REPORT_DIR reports
set -l CPPCHECK_DIR "$REPORT_DIR/cppcheck"
set -l CLANG_TIDY_DIR "$REPORT_DIR/clang_tidy"

if not test -f "$COMPDB"
    echo "error: $COMPDB not found"
    exit 1
end

mkdir -p "$CPPCHECK_DIR"
mkdir -p "$CLANG_TIDY_DIR"

echo "==> Running Cppcheck..."

cppcheck \
    --project="$COMPDB" \
    --enable=warning,style,performance,portability \
    --inconclusive \
    --xml \
    --xml-version=2 \
    --output-file="$CPPCHECK_DIR/report.xml" 2>"$CPPCHECK_DIR/stderr.txt"

echo "==> Running clang-tidy..."

jq -r '
    .[]
    | select(
        (.file | contains("/sdk/") | not)
        and
        (.file | contains("/src/3rd_party/") | not)
        and
        (.file | contains("/src/build_msvc/_deps/") | not(
    )
    | @base64
' "$COMPDB" | while read -l entry
    set -l json (echo "$entry" | base64 -d)

    set -l file (echo "$json" | jq -r '.file')
    set -l rel (string replace -r '^.*/' '' "$file")
    set -l out "$CLANG_TIDY_DIR/$rel.txt"

    echo "  $file"

    clang-tidy \
        -p "$BUILD_DIR" \
        "$file" >"$out" 2>&1
end

echo
echo "Reports written to:"
echo "  $CPPCHECK_DIR/report.xml"
echo "  $CPPCHECK_DIR/stderr.txt"
echo "  $CLANG_TIDY_DIR/"
