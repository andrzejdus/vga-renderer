cmake_minimum_required(VERSION 3.9.6)
project(VgaRenderer)

set(CMAKE_CXX_STANDARD 98)

add_executable(VgaRenderer
        src/main.cpp src/VgaRenderer.cpp src/VgaRenderer.h src/BmpBitmap.h src/BmpBitmap.cpp src/BmpBitmapInfoPrinter.h src/BmpBitmapInfoPrinter.cpp src/BitmapLoader.cpp src/BitmapLoader.h src/Sprite.cpp src/Sprite.h src/FullscreenSprite.cpp src/FullscreenSprite.h src/MovableSprite.cpp src/MovableSprite.h src/Bitmap.h)
