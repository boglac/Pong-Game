#pragma once

/*
    Struct
    ImageData
    Used to store information about image files.
*/
struct ImageData
{
    // because ImageData is an object used to store data, all it's values are const
    const char *path;
    const unsigned short width, height;

    // a constructor used, when we need a visual representation (image, text) for an actor 
    ImageData(char *file, unsigned short w, unsigned short h);

    // a constructor used, when we don't need a visual representation for our actor (like borders)
    ImageData(unsigned short w, unsigned short h) : width(w), height(h), path(nullptr) {};

    // helper function to set the name of the file
    static char * copyString(const char *file);
};
