#!/bin/bash
header="src/revision.h"
revision=$((`git-revision`+1))
echo "#ifndef REVISION_H" > $header
echo "#define REVISION_H" >> $header
echo >> $header
echo "#define REVISION_NUMBER $revision" >> $header
echo >> $header
echo "#endif" >> $header
echo >> $header
