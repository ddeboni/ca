#!/bin/sh

echo "Building GeometricCA"
cd src
make clean
make
cd ..

for rule in 160 108 30 110
do
	for distribution in "point" "uniform"
	do
		echo "Running GeometricCA with rule ${rule} and ${distribution} distibution"
#		./ca -r ${rule} -d ${distribution} -z 4 &
		./ca -r ${rule} -d ${distribution} -z 16 -g &
#		./ca -r ${rule} -d ${distribution} -z 32 -g &
	done
done
