set RunUAT=C:\UE_4.27\Engine\Build\BatchFiles\RunUAT
set PROJECT_FILE=%~dp0\rac.uproject

echo "Start build" > cook-exe.log
echo %DATE% %TIME% >> cook-exe.log

call %RunUAT% BuildCookRun -project=%PROJECT_FILE% -noP4 -ue4exe=UE4Editor-Cmd.exe -compressed -SkipCookingEditorContent^
-platform=Win64 ^
-clientconfig=Development -serverconfig=Development ^
-cook -iterate -utf8output ^
-logtimes >> cook-exe.log

echo "End build" >> cook-exe.log
echo %DATE% %TIME% >> cook-exe.log
