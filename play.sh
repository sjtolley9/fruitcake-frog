#!/bin/bash

cd build
make
rm -r bin/assets
cp -r ../assets bin/assets/
cd bin

./fcFrog
