# Copyright 2021 intbeam
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
# to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
# and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

param(
    [parameter(Mandatory = $false)][switch]$release = $false,
    [parameter(Mandatory = $false)][string]$architecture = "16bit"    
)

[string]$watcomInstallPath = $env:WATCOM
if(-not (Test-Path $watcomInstallPath))
{
    Write-Error "WATCOM environment variable not set"
    exit 2
}

if($env:PATH.contains($watcomInstallPath) -ne $true)
{
    Write-Warning "Seems that WATCOM install path is not in PATH. Are your binaries in non-standard location or WATCOM binaries are not PATH?"
}

# Set relevant environment variables
$env:EDPATH = "$watcomInstallPath/eddat"

if($IsWindows)
{
    $env:INCLUDE = "$watcomInstallPath/h;$watcomInstallPath/h/nt"
}
else
{
    $env:INCLUDE = "$watcomInstallPath/h"
}

[string]$command = "wcl"
if($architecture -eq "32bit")
{
    $command = "wcl386"
}

if(Get-Command $command)
{
    Write-Information "wcl command found"
}
else
{
    Write-Error "wcl command not found - is PATH environment set correctly?"
    exit 2
}

# define wcl arguments here
[string[]]$wclArguments = ("-w4", "-e25", "-od", "-d2", "-ml", "-xs", "-xr", "-bc", "-bt=DOS", "-fo=""./obj/""", "-fe=""./build/vr.exe""")

# Retrieve all source code files (c, cpp) from src directory
$files = (Get-ChildItem -Path "./src" -Filter "*" -Recurse | Where-Object { $_.Extension.ToLowerInvariant() -in (".c", ".cpp", ".asm")} | Select-Object -ExpandProperty FullName | ForEach-Object { """{0}""" -f $_ }  )

# append files to compile to arguments
$wclArguments += $files

# Create build and obj directories if they don't exist
if(-not (Test-Path "./build"))
{
    New-Item "./build" -ItemType Directory
}

if(-not (Test-Path "./obj"))
{
    New-Item "./obj" -ItemType Directory
}

# Compile and link. Output files to obj directory and put the binary in build
& $command $wclArguments

# Copy assets to build
Copy-Item .\assets\** .\build\assets
