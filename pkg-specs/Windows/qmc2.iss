; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{DB53A3CB-C0CA-494E-AFD4-11C8B66A7B67}
AppName=QMC2 - M.A.M.E. Catalog Launcher II
AppVerName=QMC2 0.244
AppPublisher=The QMC2 Development Team
AppPublisherURL=http://qmc2.batcom-it.net/
AppSupportURL=http://qmc2.batcom-it.net/
AppUpdatesURL=http://qmc2.batcom-it.net/
DefaultDirName={commonpf}\QMC2
DefaultGroupName=QMC2
AllowNoIcons=yes
LicenseFile=c:\projects\qmc2\gpl-2.0.txt
OutputDir=c:\projects\qmc2\InstallerOutput
OutputBaseFilename=qmc2-win32-x64-0.244
Compression=lzma2/max
SolidCompression=yes

[Languages]
Name: "English"; MessagesFile: "compiler:Default.isl"
Name: "French"; MessagesFile: "compiler:Languages\French.isl"
Name: "German"; MessagesFile: "compiler:Languages\German.isl"
Name: "Italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "Polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "Portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "Spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Files]
Source: "c:\projects\qmc2\package\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Dirs]
Name: "{app}"; Permissions: everyone-readexec

[Icons]
Name: "{group}\{cm:ProgramOnTheWeb,QMC2}"; Filename: "http://qmc2.batcom-it.net/"
Name: "{group}\{cm:UninstallProgram,QMC2}"; Filename: "{uninstallexe}"
Name: "{group}\QMC2 (M.A.M.E.)"; Filename: "{app}\qmc2-mame.exe"; WorkingDir: "{app}"; IconFilename: "{app}\data\img\mame.ico"
Name: "{group}\QMC2 Arcade"; Filename: "{app}\qmc2-arcade.exe"; WorkingDir: "{app}"; IconFilename: "{app}\data\img\qmc2-arcade.ico"
Name: "{group}\Qt CHDMAN GUI"; Filename: "{app}\qchdman.exe"; WorkingDir: "{app}"; IconFilename: "{app}\data\img\qchdman.ico"
