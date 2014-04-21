//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>



///Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

///Starts up SDL and creates window
bool init();

///Loads media
bool loadMedia();

///Frees media and shuts down SDL
void close();

///The window we'll be rendering to
SDL_Window* gWindow = NULL;

///The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

///The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init()
{
	///Initialization flag
	bool success = true;

	///Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		///Create window
		gWindow = SDL_CreateWindow( "Dario Florez", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			///Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	///Loading success flag
	bool success = true;

	///Load splash image
	gXOut = SDL_LoadBMP( "wall.bmp" );
	if( gXOut == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	///Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;

	///Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	///Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	///Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		///Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			///Main loop flag
			bool gameover = false;

			///Event handler
			SDL_Event event;

			///While application is running
			while( !gameover )
			{
				///Look for events
				if( SDL_PollEvent( &event ) )
				{
					///An event was found
					switch (event.type)
					{
                        			///Close button clicked
                        			case SDL_QUIT:
                            			gameover = 1;
                            			break;

                        			///Handle the keybord
                        			case SDL_KEYDOWN:
                            				switch (event.key.keysym.sym)
                            				{
                                				case SDLK_ESCAPE:
                                				case SDLK_q:
                                    				gameover = 1;
                                    				break;
                            				}
                            			break;
					}
				}

				///Apply the image
				SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );

				///Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	///Free resources and close SDL
	close();

	return 0;
}