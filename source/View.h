#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Actor.h"
#include "Text.h"
#include "ImageData.h"
#include "Image.h"

/*
    class
    View
    Represents visual side of the application. Responsible for creating textures.
    Keeps record of object's textures and updates screen.
*/
class View
{
public:
    View()
    {
        Renderer = nullptr;
        Textures = nullptr;
        TextFont = nullptr;
    }

    void setRenderer(SDL_Renderer *renderer);
    void setFont(TTF_Font *font, SDL_Color color, int size);

    Image * loadTexture(const char *file);
    Image * addTexture(SDL_Texture *texture);    
    Image * updateTexture(Image * image, SDL_Texture *texture);
    void renderTexture(Image *image) const;

    Image * loadText(const char *text);
    Image * loadUpdatedText(Image * image, const char *text);
    void setTextSize(Text *text);

    void updateText(Text *elem, const char *text);

    void update();

private:
    struct Item {
        Image *Image;
        Item *Next;
        Item() { Image = nullptr; Next = nullptr; }
    };

    SDL_Renderer *Renderer;
    Item *Textures;
    TTF_Font * TextFont;
    SDL_Color TextColor;
    int TextSize;
};

