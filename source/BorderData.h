#pragma once
#include <SDL.h>

// SDL_Rect doesn't have a constructor with parameters defined,
// thus a need for a helper struct.
struct mySDL_Rect
{
    int x;
    int y;
    int w;
    int h;

    mySDL_Rect(int rectX, int rectY, int rectW, int rectH)
    {
        x = rectX;
        y = rectY;
        w = rectW;
        h = rectH;
    }
};

/*
    struct
    BorderData
    Keeps information about game area borders.
*/
struct BorderData
{
    const unsigned short bordersCount;
    const mySDL_Rect *borders;

    BorderData(const mySDL_Rect *brdrs, unsigned short count)
        : bordersCount(count), borders(brdrs) {}
};

