#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include "SDL.h"
#include "SkTypeface.h"
#include <list>
#include "View.h"

#include <fstream>  
#include <iostream>  
using namespace std;


class ControlView
{
private:
	list<View*> viewList;
	list<View*>::iterator viewListIterator;
	int focus = 0;
	ofstream log;
public:
	ControlView();
	~ControlView();

	void handleEvent(SDL_Event &event);
	void addView(View *view);
};

#endif