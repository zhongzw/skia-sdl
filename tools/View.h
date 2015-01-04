#ifndef VIEW_H
#define VIEW_H

#include "SDL.h"
#include "SkTypeface.h"
#include "SkBitmap.h"
#include "SkCanvas.h"

class View
{
protected:
	SkRect rect;
	bool onFocus = false;
	bool isEnable = true;
	bool drawRect = false;

public:
	//Initializes the variables
	View(SkRect rect);
	virtual ~View();

	virtual void draw(SDL_Surface *surface);
	virtual void handleEvent(SDL_Event &event);
	void setEnable(bool isEnable);
	bool getEnable();

	void setFocus(bool onFocus);
	bool getFocus();

	SkRect getRect();

	void getFocusRect(SkRect &rectTemp);

};

#endif