#include "Actor.h"
#include <iostream>

void Actor::setID(ushort id)
{
    ID = id;
}

ushort Actor::getID() const
{
    return ID;
}

eActorType Actor::getType() const
{
    return Type;
}

Image * Actor::getImage() const
{
    return ImageHandler;
}

SDL_Rect * Actor::getImageRect() const
{
    return ImageHandler->Rect;
}

float Actor::getX() const
{
    return X;
}

unsigned short Actor::getWidth() const
{
    return Width;
}

unsigned short Actor::getHeight() const
{
    return Height;
}

void Actor::leftSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = ImageHandler->Rect->x;
    startY = ImageHandler->Rect->y + 1;
    endX = startX;
    endY = ImageHandler->Rect->y + ImageHandler->Rect->h - 1;
}

void Actor::rightSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = ImageHandler->Rect->x + ImageHandler->Rect->w;
    startY = ImageHandler->Rect->y + 1;
    endX = startX;
    endY = ImageHandler->Rect->y + ImageHandler->Rect->h - 1;
}

void Actor::topSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = ImageHandler->Rect->x;
    startY = ImageHandler->Rect->y;
    endX = startX + ImageHandler->Rect->w;
    endY = startY;
}

void Actor::bottomSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = ImageHandler->Rect->x;
    startY = ImageHandler->Rect->y + ImageHandler->Rect->h;
    endX = startX + ImageHandler->Rect->w;
    endY = startY;
}

void Actor::attachImage(Image *img)
{
    if (!img) {
        ImageHandler = new Image;
        ImageHandler->Rect = new SDL_Rect;
    } else ImageHandler = img;
        
    ImageHandler->Rect->x = int(X - (Width >> 1));
    ImageHandler->Rect->y = int(Y - (Height >> 1));
    ImageHandler->Rect->w = Width;
    ImageHandler->Rect->h = Height;
    ImageHandler->Visible = Visible;
}

void Actor::setVisibility(ushort vis)
{
    Visible = vis;
    ImageHandler->Visible = Visible;
}

void Actor::reset()
{
    X = StartX;
    Y = StartY;
    ImageHandler->Rect->x = int(X - (Width >> 1));
    ImageHandler->Rect->y = int(Y - (Height >> 1));
}

eCollisionResult Actor::handleBorderCollision(eBorderPosition borderPos, ushort borderID)
{
    return RESULT_NORMAL;
}

eCollisionResult Actor::handleBallCollision(Actor *ball)
{
    return RESULT_NORMAL;
}

eCollisionResult Actor::handleEnemyCollision()
{
    return RESULT_NORMAL;
}
