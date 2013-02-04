cd code
HEADER=om.inc
rm -f $HEADER
for file in $(find . -type f -name '*.hpp'); do echo "#include \"$file\"" >> $HEADER; done
cd ..
