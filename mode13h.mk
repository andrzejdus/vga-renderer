project : build\mode13h.exe .SYMBOLIC

!define BLANK ""
build\main.obj : src\main.cpp .AUTODEPEND
 *wpp src\main.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\main.obj -ml -xs -xr

build\Mode13h.obj : src\Mode13h.cpp .AUTODEPEND
 *wpp src\Mode13h.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\Mode13h.obj -ml -xs -xr

build\Bitmap.obj : src\Bitmap.cpp .AUTODEPEND
 *wpp src\Bitmap.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\Bitmap.obj -ml -xs -xr

build\BitmapInfoPrinter.obj : src\BitmapInfoPrinter.cpp .AUTODEPEND
 *wpp src\BitmapInfoPrinter.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\BitmapInfoPrinter.obj -ml -xs -xr

build\mode13h.exe : build\main.obj build\Mode13h.obj build\Bitmap.obj build\BitmapInfoPrinter.obj .AUTODEPEND
 @%write build\mode13h.lk1 FIL build\main.obj,build\Mode13h.obj,build\Bitmap.obj,build\BitmapInfoPrinter.obj
 @%append build\mode13h.lk1
 *wlink name build\mode13h d all sys dos op m=build\mode13h op maxe=25 op symf @build\mode13h.lk1