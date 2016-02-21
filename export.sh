#!/bin/bash
workdir=`pwd`
exportdir=$HOME/Export
revision=`git-revision`
exportname=cbp2make-rev$revision
target=$exportdir/$exportname
mkdir -p $target
mkdir -p $target/res
cp -p res/cbp2make.svg $target/res/cbp2make.svg
cp -p res/cbp2make.png $target/res/cbp2make.png
cp -pr lib $target
cp -pr src $target
cp -p cbp2make.cbp $target
cp -p cbp2make.cbp.mak.unix $target
cp -p cbp2make.cbp.mak.windows $target
cp -p Doxyfile $target
cp -p cbp2make.cfg $target
cp -p changelog.txt $target
cp -p COPYING $target
cp -p usage.txt $target
cp -p wx-config.sh $target
cd $exportdir
cd $exportname
for l in 0 1 2 3 4 5 6 7 8 9; do { for d in `find -type d`; do chmod 0755 $d; done; }; done
for f in `find -type f`; do chmod 0644 $f; done;
cd ..
rm -f $exportname.tar.gz
tar -cf $exportname.tar $exportname
gzip $exportname.tar
