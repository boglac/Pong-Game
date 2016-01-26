#include "View.h"

void View::setRenderer(SDL_Renderer *rend)
{
    Renderer = rend;
}

void View::setFont(TTF_Font *fnt, SDL_Color color, int size)
{
    TextSize = size;
    TextFont = fnt;
    TextColor = color;
}

Image * View::addTexture(SDL_Texture *texture)
{
    if (!Textures) {

        Textures = new Item;

        Textures->Image = new Image;
        Textures->Image->Texture = texture;
        Textures->Image->Rect = new SDL_Rect;

        return Textures->Image;

    } else {

        Item *temp = Textures, *last = nullptr;
        while (temp)
        {
            last = temp;
            temp = temp->Next;
        }

        last->Next = new Item;
        last->Next->Image = new Image;
        last->Next->Image->Texture = texture;
        last->Next->Image->Rect = new SDL_Rect;

        return last->Next->Image;

    }
}

Image * View::updateTexture(Image * image, SDL_Texture *texture)
{
    Item *temp = Textures;
    Image *tempImage = nullptr, *last = nullptr;

    while (temp)
    { 
        tempImage = temp->Image;
        if (tempImage == image) {
            delete tempImage->Rect;

            SDL_DestroyTexture(tempImage->Texture);
            tempImage->Texture = texture;
            tempImage->Rect = new SDL_Rect;

            return tempImage;
        }

        temp = temp->Next;
    }

    return nullptr;
}

Image * View::loadTexture(const char *file)
{
    SDL_Texture *texture = IMG_LoadTexture(Renderer, file);
    if (texture == nullptr) {
        std::cout << "-! Texture load error: " << IMG_GetError() << std::endl;
        std::cout << "\tUsing default texture" << std::endl;
        texture = IMG_LoadTexture(Renderer, "images/error.png");
    }
    
    return addTexture(texture);
}

Image * View::loadText(const char *text)
{
    SDL_Surface *surface = TTF_RenderText_Blended(TextFont, text, TextColor);
    
    if (surface == nullptr) {
        std::cout << "-! Text render error: " << TTF_GetError();
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, surface);
    if (texture == nullptr) {
        std::cout << "-! Couldn't create texture for text: " << IMG_GetError();
        return nullptr;
    }

    SDL_FreeSurface(surface);
    
    return addTexture(texture);
}

Image * View::loadUpdatedText(Image * image, const char *text)
{
    SDL_Surface *surface = TTF_RenderText_Blended(TextFont, text, TextColor);

    if (surface == nullptr) {
        std::cout << "-! Text render error: " << TTF_GetError();
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, surface);
    if (texture == nullptr) {
        std::cout << "-! Couldn't create texture for text: " << IMG_GetError();
        return nullptr;
    }

    SDL_FreeSurface(surface);

    return updateTexture(image, texture);
}

 void View::updateText(Text *elem, const char *text)
{
    elem->attachImage(loadUpdatedText(elem->getImage(), text));

    int w, h;
    TTF_SizeText(TextFont, text, &w, &h);

    elem->setSize(w, h);
}

 void View::setTextSize(Text *elem)
 {
     int w, h;
     TTF_SizeText(TextFont, elem->getText(), &w, &h);

     elem->setSize(w, h);
 }

void View::renderTexture(Image *img) const
{
    SDL_RenderCopy(Renderer, img->Texture, NULL, img->Rect);
}

void View::update()
{
    SDL_RenderClear(Renderer);

    Item *temp = Textures;
    if (!temp) return;

    while (temp)
    {
        if (temp->Image->Visible) renderTexture(temp->Image);
        temp = temp->Next;
    }

    SDL_RenderPresent(Renderer);
}
