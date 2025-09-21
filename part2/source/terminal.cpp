#include "terminal.hpp"

#include "text.h"

#define TERMINAL_TEXT_WIDTH 28
#define TERMINAL_TEXT_HEIGHT 18

#define TERMINAL_VOFS 96

//static class stuff
u16 Terminal::curr_line_num = 0;
u16 Terminal::curr_tile_num = 0;
u16 Terminal::text_sbb = 0;
u16 Terminal::text_cbb = 0;
u8 Terminal::bg_ind = 0;

//now i can use ind to access certain registers
vu16* BG_VOFS[4] = {
    &REG_BG0VOFS,
    &REG_BG1VOFS,
    &REG_BG2VOFS,
    &REG_BG3VOFS
};

//set control flags for bg
u16 Terminal::setCNT(u8 bg, u16 cbb, u16 sbb){
    bg_ind = clamp(bg, 0, 4);
    text_sbb = sbb;
    text_cbb = cbb;

    LZ77UnCompVram(textTiles, &tile_mem[text_cbb]);

    reset();
    
    //These could be added to the function parameters if you call for it
    return BG_BUILD(cbb,sbb,0,0,0,0,1);
}

// reset line, clear the whole screen, and reset offset
void Terminal::reset(){
    curr_line_num = 0;
    memset16(&se_mem[text_sbb], 0, sizeof(SCREENBLOCK)/2);
    *(BG_VOFS[bg_ind]) = TERMINAL_VOFS;
}

//turn character into index of tileset image
int charToTileInd(char c){
    //31 is the start of the text tileset
    return (c - 31);
}

//turn int (0,9) to char
char intToChar(int x){
    return (char)(x + '0');
}

//cool use of recursion and function overloading
void Terminal::drawVal(int val){
    //draw a negative sign but only once
    if(val < 0){
        drawVal('-');
        val = val * -1;
    }

    //if value is greater than 9
    if(val > 9){
        //recurse
        drawVal(val/10);
    }

    //base case, sorta
    drawVal(intToChar(val%10));
}

//every single char will be drawn with this function, so put in new line logic and screen logic
void Terminal::drawVal(char c){
    //if new tile will overflow onto next line, move to next line
    if(curr_tile_num == TERMINAL_TEXT_WIDTH){
        move_one_line();
    }

    u16 se_ind = (curr_line_num * 32) + curr_tile_num + 1;// + 1 to skip left border
    se_mem[text_sbb][se_ind] = charToTileInd(c);

    //update new tiles
    curr_tile_num++;
}

void Terminal::move_one_line(){
    //update line num
    curr_line_num = (curr_line_num+1) % 32;

    //erase current top line of text
    memset16(&se_mem[text_sbb][((curr_line_num+12+1)%32)*32], 0, 32);

    //update bg ofs
    *(BG_VOFS[bg_ind]) = TERMINAL_VOFS + ((curr_line_num+1)*8);

    //reset tile num
    curr_tile_num = 0;
}

