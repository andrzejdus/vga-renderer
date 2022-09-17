# VGA DOS Renderer
DOS 16 bit, real mode app that draws stuff on VGA display hardware.
At the moment code uses [Mode X](https://en.wikipedia.org/wiki/Mode_X).

## Dependences
* WATCOM compiler
* DOSBox (if you want to run it under modern system)

## How can I build it?
Use [WATCOM compiler](https://github.com/open-watcom/open-watcom-v2), it can cross compile targeting DOS 16 bit.

Remember to set environment variables - add binaries directory to PATH and point WATCOM to root installation directory. Than you should be able to build that project using [build.ps1](https://github.com/andrzejdus/vga-renderer/blob/master/build.ps1) script.

## How can I run it?
DOSBox or real hardware with DOS! Check bin/run.bat for DOSBox runner script.

## Why?
* DOS? Yes.
* 16 bit? Yes.
* Are you mad? No. (?)
* Why are you wasting your time? I'm not. Programming for DOS is fun and you can learn a lot about computers. :-P
