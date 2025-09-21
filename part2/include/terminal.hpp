#ifndef __TERMINAL__
#define __TERMINAL__

#include "tonc.h"

class Terminal{
    public:
        static u16 setCNT(u8 bg, u16 cbb, u16 sbb);

        static void reset();

        static void log(const char* word){
            while(*word != '\0'){
                //draw next char
                drawVal(*word);
                word++;
            }
            move_one_line();
        };


        template <typename T, typename... Args>
        static void log(const char* word, T val, Args... args){
            while(*word != '\0'){

                //'%%' will be used to display a char or int
                if(*word == '%' && *word == '%'){
                    //draw value
                    drawVal(val);
                    //move past '%%'
                    word += 2;
                    //continue logging w/o val
                    log(word, args...);
                    return;
                }else{
                    //draw next char
                    drawVal(*word);
                    word++; 
                }
            }
            move_one_line();
        };


    private:
        static void drawVal(int val);
        static void drawVal(char c);
        static void move_one_line();
        
        static u16 curr_line_num;
        static u16 curr_tile_num;

        //For DCNT_BG$(0-3)
        static u8 bg_ind;

        static u16 text_sbb;
        static u16 text_cbb;
};

#endif