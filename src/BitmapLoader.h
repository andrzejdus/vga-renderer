#ifndef VGARENDERER_BITMAPLOADER_H
#define VGARENDERER_BITMAPLOADER_H

#include "BmpBitmap.h"

class BitmapLoader {
public:
    static Bitmap *load(char *fileName);
};

#endif //VGARENDERER_BITMAPLOADER_H
