#!/bin/bash
bin/Release/cbp2make --help > usage.txt
cp -p usage.txt src/doc/usage.txt
doxygen Doxyfile
