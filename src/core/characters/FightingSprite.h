#ifndef _FightingSprite_H_
#define _FightingSprite_H_

#include <iostream>

#include "DatLib.h"
#include "ResImage.h"
#include "Canvas.h"

class FightingSprite
{
public:
    FightingSprite(int resType, int index);
    virtual ~FightingSprite();
    void draw(Canvas *canvas);

    void draw(Canvas *canvas, int x, int y);

    void setCombatPos(int x, int y);

    void move(int dx, int dy);

    int getCombatX();

    int getCombatY();

    int getWidth();

    int getHeight();

    int getCurrentFrame();

    /**
     *
     * @param i > 0
     */
    void setCurrentFrame(int i);

    int getFrameCnt();


private:
    ResImage *mImage;

    int mCurrentFrame;

    /** 在战斗场景中的屏幕坐标*/
    int mCombatX;
    int mCombatY;
};

#endif
