# VGA DOS Renderer
DOS 16 bit, real mode app that draws stuff on VGA display hardware.
At the moment code uses [Mode X/Y](https://en.wikipedia.org/wiki/Mode_X).

## Dependences
* [WATCOM compiler](https://github.com/open-watcom/open-watcom-v2), it can cross compile targeting DOS 16 bit
* DOSBox (if you want to run it under modern system)

## How can I build it?
Remember to set WATCOM compiler environment variables:
* add binaries directory to PATH environment variable
* set WATCOM environment variable pointing to WATCOM root installation directory.

Than you should be able to build project using [build.ps1](https://github.com/andrzejdus/vga-renderer/blob/master/build.ps1) script or use build target in vscode.

## How can I run it?
DOSBox or real hardware with DOS!

Check [run.ps1](https://github.com/andrzejdus/vga-renderer/blob/master/run.ps1) for DOSBox runner script. You should be able to use launch target in vscode.

## Why?
* DOS? Yes.
* 16 bit? Yes.
* Are you mad? No. (?)
* Why are you wasting your time? I'm not. Programming for DOS is cool and one can learn a lot. :-P
