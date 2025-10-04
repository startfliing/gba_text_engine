# gba_text_engine

Collection of three incremental GBA text-display examples (parts 1, 2, and 3) in C++. Each part is a small project with its own Makefile and sources demonstrating increasingly advanced text rendering techniques on the Game Boy Advance.

## GBA Resources
Here are some resources I used/am using to learn about the GBA
- [devkitPro](https://devkitpro.org/)
- [Tonc](https://gbadev.net/tonc/foreword.html)
- [gbadev](https://gbadev.net/)

## Foreword
THIS IS NOT THE BEST C++ CODE EVER. IT IS FAR FROM PERFECT. THIS IS INTENDED AS A PROOF OF CONCEPT, RATHER THAN A FINAL PRODUCT. PLEASE TAKE THIS INTO CONSIDERATION!

I love feedback, criticisms, suggestions, comments, concerns, PRs, issues, and things of that nature.

I really reccomend using the `no$gba` emulator specifically for it's debugging tools. Extremely helpful for seeing tilesets and maps in the VRAM viewer while a game is running. It can be daunting at first, but I encourage you to explore some of it's other functionalities and tools as well.

I also have used a Windows machine for the development of this project. There might be differences for building this project on a Mac or Linux that I am not familiar with.

### Makefile

Important environment variables to set.

- DEVKITARM — path to devkitARM installation
- DEVKITPRO — path to devkitPro

In addition to `make` and `make clean`, I've added two custom options for `make`;

- `make pad` will pad the gba file to the nearest 4kb which might help if flashing the file to a GBA cart
- `make full` will run `make clean`, `make`, and then `make pad` in a row for a "full build" of the projects 

## part 1 - Image Display
Simple background image rendering on the GBA. This is the simplest version of the text engine and doesn't actually do much. If you aren't comfortable drawing images to the GBA screen, this is the perfect place to start.

## part 2 - Simple Text Engine
A basic tile-based terminal using a custom tileset for characters. This is an advancement on the previous part and requires a reasonable amount of understanding in GBA functionality and C++ to understand.

Most of the actual functionality for the terminal is defined in the static terminal class. There are a lot of techniques used to make this work like a traditional terminal including an overloaded log function that also uses templates, some recursion for drawing all variables in the text, and some more recursion to draw multi-digit numbers.

In terminal.cpp,
```#define IS_TEXT_SCROLL_ENABLED``` will enable letter-by-letter scrolling like you might see in an RPG game

## part 3 - *THE* Text Engine
A more advanced terminal that uses a variable-width font to render characters across tile boundaries. This uses a very similar terminal class, with the obvious differences and additions for rendering the tiles. I also added a font class to simplify accessing tile data and tile width data. This could easily be reduced by using other values, but it made sense to me to consolidate it into one class.

In terminal.cpp again,
```#define IS_TEXT_SCROLL_ENABLED``` will enable letter-by-letter scrolling like you might see in an RPG game
