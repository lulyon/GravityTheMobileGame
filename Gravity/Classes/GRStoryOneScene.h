//
//  GRStoryOneScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRStoryOneScene_h
#define Gravity_GRStoryOneScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


class GRStoryOneScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRStoryOneScene);

private:
    void initWidget(void);
    void startLoading(float time);
};

#endif
