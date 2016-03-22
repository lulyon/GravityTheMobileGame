//
//  GRStoryFourScene.cpp
//  Gravity
//
//
//

#include "GRStoryFourScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRStoryFourScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRStoryFourScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRStoryFourScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRStoryFourScene::startLoading), 3.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRStoryFourScene::initWidget(void)
{
    if (!system("publish/Story4UI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/Story4UI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRStoryFourScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRStoryFourScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_STORY_FIVE);
}
