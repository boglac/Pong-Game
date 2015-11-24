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

    // constructor used to initialize object with data
    ImageData(char *file, unsigned short w, unsigned short h);

    // helper function to set the name of the file
    static char * copyString(const char *file);
};
