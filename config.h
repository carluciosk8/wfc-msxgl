#pragma once

#include <core.h>

#define MAP_WIDTH   32
#define MAP_HEIGHT  24

#define NUM_TILES 16

typedef u8 tile_id_t;

typedef struct
{
    tile_id_t* up;
    tile_id_t* right;
    tile_id_t* down;
    tile_id_t* left;
} adjacency_rules_t;

typedef enum
{
    DIRECTION_UP    = 0,
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN  = 2,
    DIRECTION_LEFT  = 3,
} direction_t;

static const tile_id_t TILE_CHARS[NUM_TILES] =
{
    0x18,     // '┌'
    0x1A,     // '└'
    0x19,     // '┐'
    0x1B,     // '┘'

    0x14,     // '├'
    0x13,     // '┤'
    0x12,     // '┬'
    0x11,     // '┴'

    0x15,     // '┼'
    0x16,     // '│'
    0x17,     // '─'
    0x20,     // ' '

    0xCD,     // '🭭'
    0xCE,     // '🭯'
    0xCF,     // '🭬'
    0xD0,     // '🭮'
};

static const tile_id_t UC[] = {0, 2, 4, 5, 6, 8, 9, 13};
static const tile_id_t RC[] = {2, 3, 5, 6, 7, 8, 10, 14};
static const tile_id_t DC[] = {1, 3, 4, 5, 7, 8, 9, 12};
static const tile_id_t LC[] = {0, 1, 4, 6, 7, 8, 10, 15};

static const tile_id_t UN[] = {1, 3, 7, 10, 11, 12, 14, 15};
static const tile_id_t RN[] = {0, 1, 4, 9, 11, 12, 13, 15};
static const tile_id_t DN[] = {0, 2, 6, 10, 11, 13, 14, 15};
static const tile_id_t LN[] = {2, 3, 5, 9, 11, 12, 13, 14};

// Adjacency rules:
// For each tile, define which tiles can be placed on each side:
// - UP: tiles that can be above this tile
// - RIGHT: tiles that can be to the right of this tile
// - DOWN: tiles that can be below this tile
// - LEFT: tiles that can be to the left of this tile
static const adjacency_rules_t ADJACENCY_RULES[NUM_TILES] =
{
    // Tile 0: '┌'
    {
        .up = UN,
        .right = RC,
        .down = DC,
        .left = LN,
    },
    // Tile 1: '└'
    {
        .up = UC,
        .right = RC,
        .down = DN,
        .left = LN,
    },
    // Tile 2: '┐'
    {
        .up = UN,
        .right = RN,
        .down = DC,
        .left = LC,
    },
    // Tile 3: '┘'
    {
        .up = UC,
        .right = RN,
        .down = DN,
        .left = LC,
    },
    // Tile 4: '├'
    {
        .up = UC,
        .right = RC,
        .down = DC,
        .left = LN,
    },
    // Tile 5: '┤'
    {
        .up = UC,
        .right = RN,
        .down = DC,
        .left = LC,
    },
    // Tile 6: '┬'
    {
        .up = UN,
        .right = RC,
        .down = DC,
        .left = LC,
    },
    // Tile 7: '┴'
    {
        .up = UC,
        .right = RC,
        .down = DN,
        .left = LC,
    },
    // Tile 8: '┼'
    {
        .up = UC,
        .right = RC,
        .down = DC,
        .left = LC,
    },
    // Tile 9: '│'
    {
        .up = UC,
        .right = RN,
        .down = DC,
        .left = LN,
    },
    // Tile 10: '─'
    {
        .up = UN,
        .right = RC,
        .down = DN,
        .left = LC,
    },
    // Tile 11: ' '
    {
        .up = UN,
        .right = RN,
        .down = DN,
        .left = LN,
    },
    // Tile 12: '╵'
    {
        .up = UC,
        .right = RN,
        .down = DN,
        .left = LN,
    },
    // Tile 13: '╷'
    {
        .up = UN,
        .right = RN,
        .down = DC,
        .left = LN,
    },
    // Tile 14: '╴'
    {
        .up = UN,
        .right = RN,
        .down = DN,
        .left = LC,
    },
    // Tile 15: '╶'
    {
        .up = UN,
        .right = RC,
        .down = DN,
        .left = LN,
    },
};
