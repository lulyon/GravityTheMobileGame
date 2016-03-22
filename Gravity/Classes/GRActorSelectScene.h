//
//  GRActorSelectScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRActorSelectScene_h
#define Gravity_GRActorSelectScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

enum ActorType
{
    Actor_1 = 1,
    Actor_2 = 2,
    Actor_3 = 3,
    Actor_4 = 4,
    Actor_5 = 5,
    Actor_6 = 6,
    Actor_7 = 7,
};

class GRActorSelectScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRActorSelectScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
    void initWidget(void);
    void initCallback(void);
    void lastButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void nextButtonCallback(ObjectFactory* pSender, TouchEventType type);
    void selectActorCallback(ObjectFactory* pSender, TouchEventType type);
    void changeActorType(void);
    
private:
    Widget* actorSelectUI;
    int currentActorType;
    std::string actorImageString;
    std::string actorTextString;
};

#endif
