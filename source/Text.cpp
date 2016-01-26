#include "Text.h"

void Text::setText(const char *txt)
{
    CurrentText = ImageData::copyString(txt);
}

const char * Text::getText() const
{
    return CurrentText;
}

void Text::setSize(int w, int h)
{
    Width = w;
    ImageHandler->Rect->x = int(X - (w >> 1));
    ImageHandler->Rect->w = w;

    Height = h;
    ImageHandler->Rect->y = int(Y - (h >> 1));
    ImageHandler->Rect->h = h;
}