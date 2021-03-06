#ifndef _ScreenMenuSystem_H_
#define _ScreenMenuSystem_H_

#include <iostream>
#include "GameView.h"
#include "TextRender.h"
#include "BaseScreen.h"
#include "Bitmap.h"
#include "canvas.h"
#include "Point.h"
#include "Paint.h"

class ScreenMenuSystem: public BaseScreen
{
public:
    ScreenMenuSystem();
    virtual ~ScreenMenuSystem();

    virtual void update(long delta){}

    virtual void draw(Canvas *canvas);

    virtual void onKeyDown(int key);

    virtual void onKeyUp(int key);

    virtual bool isPopup(){return true;}

private:
    int first;
    int index;
    std::string str[4];
    int strX;
    int strY;
    int selY;

    Bitmap *bmpFrame;
    Bitmap *bmpArrowUp;
    Bitmap *bmpArrowDown;
    Bitmap *bmpArr[2];
    int arrowX;
    int arrowY;
    int bmpi;

};
#endif