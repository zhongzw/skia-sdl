#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "SDL.h"
#include "SkBitmap.h"
#include "SkCanvas.h"
#include "SkString.h"
#include "SkTypeface.h"
#include <string>

#include "View.h"

class TextBox:public View
{
private:
	float cursorFrom = -1;//���λ�����
	float cursorTo = -1;//���λ���յ㣬���ֻ�����û���յ�ֻ��ʾһ�����ߣ�����������ѡ����һ������
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