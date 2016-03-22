//
//  GRTransitionScene.cpp
//  Gravity
//
//
//

#include "GRTransitionScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRTransitionScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRTransitionScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRTransitionScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->schedule(schedule_selector(GRTransitionScene::startLoading), 4.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRTransitionScene::initWidget(void)
{
    if (!system("publish/LoadingUI.json")) return;
    Widget* loadingUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("publish/LoadingUI.json");
    if(!loadingUI) return;
    this->addChild(loadingUI);
    
    // 添加加载按钮
    Size gameSize = Director::getInstance()->getWinSize();
    auto loadButtonSprite = Sprite::create("publish/image/buttons/loadingButton.png");
    loadButtonSprite->setTag(2);
    loadButtonSprite->setPosition(Point(gameSize.width/2, gameSize.height*2/3));
    this->addChild(loadButtonSprite);
    loadButtonSprite->runAction(RotateBy::create(3.0f, 720));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRTransitionScene::startLoading(float time)
{
    this->unschedule(schedule_selector(GRTransitionScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_WORMHOLE);
}
