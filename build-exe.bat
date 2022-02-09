set RunUAT=C:\UE_4.27\Engine\Build\BatchFiles\RunUAT
set PROJECT_FILE=%~dp0\rac.uproject

%RunUAT% BuildCookRun -project=%PROJECT_FILE% -noP4 -ue4exe=UE4Editor-Cmd.exe -compressed -SkipCookingEditorContent^
-platform=Win64 ^
-clientconfig=Development -serverconfig=Development -allmaps ^
-cook -build -stage -pak -logtimes -utf8output ^
-archive -archivedirectory=%~dp0\AutoBuild\
