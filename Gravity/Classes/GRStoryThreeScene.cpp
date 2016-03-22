//
//  GRStoryThreeScene.cpp
//  Gravity
//
//
//

#include "GRStoryThreeScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRStoryThreeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRStoryThreeScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRStoryThreeScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRStoryThreeScene::startLoading), 3.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRStoryThreeScene::initWidget(void)
{
    if (!system("publish/Story3UI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/Story3UI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRStoryThreeScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRStoryThreeScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_STORY_FOUR);
}
