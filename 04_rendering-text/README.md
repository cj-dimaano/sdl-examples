# Example 04 - Rendering text

![Example 04 Screenshot](https://github.com/cj-dimaano/sdl-examples/tree/master/screenshots/example04.png)

In this example, we cover how to render text. The procedure is similar to rendering an image, and
the code uses the TTL extension library. Refer to
[Example 03](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image) for
directions on how to import the library into the project.

As with the previous example, we will only cover new material.

[Previous](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image)

## The Code

```cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

/* Function declarations ******************************************************/

bool init();
void close();
SDL_Texture *createTextureFromText(const char * const);

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
 * `gRenderer`
 *
 *   The window renderer.
 */
static SDL_Renderer *gRenderer = NULL;

/**
 * `gTexture`
 *
 *   The texture to be rendered.
 */
static SDL_Texture *gTexture = NULL;

/**
 * `TTF_Font`
 *
 *   The font to be rendered.
 */
static TTF_Font *gFont = NULL;

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
      }
    }

    /*** Clear the screen. ***/
    SDL_RenderClear(gRenderer);

    /*** Render texture to screen. ***/
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

    /*** Update the screen. ***/
    SDL_RenderPresent(gRenderer);
  }

  /*** Free resources and close SDL. ***/
  close();

  return 0;
}

/* Function definitions *******************************************************/

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

  /*** Initialize TTF. ***/
  if (TTF_Init() < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_ttf: %s\n",
                 TTF_GetError());
    close();
    return false;
  }

  /*** Create the main window. ***/
  gWindow = SDL_CreateWindow("Example 04: Rendering text",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create window: %s\n",
                 SDL_GetError());
    close();
    return false;
  }

  /*** Create renderer for the window. ***/
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create renderer: %s\n",
                 SDL_GetError());
    close();
    return false;
  }

  /*** Set renderer color. ***/
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  /*** Load font. ***/
  gFont = TTF_OpenFont("Roboto-Medium.ttf", 16);
  if (gFont == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load font: %s\n",
                 TTF_GetError());
    close();
    return false;
  }

  /*** Create texture from text. ***/
  gTexture = createTextureFromText("Hello world!");
  if (gTexture == NULL) {
    close();
    return false;
  }

  return true;
}

/**
 * `close`
 *
 *   Frees resources and shuts down SDL.
 */
void close() {

  /*** Destroy the texture. ***/
  if (gTexture != NULL) {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
  }

  /*** Close the font. ***/
  if (gFont != NULL) {
    TTF_CloseFont(gFont);
    gFont = NULL;
  }

  /*** Destroy the renderer. ***/
  if (gRenderer != NULL) {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
  }

  /*** Destroy the window. ***/
  if (gWindow != NULL) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
  }

  /*** Quit SDL subsystems. ***/
  TTF_Quit();
  SDL_Quit();
}

/**
 * `createTextureFromText`
 *
 *   Creates a texture from the given text.
 */
SDL_Texture *createTextureFromText(const char * const text) {

  /*** Render the text on a surface. ***/
  SDL_Color black = { 0, 0, 0, 0 };
  SDL_Surface *surface = TTF_RenderText_Solid(gFont, text, black);
  if (surface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to render text: %s\n",
                 TTF_GetError());
    return NULL;
  }

  /*** Create texture from surface pixels. ***/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Unable to create texture from rendered text: %s\n",
                 SDL_GetError());
    return NULL;
  }

  return texture;
}
```

### The `init()` function

```cpp
  /*** Initialize TTF. ***/
  if (TTF_Init() < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_ttf: %s\n",
                 TTF_GetError());
    close();
    return false;
  }
```

We initialize `SDL_ttf` similarly to how we initialize `SDL_image` by calling
[`TTF_Init()`](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC8).

```cpp
  /*** Load font. ***/
  gFont = TTF_OpenFont("Roboto-Medium.ttf", 16);
  if (gFont == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load font: %s\n",
                 TTF_GetError());
    close();
    return false;
  }

  /*** Create texture from text. ***/
  gTexture = createTextureFromText("Hello world!");
  if (gTexture == NULL) {
    close();
    return false;
  }
```

Then we load the font with
[`TTF_OpenFont()`](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC14) and create a new
texture for the string "Hello world!".

### The `close()` function

```cpp
  ...

  /*** Close the font. ***/
  if (gFont != NULL) {
    TTF_CloseFont(gFont);
    gFont = NULL;
  }

  ...

  /*** Quit SDL subsystems. ***/
  TTF_Quit();
  SDL_Quit();
```

Standard closure procedure.

### The `createTextureFromText()` function

```cpp
SDL_Texture *createTextureFromText(const char * const text) {

  /*** Render the text on a surface. ***/
  SDL_Color black = { 0, 0, 0, 0 };
  SDL_Surface *surface = TTF_RenderText_Solid(gFont, text, black);
  if (surface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to render text: %s\n",
                 TTF_GetError());
    return NULL;
  }

  /*** Create texture from surface pixels. ***/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Unable to create texture from rendered text: %s\n",
                 SDL_GetError());
    return NULL;
  }

  return texture;
}
```

The `createTextureFromText()` function is just the `loadTexture()` function from
[Example 03](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image),
replacing `IMG_Load()` with
[TTF_RenderText_Solid()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC43) and
accounting for the new function's parameters.

### The `main()` function

The main function is unchanged from the previous example.

---

[Previous](https://github.com/cj-dimaano/sdl-examples/tree/master/03_rendering-an-image)

## Resources
* [Lazy Foo's Lesson 16](http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php)
* [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
* [TTF_Font](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC56)
* [TTF_Init()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC8)
* [TTF_Quit()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC10)
* [TTF_OpenFont()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC14)
* [TTF_CloseFont()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC18)
* [TTF_RenderText_Solid()](https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC43)
