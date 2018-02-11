project : build\mode13h.exe .SYMBOLIC

!define BLANK ""
build\main.obj : src\main.cpp .AUTODEPEND
 *wpp src\main.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\main.obj -ml -xs -xr

build\Mode13h.obj : src\Mode13h.cpp .AUTODEPEND
 *wpp src\Mode13h.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\Mode13h.obj -ml -xs -xr

build\BmpBitmap.obj : src\BmpBitmap.cpp .AUTODEPEND
 *wpp src\BmpBitmap.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\BmpBitmap.obj -ml -xs -xr

build\BmpBitmapInfoPrinter.obj : src\BmpBitmapInfoPrinter.cpp .AUTODEPEND
 *wpp src\BmpBitmapInfoPrinter.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\BmpBitmapInfoPrinter.obj -ml -xs -xr

build\BitmapLoader.obj : src\BitmapLoader.cpp .AUTODEPEND
 *wpp src\BitmapLoader.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\BitmapLoader.obj -ml -xs -xr

build\Sprite.obj : src\Sprite.cpp .AUTODEPEND
 *wpp src\Sprite.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\Sprite.obj -ml -xs -xr

build\FullscreenSprite.obj : src\FullscreenSprite.cpp .AUTODEPEND
 *wpp src\FullscreenSprite.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\FullscreenSprite.obj -ml -xs -xr

build\MovableSprite.obj : src\MovableSprite.cpp .AUTODEPEND
 *wpp src\MovableSprite.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\MovableSprite.obj -ml -xs -xr

build\mode13h.exe : build\main.obj build\Mode13h.obj build\BmpBitmap.obj build\BmpBitmapInfoPrinter.obj build\BitmapLoader.obj build\Sprite.obj build\FullscreenSprite.obj build\MovableSprite.obj .AUTODEPEND
 @%write build\mode13h.lk1 FIL build\main.obj,build\Mode13h.obj,build\BmpBitmap.obj,build\BmpBitmapInfoPrinter.obj,build\BitmapLoader.obj,build\Sprite.obj,build\FullscreenSprite.obj,build\MovableSprite.obj
 @%append build\mode13h.lk1
 *wlink name build\mode13h d all sys dos op m=build\mode13h op maxe=25 op symf @build\mode13h.lk1
