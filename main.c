#include "wfc.h"

#include <input.h>
#include <print.h>
#include <vdp.h>

void main()
{
	VDP_SetMode(VDP_MODE_SCREEN2);
	VDP_ClearVRAM();

	Print_SetTextFont(PRINT_DEFAULT_FONT, 1);

	wave_t wave;
    wave_reset(&wave);

	for (u16 y = 0; y < MAP_HEIGHT; y++)
	{
		for (u16 x = 0; x < MAP_WIDTH; x++)
		{
			Print_SetPosition(x, y);
			if (wave_is_collapsed(&wave, x, y))
			{
				tile_id_t tile = wave_get_tile(&wave, x, y);
				Print_DrawChar(TILE_CHARS[tile]);
			}
			else
			{
				Print_DrawChar(0xD7);
			}
		}
	}

	wave_collapse(&wave);

	while (!Keyboard_IsKeyPressed(KEY_ESC))
	{
        // Wait for ESC key to exit
    }
}
