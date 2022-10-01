#!/bin/bash

for f in {A..O} ; do
    echo "cp _template.cpp $f.cpp"
    cp _template.cpp $f.cpp
    echo "cp _template_gen.cpp ${f}_gen.cpp"
    cp _template_gen.cpp ${f}_gen.cpp
done

