#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SkBitmap.h"
#include "SkCanvas.h"
#include "SkString.h"
#include "SkTypeface.h"
#include <string>

#include "View.h"

class TextBox:public View
{
private:
	float cursorFrom = -1;//光标位置起点
	float cursorTo = -1;//光标位置终点，如果只有起点没有终点只显示一条竖线，否则就是鼠标选中了一段文字
	std::string str;

public:
	//Initializes the variables
	TextBox(SkRect rect);
	TextBox(SkRect rect,std::string str);
	~TextBox();

	void draw(SDL_Surface *surface);
	void handleEvent(SDL_Event &event);

	void setText(std::string str);
	std::string getText();
	
};

#endif