#include "tonc.h"

#include "image.h"

int main(){
    //enable bg
    u8 cbb = 0;
    u8 sbb = 16;
    REG_BG0CNT = BG_BUILD(cbb, sbb, 0, 0, 0, 0, 0);
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;

    //load palette
    memcpy16(pal_bg_mem, imagePal, imagePalLen/2);

    //load tiles
    LZ77UnCompVram(imageTiles, tile_mem[cbb]);
    
    //load image
    memcpy16(&se_mem[sbb], imageMap, imageMapLen/2);

}