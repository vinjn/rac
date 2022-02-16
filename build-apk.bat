set RunUAT=C:\UE_4.27\Engine\Build\BatchFiles\RunUAT
set PROJECT_FILE=%~dp0\rac.uproject

cp source\GameActivity.java c:\UE_4.27\Engine\Build\Android\Java\src\com\epicgames\ue4\GameActivity.java.template

%RunUAT% BuildCookRun -project=%PROJECT_FILE% -noP4 -ue4exe=UE4Editor-Cmd.exe -compressed -SkipCookingEditorContent^
-platform=android -targetplatform=android -cookflavor=ASTC ^
-clientconfig=Development -serverconfig=Development ^
-cook -iterate -build -stage -pak -utf8output ^
-logtimes ^
-archive -archivedirectory=%~dp0 > build-apk.log