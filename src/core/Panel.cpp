#include "Panel.h"
#include "Manager.h"

Panel::Panel()
{
    background = NULL;
}
Panel::~Panel()
{
    if (NULL != background)
    {
        delete background;
    }
}
void Panel::paint()
{
    if(background != NULL)
    {
        draw(background);
    }
}

void Panel::repaint()
{
    paint();
}

void Panel::setBackground(Bitmap *background)
{
    this->background = background;
}

void Panel::draw(Bitmap *background)
{
    //整个程序中，只在这里用作帧更新
    Manager *m = Manager::getInstance();
    m->getMethod()->DrawScreen(background->handle);
}

