IF NOT EXIST obs-studio (
  mkdir obs-studio
)

cd obs-studio

if NOT EXIST obs-studio (
  git clone --recursive git@github.com:obsproject/obs-studio.git
)

cd obs-studio

IF NOT EXIST build64 (
  powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; ./CI/'build-windows.ps1'}"
)
pause