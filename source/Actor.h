#pragma once
#include <SDL.h>
#include "ImageData.h"
#include "ActorData.h"
#include "Image.h"

/*
    abstract class
    Actor
    Base class for Actors in the game.
    Every object in the game is an Actor instance, thus it's easy to implement new functionalities for each
    (for example handling collisions with texts equals to adding a condition for text type in Scene class).
*/
class Actor
{
protected:
    actorType type;

    float x;
    float y;
    float startX;
    float startY;
    
    Image *image;
    ushort width;
    ushort height;

    ushort visible;

public:
    Actor(const ActorData &params)
    {
        type = params.type;

        x = startX = params.x;
        y = startY = params.y;

        image = nullptr;
        width = params.image.width;
        height = params.image.height;

        visible = params.visible;
    }

    void setVisibility(ushort visible);

    // some necessary getters
    float getX() const;
    actorType getType() const;    
    Image * getImage() const;
    SDL_Rect * getImageRect() const;
    ushort getWidth() const;
    ushort getHeight() const;

    // methods used to get outer lines of the actor's rectangle
    // used in collision detection (SDL_IntersectRectAndLine)
    void leftSideLine(int &, int &, int &, int &) const;
    void rightSideLine(int &, int &, int &, int &) const;
    void topSideLine(int &, int &, int &, int &) const;
    void bottomSideLine(int &, int &, int &, int &) const;

    // stores pointer to Image object delivered by View
    bool attachImage(Image *img);

    // in mose cases - brings Actor back to starting position
    virtual void reset();
    virtual void update() = 0;
};

