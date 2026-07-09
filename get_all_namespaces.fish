#!/usr/bin/env fish

fd \
    -0 \
    --exclude sdk \
    --exclude src/3rd_party \
    -e cpp -e cxx -e cc -e c -e h -e hh -e hpp -e hxx . \
    | xargs -0 rg --pcre2 --no-filename -o \
    '^\s*(?:inline\s+)?namespace\s+\K(?:[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)' \
    | sort -u
