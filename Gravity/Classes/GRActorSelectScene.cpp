//
//  GRActorSelectScene.cpp
//  Gravity
//
//
//

#include "GRActorSelectScene.h"
#include "GRMessageInfo.h"
#include <string>

#include "../cocos2d/cocos/audio/include/SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRActorSelectScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRActorSelectScene::create();
    
    scene->addChild(layer);
    return scene;
}

//---------------------------------------------------------------------------------------------------
bool GRActorSelectScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->currentActorType = ActorType::Actor_1;
    
    this->initWidget();
    
    this->initCallback();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::initWidget(void)
{
    if (!system("publish/ActorSelectUI.json")) return;
    this->actorSelectUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/ActorSelectUI.json");
    if(!this->actorSelectUI) return;
    this->addChild(this->actorSelectUI);
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::initCallback(void)
{
    if (!this->actorSelectUI) return;
    
    Button* lastButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->actorSelectUI, "lastButton"));
    if (lastButton) lastButton->addTouchEventListener(this, toucheventselector(GRActorSelectScene::lastButtonCallback));
    
    Button* nextButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->actorSelectUI, "nextButton"));
    if (nextButton) nextButton->addTouchEventListener(this, toucheventselector(GRActorSelectScene::nextButtonCallback));
    
    Button* selectActorButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->actorSelectUI, "selectButton"));
    if (selectActorButton) selectActorButton->addTouchEventListener(this, toucheventselector(GRActorSelectScene::selectActorCallback));
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GRActorSelectScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::lastButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        if (this->currentActorType != ActorType::Actor_1)
        {
            this->currentActorType--;
            this->changeActorType();
        }
    }
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::nextButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        if (this->currentActorType != ActorType::Actor_7)
        {
        this->currentActorType++;
        this->changeActorType();
        }
    }
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::selectActorCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_BACK_OPERATION);
    }
}

//----------------------------------------------------------------------------------------------------
void GRActorSelectScene::changeActorType(void)
{
    if ((this->currentActorType<1) || (this->currentActorType>7)) return;
    
    switch (this->currentActorType)
    {
        case 1 : actorImageString = "publish/image/actor/actor1.png";
                 actorTextString =  "publish/image/actor/actorText1.png";
                 break;
        case 2 : actorImageString = "publish/image/actor/actor2.png";
                 actorTextString =  "publish/image/actor/actorText2.png";
                 break;
        case 3 : actorImageString = "publish/image/actor/actor3.png";
                 actorTextString =  "publish/image/actor/actorText3.png";
                 break;
        case 4 : actorImageString = "publish/image/actor/actor4.png";
                 actorTextString =  "publish/image/actor/actorText4.png";
                 break;
        case 5 : actorImageString = "publish/image/actor/actor5.png";
                 actorTextString =  "publish/image/actor/actorText5.png";
                 break;
        case 6 : actorImageString = "publish/image/actor/actor6.png";
                 actorTextString =  "publish/image/actor/actorText6.png";
                 break;
        case 7 : actorImageString = "publish/image/actor/actor7.png";
                 actorTextString =  "publish/image/actor/actorText7.png";
                 break;
        default: break;
    }
    
    ImageView* actorImage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(actorSelectUI, "actorImage"));
    actorImage->loadTexture(actorImageString);
    ImageView* actorText  = dynamic_cast<ImageView*>(Helper::seekWidgetByName(actorSelectUI, "actorText"));
    actorText->loadTexture(actorTextString);
}
