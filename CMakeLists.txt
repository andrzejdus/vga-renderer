cmake_minimum_required(VERSION 3.9.6)
project(mode13h)

set(CMAKE_CXX_STANDARD 98)

add_executable(mode13h
        src/main.cpp src/Mode13h.cpp src/Mode13h.h src/BmpBitmap.h src/BmpBitmap.cpp src/BmpBitmapInfoPrinter.h src/BmpBitmapInfoPrinter.cpp src/BitmapLoader.cpp src/BitmapLoader.h src/Sprite.cpp src/Sprite.h src/FullscreenSprite.cpp src/FullscreenSprite.h src/MovableSprite.cpp src/MovableSprite.h src/Bitmap.h)
