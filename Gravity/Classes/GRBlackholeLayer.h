//
//  GRBlackholeLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRBlackholeLayer_h
#define GravityTemplate_GRBlackholeLayer_h

#include "GRPropBaseLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

enum BlackholeTag
{
    Black_Hole = 10,
};

class GRBlackholeLayer : public GRPropBaseLayer
{
public:
    static GRBlackholeLayer* create();
    
    //virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    
    virtual void handleCollision(void);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
    /// 碰撞检测
    virtual bool checkCollision(void);
    
    virtual void attractActor(void);
    
protected:
    int attractSpeed;
};


#endif
