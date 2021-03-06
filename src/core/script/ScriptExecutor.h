#ifndef _ScriptExecutor_h_
#define _ScriptExecutor_h_

#include "Operate.h"
#include "Canvas.h"

#include <iostream>
#include <hash_map>

class ScriptExecutor
{
public:
    /**
     *
     * @param list 一个脚本文件对应的操作表
     * @param eventIndex eventIndex[i]等于触发事件i+1时，要执行的Operate在list中的序号
     * @param map 地址偏移-序号
     */
    ScriptExecutor(std::vector<Operate *> &list, std::vector<int> &eventIndex, std::hash_map<int, int> &map, int headerCnt);

    virtual ~ScriptExecutor();
    /**
     * 触发地图事件,场景切换，NPC对话，开宝箱等
     * @param eventId 是否成功触发
     */
    bool triggerEvent(int eventId);

    void gotoAddress(int address);

    void process();

    void update(long delta);

    void draw(Canvas *canvas);

    void keyDown(int key);

    void keyUp(int key);

public:
    static bool goonExecute;

private:
    std::vector<Operate *> mOperateList;

    /**
    * 当前正在执行的操作在mOperateList中的位置
    */
    int mCurExeOperateIndex;

    /**
    * 当前是否正在执行 update() draw()
    */
    bool mIsExeUpdateDraw;

    /**
    * mEventIndex[i]等于触发事件i+1时，要执行的Operate在list中的序号，
    * -1表示不存在
    */
    std::vector<int> mEventIndex;

    /**
    * address offset --- operate's index of mOperateList
    */
    std::hash_map<int, int>  mMapAddrOffsetIndex;
    typedef std::pair<int, int> Int_Pair;

    /**
    * code数据前的长度
    */
    int mHeaderCnt;
};

#endif
