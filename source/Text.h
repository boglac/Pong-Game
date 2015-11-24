#pragma once
#include "Actor.h"

/*
    class
    Text
    inherits Actor
    A class representing a text displayed on the screen.
    At the moment all text objects share font, size and color, delivered by View class object.
*/
class Text : public Actor
{
public:
    Text(const ActorData &params) : Actor(params), maxWidth(width), maxHeight(height)
    {
        setText(params.image.path);
        purpose = params.extra;
    }

    const char *getText() const;
    void setText(const char *text);
    void setSize(int w, int h);

    void update() {};
    
private:
    char *text;
    short purpose;

    const unsigned short maxWidth;
    const unsigned short maxHeight;
};

