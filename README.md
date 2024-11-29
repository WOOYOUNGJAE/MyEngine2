## How To Build
1. Run the .sln file.
2. Right-click on the solution and select "Restore NuGet Packages."
3. Build Projects, Common -> Renderer_OpenGL -> CUDA -> Engine_Core -> Asset_Loader
4. Build and Run App

## Directory Structure
Root\
├── App\
├── Engine_Common\
├── Engine_OpenGL\
├── Engine_...\
└── Libs\
│   ├── Engine_Common\
│       ├── Includes // .h, .hpp, ...\
│       ├── bin // .dll, .lib, ...\
│   ├── Engine_OpenGL\
│   ├── Engine_...\
└   └── GL Libs...

The main project reference header files duplicated ones in the Lib directory instead of directly referencing the external project.
