//
//  GRStoryFiveScene.cpp
//  Gravity
//
//
//

#include "GRStoryFiveScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRStoryFiveScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRStoryFiveScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRStoryFiveScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRStoryFiveScene::startLoading), 3.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRStoryFiveScene::initWidget(void)
{
    if (!system("publish/Story5UI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/Story5UI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRStoryFiveScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRStoryFiveScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_LOGIN);
}
