//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>



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

///The ball
SDL_Surface* Ball = NULL;
///Ball position
SDL_Rect rcball;

///The Player1 (Rect istället för Surface)
SDL_Surface* Player1;
///Player1 position
SDL_Rect rcPlayer1;

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
		printf( "Unable to load image %s! SDL Error: %s\n", "wall.bmp", SDL_GetError() );
		success = false;
	}

	///Load a ball
	Ball = SDL_LoadBMP("ball.bmp");
	if(Ball == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", "ball.bmp", SDL_GetError() );
		success = false;
	}
	///Load a Player1
	Player1 = SDL_LoadBMP("rectangle1.bmp");
	if(Player1 == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", "rectangle1.bmp", SDL_GetError() );
		success = false;
	}

	///Player1 position
	rcPlayer1.x = 640/2-75;
	rcPlayer1.y = 480-50;

	///Ball position (Random skulle passa bättre)
	rcball.x = 640/2-30;
    rcball.y = 480/2-30;

	return success;
}

void close()
{
	///Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;
	SDL_FreeSurface(Ball);
	Ball = NULL;

	///Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	///Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
    ///Ball direction
    int Dir = 0;
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

                            case SDLK_LEFT:
                                rcPlayer1.x -= 10;
                                if(rcPlayer1.x < 0 )
                                {
                                    rcPlayer1.x = 0;
                                }
                                break;

                            case SDLK_RIGHT:
                                rcPlayer1.x += 10;
                                if(rcPlayer1.x > SCREEN_WIDTH - 150)
                                {
                                    rcPlayer1.x = SCREEN_WIDTH - 150;
                                }
                                break;

                        }
                        break;
					}
				}



				///Apply the image
				SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
				SDL_BlitSurface(Ball, NULL, gScreenSurface, &rcball);
				SDL_BlitSurface(Player1, NULL, gScreenSurface, &rcPlayer1);

				if(Dir==0)
				{
                    rcball.y -= 2;
                    if (rcball.y < 0)
                    {
                        Dir = 1;
                    }
				}
				if(Dir==1)
				{
                    rcball.y += 2;
                    if (rcball.y > SCREEN_HEIGHT - 30)
                    {
                        Dir = 0;
                    }
				}

				///Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	///Free resources and close SDL
	close();

	return 0;
}
