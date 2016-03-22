//
//  GRWormholeLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRWormholeLayer_h
#define GravityTemplate_GRWormholeLayer_h

#include "GRPropBaseLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRWormholeLayer : public GRPropBaseLayer
{
public:
    static GRWormholeLayer* create();
    
    //virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    
    virtual void handleCollision(void);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
    virtual void handleCollisionProp(Sprite* sprite);
    
protected:

};


#endif
