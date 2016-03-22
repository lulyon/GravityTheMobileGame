//
//  GRStoryThreeScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRStoryThreeScene_h
#define Gravity_GRStoryThreeScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


class GRStoryThreeScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRStoryThreeScene);

private:
    void initWidget(void);
    void startLoading(float time);
};

#endif