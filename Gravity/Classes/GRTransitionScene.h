//
//  GRTransitionScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRTransitionScene_h
#define Gravity_GRTransitionScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


class GRTransitionScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRTransitionScene);

private:
    void initWidget(void);
    void startLoading(float time);
};

#endif
