#!/bin/sh

echo "Building GeometricCA"
cd src
make clean
make
cd ..

for rule in {0..255}
do
	echo "Running ElementaryCA with rule ${rule}"
	./ca -r ${rule}
#	./ca -r ${rule} -z 4
#	./ca -r ${rule} -z 16 -g
#	./ca -r ${rule} -z 32 -g
done
