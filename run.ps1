Clear-Host

# Expect dosbox in PATH
[string]$command = 'dosbox';

if(Get-Command $command)
{
    Write-Information 'DOSBox found'
}
else
{
    # write error and return file not found
    Write-Error 'DOSBox not found'
    exit 2
}

[string]$binary = './build/vr.exe';
if($IsWindows)
{
    $binary = '.\build\vr.exe';
}
[string[]]$dosboxArguments = ($binary, '-noconsole')

& $command $dosboxArguments