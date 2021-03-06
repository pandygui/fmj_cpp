#ifndef _NPC_H_
#define _NPC_H_

#include <iostream>

#include "Character.h"
#include "Direction.h"
#include "Random.h"

class SaveLoadStream;

struct ICanWalk
{
    virtual bool canWalk(int x, int y) = 0;
};

class NPC: public Character
{
public:
    NPC();
    virtual ~NPC();
    virtual void setData(char *buf, int offset);

    void setICanWalk(ICanWalk *arg);

    void update(long delta);

    virtual void walk();

    void read(SaveLoadStream *buff);
    void write(SaveLoadStream *buff);

protected :
    /**
     * 暂停状态，等到延时到了后转变为巡逻状态
     */
    int mDelay;

private:
    Random mRandom;
    long mPauseCnt;
    long mActiveCnt;
    long mWalkingCnt;
    ICanWalk *mCanWalk;
public:
    bool bInstanceOf_SceneObj;
};

#endif
