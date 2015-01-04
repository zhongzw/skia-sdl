#include "View.h"
#include <string>
#include <SkImage.h>
#include <SkStream.h>
#include <SkImageDecoder.h>

class Button : public View
{
private:
	std::string name;
	SkScalar fontSize;
	std::string fontType;
	SkColor fontColor;
	SkPoint fontMargin;
	std::string backPic;
	SkBitmap *bkBitmap = NULL;
public:

	//Initializes the variables
	Button(SkRect rect);
	~Button();

	//Takes key presses and adjusts the button's velocity
	void handleEvent(SDL_Event &event);

	//Shows the button on the screen
	void draw(SDL_Surface *surface);

	//set button's name
	void setName(std::string name);

	void setFont(SkScalar fontSize, std::string fontType, SkColor fontColor);

	void setFontMargin(SkPoint fontMargin);

	void setBackPic(std::string backPic);
};