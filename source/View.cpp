#include "View.h"

void View::setRenderer(SDL_Renderer *rend)
{
    renderer = rend;
}

void View::setFont(TTF_Font *fnt, SDL_Color color, int size)
{
    textSize = size;
    textFont = fnt;
    textColor = color;
}

Image * View::addTexture(SDL_Texture *texture)
{
    if (!textures) {

        textures = new Item;

        textures->image = new Image;
        textures->image->texture = texture;
        textures->image->rect = new SDL_Rect;

        return textures->image;

    } else {

        Item *temp = textures, *last = nullptr;
        while (temp)
        {
            last = temp;
            temp = temp->next;
        }

        last->next = new Item;
        last->next->image = new Image;
        last->next->image->texture = texture;
        last->next->image->rect = new SDL_Rect;

        return last->next->image;

    }
}

Image * View::updateTexture(Image * image, SDL_Texture *texture)
{
    Item *temp = textures;
    Image *tempImage = nullptr, *last = nullptr;

    while (temp)
    { 
        tempImage = temp->image;
        if (tempImage == image) {
            delete tempImage->rect;

            SDL_DestroyTexture(tempImage->texture);
            tempImage->texture = texture;
            tempImage->rect = new SDL_Rect;

            return tempImage;
        }

        temp = temp->next;
    }

    return nullptr;
}

Image * View::loadTexture(const char *file)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (texture == nullptr) {
        std::cout << "-! Texture load error: " << IMG_GetError() << std::endl;
        std::cout << "\tUsing default texture" << std::endl;
        texture = IMG_LoadTexture(renderer, "images/error.png");
    }
    
    return addTexture(texture);
}

Image * View::loadText(const char *text)
{
    SDL_Surface *surface = TTF_RenderText_Blended(textFont, text, textColor);
    
    if (surface == nullptr) {
        std::cout << "-! Text render error: " << TTF_GetError();
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cout << "-! Couldn't create texture for text: " << IMG_GetError();
        return nullptr;
    }

    SDL_FreeSurface(surface);
    
    return addTexture(texture);
}

Image * View::loadUpdatedText(Image * image, const char *text)
{
    SDL_Surface *surface = TTF_RenderText_Blended(textFont, text, textColor);

    if (surface == nullptr) {
        std::cout << "-! Text render error: " << TTF_GetError();
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
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
    TTF_SizeText(textFont, text, &w, &h);

    elem->setSize(w, h);
}

 void View::setTextSize(Text *elem)
 {
     int w, h;
     TTF_SizeText(textFont, elem->getText(), &w, &h);

     elem->setSize(w, h);
 }

void View::renderTexture(Image *img) const
{
    SDL_RenderCopy(renderer, img->texture, NULL, img->rect);
}

void View::update()
{
    SDL_RenderClear(renderer);

    Item *temp = textures;
    if (!temp) return;

    while (temp)
    {
        if (temp->image->visible) renderTexture(temp->image);
        temp = temp->next;
    }

    SDL_RenderPresent(renderer);
}
