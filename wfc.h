#pragma once

#include "config.h"

typedef struct
{
    u16 possibilities_bitmap;
    u8 entropy : 5;
    bool collapsed : 1;
    tile_id_t value : 4;
} cell_t;

typedef struct
{
    cell_t cells[MAP_HEIGHT * MAP_WIDTH];
} wave_t;

void wave_reset(wave_t* wave);
void wave_collapse(wave_t* wave);

void wave_propagate(wave_t* wave, i16 cell_index);
bool wave_is_fully_collapsed(wave_t* wave);
i16 wave_observe(wave_t* wave);
i16 wave_get_min_entropy_cell(wave_t* wave);

bool wave_is_collapsed(const wave_t* wave, u8 x, u8 y);
tile_id_t wave_get_tile(const wave_t* wave, u8 x, u8 y);
