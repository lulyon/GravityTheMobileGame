//
//  GRPropBaseLayer.h
//  Gravity
//
//
//

#ifndef GravityTemplate_GRPropBaseLayer_h
#define GravityTemplate_GRPropBaseLayer_h

#include "cocos2d.h"
USING_NS_CC;

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "GRActorLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRPropBaseLayer : public Layer
{
public:
    GRPropBaseLayer();
    virtual ~GRPropBaseLayer();
    
    static GRPropBaseLayer* create();
    
    virtual bool init();
    
    /// 添加道具
    virtual void addProps(int location);
    /// 处理碰撞检测逻辑
    virtual void handleCollision(void);
    
protected:
    /// 初始化道具动画
    virtual void initAnimation(void);
    
    /// 碰撞检测
    virtual bool checkCollision(void);
    
    virtual bool isIntersected(Point p1, float r1, Point p2, float r2);
    
    virtual void handleCollisionProp(Sprite* sprite);
    
    /// 移除道具
    virtual void removeProps(Node* pNode);
    
protected:
    Size gameSize;
    Vector<Sprite*> actorVector;
    Vector<Sprite*> propVector;

};


#endif
