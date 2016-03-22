//
//  GRStoryTwoScene.cpp
//  Gravity
//
//
//

#include "GRStoryTwoScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRStoryTwoScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRStoryTwoScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRStoryTwoScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRStoryTwoScene::startLoading), 3.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRStoryTwoScene::initWidget(void)
{
    if (!system("publish/Story2UI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/Story2UI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRStoryTwoScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRStoryTwoScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_STORY_THREE);
}
