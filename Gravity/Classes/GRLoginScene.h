//
//  GRLoginScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRLoginScene_h
#define Gravity_GRLoginScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRLoginScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRLoginScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
    void initWidget(void);
    void initCallback(void);
    void wechatButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void qqButtonCallback(ObjectFactory* pSender, TouchEventType type);
    
private:
    Widget* loginUI;
    
    Button* wechatButton;
    Button* qqButton;
};

#endif
