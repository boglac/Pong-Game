#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "ImageFIle.h"

using namespace std;
struct FileReader
{
    // a list of images, storing information about files' names, sizes and positions
    ImageFile *data;
    int amount;

    // constructor, takes a file path as a argument
    FileReader(char *file)
    {        
        fstream handler;

        handler.open(file, ios::in);

        if (handler.good())
        {
            char text[30];

            // read the first line - amount of images
            handler >> text;
            amount = atoi(text);

            data = new ImageFile[amount];

            int count = 0;
            while (!handler.eof())
            {       
                handler >> text;
                strcpy(data[count].name, text);

                handler >> text;
                data[count].width = atoi(text);
                handler >> text;
                data[count].height = atoi(text);

                handler >> text;
                data[count].x = atoi(text);
                handler >> text;
                data[count].y = atoi(text);
                
                count++;
            }

            cout << "+ Successfully read the file" << endl;
        } 
        else cout << "! Couldn't read the file!" << endl;
    }
};
