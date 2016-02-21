#!/bin/bash
bin/Debug/cbp2make --local -in cbp2make.cbp -unix -windows --wrap-objects --wrap-options --with-deps --target-case lower --verbose
#bin/Debug/cbp2make --local -in cbp2make.cbp --verbose
cp -p cbp2make.cbp.mak.unix Makefile
