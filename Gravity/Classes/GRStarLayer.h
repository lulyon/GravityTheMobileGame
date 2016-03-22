//
//  GRStarLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRStarLayer_h
#define GravityTemplate_GRStarLayer_h

#include "GRPropBaseLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRStarLayer : public GRPropBaseLayer
{
public:
    static GRStarLayer* create();
    
    //virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    
    virtual void handleCollision(void);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
protected:

};


#endif
