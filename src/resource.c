#include <grc.h>
#include "resource.h"

static void *__resource_table[R_END] = { NULL };

static const char *__resource_names[R_END] = {
    "checkbox",
    "icons",
};

static void *__load_resource(enum resource resource){
    if(__resource_names[resource]){
        gfx_texture *kztext = malloc(sizeof(*kztext));
        if(!kztext){
            return kztext;
        }
        memset(kztext, 0, sizeof(*kztext));
        void *grctexture;
        if(!grc_resource_get(__resource_names[resource], &grctexture, NULL)){
            return kztext;
        }
        struct grc_texture *gtext = grctexture;
        kztext->data = gtext->texture_data;
        kztext->img_fmt = gtext->im_fmt;
        kztext->img_size = gtext->im_siz;
        kztext->tile_width = gtext->tile_width;
        kztext->tile_height = gtext->tile_height;
        kztext->x_tiles = gtext->tiles_x;
        kztext->y_tiles = gtext->tiles_y;
        kztext->tile_size = (kztext->tile_width * kztext->tile_height * G_SIZ_BITS(kztext->img_size) + 63) / 64 * 8;
        return kztext;
    }
    return NULL;
}

void *__resource_get(enum resource resource){
    if(!__resource_table[resource]){
        __resource_table[resource] = __load_resource(resource);
    }
    return __resource_table[resource];
}