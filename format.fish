#!/usr/bin/env fish

fd --type f \
    --extension c \
    --extension cc \
    --extension cpp \
    --extension cxx \
    --extension h \
    --extension hh \
    --extension hpp \
    --extension hxx \
    --extension inc \
    --extension inl \
    --extension m \
    --extension mm \
    --exec-batch clang-format -i
