/*
  Simple DirectMedia Layer
  Copyright (C) 2022 GaryOderNichts <garyodernichts@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_VIDEO_RENDER_WIIU

#include "SDL_shaders_wiiu.h"

#include "shaders/colorShader.inc"
#include "shaders/textureShader.inc"
#include "shaders/textureShaderYUV_JPEG.inc"
#include "shaders/textureShaderYUV_BT601.inc"
#include "shaders/textureShaderYUV_BT709.inc"

static WHBGfxShaderGroup shaderGroups[NUM_SHADERS];
static int shaderRefCount = 0;

void WIIU_SDL_CreateShaders(void)
{
    if (!shaderRefCount++) {
        WHBGfxShaderGroup* colorShader = &shaderGroups[SHADER_COLOR];
        WHBGfxShaderGroup* textureShader = &shaderGroups[SHADER_TEXTURE];
        WHBGfxShaderGroup* textureShaderYUV_JPEG = &shaderGroups[SHADER_YUV_JPEG];
        WHBGfxShaderGroup* textureShaderYUV_BT601 = &shaderGroups[SHADER_YUV_BT601];
        WHBGfxShaderGroup* textureShaderYUV_BT709 = &shaderGroups[SHADER_YUV_BT709];

        WHBGfxLoadGFDShaderGroup(colorShader, 0, colorShader_gsh);
        WHBGfxInitShaderAttribute(colorShader, "a_position", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitShaderAttribute(colorShader, "a_color", 0, 8, GX2_ATTRIB_FORMAT_UNORM_8_8_8_8);
        WHBGfxInitFetchShader(colorShader);

        WHBGfxLoadGFDShaderGroup(textureShader, 0, textureShader_gsh);
        WHBGfxInitShaderAttribute(textureShader, "a_position", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitShaderAttribute(textureShader, "a_color", 0, 8, GX2_ATTRIB_FORMAT_UNORM_8_8_8_8);
        WHBGfxInitShaderAttribute(textureShader, "a_texcoord", 0, 12, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitFetchShader(textureShader);

        WHBGfxLoadGFDShaderGroup(textureShaderYUV_JPEG, 0, textureShaderYUV_JPEG_gsh);
        WHBGfxInitShaderAttribute(textureShaderYUV_JPEG, "a_position", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitShaderAttribute(textureShaderYUV_JPEG, "a_color", 0, 8, GX2_ATTRIB_FORMAT_UNORM_8_8_8_8);
        WHBGfxInitShaderAttribute(textureShaderYUV_JPEG, "a_texcoord", 0, 12, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitFetchShader(textureShaderYUV_JPEG);

        WHBGfxLoadGFDShaderGroup(textureShaderYUV_BT601, 0, textureShaderYUV_BT601_gsh);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT601, "a_position", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT601, "a_color", 0, 8, GX2_ATTRIB_FORMAT_UNORM_8_8_8_8);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT601, "a_texcoord", 0, 12, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitFetchShader(textureShaderYUV_BT601);

        WHBGfxLoadGFDShaderGroup(textureShaderYUV_BT709, 0, textureShaderYUV_BT709_gsh);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT709, "a_position", 0, 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT709, "a_color", 0, 8, GX2_ATTRIB_FORMAT_UNORM_8_8_8_8);
        WHBGfxInitShaderAttribute(textureShaderYUV_BT709, "a_texcoord", 0, 12, GX2_ATTRIB_FORMAT_FLOAT_32_32);
        WHBGfxInitFetchShader(textureShaderYUV_BT709);
    }
}

void WIIU_SDL_DestroyShaders(void)
{
    if (!--shaderRefCount) {
        WHBGfxFreeShaderGroup(&shaderGroups[SHADER_COLOR]);
        WHBGfxFreeShaderGroup(&shaderGroups[SHADER_TEXTURE]);
        WHBGfxFreeShaderGroup(&shaderGroups[SHADER_YUV_JPEG]);
        WHBGfxFreeShaderGroup(&shaderGroups[SHADER_YUV_BT601]);
        WHBGfxFreeShaderGroup(&shaderGroups[SHADER_YUV_BT709]);
    }
}

void WIIU_SDL_SelectShader(WIIU_ShaderType shader)
{
    WHBGfxShaderGroup* shaderGroup = &shaderGroups[shader];

    GX2SetFetchShader(&shaderGroup->fetchShader);
    GX2SetVertexShader(shaderGroup->vertexShader);
    GX2SetPixelShader(shaderGroup->pixelShader);
}

WHBGfxShaderGroup* WIIU_SDL_GetShaderGroup(WIIU_ShaderType shader)
{
    return &shaderGroups[shader];
}

#endif //SDL_VIDEO_RENDER_WIIU
