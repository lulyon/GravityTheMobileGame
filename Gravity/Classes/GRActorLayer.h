//
//  GRActorLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRActorLayer_h
#define GravityTemplate_GRActorLayer_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

/// 定义演员标签
enum ActorTag
{
    SPACE_MAN = 1,
};

/// 定义触摸区域，用于判断用户是否点击了屏幕下半部区域
enum TouchArea
{
    TOUCH_NULL  = 0,
    TOUCH_LEFT  = 1,
    TOUCH_RIGHT = 2,
};

enum ActorLevel
{
    A_LEVEL_OVER  = 0,
    A_LEVEL_ONE   = 1,
    A_LEVEL_TWO   = 2,
    A_LEVEL_THREE = 3,
    A_LEVEL_FOUR  = 4,
};

enum ActorIcon
{
    ACTOR_ICON   = 10,
    ACTOR_SCORE  = 11,
    ACTOR_TARGET = 12,
};

class GRActorLayer : public Layer
{
public:
    static GRActorLayer* create();
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    static GRActorLayer* getInstance(void);
    
    Vector<Sprite*> getActors(void);
    
    void setCurrentActorLevel(int level);
    int getCurrentActorLevel(void);
    
    void setCurrentActorScore(void);
    int getCurrentActorScore(void);
    
    void setTargetMeteoriteNumber(void);
    void updateTargetMeteoriteNumber(void);
    
    void updataArmature(int level);
    
private:
    /// 初始化演员
    void initActor(void);
    
    void initAnimation(void);
    
    /// 检查演员边界
    void checkBoard(float time);
    
private:
    Size gameSize;
    
    int actorMoveSpeed;
    
    int touchArea;
    
    Vector<Sprite*> actorVector;
    
    static GRActorLayer* sharedActor;
    
    int currentActorLevel;
    
    int currentActorScore;
    
    int targetMeteoriteNumber;
    
    LabelBMFont* scoreItem;
    
    LabelBMFont* targetItem;
};

#endif
