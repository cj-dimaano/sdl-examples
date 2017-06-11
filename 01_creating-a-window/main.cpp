/*******************************************************************************
File: main.cpp
Created by: CJ Dimaano
Date created: June 7, 2017
Last updated: June 11, 2017

References:
- http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
- http://wiki.libsdl.org/CategoryLog
- https://wiki.libsdl.org/SDL_Surface
- http://wiki.libsdl.org/SDL_Init
- http://wiki.libsdl.org/SDL_Quit
- http://wiki.libsdl.org/SDL_CreateWindow
- http://wiki.libsdl.org/SDL_GetWindowSurface
- http://wiki.libsdl.org/SDL_FillRect
- http://wiki.libsdl.org/SDL_MapRGB
- http://wiki.libsdl.org/SDL_UpdateWindowSurface
- http://wiki.libsdl.org/SDL_Delay
- http://wiki.libsdl.org/SDL_DestroyWindow
- https://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer

*******************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <stdio.h>

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
