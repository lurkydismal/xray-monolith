#!/usr/bin/env fish

set slndir (realpath src)

fd -e vcxproj -e props -e targets | while read -l file
    set dir (dirname (realpath $file))
    set rel (realpath --relative-to "$dir" "$slndir")
    set rel (string replace -a / \\ "$rel")

    set rel (string replace -a / \\ "$rel")
    set rel_escaped (string replace -a \\ \\\\ "$rel")

    sed -i "s|\$(SolutionDir)|$rel_escaped\\\\|g" "$file"
end
