#include <nds.h>

#include <nds/arm9/console.h>  // consoleDemoInit
#include <nds/arm9/input.h>    // touchRead
#include <nds/interrupts.h>    // swiWaitForVBlank

#include <stdio.h>  // iprintf

#include "sample_image_bmp.h"

int main(void) {
    videoSetMode(MODE_5_2D);  // set the mode for 2 text layers and 2 ext bg's
    videoSetModeSub(MODE_0_2D);  // sub bg 0 to print text for now

    vramSetBankA(VRAM_A_MAIN_BG);
    bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
    dmaCopy(sample_image_bmp + 0x46, BG_GFX, sample_image_bmp_size - 0x46);

    consoleDemoInit();  // setup the sub screen for printing

    do {
        touchPosition touch;
        touchRead(&touch);
        iprintf("\x1b[10;0HTouch x = %04i, %04i\n", touch.rawx, touch.px);
        iprintf("Touch y = %04i, %04i\n", touch.rawy, touch.py);
        swiWaitForVBlank();
    } while (!(scanKeys(), keysDown() & KEY_START));

    return 0;
}
