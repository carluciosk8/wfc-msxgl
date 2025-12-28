#include "wfc.h"

#include <math.h>
#include <print.h>

static inline u16 cell_index(u8 x, u8 y)
{
    return (u16)y * MAP_WIDTH + (u16)x;
}

static inline u8 cell_x(u16 index)
{
    return index % MAP_WIDTH;
}

static inline u8 cell_y(u16 index)
{
    return index / MAP_WIDTH;
}

static void cell_collapse(cell_t* cell, tile_id_t tile)
{
    cell->collapsed = true;
    cell->value = tile;
    cell->entropy = 1;

    for (u8 i = 0; i < NUM_TILES; i++)
    {
        if (i != tile)
        {
            cell->possibilities_bitmap &= ~(1 << i);
        }
    }
}

static bool can_place(tile_id_t tile_a, tile_id_t tile_b, direction_t direction)
{
    const adjacency_rules_t* rules = &ADJACENCY_RULES[tile_b];
    
    switch (direction)
    {
        case DIRECTION_UP:
        {
            for (u8 i = 0; i < 8; i++)
            {
                if (rules->up[i] == tile_a) return true;
            }
            return false;
        }
        case DIRECTION_RIGHT:
        {
            for (u8 i = 0; i < 8; i++)
            {
                if (rules->right[i] == tile_a) return true;
            }
            return false;
        }
        case DIRECTION_DOWN:
        {
            for (u8 i = 0; i < 8; i++)
            {
                if (rules->down[i] == tile_a) return true;
            }
            return false;
        }
        case DIRECTION_LEFT:
        {
            for (u8 i = 0; i < 8; i++)
            {
                if (rules->left[i] == tile_a) return true;
            }
            return false;
        }
    }
    return false;
}


void wave_reset(wave_t* wave)
{
    for (u16 i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
    {
        wave->cells[i].entropy = NUM_TILES;
        wave->cells[i].collapsed = false;
        wave->cells[i].value = 0;
        wave->cells[i].possibilities_bitmap = 0xFFFF;
    }
}

bool wave_is_fully_collapsed(wave_t* wave)
{
    for (u16 i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
    {
        if (!wave->cells[i].collapsed)
        {
            return false;
        }
    }
    return true;
}

i16 wave_get_min_entropy_cell(wave_t* wave)
{
    u8 min_entropy = NUM_TILES + 1;
    i16 min_index = -1;
    
    for (u16 i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
    {
        if (wave->cells[i].collapsed) continue;
        
        if (wave->cells[i].entropy > 0)
        {
            if (wave->cells[i].entropy < min_entropy)
            {
                min_entropy = wave->cells[i].entropy;
                min_index = i;
            }
            else if (wave->cells[i].entropy == min_entropy)
            {
                if (Math_GetRandom8() == 0)
                {
                    min_entropy = wave->cells[i].entropy;
                    min_index = i;
                }
            }
        }
    }
    
    return min_index;
}

i16 wave_observe(wave_t* wave)
{
    i16 cell_index_val = wave_get_min_entropy_cell(wave);

    if (cell_index_val == -1) return -1;
    
    cell_t* cell = &wave->cells[cell_index_val];

    u8 count = 0;
    tile_id_t possibilities[NUM_TILES];
    for (u8 i = 0; i < NUM_TILES; i++)
    {
        if (cell->possibilities_bitmap & (1 << i))
        {
            possibilities[count++] = i;
        }
    }
    
    tile_id_t selected = possibilities[Math_GetRandomMax8(count)];
    cell_collapse(cell, selected);

    Print_SetPosition(cell_x(cell_index_val), cell_y(cell_index_val));
    Print_DrawChar(TILE_CHARS[selected]);

    return cell_index_val;
}

void wave_propagate_direc(wave_t* wave, u8 x, u8 y, tile_id_t tile_value, direction_t direction)
{
    u16 neighbor_idx = cell_index(x, y);
    cell_t* neighbor = &wave->cells[neighbor_idx];

    if (!neighbor->collapsed)
    {
        for (u8 t = 0; t < NUM_TILES; t++)
        {
            if (neighbor->possibilities_bitmap & (1 << t))
            {
                if (!can_place(tile_value, t, direction))
                {
                    neighbor->possibilities_bitmap &= ~(1 << t);
                    neighbor->entropy--;
                }
            }
        }
    }
}

void wave_propagate(wave_t* wave, i16 cell_idx)
{
    u8 x = cell_x(cell_idx);
    u8 y = cell_y(cell_idx);
    tile_id_t tile_value = wave->cells[cell_idx].value;
    
    if (y < MAP_HEIGHT - 1)
    {
        wave_propagate_direc(wave, x, y + 1, tile_value, DIRECTION_UP);
    }
    
    if (x > 0)
    {
        wave_propagate_direc(wave, x - 1, y, tile_value, DIRECTION_RIGHT);
    }

    if (y > 0)
    {
        wave_propagate_direc(wave, x, y - 1, tile_value, DIRECTION_DOWN);
    }
    
    if (x < MAP_WIDTH - 1)
    {
        wave_propagate_direc(wave, x + 1, y, tile_value, DIRECTION_LEFT);
    }
}

void wave_collapse(wave_t* wave)
{
    while (!wave_is_fully_collapsed(wave))
    {
        i16 cell_idx = wave_observe(wave);
        if (cell_idx == -1) return;
        wave_propagate(wave, cell_idx);
    }
}

tile_id_t wave_get_tile(const wave_t* wave, u8 x, u8 y)
{
    return wave->cells[cell_index(x, y)].value;
}

bool wave_is_collapsed(const wave_t* wave, u8 x, u8 y)
{
    return wave->cells[cell_index(x, y)].collapsed;
}
