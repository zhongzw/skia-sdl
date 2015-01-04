#include "Button.h"

static bool setBitmapFromSurface(SkBitmap* dst, SDL_Surface* src);

Button::Button(SkRect rect) : View(rect)
{
	//Initialize the offsets
	name = "";
	fontType = "";
	fontSize = rect.height()/2;
	fontColor = 0xFF000000;
	fontMargin.set(0, 0);
	SDL_EnableUNICODE(SDL_ENABLE);
}

Button::~Button()
{
	SDL_EnableUNICODE(SDL_DISABLE);
}

void Button::handleEvent(SDL_Event &event)
{
	int mouseX = event.motion.x;
	int mouseY = event.motion.y;
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//如果鼠标在TextBox内部点击
		if ((mouseX > rect.x()) && (mouseX < (rect.x() + rect.width())) && (mouseY > rect.y()) && (mouseY < (rect.y() + rect.height())))
			onFocus = true;
		else
			onFocus = false;
	}
}

void Button::draw(SDL_Surface *surface)
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
			
			if (!drawRect)  //第一次画，以后都不画
			{
				//画框
				SkPaint rectPaint;
				rectPaint.setAntiAlias(false); 
				rectPaint.setColor(0xFF004080);
				rectPaint.setStrokeWidth(SkIntToScalar(2));
				
				
				//画字
				SkPaint fontPaint;
				fontPaint.setAntiAlias(false);
				fontPaint.setColor(fontColor);
				fontPaint.setStrokeWidth(SkIntToScalar(2));

				SkTypeface* pFace = SkTypeface::CreateFromFile(fontType.c_str());
				fontPaint.setTypeface(pFace);
				fontPaint.setTextSize(fontSize);

				canvas.drawRoundRect(rect, 2, 2, rectPaint);
				canvas.drawText(name.c_str(), name.length(), rect.x() + fontMargin.x(), rect.y() + fontSize + fontMargin.y(), fontPaint);
				drawRect = true;
			}
			
		}
		SDL_UnlockSurface(surface);
		SDL_UpdateRect(surface, 0, 0, surface->w, surface->h);
	}

}

void Button::setName(std::string name)
{
	this->name = name;
}

void Button::setFont(SkScalar fontSize, std::string fontType, SkColor fontColor)
{
	this->fontSize = fontSize;
	this->fontType = fontType;
	this->fontColor = fontColor;
}

void Button::setFontMargin(SkPoint fontMargin)
{
	this->fontMargin = fontMargin;
}

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

void Button::setBackPic(std::string backPic)
{
	this->backPic = backPic;
	if (backPic.length() != 0)
	{
		SkFILEStream stream(backPic.c_str());
		SkImageDecoder * coder = SkImageDecoder::Factory(&stream);
		if (coder)
		{
			bkBitmap = new SkBitmap();
			coder->decode(&stream, bkBitmap, SkBitmap::kARGB_8888_Config, SkImageDecoder::kDecodePixels_Mode);
		}
	}
}
