#ifndef MODE13H_BITMAPLOADER_H
#define MODE13H_BITMAPLOADER_H

#include "Bitmap.h"

class BitmapLoader {
public:
    static Bitmap *load(char *fileName);
};

#endif //MODE13H_BITMAPLOADER_H
