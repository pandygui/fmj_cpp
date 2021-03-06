#ifndef _ScreenMainGame_h_
#define _ScreenMainGame_h_

#include "Util.h"
#include "BaseScreen.h"
#include "SaveLoadGame.h"
#include "ScriptProcess.h"
#include "ResMap.h"
#include "Player.h"
#include <iostream>

using namespace std;

class Combat;

class ScreenMainGame : public BaseScreen
{
public:
    ScreenMainGame();
    virtual ~ScreenMainGame();
 
    void setSceneName(std::string name);

    std::string getSceneName()
    {
        return mSceneName;
    }

    void exitScript();
    void runScript();
    void startChapter(int type, int index);
    virtual void update(long delta);
    virtual void draw(Canvas *canvas);
    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);

    /**
     * 按enter键后，检测并触发场景对象里的事件，如NPC对话，开宝箱等
     */
    void triggerSceneObjEvent();

    /**
     * 场景切换
     * 如果地图(x,y)有地图事件，就触发该事件
     * @param x
     * @param y
     */
    bool triggerMapEvent(int x, int y);

    /**
     * 地图的(x,y)处，是否可行走，是否有NPC
     * @param x
     * @param y
     * @return
     */
    bool canPlayerWalk(int x, int y);

    void walkLeft();
    void walkUp();
    void walkRight();
    void walkDown();

    /**
     * 载入号码n,类型m的地图，初始位置（x，y）
     */
    void loadMap(int type, int index, int x, int y);

    ResMap *getCurrentMap();

    void setMapScreenPos(int x, int y);

    /**
     * 创建主角号码actor，位置为（x，y）
     * @param actorId
     * @param x
     * @param y
     */
    void createActor(int actorId, int x, int y);
    void deleteActor(int actorId);

    Player *getPlayer();
    Player *getPlayer(int actorId);

    /**
     * 创建配角号码npc，位置为（x，y），id为操作号
     * @param id
     * @param npc
     * @param x
     * @param y
     */
    void createNpc(int id, int npc, int x, int y);

    void deleteNpc(int id);

    void deleteAllNpc();

    NPC *getNPC(int id);

    bool isNpcVisible(NPC *npc);

    bool isNpcVisible(int id);

    /**
     * 建一个宝箱，宝箱号码boxindex(角色图片，type为4)，
     * 位置为（x，y），id为操作号（与NPC共用)
     */
    void createBox(int id, int boxIndex, int x, int y);

    void deleteBox(int id);

    Combat *getCombat();
private:
    struct NpcCanWalk :public ICanWalk
    {
        virtual bool canWalk(int x, int y);
    };

private:
    /* 按y值从大到小排序，确保正确的遮挡关系 */
    static std::vector<NPC *> getSortedNpcObjs();
public:
    static void drawScene(Canvas *canvas);
    static void gotoAddress(int address);
    static void triggerEvent(int eventId);

    static NPC *getNpcFromPosInMap(int x, int y); //得到地图的(x,y)处的NPC，没有就返回NULL
    static int getNpcIdFromPosInMap(int x, int y);
public:
    static std::vector<Player *> sPlayerList;
    static NPC * sNPCObjs[41]; // id--NPC或场景对象 (1-40)
    static Player *sPlayer;//这个变量不需要delete，它的值是sPlayerList中的一个
    static ResMap *sMap;
private:
    static Point mMapScreenPos; // 屏幕左上角对应地图的位置
    static ScriptExecutor *mScriptExecutor;
    static bool mRunScript; //当前是否在执行脚本

private:
    ScriptProcess *mScriptSys;
    Combat *mCombat;
    std::string mSceneName;
    ICanWalk *mNpcCanWalk;
};

#endif