/*
* resource.h
*
* definitions for loading graphic resources
*/

#ifndef _RESOURCE_H
#define _RESOURCE_H
#include "gfx.h"
#include "menu.h"

enum resource {
    R_CHECKBOX,
    R_ICON,
    R_END
};

void           *__resource_get(enum resource resource);

#endif