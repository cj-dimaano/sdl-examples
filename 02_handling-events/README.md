# Example 02 - Handling events

In this example, we create a window that listens for events then handles the `SDL_QUIT`,
`SDL_KEYDOWN`, and `SDL_KEYUP` events. We also introduce a very common concept in game development:
the game loop. This loop is always a `while` loop that can be broken up into three parts: event
handling (or message handling, depending on your background), logic updating, and drawing.

Two other software engineering concepts are introduced here: event (or message) polling, and
abstraction (or separation of concerns). Very little discussion of these concepts will be provided
in these examples.

[Previous](https://github.com/cj-dimaano/sdl-examples/tree/master/01_creating-a-window) |
[Next](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image)

## The Code

```cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <stdio.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

/* Function declarations ******************************************************/

bool init();
void close();
void onKeyDown(SDL_Event &);

/* Static variables ************************************************************
> NOTE:
> In practice, it is best to avoid using global variables.
*******************************************************************************/

/**
 * `gWindow`
 *
 *   The main window.
 */
static SDL_Window *gWindow = NULL;

/**
 * `gScreenSurface`
 *
 *   The rendering surface contained by the window.
 */
static SDL_Surface *gScreenSurface = NULL;

/* Colors */
static Uint32 white = 0;
static Uint32 red = 0;
static Uint32 yellow = 0;
static Uint32 green = 0;
static Uint32 blue = 0;
static Uint32 currentColor = 0;

/* Main ***********************************************************************/

int main() {

  /*** Initialize. ***/
  if (!init())
    return -1;

  /*** Main loop flag. ***/
  bool quit = false;

  /*** Event handler. ***/
  SDL_Event evt;

  /*** Main loop. ***/
  while (!quit) {

    /*** Handle events on the queue. ***/
    while (SDL_PollEvent(&evt) != 0) {
      switch (evt.type) {
      /*** Handle quit event. ***/
      case SDL_QUIT:
        quit = true;
        break;

      /*** Handle keydown event. ***/
      case SDL_KEYDOWN:
        onKeyDown(evt);
        break;

      /*** Handle keyup event. ***/
      case SDL_KEYUP:
        currentColor = white;
        break;
      }
    }

    /*** Fill the surface with the current color. ***/
    SDL_FillRect(gScreenSurface, NULL, currentColor);

    /*** Update the screen. ***/
    SDL_UpdateWindowSurface(gWindow);
  }

  /*** Free resources and close SDL. ***/
  close();

  return 0;
}

/* Function definitions *******************************************************/

/**
 * `onKeyDown`
 *
 *   Handles the keydown event.
 */
void onKeyDown(SDL_Event &evt) {
  switch (evt.key.keysym.sym) {
  case SDLK_UP:
    currentColor = red;
    break;

  case SDLK_RIGHT:
    currentColor = yellow;
    break;

  case SDLK_DOWN:
    currentColor = green;
    break;

  case SDLK_LEFT:
    currentColor = blue;
    break;
  }
}

/**
 * `init`
 *
 *   Initializes SDL and global data.
 */
bool init() {

  /*** Initialize SDL. ***/
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s\n",
                    SDL_GetError());
    return false;
  }

  /*** Create the main window. ***/
  gWindow = SDL_CreateWindow("Example 02: Handling events",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    SDL_Quit();
    return false;
  }

  /*** Get the main rendering surface. ***/
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  /*** Initialize colors. ***/
  white = SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF);
  red = SDL_MapRGB(gScreenSurface->format, 0xFF, 0x00, 0x00);
  yellow = SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0x00);
  green = SDL_MapRGB(gScreenSurface->format, 0x00, 0xFF, 0x00);
  blue = SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0xFF);
  currentColor = white;

  return true;
}

/**
 * `close`
 *
 *   Frees resources and shuts down SDL.
 */
void close() {

  /*** Destroy the window. ***/
  if (gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }

  /*** Quit SDL subsystems. ***/
  SDL_Quit();
}
```

### The `init()` function

```cpp
bool init() {

  /*** Initialize SDL. ***/
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s\n",
                    SDL_GetError());
    return false;
  }

  /*** Create the main window. ***/
  gWindow = SDL_CreateWindow("Example 02: Handling events",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    SDL_Quit();
    return false;
  }

  /*** Get the main rendering surface. ***/
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  /*** Initialize colors. ***/
  white = SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF);
  red = SDL_MapRGB(gScreenSurface->format, 0xFF, 0x00, 0x00);
  yellow = SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0x00);
  green = SDL_MapRGB(gScreenSurface->format, 0x00, 0xFF, 0x00);
  blue = SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0xFF);
  currentColor = white;

  return true;
}
```

In [example 01](https://github.com/cj-dimaano/sdl-examples/tree/master/01_creating-a-window), the
first things we do are initialize SDL, create a window, and get the window's surface. The `init()`
function basically tucks all of that logic away into its own function with the added bonus of 
initializing some colors to be used in the main loop.

### The `close()` function

```cpp
void close() {

  /*** Destroy the window. ***/
  if (gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }

  /*** Quit SDL subsystems. ***/
  SDL_Quit();
}
```

Much like the `init()` function, we tuck away cleaning up SDL stuff in the `close()` function.

### The `onKeyDown()` function

```cpp
void onKeyDown(SDL_Event &evt) {
  switch (evt.key.keysym.sym) {
  case SDLK_UP:
    currentColor = red;
    break;

  case SDLK_RIGHT:
    currentColor = yellow;
    break;

  case SDLK_DOWN:
    currentColor = green;
    break;

  case SDLK_LEFT:
    currentColor = blue;
    break;
  }
}
```

A very ubiquitous concept in software development is "abstraction." Here, we use abstraction to
put code for handling the `keydown` event in its own function in the same way that we put code for
initialization and cleanup in their own respective functions.

### The `main()` function

```cpp
int main() {

  /*** Initialize. ***/
  if (!init())
    return -1;

  /*** Main loop flag. ***/
  bool quit = false;

  /*** Event handler. ***/
  SDL_Event evt;

  /*** Main loop. ***/
  while (!quit) {

    /*** Handle events on the queue. ***/
    while (SDL_PollEvent(&evt) != 0) {
      switch (evt.type) {
      /*** Handle quit event. ***/
      case SDL_QUIT:
        quit = true;
        break;

      /*** Handle keydown event. ***/
      case SDL_KEYDOWN:
        onKeyDown(evt);
        break;

      /*** Handle keyup event. ***/
      case SDL_KEYUP:
        currentColor = white;
        break;
      }
    }

    /*** Fill the surface with the current color. ***/
    SDL_FillRect(gScreenSurface, NULL, currentColor);

    /*** Update the screen. ***/
    SDL_UpdateWindowSurface(gWindow);
  }

  /*** Free resources and close SDL. ***/
  close();

  return 0;
}
```

With the initialization and cleanup code moved into their own functions, the majority of the code in
`main()` consists of the main loop. Inside the main loop, we handle any pending events on the event
queue then update the window with the current active color.

Event handling takes place in the inner `while` loop, calling
[`SDL_PollEvent()`](http://wiki.libsdl.org/SDL_PollEvent) with the
[`SDL_Event`](http://wiki.libsdl.org/SDL_Event) struct `evt` repeatedly until the event queue is
empty.

Once the event queue is emptied, we change the color of the window and update the display as in
[Example 01](https://github.com/cj-dimaano/sdl-examples/tree/master/01_creating-a-window).

---

[Previous](https://github.com/cj-dimaano/sdl-examples/tree/master/01_creating-a-window) |
[Next](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image)

## Resources
* [Lazy Foo's Lesson 03](http://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php)
* [Lazy Foo's Lesson 04](http://lazyfoo.net/tutorials/SDL/04_key_presses/index.php)
* [SDL_PollEvent()](http://wiki.libsdl.org/SDL_PollEvent)
* [SDL_Event](http://wiki.libsdl.org/SDL_Event)
