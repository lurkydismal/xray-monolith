#!/usr/bin/env fish

rg -n \
    -g '!sdk/**' \
    -g '!src/3rd_party/**' \
    '#\s*include\s*[<"]([^">]+)[">]' . |
    while read -l match
        set file (string split : $match)[1]
        set line (string split : $match)[2]
        set inc (string replace -r '.*[<"]([^">]+)[">].*' '$1' $match)

        set dir (path dirname $file)
        set candidate $dir/$inc

        if test -e $candidate
            continue
        end

        set found (fd \
        -E sdk \
        -E 'src/3rd_party' \
        -i --full-path \
        "^.*/"(string escape --style=regex $inc)'$' \
        $dir)

        if test -n "$found"
            echo "$file:$line"
            echo "  include: $inc"
            echo "  actual : $found"
            echo
        end
    end
