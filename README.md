# RoboChase

*Under Construction!*

Zap the robots before they catch you!

## TODO

 - Add scoring and window chome
 - Fix level generation to prevent robots and player spawning on blocks
 - Defeat & victory animations for either game outcome
 - Improve graphics and replace placeholders
 - Fix collision detection
 - Fix the way the objects are stored in the scene

# Build

## Visual Studio

    cmake -A x64 -DSDL2_IMAGE_DIR=c:\opt\SDL2_image-2.0.4 -DSDL2_DIR=c:\opt\SDL2-2.0.9 ..

## MingGW32 / MingGW64

Set the SDL2_DIR and SDL2_IMAGE_DIR variables in CMakeLists.txt

In the project folder create a build folder. Open in a MingGW command prompt and type:

    cmake -G "CodeBlocks" -DCMAKE_BUILD_TYPE=Debug  ..

Change the CMAKE_BUILD_TYPE where appropriate.