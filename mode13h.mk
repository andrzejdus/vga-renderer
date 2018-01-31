project : build\dev.exe .SYMBOLIC

!define BLANK ""
build\main.obj : src\main.cpp .AUTODEPEND
 *wpp src\main.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\main.obj -ml -xs -xr

build\Mode13h.obj : src\Mode13h.cpp .AUTODEPEND
 *wpp src\Mode13h.cpp -i="C:\WATCOM/h" -w4 -e25 -od -d2 -bt=dos -fo=build\Mode13h.obj -ml -xs -xr

build\dev.exe : build\main.obj build\Mode13h.obj src\Mode13h.h src\ScreenDimensions.h .AUTODEPEND
 @%write build\dev.lk1 FIL build\main.obj,build\Mode13h.obj
 @%append build\dev.lk1
 *wlink name build\dev d all sys dos op m=build\dev op maxe=25 op symf @build\dev.lk1
