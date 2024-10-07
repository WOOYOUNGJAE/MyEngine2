## How To Build
1. Run the .sln file.
2. Right-click on the solution and select "Restore NuGet Packages."
3. Build Engine_Common.
4. Build Engine_OpenGL.
5. Build and Run App

## Directory Structure
Root
├── App
├── Engine_Common
├── Engine_OpenGL
├── Engine_...
└── Libs
│   ├── Engine_Common
│       ├── Includes // .h, .hpp, ...
│       ├── bin // .dll, .lib, ...
│   ├── Engine_OpenGL
│   ├── Engine_...
└   └── GL Libs...

The source files of the main project reference the duplicated ones in the Lib directory instead of directly referencing the external project.
