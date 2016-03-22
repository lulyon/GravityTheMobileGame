//
//  GROperationScene.h
//  Gravity
//
//
//

#ifndef Gravity_GROperationScene_h
#define Gravity_GROperationScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GROperationScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GROperationScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
private:
    void initWidget(void);
    void initCallback(void);

    void actorSelectButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void settingButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void playButtonCallback(ObjectFactory* pSender, TouchEventType type);
    
private:
    Widget* operatorUI;
    
};

#endif
