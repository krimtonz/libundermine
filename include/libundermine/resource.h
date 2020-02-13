/*
* resource.h
*
* definitions for loading graphic resources
*/

#ifndef _LIBUM_RESOURCE_H
#define _LIBUM_RESOURCE_H
#include "gfx.h"
#include "menu.h"

#define RESOURCE_MAX    256

#define R_CHECKBOX      0
#define R_ICON          1
#define R_END           2

typedef void   *(*resource_ctor)    (int resource_id);
typedef void    (*resource_dtor)    (int resource_id);

typedef struct {
    int             resource_id;
    const char     *resource_name;
    void           *data;
    resource_ctor   ctor;
    resource_dtor   dtor;
} resource_ent_t;

void           *resource_get        (int resource);
void            resource_free       (int resource);
resource_ent_t *resource_create     (const char *name, resource_ctor ctor, resource_dtor dtor);
void           *grc_ctor            (int resource_id);
void            resource_init       (void);
#endif