//
//  GRStoryOneScene.cpp
//  Gravity
//
//
//

#include "GRStoryOneScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRStoryOneScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRStoryOneScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRStoryOneScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRStoryOneScene::startLoading), 3.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRStoryOneScene::initWidget(void)
{
    if (!system("publish/Story1UI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/Story1UI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRStoryOneScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRStoryOneScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_STORY_TWO);
}
