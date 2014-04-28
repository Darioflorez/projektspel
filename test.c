#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>



///Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_SPEED_BALL = 5;

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

///Ball direction
int DirectionX, DirectionY;

///The Player1
SDL_Surface* Player1;
///Player1 position
SDL_Rect rcPlayer1;

///The Player2
SDL_Surface* Player2;
///Player2 position
SDL_Rect rcPlayer2;

///The Player3
SDL_Surface* Player3;
///Player3 position
SDL_Rect rcPlayer3;

///The Player4
SDL_Surface* Player4;
///Player4 position
SDL_Rect rcPlayer4;

typedef struct BallDir
{
    int dx;
    int dy;
} BallDirection;

BallDirection BallDirection_S;

int vel=5;
int angle;
int scale_x =10, scale_y;

///Restart ball
void RestartBall()
{
    printf("COS: %d ", scale_x);
    rcball.x = SCREEN_WIDTH/2-30;
    rcball.y = SCREEN_HEIGHT/2-30;
    angle = rand() % 360 +1;
    scale_x = cos(angle);
    scale_y = sin(angle);


}

///Move ball
void MoveBall()
{
    rcball.x += scale_x * vel;
    rcball.y += scale_y * vel;

    if(rcball.y < 1 || rcball.y > SCREEN_HEIGHT -40 -1 || rcball.x > SCREEN_WIDTH -40 -1 || rcball.x < 1)
    {
        RestartBall();
    }
}

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
		gWindow = SDL_CreateWindow( "Ping-Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
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
	gXOut = SDL_LoadBMP( "bgblack.bmp" );
	if( gXOut == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "black.bmp", SDL_GetError() );
		success = false;
	}

	///Create a window surface
	/*gScreenSurface = SDL_GetWindowSurface(gWindow);
	///Fill the surface
	SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 50, 64, 64));
    */
	///Load a ball
	Ball = SDL_LoadBMP("ball.bmp");
	if(Ball == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", "ball.bmp", SDL_GetError() );
		success = false;
	}

	SDL_SetColorKey(Ball,
    SDL_TRUE,
    (Uint32) SDL_MapRGB(Ball->format,
    255, 255, 255));
	///Load a Player1
	Player1 = SDL_LoadBMP("rectangle_blue.bmp");
	if(Player1 == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", "rectangle_blue.bmp", SDL_GetError() );
		success = false;
	}

	///Load a Player2
	Player2 = SDL_LoadBMP("rectangle_yellow2.bmp");
	if(Player2 == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", "rectangle4.bmp", SDL_GetError() );
		success = false;
	}

	///Start position Player1
	rcPlayer1.x = 640/2-75;
	rcPlayer1.y = 480-30;

	///Start position Player2
	rcPlayer2.x = 640/2-75;
	rcPlayer2.y = 5;

	return success;
}

void close()
{
	///Deallocate surface
	SDL_FreeSurface( gXOut );
	SDL_FreeSurface(Ball);
	SDL_FreeSurface(Player1);
	SDL_FreeSurface(Player2);
	gXOut = NULL;
	Ball = NULL;
	Player1 = NULL;
	Player2 = NULL;

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
    srand(time(NULL));
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

            ///Release the ball
            RestartBall();
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

                            case SDLK_a:
                                rcPlayer2.x -= 10;
                                if(rcPlayer2.x < 0 )
                                {
                                    rcPlayer2.x = 0;
                                }
                                break;

                            case SDLK_d:
                                rcPlayer2.x += 10;
                                if(rcPlayer2.x > SCREEN_WIDTH - 150)
                                {
                                    rcPlayer2.x = SCREEN_WIDTH - 150;
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
				SDL_BlitSurface(Player2, NULL, gScreenSurface, &rcPlayer2);

				//printf("%d\n", rcPlayer1.x);

                ///Collision Detection


                ///Move ball
                MoveBall();


				///Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	///Free resources and close SDL
	close();

	return 0;
}


