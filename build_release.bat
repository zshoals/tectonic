@call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
@MSBuild.exe "C:\Users\Zanarias\Desktop\Programming_Projects\tectonic\build\Tectonic.vcxproj" /warnaserror:C4090,C4133 /nologo /m /clp:Summary /p:Configuration=Release,Platform=x64,OutDir="c:\Users\Zanarias\Desktop\Programming_Projects\tectonic\Deployment/"