#include "TextBox.h"

static bool setBitmapFromSurface(SkBitmap* dst, SDL_Surface* src)
{
	SkBitmap::Config config;

	switch (src->format->BytesPerPixel) {
	case 2:
		config = SkBitmap::kRGB_565_Config;
		break;
	case 4:
		config = SkBitmap::kARGB_8888_Config;
		break;
	default:
		return false;
	}

	dst->setConfig(config, src->w, src->h, src->pitch);
	dst->setPixels(src->pixels);
	return true;
}

TextBox::TextBox(SkRect rect):View(rect)
{
	SDL_EnableUNICODE(SDL_ENABLE);
}

TextBox::TextBox(SkRect rect, std::string str) : View(rect)
{
	this->str = str;
}


TextBox::~TextBox()
{
	SDL_EnableUNICODE(SDL_DISABLE);
}

void TextBox::setText(std::string str)
{
	this->str = str;
}

std::string TextBox::getText()
{
	return str;
}

void TextBox::handleEvent(SDL_Event &event)
{
	if ((event.type == SDL_KEYDOWN))
	{
		//If the key is a space
		if (event.key.keysym.sym == (Uint16)' ')
		{
			//Append the character
			str += (char)event.key.keysym.sym;
		}
		//If the key is a number
		else if ((event.key.keysym.sym >= (Uint16)'0') && (event.key.keysym.sym <= (Uint16)'9'))
		{
			//Append the character
			str += (char)event.key.keysym.sym;
		}
		//If the key is a uppercase letter
		else if ((event.key.keysym.sym >= (Uint16)'A') && (event.key.keysym.sym <= (Uint16)'Z'))
		{
			//Append the character
			str += (char)event.key.keysym.sym;
		}
		//If the key is a lowercase letter
		else if ((event.key.keysym.sym >= (Uint16)'a') && (event.key.keysym.sym <= (Uint16)'z'))
		{
			//Append the character
			str += (char)event.key.keysym.sym;
		}

		//If backspace was pressed and the string isn't blank
		if ((event.key.keysym.sym == SDLK_BACKSPACE) && (str.length() != 0))
		{
			//Remove a character from the end
			str.erase(str.length() - 1);
		}

	}
	else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEMOTION)//发生了鼠标事件，鼠标点击，放开，移动。
	{
		//获得鼠标坐标
		int mouseX = event.motion.x;
		int mouseY = event.motion.y;
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//如果鼠标在TextBox内部点击
			if ((mouseX > rect.x()) && (mouseX < (rect.x() + rect.width())) && (mouseY > rect.y()) && (mouseY < (rect.y() + rect.height())))
			{
				onFocus = true;
				cursorFrom = mouseX;
				if (cursorTo >= 0)//textbox已经处于有蓝色背景状态
				{
					cursorTo = -1;
				}
			}
			//如果不是
			else
			{
				onFocus = false;
				cursorFrom = -1;
				cursorTo = -1;
			}
		}
		else if (event.type == SDL_MOUSEMOTION){
			if (cursorFrom >= 0 && cursorTo<0)
			{
				cursorTo = mouseX;
				if (cursorTo>(rect.x() + rect.width()))
				{
					cursorTo = (rect.x() + rect.width());
				}
			}
		}

		else if (event.type == SDL_MOUSEBUTTONUP){
			if (cursorFrom >= 0)
			{
				cursorTo = mouseX;
				if (cursorTo>(rect.x() + rect.width()))
				{
					cursorTo = (rect.x() + rect.width());
				}
			}
		}
		
	}

}


static void getCursor(float &cursorFrom, SkScalar *widths)
{
	int i = 0;
	for (i; i < sizeof(widths); i++){
		if (cursorFrom>=widths[i]){
			cursorFrom = widths[i];
			break;
		}
	}
}
void TextBox::draw(SDL_Surface *surface)
{
	if (isEnable)
	{
		SDL_LockSurface(surface);
		SkBitmap mbitmap;
		if (setBitmapFromSurface(&mbitmap, surface)) {
			SkCanvas canvas(mbitmap);
			SkRect rectTemp;
			SkPaint focusPaint;
			focusPaint.setAntiAlias(false);
			focusPaint.setStrokeWidth(SkIntToScalar(2));
			focusPaint.setStyle(SkPaint::kStroke_Style);
			if (onFocus)
				focusPaint.setColor(0xFFFF8000);
			else
				focusPaint.setColor(0xFFFFFFFF);
			getFocusRect(rectTemp);
			canvas.drawRoundRect(rectTemp, 2, 2, focusPaint);


			SkPaint fontPaint;
			fontPaint.setAntiAlias(false); // Turning off anti-aliasing speeds up the line drawing
			fontPaint.setColor(0xFF000000);
			fontPaint.setStrokeWidth(SkIntToScalar(2));

			SkTypeface* pFace = SkTypeface::CreateFromName("宋体", SkTypeface::kNormal);
			fontPaint.setTypeface(pFace);
			fontPaint.setTextSize(24);

			int fontHeight = fontPaint.getTextSize();
			canvas.drawText(str.c_str(), str.length(), rect.x(), (rect.y() + fontHeight), fontPaint);

			if (!drawRect)  //第一次画，以后都不画
			{
				SkPaint rectPaint;
				rectPaint.setAntiAlias(false);
				rectPaint.setColor(0xFFC8C8C8);
				rectPaint.setStrokeWidth(SkIntToScalar(2)); // This makes the lines have a thickness of 2 pixels

				rectPaint.setStyle(SkPaint::kStroke_Style);
				canvas.drawRoundRect(rect, 2, 2, rectPaint);
				drawRect = true;
			}
		}
		SDL_UnlockSurface(surface);
		SDL_UpdateRect(surface, 0, 0, surface->w, surface->h);
	}
}