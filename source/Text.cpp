#include "Text.h"

void Text::setText(const char *txt)
{
    text = ImageData::copyString(txt);
}

const char * Text::getText() const
{
    return text;
}

void Text::setSize(int w, int h)
{
    if (w <= maxWidth) {
        width = w;
        image->rect->x = int(x - (w >> 1));
        image->rect->w = w;
    } else {
        width = maxWidth;
        image->rect->x = int(x - (width >> 1));
        image->rect->w = width;
    }

    if (h <= maxHeight) {
        height = h;
        image->rect->y = int(y - (h >> 1));
        image->rect->h = h;
    }
    else {
        height = maxHeight;
        image->rect->y = int(x - (height >> 1));
        image->rect->h = height;
    }
}