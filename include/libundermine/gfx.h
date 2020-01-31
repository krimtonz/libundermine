/*
* gfx.h
*
* definitions for graphics drawing
*/

#ifndef _LIBUM_GFX_H
#define _LIBUM_GFX_H
#include <n64.h>
#include <stdarg.h>

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240

#define gfx_push(...)   {Gfx gfx__[]={__VA_ARGS__};     \
                        gfx_append(gfx__,sizeof(gfx__));}

enum rdp_mode {
    RDP_MODE_COLOR,
    RDP_MODE_COMBINE,
    RDP_MODE_FILTER,
    RDP_MODE_ALL
};

typedef struct {
    void       *data;                   /* 0x0000 */
    uint16_t    tile_width;             /* 0x0004 */
    uint16_t    tile_height;            /* 0x0006 */
    uint16_t    x_tiles;                /* 0x0008 */
    uint16_t    y_tiles;                /* 0x000A */
    size_t      tile_size;              /* 0x000C */
    g_ifmt_t    img_fmt;                /* 0x0010 */
    g_isiz_t    img_size;               /* 0x0011 */
} gfx_texture;                          /* 0x0012 */

typedef struct {
    gfx_texture    *texture;            /* 0x0000 */
    uint16_t        c_width;            /* 0x0004 */
    uint16_t        c_height;           /* 0x0006 */
    uint16_t        cx_tile;            /* 0x0008 */
    uint16_t        cy_tile;            /* 0x000A */
} gfx_font;                             /* 0x000C */

void            gfx_init                    (size_t gfx_size, gfx_texture *font, Gfx **gfx_finish_p);
void            gfx_begin                   (void);
void            gfx_finish                  (void);
void            gfx_finish_set              (Gfx **gfx_append_p);

void           *gfx_data_push               (void *data, size_t size);
void            gfx_append                  (Gfx *gfx, size_t size);

void            gfx_printf                  (uint16_t,uint16_t,const char*,...);
void            gfx_printf_color            (uint16_t,uint16_t,uint32_t,const char*,...);

void            gfx_draw_sprite             (gfx_texture *texture, int x, int y, int tile, int width, int height);
void            gfx_draw_sprite_color       (gfx_texture *texture, int x, int y, int tile, int width, int height, uint32_t color);
void            gfx_draw_rectangle          (int x, int y, int width, int height, uint32_t color);

void            gfx_load_tile               (gfx_texture *texture, uint16_t tilenum);

void            gfx_destroy_texture         (gfx_texture *texture);
void            gfx_texture_desaturate      (void *data, size_t len);

extern gfx_font *kfont;

#endif