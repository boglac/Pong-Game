#pragma once
#include <SDL.h>
#include <random>
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
    eActorType Type;

    ushort ID;
    float X;
    float Y;
    float StartX;
    float StartY;
    
    Image *ImageHandler;
    ushort Width;
    ushort Height;

    ushort Visible;

public:
    Actor(const ActorData &params)
    {
        Type = params.type;

        X = StartX = params.x;
        Y = StartY = params.y;

        ImageHandler = nullptr;
        Width = params.image.width;
        Height = params.image.height;

        Visible = params.visible;
    }

    void setVisibility(ushort visible);

    // some necessary getters
    float getX() const;
    eActorType getType() const;    
    Image * getImage() const;
    SDL_Rect * getImageRect() const;
    ushort getWidth() const;
    ushort getHeight() const;
    ushort getID() const;

    void setID(ushort id);

    // methods used to get outer lines of the actor's rectangle
    // used in collision detection (SDL_IntersectRectAndLine)
    void leftSideLine(int &, int &, int &, int &) const;
    void rightSideLine(int &, int &, int &, int &) const;
    void topSideLine(int &, int &, int &, int &) const;
    void bottomSideLine(int &, int &, int &, int &) const;

    // stores pointer to Image object delivered by View
    void attachImage(Image *img);

    // in mose cases - brings Actor back to starting position
    virtual void reset();

    // pure virtual - to be defined by child classes
    virtual void update() = 0;

    virtual void addRandomDevice(std::random_device *rnd) {};

    // virtual functions used to handle various types of collision
    virtual eCollisionResult handleBorderCollision(eBorderPosition borderPos, ushort borderID);
    virtual eCollisionResult handleBallCollision(Actor *ball);
    virtual eCollisionResult handleEnemyCollision();
    
};

