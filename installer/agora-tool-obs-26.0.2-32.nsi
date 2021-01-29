;
; NSIS Installer of Agora Tool for OBS Studio(https://obsproject.com/)
;
; This installer script is designed only for the release process
; of Agora Tool. It requires a lot of files to be in exactly the
; right places. If you're making a fork, it's strongly suggested
; that you make your own installer.

Unicode true
ManifestDPIAware true

; Define your application name
!define APPNAME "Agora Tool"

!ifndef APPVERSION
!define APPVERSION "26.0.2"
!define SHORTVERSION "26.0.2"
!endif

; Additional script dependencies
!include WinVer.nsh
!include x64.nsh

; Main Install settings
Name "${APPNAME}"

!ifdef INSTALL64
 OutFile "Agora-Tool-${SHORTVERSION}-Installer-x64.exe"
!else
 OutFile "Agora-Tool-${SHORTVERSION}-Installer-x86.exe"
!endif

; Use compression
SetCompressor /SOLID LZMA

; Need Admin
RequestExecutionLevel admin

; Modern interface settings
!include "MUI.nsh"
!define MUI_ICON "agora.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "agora.bmp"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN

!define MUI_WELCOMEPAGE_TEXT "This setup will guide you through installing Agora Tool Plugin for OBS Studio.\n\nIt is recommended that you close OBS Studio. This will make it possible to load agora tool for OBS Studio."

!define MUI_HEADERIMAGE
!define MUI_PAGE_HEADER_TEXT "License Information"
!define MUI_PAGE_HEADER_SUBTEXT "Please review the license terms before installing OBS Studio."
!define MUI_LICENSEPAGE_TEXT_TOP "Press Page Down or scroll to see the rest of the license."
!define MUI_LICENSEPAGE_TEXT_BOTTOM " "
!define MUI_LICENSEPAGE_BUTTON "&Next >"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gplv2.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

; Set languages (first is default language)
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL

Function .onInit
    ReadRegStr $INSTDIR HKLM "Software\OBS Studio" "" 
	${If} $INSTDIR == ""
	  MessageBox MB_OK|MB_ICONSTOP "Please Install OBS Studio First"
	  Quit
	${EndIf}
FunctionEnd

InstallDir $INSTDIR

Section "Agora Tool" SecAgoraTool
    SetOutPath "$INSTDIR"
    File /r "..\Release\data" 
	SetOutPath "$INSTDIR"
    File /r "..\Release\obs-plugins" 
	SetOutPath "$INSTDIR"
    File /r "..\Release\bin"
SectionEnd

Section -FinishSection

SectionEnd