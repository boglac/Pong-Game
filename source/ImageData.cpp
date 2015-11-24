#include "ImageData.h"

ImageData::ImageData(char *file, unsigned short w, unsigned short h)
    : path(copyString(file)), width(w), height(h) {}

char * ImageData::copyString(const char *file)
{
    const char *temp = file;
    short length = 0, i = 0;

    // get source string length
    while (*(temp++))
        length++;

    // allocate memory for string of given length
    char *copy = new char[length + 1];

    // copy string
    while (copy[i] = *file)
    {
        file++;
        i++;
    }

    return copy;
}
