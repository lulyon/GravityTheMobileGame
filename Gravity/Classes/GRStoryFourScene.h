//
//  GRStoryFourScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRStoryFourScene_h
#define Gravity_GRStoryFourScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRStoryFourScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRStoryFourScene);

private:
    void initWidget(void);
    void startLoading(float time);
};

#endif
