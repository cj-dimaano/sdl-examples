# Example 01 - Creating a window

This example demonstrates how to create a new window with SDL.

[Next][1]

## Getting Started

Before diving right into the code, we need to set up our development environment. [Lazy Foo'][2] has
excellent guides for setting up SDL on each major OS platform in his [Lesson 01][3] SDL tutorial.

> These examples are designed specifically for Linux using the [clang][4] compiler and
> [Visual Studio Code][5]. Compiling is performed on the command line via the makefile.

## The Code

```cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

int main() {

  /*** The main window. ***/
  SDL_Window *window = NULL;

  /*** The main rendering surface contained by the window. ***/
  SDL_Surface *screenSurface = NULL;

  /*** Initialize SDL. ***/
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s\n",
                    SDL_GetError());
    return -1;
  }

  /*** Create the main window. ***/
  window = SDL_CreateWindow("Example 01: Creating a window",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    SDL_Quit();
    return -2;
  }

  /*** Get the main rendering surface. ***/
  screenSurface = SDL_GetWindowSurface(window);

  /*** Fill the surface with white. ***/
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  /*** Update the surface. ***/
  SDL_UpdateWindowSurface(window);

  /*** Wait two seconds. ***/
  SDL_Delay(2000);

  /*** Destroy the window. ***/
  SDL_DestroyWindow(window);

  /*** Quit SDL subsystems. ***/
  SDL_Quit();

  return 0;
}
```

### Step 1: Initialize SDL

```cpp
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s\n",
                    SDL_GetError());
    return -1;
  }
```

First, we initialize SDL with [`SDL_Init()`][6]. This sets up the SDL subsystem. If any errors occur
during initialization, we immediately log the error and terminate the program.

> Handling errors wherever possible is a good habit to get into; it helps tremendously with
> debugging. If speed is a concern, code profiling is the better way to decide where optimizations
> are necessary.

### Step 2: Create the window

```cpp
  window = SDL_CreateWindow("Example 01: Creating a window",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    SDL_Quit();
    return -2;
  }
```

Assuming SDL initialized successfully, we create the window with [`SDL_CreateWindow()`][7], again,
logging errors and terminating early if any are encountered.

### Step 3: Fill the window with a solid color

```cpp
  screenSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);
```

With the newly created window, we get its surface with [`SDL_GetWindowSurface()`][8], fill its color
with a solid white using [`SDL_FillRect()`][9] and [`SDL_MapRGB()`][10], and update the screen with
[`SDL_UpdateWindowSurface()`][11] so that the user can see the changes.

> For a discussion about the difference between a surface and a renderer in SDL, visit
> [this link][12].

```cpp
  SDL_Delay(2000);
```

Once the window is updated, we wait 2 seconds with [`SDL_Delay()`][13].

### Step 4: Cleanup

```cpp
  SDL_DestroyWindow(window);

  SDL_Quit();
```

Finally, we destroy the window with [`SDL_DestroyWindow()`][14] and clean up the SDL subsystems with
[`SDL_Quit()`][15].

> Always remember to clean up after yourself. If you allocate memory for anything, be sure to
> deallocate that memory when you are finished. For SDL, this generally means calling the `Destroy`
> function for every `Create` function or calling the `Quit` function for any `Init` function. Other
> APIs use similar conventions. If you create objects in C++ using the `new` keyword, be sure to
> destroy that object by using the `delete` keyword.

---

[Next][1]

## Resources
* [Lazy Foo's Lesson 01][3]
* [SDL Logging][16]
* SDL_Window
* [SDL_Surface][17]
* [SDL_Init()][6]
* [SDL_Quit()][15]
* [SDL_CreateWindow()][7]
* [SDL_GetWindowSurface()][8]
* [SDL_FillRect()][9]
* [SDL_MapRGB()][10]
* [SDL_UpdateWindowSurface()][11]
* [SDL_Delay()][13]
* [SDL_DestroyWindow()][14]
* [Surface VS Renderer][12]

[1]: ../02_handling-events
[2]: http://lazyfoo.net/
[3]: http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
[4]: https://clang.llvm.org/
[5]: https://code.visualstudio.com/
[6]: http://wiki.libsdl.org/SDL_Init
[7]: http://wiki.libsdl.org/SDL_CreateWindow
[8]: http://wiki.libsdl.org/SDL_GetWindowSurface
[9]: http://wiki.libsdl.org/SDL_FillRect
[10]: http://wiki.libsdl.org/SDL_MapRGB
[11]: http://wiki.libsdl.org/SDL_UpdateWindowSurface
[12]: https://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
[13]: http://wiki.libsdl.org/SDL_Delay
[14]: http://wiki.libsdl.org/SDL_DestroyWindow
[15]: http://wiki.libsdl.org/SDL_Quit
[16]: http://wiki.libsdl.org/CategoryLog
[17]: https://wiki.libsdl.org/SDL_Surface
