#!/bin/bash
# to build shaders you need to place a copy of latte-assembler into the current directory
# latte-assembler is part of decaf-emu <https://github.com/decaf-emu/decaf-emu>

cd "${0%/*}"

# colorShader
echo "Building colorShader ..."
./latte-assembler assemble --vsh=colorShader.vsh --psh=colorShader.psh colorShader.gsh
xxd -i colorShader.gsh > colorShader.inc
echo "Done!"

# textureShader
echo "Building textureShader ..."
./latte-assembler assemble --vsh=textureShader.vsh --psh=textureShader.psh textureShader.gsh
xxd -i textureShader.gsh > textureShader.inc
echo "Done!"

# textureShaderYUV_JPEG
echo "Building textureShaderYUV_JPEG ..."
./latte-assembler assemble --vsh=textureShader.vsh --psh=textureShaderYUV_JPEG.psh textureShaderYUV_JPEG.gsh
xxd -i textureShaderYUV_JPEG.gsh > textureShaderYUV_JPEG.inc
echo "Done!"

# textureShaderYUV_BT601
echo "Building textureShaderYUV_BT601 ..."
./latte-assembler assemble --vsh=textureShader.vsh --psh=textureShaderYUV_BT601.psh textureShaderYUV_BT601.gsh
xxd -i textureShaderYUV_BT601.gsh > textureShaderYUV_BT601.inc
echo "Done!"

# textureShaderYUV_BT709
echo "Building textureShaderYUV_BT709 ..."
./latte-assembler assemble --vsh=textureShader.vsh --psh=textureShaderYUV_BT709.psh textureShaderYUV_BT709.gsh
xxd -i textureShaderYUV_BT709.gsh > textureShaderYUV_BT709.inc
echo "Done!"
