/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include <string>


#include "SkBitmap.h"
#include "SkCanvas.h"
#include "SkString.h"
#include "SkTypeface.h"

#include "TextBox.h"
#include "Button.h"
#include "View.h"
#include "ControlView.h"
#include "Timer.h"


//The screen attributes
const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 1;

//The surfaces
SDL_Surface *screen = NULL;
//The event structure
SDL_Event event;

bool init()
{
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	//If there was an error in setting up the screen
	if (screen == NULL)
	{
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption("testBox", NULL);


	//If everything initialized fine
	return true;
}

void clean_up()
{
	SDL_FreeSurface(screen);
	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[])
{
	
	bool quit = false;//Quit flag

	Timer fps;//The frame rate regulator

	
	if (init() == false)//Initialize
	{
		return 1;
	}
	ControlView control;
	SkRect rect;
	rect.setXYWH(10, 100, 200, 30);
	View *textBox1 = new TextBox(rect);

	rect.setXYWH(220, 100, 200, 30);
	View *textBox2 = new TextBox(rect);

	rect.setXYWH(440, 100, 200, 30);
	Button *myButton = new Button(rect);
	SkPoint fontMargin;
	fontMargin.set(22, -2);
	myButton->setName("setting");
	myButton->setFont(24, "times.ttf", 0xFFFFFFFF);
	myButton->setFontMargin(fontMargin);
	myButton->setBackPic("Button.png");

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	textBox1->draw(screen);
	textBox2->draw(screen);
	myButton->draw(screen);



	control.addView(textBox1);
	control.addView(textBox2);
	control.addView(myButton);
	while (quit == false)//While the user hasn't quit
	{
		//Start the frame timer
		fps.start();

		//While there's events to handle
		while (SDL_PollEvent(&event))
		{
			//Handle events for the dot
			control.handleEvent(event);
			//If the user has Xed out the window
			if (event.type == SDL_QUIT)
			{
				//Quit the program
				quit = true;
			}
			textBox1->draw(screen);
			textBox2->draw(screen);
			myButton->draw(screen);
		}

		//Fill the screen white
		
		//Update the screen
		if (SDL_Flip(screen) == -1)
		{
			return 1;
		}

		//Cap the frame rate
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

	//Clean up
	clean_up();

	return 0;
}
