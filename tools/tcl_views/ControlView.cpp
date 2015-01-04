#include "ControlView.h"

ControlView::ControlView()
{
	focus = -1;
}
ControlView:: ~ControlView()
{
	log.close();
}


void ControlView::addView(View *view)
{
	if (viewList.size() == 0)
	{
		focus = 0;
		view->setFocus(true);
	}
	viewList.push_back(view);
}

void ControlView::handleEvent(SDL_Event &event)
{
	int i = 0;
	if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT))
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			if (focus == (viewList.size()-1)){     //光标已经在最右侧

			}
			else{
				for (i = 0,viewListIterator = viewList.begin(); viewListIterator != viewList.end(); ++viewListIterator,i++)
				{
					View *view = *viewListIterator;
					view->setFocus(false);
					if (i == (focus + 1))
					{
						view->setFocus(true);
					}
				}
				focus++;
			}
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
		{
			if (focus == 0){      //光标已经在最左侧
				
			}
			else{
				for (i = 0, viewListIterator = viewList.begin(); viewListIterator != viewList.end(); ++viewListIterator, i++)
				{
					View *view = *viewListIterator;
					view->setFocus(false);
					if (i == (focus - 1))
					{
						view->setFocus(true);
					}
				}
				focus--;
			}
		}
	}

	else if (event.type == SDL_MOUSEBUTTONDOWN){
		int mouseX = event.motion.x;
		int mouseY = event.motion.y;
		for (i = 0, viewListIterator = viewList.begin(); viewListIterator != viewList.end(); ++viewListIterator, i++)
		{
			View *view = *viewListIterator;
			view->setFocus(false);
			if ((mouseX > view->getRect().x()) && (mouseX < (view->getRect().x() + view->getRect().width())) && (mouseY > view->getRect().y()) && (mouseY < (view->getRect().y() + view->getRect().height())))
			{
				view->setFocus(true);
				focus = i;
			}
		}
	}

	else{
		for (i = 0, viewListIterator = viewList.begin(); viewListIterator != viewList.end(); ++viewListIterator, i++)
		{
			View *view = *viewListIterator;
			if (i == focus)
			{
				log << "i = " << i << "---------focus = " << focus << endl;
				view->handleEvent(event);
				break;
			}
		}
	}
}