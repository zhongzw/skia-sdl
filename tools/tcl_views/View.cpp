#include "View.h"
	//Initializes the variables
View::View(SkRect rect)
{
	this->rect = rect;
}
View::~View()
{

}

void View::draw(SDL_Surface *surface)
{

}
void View::handleEvent(SDL_Event &event)
{

}


void View::setEnable(bool isEnable)
{
	this->isEnable = isEnable;
}
bool View::getEnable()
{
	return isEnable;
}

void View::setFocus(bool onFocus)
{
	this->onFocus = onFocus;
}
bool View::getFocus()
{
	return onFocus;
}

SkRect View::getRect()
{
	return rect;
}

void View::getFocusRect(SkRect &rectTemp)
{
	rectTemp.setXYWH(rect.x() - 3, rect.y() - 3, rect.width() + 6, rect.height() + 6);
}