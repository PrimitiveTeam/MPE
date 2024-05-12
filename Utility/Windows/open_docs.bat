@echo off
@rem open docs in browser
for %%i in ("%~dp0..\Documentation\MPE\html\index.html") do set "absPath=%%~fi"
set "correctedPath=%absPath:\=/%"
start "" "file:///%correctedPath%"