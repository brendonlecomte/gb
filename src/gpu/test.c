/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init(){
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      success = false;
        }
        else
        {
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow );

      gXOut = SDL_CreateRGBSurface(0,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  32,
                                  0,
                                  0,
                                  0,
                                  0);
        }
    }

    return success;
}

void draw_display(uint32_t *pixels) {
    uint32_t *p = (uint32_t*)gXOut->pixels;
    for(int i =0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
            *p++ = rand(); //pix[i];
    }

}

void close(){
    //Deallocate surface
    SDL_FreeSurface( gXOut );
    gXOut = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] ){
    uint8_t pix[SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int)]; //4 colours per pixel RGBA

    //Start up SDL and create window
    if( !init() ){
        printf( "Failed to initialize!\n" );
    }
    else{
      //Main loop flag
      bool quit = false;
      //Event handler
      SDL_Event e;
      //While application is running

      while( !quit )
      {
          //Handle events on queue
          while( SDL_PollEvent( &e ) != 0 )
          {
              //User requests quit
              if( e.type == SDL_QUIT )
              {
            quit = true;
              }
          }
          //Fill the surface white
          // SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF ) );
          draw_display((uint32_t*)&pix[0]); //randomise display
          //Apply the image
          SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
          //Update the surface
          SDL_UpdateWindowSurface( gWindow );
      }
    }
    //Free resources and close SDL
    close();
    return 0;
}
