; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "�������� ��������"
!define PRODUCT_VERSION "1.1.0"
!define PRODUCT_PUBLISHER "�������� ����"
!define PRODUCT_WEB_SITE "http://utech.com.ua"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\autopark.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma
XPStyle on

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!define MUI_LICENSEPAGE_RADIOBUTTONS
!insertmacro MUI_PAGE_LICENSE "..\license.txt"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\bin\updater.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "Ukrainian"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "AParkMeneger_bin_v${PRODUCT_VERSION}.exe"
InstallDir "D:\AutoParkMeneger"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "��������� ����������" SEC01
SectionIn RO

  SetOutPath "$INSTDIR\bin"
  SetOverwrite ifnewer
  File "extDll\QtXml4.dll"
  File "extDll\QtSql4.dll"
  File "extDll\QtScript4.dll"
  File "extDll\QtNetwork4.dll"
  File "extDll\QtGui4.dll"
  File "extDll\QtCore4.dll"
  File "extDll\mingwm10.dll"
  File "extDll\libmysql.dll"
  File "extDll\libgcc_s_dw2-1.dll"
  File "..\bin\gurtSklad.ini"
  File "..\bin\updater.exe"
  File "..\bin\autopark.exe"
  File "..\bin\salary.ini"
  File "..\bin\salaryDBUpdate"
  File "..\bin\libxl.dll"
  SetOutPath "$INSTDIR\bin\sqldrivers"
  File "..\bin\sqldrivers\qsqlmysql4.dll"
  SetOutPath "$INSTDIR\doc"
  SetOverwrite ifnewer
  File "..\doc\gui_about_el-zar.html"
  SetOutPath "$INSTDIR\templates"
  File "..\templates\cheky_okko.xls"
  CreateDirectory "$SMPROGRAMS\�������� ��������"
  CreateShortCut "$SMPROGRAMS\�������� ��������\�������� ��������.lnk" "$INSTDIR\bin\updater.exe"
  CreateShortCut "$DESKTOP\�������� ��������.lnk" "$INSTDIR\bin\updater.exe"
SectionEnd

Section   "������� ����������� ��������" SEC02
  SetOutPath "$INSTDIR\script"
  File "..\script\utr_vidrah_osn_dohodu.js"
  File "..\script\utr_vidrah_inshi_dohody.js"
  File "..\script\test.js"
  File "..\script\saldo.js"
  File "..\script\prob.js"
  File "..\script\osn_narah.js"
  File "..\script\oplata.js"
SectionEnd

Section /o  "���� ����������� ��������" SEC03
  SetOutPath "$INSTDIR\bin"
  File "..\install\ini\autopark.ini"
SectionEnd

#Function .onInit
  #IfSilent +1 +2
  #  SectionSetFlags ${SEC02} 0
#FunctionEnd

Function .onInstSuccess
  ifSilent +1 +2
    Exec '$INSTDIR\bin\autopark.exe'
FunctionEnd


Section -AdditionalIcons
  SetOutPath $INSTDIR
  CreateShortCut "$SMPROGRAMS\�������� ��������\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  #WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\bin\autopark.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\bin\autopark.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "��������� �������� $(^Name) ���� ������ ���������."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "�� �������� � ����, �� ������ �������� $(^Name) � �� ���� ����������?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\script\oplata.js"
  Delete "$INSTDIR\script\osn_narah.js"
  Delete "$INSTDIR\script\prob.js"
  Delete "$INSTDIR\script\saldo.js"
  Delete "$INSTDIR\script\test.js"
  Delete "$INSTDIR\script\utr_vidrah_inshi_dohody.js"
  Delete "$INSTDIR\script\utr_vidrah_osn_dohodu.js"
  Delete "$INSTDIR\bin\sqldrivers\qsqlmysql4.dll"
  Delete "$INSTDIR\bin\libxl.dll"
  Delete "$INSTDIR\bin\salary.ini"
  Delete "$INSTDIR\bin\autopark.exe"
  Delete "$INSTDIR\bin\updater.exe"
  Delete "$INSTDIR\bin\autopark.ini"
  Delete "$INSTDIR\bin\gurtSklad.ini"
  Delete "$INSTDIR\bin\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\bin\libmysql.dll"
  Delete "$INSTDIR\bin\mingwm10.dll"
  Delete "$INSTDIR\bin\QtCore4.dll"
  Delete "$INSTDIR\bin\QtGui4.dll"
  Delete "$INSTDIR\bin\QtNetwork4.dll"
  Delete "$INSTDIR\bin\QtScript4.dll"
  Delete "$INSTDIR\bin\QtSql4.dll"
  Delete "$INSTDIR\bin\QtXml4.dll"
  Delete "$INSTDIR\bin\salaryDBUpdate"
  Delete "$INSTDIR\doc\gui_about_el-zar.html"
  Delete "$INSTDIR\templates\cheky_okko.xls"

  Delete "$SMPROGRAMS\�������� ��������\Uninstall.lnk"
  Delete "$DESKTOP\�������� ��������.lnk"
  Delete "$SMPROGRAMS\�������� ��������\�������� ��������.lnk"

  RMDir "$SMPROGRAMS\�������� ��������"
  RMDir "$INSTDIR\script"
  RMDir "$INSTDIR\bin\sqldrivers"
  RMDir "$INSTDIR\bin"
  RMDir "$INSTDIR\doc"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd