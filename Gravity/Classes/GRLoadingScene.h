//
//  GRLoadingScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRLoadingScene_h
#define Gravity_GRLoadingScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


class GRLoadingScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRLoadingScene);

private:
    void initWidget(void);
    void initAudio(void);
    void startLoading(float time);
};

#endif
