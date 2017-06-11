/*******************************************************************************
File: main.cpp
Created by: CJ Dimaano
Date created: June 7, 2017
Last updated: June 10, 2017

# References
- http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
- http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
- http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php
- http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php
- https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html
- https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC8
- https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC9
- https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC11
- https://wiki.libsdl.org/SDL_Renderer
- https://wiki.libsdl.org/SDL_Texture
- https://wiki.libsdl.org/SDL_CreateRenderer
- https://wiki.libsdl.org/SDL_DestroyRenderer
- https://wiki.libsdl.org/SDL_SetRenderDrawColor
- https://wiki.libsdl.org/SDL_RenderClear
- https://wiki.libsdl.org/SDL_RenderCopy
- https://wiki.libsdl.org/SDL_RenderPresent
- https://wiki.libsdl.org/SDL_CreateTextureFromSurface
- https://wiki.libsdl.org/SDL_DestroyTexture

# Notes
For loading images other than `.bmp`, `SDL_image.h` must be included and
`-lSDL2_image` must be added to the compiler flags.

*******************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

/* Function declarations ******************************************************/

bool init();
void close();
SDL_Texture *loadTexture(const char *const);

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

  /*** Initialize PNG loading. ***/
  const int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL_Image: %s\n",
                 IMG_GetError());
    close();
    return false;
  }

  /*** Create the main window. ***/
  gWindow = SDL_CreateWindow("Example 03: Rendering an image",
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
  SDL_SetRenderDrawColor(gRenderer, 0xEE, 0xEE, 0xEE, 0xEE);

  /*** Load image. ***/
  gTexture = loadTexture("colors.png");
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
  IMG_Quit();
  SDL_Quit();
}

/**
 * `loadTexture`
 *
 *   Loads a texture from file.
 */
SDL_Texture *loadTexture(const char *const path) {

  /*** Load the image as a surface. ***/
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load image '%s': %s\n",
                 path, IMG_GetError());
    return NULL;
  }

  /*** Create texture from surface pixels. ***/
  SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                 "Unable to create texture from '%s': %s\n", path,
                 SDL_GetError());
    return NULL;
  }

  return texture;
}
