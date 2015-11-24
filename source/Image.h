#pragma once
#include <SDL.h>

/*
    struct
    Image
    Visual representation of an object (Actor).
    Keeps record of pointers to the object's texture and it's parameters (size and position).
*/
struct Image
{
    SDL_Texture *texture;
    SDL_Rect *rect;
    unsigned short visible;

    Image() 
    { 
        texture = nullptr;
        rect = nullptr;
        visible = 1; 
    }
};
