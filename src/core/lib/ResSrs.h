#ifndef _ResSrs_h_
#define _ResSrs_h_

#include "ResBase.h"
#include "ResImage.h"

#include <iostream>
#include <list>


class ResSrs : public ResBase
{

public:
    ResSrs();
    virtual ~ResSrs();

    virtual  void setData(char * buf, int offset);

    /**
    * 开始特效动画
    */
    void startAni();

    /**
    *
    * @return 返回false动画播放完毕
    */
    bool update(long delta);

    void draw(Canvas *canvas, int dx, int dy);
    void drawAbsolutely(Canvas *canvas, int x, int y);
    void setIteratorNum(int n);

    void pollList();

    struct SrsFrame
    {
        int data[5];
    };

    struct Key
    {
        int index;
        int show;
        int nshow;

        Key(int index, std::vector<SrsFrame> &header)
        {
            this->index = index;
            this->show = header[index].data[2];
            this->nshow = header[index].data[3];
        }
    };

private:
    /**
    * 帧数
    */
    int mFrameNum;

    /**
    *  图片数
    */
    int mImageNum;

    int mStartFrame;
    int mEndFrame;

    /**
    * <code>mFrameHeader = new int[mFrameNum][5];</code><p>
    * x,y,Show,nShow,imgIndex
    */
    std::vector<SrsFrame> mFrameHeader;
    std::vector<ResImage *> mImage;
    std::list<Key *> mShowList;

    int mIterator;
};

#endif
