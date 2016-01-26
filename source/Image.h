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
    SDL_Texture *Texture;
    SDL_Rect *Rect;
    unsigned short Visible;

    Image() 
    { 
        Texture = nullptr;
        Rect = nullptr;
        Visible = 1; 
    }
};
