/*
  Simple DirectMedia Layer
  Copyright (C) 2022 Clownacy

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

#include "../SDL_sysurl.h"

#include <stddef.h>
#include <string.h>

#include <sysapp/switch.h>

#include "SDL_stdinc.h"

int
SDL_SYS_OpenURL(const char *url)
{
    size_t url_length = strlen(url);
    char *url_copy = SDL_malloc(url_length);

    if (url_copy == NULL) {
        return SDL_OutOfMemory();
    } else {
        SysAppBrowserArgs args;

        args.stdArgs.anchor = NULL;
        args.stdArgs.anchorSize = 0;
        args.url = url_copy;
        args.urlSize = url_length;

        SDL_memcpy(url_copy, url, url_length);

        SYSSwitchToBrowserForViewer(&args);

        SDL_free(url_copy);

        return 0;
    }
}
