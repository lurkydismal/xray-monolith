#!/usr/bin/env fish

set slndir (realpath src)

fd -e vcxproj -e props -e targets . | while read -l file
    set dir (dirname (realpath $file))
    set rel (realpath --relative-to $dir $slndir)

    # Visual Studio expects backslashes
    set rel (string replace -a / \\ $rel)

    perl -pi -e "s/\\\$\\(SolutionDir\\)/$rel\\\\/g" $file
    # echo "$file -> $rel\\"
end
