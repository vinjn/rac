# rac

## accept Android license
- set JAVA_HOME
- D:\android-sdk\tools\bin\sdkmanager.bat --update

## hack UE 427
- c:\UE_4.27\Engine\Source\ThirdParty\PhysX3\PhysX_3.4\Include\PxPhysicsAPI.h
    - Disable `//Vehicle Simulation` headers
- c:\UE_4.27\Engine\Build\Android\Java\src\com\epicgames\ue4\GameActivity.java.template
    - look for `CONSOLE_SPINNER_ITEMS`
- Rename c:\UE_4.27\Engine\Source\ThirdParty\heapprofd\arm64-v8a\libheapprofd_standalone_client.so