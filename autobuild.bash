#!/bin/bash

# Build ImageDisplayTool
mkdir Build

cd Build

mkdir ImageDisplayTool

cd ImageDisplayTool

cmake ../../ImageDisplayTool

make

# Build QtRenderTool

cd ../

mkdir QtRenderTool

cd QtRenderTool

cmake ../../QtRenderTool

make

# buiBuildld TestDemo

cd ../

mkdir TestDemo

cd TestDemo

cmake ../../TestDemo

make

cd ../