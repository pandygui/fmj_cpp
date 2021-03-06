#ifndef _FightingCharacter_H_
#define _FightingCharacter_H_

#include <iostream>
#include <limits>

#include "FightingSprite.h"
#include "ResMagicChain.h"
#include "Character.h"

class FightingCharacter: public Character
{
public:
    FightingCharacter();
    virtual ~FightingCharacter();
    FightingSprite *getFightingSprite();

    void setFightingSprite(FightingSprite *fightingSprite);

    /** 设置中心坐标*/
    void setCombatPos(int x, int y);

    /**中心坐标*/
    int getCombatX();

    /**中心坐标*/
    int getCombatY();

    int getCombatLeft();

    int getCombatTop();

    void setMagicChain(ResMagicChain *magicChain);

    ResMagicChain *getMagicChain();

    void setLevel(int level);

    int getLevel();

    void setMaxHP(int maxHP);

    int getMaxHP();

    void setMaxMP(int maxMP);

    int getMaxMP();

    void setHP(int hp);

    int getHP();

    bool isAlive();


    bool isVisiable();

    void setVisiable(bool visiable);

    void setMP(int mp);

    int getMP();

    void setAttack(int at);

    int getAttack();

    void setDefend(int d);

    int getDefend();

    void setSpeed(int s);

    int getSpeed();


    int getLingli();

    void setLingli(int l);


    void setLuck(int l);

    int getLuck();



    /**
     * 是否免疫异常状态
     * @param mask 只能为下面几个值，或者他们的位或<p>
     * <code>BUFF_MASK_DU</code>，
     * <code>BUFF_MASK_LUAN</code>，
     * <code>BUFF_MASK_FENG</code>，
     * <code>BUFF_MASK_MIAN</code>，
     * @return 是否免疫mask状态
     */
    bool hasBuff(int mask);

    /**
     * 是否身中异常状态
     * @param mask 只能为下面几个值，或者他们的位或中的任意一个<p>
     * <code>BUFF_MASK_DU</code>，
     * <code>BUFF_MASK_LUAN</code>，
     * <code>BUFF_MASK_FENG</code>，
     * <code>BUFF_MASK_MIAN</code>，
     * @return 是否身中mask状态
     */
    bool hasDebuff(int mask);

    /**
     * 攻击是否能够产生异常状态
     * @param mask 只能为下面几个值，或者他们的位或中的任意一个<p>
     * <code>BUFF_MASK_DU</code>，
     * <code>BUFF_MASK_LUAN</code>，
     * <code>BUFF_MASK_FENG</code>，
     * <code>BUFF_MASK_MIAN</code>，
     * @return 物理攻击是否具有mask效果
     */
    bool hasAtbuff(int mask);

    /**
     * 增加角色能够免疫的状态
     * @see {@link #hasBuff(int)}
     * @param mask
     */
    void addBuff(int mask);

    /**
     * 增加角色能够免疫的状态
     * @see {@link #hasBuff(int)}
     * @param mask
     * @param rounds
     */
    void addBuff(int mask, int rounds);

    void delBuff(int mask);

    int getBuffRound(int mask);

    /**
     * 增加角色身中的异常状态
     * @see {@link #hasDebuff(int)}
     * @param mask
     */
    void addDebuff(int mask, int rounds);

    void delDebuff(int mask)
    {
        mDebuff &= (~mask);
    }

    /**
     * 增加角色攻击能够产生的异常状态
     * @see {@link #hasAtbuff(int)}
     * @param mask
     */
    void addAtbuff(int mask, int rounds);

    void delAtbuff(int mask);



private:
    /**
    * 人物战斗图
    */
    FightingSprite *mFightingSprite;

    /**
    * 等级
    */
    int mLevel;

    /**
    * 魔法链
    */
    ResMagicChain *mMagicChain;
    int mMaxHP;
    int mMaxMP;
    int mHP;
    bool mIsVisiable;
    int mMP;
    int mAttack; // 攻击
    int mDefend; // 防御
    int mSpeed; // 身法
    int mlingli; // 灵力
    int mLuck; // 幸运

public:
    bool bInstanceof_Monster;
    bool bInstanceof_Player;
public:
    enum
    {
        BUFF_MASK_ALL = 16,
        BUFF_MASK_DU = 8,
        BUFF_MASK_LUAN = 4,
        BUFF_MASK_FENG = 2,
        BUFF_MASK_MIAN = 1,

        BUFF_MASK_GONG = 32,
        BUFF_MASK_FANG = 64,
        BUFF_MASK_SU   = 128,
    };

protected:
    /** 免疫毒乱封眠，不同装备可能具有相同的免疫效果，叠加之*/
    int mBuff[4];
    int mBuffRound[4] ;
    /** 身中毒乱封眠*/
    int mDebuff;
    int mDebuffRound[4];
    /** 普通攻击产生(全体)毒乱封眠，对于主角，只有武器具有该效果*/
    int mAtbuff;
    int mAtbuffRound[4];

};

#endif
