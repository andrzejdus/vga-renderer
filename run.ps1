Clear-Host

[string]$binaryPath = 'C:\Program Files (x86)\DOSBox-0.74-3\DOSBox.exe';

# Check if DosBox is in the tools directory
if(Test-Path -Path $binaryPath)
{
    Write-Information 'DOSBox found'
}
else
{
    # write error and return file not found
    Write-Error 'DOSBox not found'
    exit 2
}

[string[]]$dosboxArguments = ('.\build\vr.exe', '-exit', '-noconsole')

& $binaryPath $dosboxArguments