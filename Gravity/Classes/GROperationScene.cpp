//
//  GROperationScene.cpp
//  Gravity
//
//
//

#include "GROperationScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GROperationScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GROperationScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GROperationScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->operatorUI = NULL;
    
    this->initWidget();
    
    this->initCallback();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::initWidget(void)
{
    if (!system("publish/LoginUI.json")) return;
    this->operatorUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/OperatorUI.json");
    if(!this->operatorUI) return;
    this->addChild(this->operatorUI);
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::initCallback(void)
{
    if (!this->operatorUI) return;
    
    Button* playButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->operatorUI, "playButton"));
    if (playButton) playButton->addTouchEventListener(this, toucheventselector(GROperationScene::playButtonCallback));
    
    Button* actorSelectButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->operatorUI, "actorSelectButton"));
    if (actorSelectButton) actorSelectButton->addTouchEventListener(this, toucheventselector(GROperationScene::actorSelectButtonCallback));
    
    Button* settingButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->operatorUI, "settingButton"));
    if (settingButton) settingButton->addTouchEventListener(this, toucheventselector(GROperationScene::settingButtonCallback));
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GROperationScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::playButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_START);
    }
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::actorSelectButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ACTOR_SELECT);
    }
}

//----------------------------------------------------------------------------------------------------
void GROperationScene::settingButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_SETTING);
    }
}
