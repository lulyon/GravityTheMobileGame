//
//  GRLoginScene.cpp
//  Gravity
//
//
//

#include "GRLoginScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRLoginScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRLoginScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRLoginScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->loginUI = NULL;
    
    this->initWidget();
    
    this->initCallback();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRLoginScene::initWidget(void)
{
    if (!system("publish/LoginUI.json")) return;
    this->loginUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/LoginUI.json");
    if(!this->loginUI) return;
    this->addChild(this->loginUI);
}

//----------------------------------------------------------------------------------------------------
void GRLoginScene::initCallback(void)
{
    this->wechatButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->loginUI, "wechatButton"));
    if (this->wechatButton)
    {
      this->wechatButton->addTouchEventListener(this, toucheventselector(GRLoginScene::wechatButtonCallback));
    }
    
    this->qqButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->loginUI, "qqButton"));
    if (this->qqButton)
    {
       this->qqButton->addTouchEventListener(this, toucheventselector(GRLoginScene::qqButtonCallback));
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GRLoginScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------------------------------------------------------
void GRLoginScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
void GRLoginScene::wechatButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type) {
        // 添加点击按钮音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_OPERATOR);
    }
}

//----------------------------------------------------------------------------------------------------
void GRLoginScene::qqButtonCallback(ObjectFactory* pSender, TouchEventType type)
{
    if (TOUCH_EVENT_BEGAN == type) {
        // 添加点击按钮音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/clickButton.mp3");
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_ACCOUNT);
    }
}
