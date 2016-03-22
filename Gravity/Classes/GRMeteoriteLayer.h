//
//  GRMeteoriteLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRMeteoriteLayer_h
#define GravityTemplate_GRMeteoriteLayer_h

#include "GRPropBaseLayer.h"

class GRMeteoriteLayer : public GRPropBaseLayer
{
public:
    static GRMeteoriteLayer* create();
    
    //virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    
    virtual void handleCollision(void);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
    virtual bool checkCollision(void);
};


#endif
