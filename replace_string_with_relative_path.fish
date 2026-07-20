#!/usr/bin/env fish

if test (count $argv) -ne 2
    echo "Usage: "(status basename)" <path> <variable>"
    exit 1
end

set target (realpath $argv[1])
set variable $argv[2]

fd -e vcxproj -e props -e targets | while read -l file
    set dir (dirname (realpath $file))
    set rel (realpath --relative-to "$dir" "$target")

    # MSBuild uses backslashes.
    set rel (string replace -a / \\ "$rel")

    # If the target is a directory, preserve the trailing slash.
    if test -d "$target"
        set rel "$rel\\"
    end

    # Escape backslashes for sed.
    set rel_escaped (string replace -a \\ \\\\ "$rel")

    set pattern '$('"$variable"')'

    sed -i "s|$pattern|$rel_escaped|g" "$file"
end
