//
//  GRLevelMeteoriteLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRLevelMeteoriteLayer_h
#define GravityTemplate_GRLevelMeteoriteLayer_h

#include "GRPropBaseLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

enum MeteoriteLevel
{
    M_LEVEL_ONE   = 1,
    M_LEVEL_TWO   = 2,
    M_LEVEL_THREE = 3,
};

class GRLevelMeteoriteLayer : public GRPropBaseLayer
{
public:
    static GRLevelMeteoriteLayer* create();
    
    virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    
    virtual void handleCollision(void);
    
    void setCurrentMeteoriteLevel(int level);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
    virtual bool checkCollision(void);
    
protected:
    int currentMeteoriteLevel;
    
    std::string animationString;
    
    int eatNumbers;
    
    int targetNumbers;
    
};


#endif
