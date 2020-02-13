#include <grc.h>
#include <list/list.h>
#include <libundermine.h>

static struct list  resource_list;
static int          next_resource_id;

static resource_ent_t *resource_find(int resource_id){
    for(resource_ent_t *ent = resource_list.first;ent;ent = list_next(ent)){
        if(ent->resource_id == resource_id){
            return ent;
        }
    }
    return NULL;
}

void *grc_ctor(int resource_id){
    resource_ent_t *ent = resource_find(resource_id);
    gfx_texture *kztext = malloc(sizeof(*kztext));
    if(!kztext){
        return kztext;
    }
    memset(kztext, 0, sizeof(*kztext));
    void *grctexture;
    if(!grc_resource_get(ent->resource_name, &grctexture, NULL)){
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

void resource_init(void){
    list_init(&resource_list, sizeof(resource_ent_t));
    static resource_ent_t checkbox_res = {
        0,  "checkbox", NULL,   grc_ctor,   NULL,
    };
    static resource_ent_t icons_res = {
        1,  "icons",    NULL,   grc_ctor,   NULL,
    };
    list_push_back(&resource_list, &checkbox_res);
    list_push_back(&resource_list, &icons_res);
    next_resource_id = R_END;
}

void *resource_get(int resource_id){
    resource_ent_t *ent = resource_find(resource_id);
    if(ent){
        if(!ent->data){
            ent->data = ent->ctor(resource_id);
        }
        return ent->data;
    }
    return NULL;
}

void resource_free(int resource_id){
    resource_ent_t *ent = resource_find(resource_id);
    if(ent){
        if(ent->dtor){
            ent->dtor(resource_id);
        }
        list_erase(&resource_list, ent);
    }
}

resource_ent_t *resource_create(const char *name, resource_ctor ctor, resource_dtor dtor){
    resource_ent_t *new_ent = list_push_back(&resource_list, NULL);
    if(new_ent){
        new_ent->resource_name = name;
        new_ent->resource_id = next_resource_id++;
        new_ent->data = NULL;
        new_ent->ctor = ctor;
        new_ent->dtor = dtor;
    }
    return new_ent;
}