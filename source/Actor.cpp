#include "Actor.h"

actorType Actor::getType() const
{
    return type;
}

Image * Actor::getImage() const
{
    return image;
}

SDL_Rect * Actor::getImageRect() const
{
    return image->rect;
}

float Actor::getX() const
{
    return x;
}

unsigned short Actor::getWidth() const
{
    return width;
}

unsigned short Actor::getHeight() const
{
    return height;
}

void Actor::leftSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = image->rect->x;
    startY = image->rect->y + 1;
    endX = startX;
    endY = image->rect->y + image->rect->h - 1;
}

void Actor::rightSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = image->rect->x + image->rect->w;
    startY = image->rect->y + 1;
    endX = startX;
    endY = image->rect->y + image->rect->h - 1;
}

void Actor::topSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = image->rect->x;
    startY = image->rect->y;
    endX = startX + image->rect->w;
    endY = startY;
}

void Actor::bottomSideLine(int &startX, int &startY, int &endX, int &endY) const
{
    startX = image->rect->x;
    startY = image->rect->y + image->rect->h;
    endX = startX + image->rect->w;
    endY = startY;
}

bool Actor::attachImage(Image *img)
{
    if (!img) return false;

    image = img;
    image->rect->x = int(x - (width >> 1));
    image->rect->y = int(y - (height >> 1));
    image->rect->w = width;
    image->rect->h = height;
    image->visible = visible;

    return true;
}

void Actor::setVisibility(ushort vis)
{
    visible = vis;
    image->visible = visible;
}

void Actor::reset()
{
    x = startX;
    y = startY;
    image->rect->x = int(x - (width >> 1));
    image->rect->y = int(y - (height >> 1));
}

