//
//  GRStoryTwoScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRStoryTwoScene_h
#define Gravity_GRStoryTwoScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


class GRStoryTwoScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRStoryTwoScene);

private:
    void initWidget(void);
    void startLoading(float time);
};

#endif
