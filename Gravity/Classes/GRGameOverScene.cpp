//
//  GRGameOverScene.cpp
//  Gravity
//
//
//

#include "GRGameOverScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRGameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRGameOverScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRGameOverScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->initCallback();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::initWidget(void)
{
    if (!system("publish/GameOverUI.json")) return;
    this->gameOverUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/GameOverUI.json");
    if(!this->gameOverUI) return;
    this->addChild(this->gameOverUI);
}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::initCallback(void)
{
    Button* backButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->gameOverUI, "backButton"));
    if (backButton) backButton->addTouchEventListener(this, toucheventselector(GRGameOverScene::backButtonCallback));

    Button* trayAgainButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->gameOverUI, "trayAgainButton"));
    if (trayAgainButton) trayAgainButton->addTouchEventListener(this, toucheventselector(GRGameOverScene::trayAgainButtonCallback));

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GRGameOverScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::backButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_OPERATOR);
    }
}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::trayAgainButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_START);
    }
}

//----------------------------------------------------------------------------------------------------
void GRGameOverScene::addFriendButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type) {
        // 添加点击按钮音乐
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_OPERATOR);
    }
}
