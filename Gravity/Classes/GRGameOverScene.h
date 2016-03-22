//
//  GRGameOverScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRGameOverScene_h
#define Gravity_GRGameOverScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRGameOverScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRGameOverScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
    void initWidget(void);
    void initCallback(void);
    void trayAgainButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void addFriendButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void backButtonCallback(ObjectFactory* pSender, TouchEventType type);
    
private:
    Widget* gameOverUI;

};

#endif
