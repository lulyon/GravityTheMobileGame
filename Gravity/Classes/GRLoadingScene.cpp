//
//  GRLoadingScene.cpp
//  Gravity
//
//
//

#include "GRLoadingScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRLoadingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRLoadingScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRLoadingScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initWidget();
    
    this->initAudio();
    
    this->schedule(schedule_selector(GRLoadingScene::startLoading), 2.0f);
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRLoadingScene::initWidget(void)
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
    loadButtonSprite->runAction(RotateBy::create(2.0f, 720));    
}

//----------------------------------------------------------------------------------------------------
void GRLoadingScene::initAudio(void)
{
    /*std::vector<std::string> pathString;
    pathString.push_back("image/star");
    pathString.push_back("image/actorAnimation");
    FileUtils::getInstance()->setSearchPaths(pathString);*/
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/gameBackground.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/clickButton.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/eat.mp3");
    
    // 星星动画
    auto starAnimation = Animation::create();
    starAnimation->addSpriteFrameWithFile("publish/image/star/star1.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star2.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star3.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star4.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star5.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star6.png");
    starAnimation->addSpriteFrameWithFile("publish/image/star/star7.png");
    starAnimation->setRestoreOriginalFrame(true);
    starAnimation->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(starAnimation, "StarAnimation");
    
    // 演员动画零
    auto animation0 = Animation::create();
    animation0->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation0_1.png");
    animation0->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation0_2.png");
    animation0->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation0_3.png");
    animation0->setRestoreOriginalFrame(true);
    animation0->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(animation0, "ActorAnimation0");
    
    // 演员动画一
    auto animation1 = Animation::create();
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_1.png");
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_2.png");
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_3.png");
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_4.png");
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_5.png");
    animation1->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation1_6.png");
    animation1->setRestoreOriginalFrame(true);
    animation1->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(animation1, "ActorAnimation1");
    
    auto animation2 = Animation::create();
    animation2->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation2_1.png");
    animation2->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation2_2.png");
    animation2->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation2_3.png");
    animation2->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation2_4.png");
    animation2->setRestoreOriginalFrame(true);
    animation2->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(animation2, "ActorAnimation2");
    
    auto animation3 = Animation::create();
    animation3->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation3_1.png");
    animation3->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation3_2.png");
    animation3->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation3_3.png");
    animation3->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation3_4.png");
    animation3->setRestoreOriginalFrame(true);
    animation3->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(animation3, "ActorAnimation3");
    
    auto animation4 = Animation::create();
    animation4->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation4_1.png");
    animation4->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation4_2.png");
    animation4->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation4_3.png");
    animation4->addSpriteFrameWithFile("publish/image/actorAnimation/actorAnimation4_4.png");
    animation4->setRestoreOriginalFrame(true);
    animation4->setDelayPerUnit(0.1f);
    AnimationCache::getInstance()->addAnimation(animation4, "ActorAnimation4");
    
    float animationDelay = 0.2f;
    
    // 一级陨石
    auto levelMeteoriteAnimation1Eat = Animation::create();
    levelMeteoriteAnimation1Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite1/levelMeteorite1_1.png");
    levelMeteoriteAnimation1Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite1/levelMeteorite1_2.png");
    levelMeteoriteAnimation1Eat->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation1Eat->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation1Eat, "LevelMeteoriteAnimation1Eat");
    
    auto levelMeteoriteAnimation1No = Animation::create();
    levelMeteoriteAnimation1No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite1/levelMeteorite1_3.png");
    levelMeteoriteAnimation1No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite1/levelMeteorite1_4.png");
    levelMeteoriteAnimation1No->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation1No->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation1No, "LevelMeteoriteAnimation1No");
    
    // 二级陨石
    auto levelMeteoriteAnimation2Eat = Animation::create();
    levelMeteoriteAnimation2Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite2/levelMeteorite2_1.png");
    levelMeteoriteAnimation2Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite2/levelMeteorite2_2.png");
    levelMeteoriteAnimation2Eat->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation2Eat->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation2Eat, "LevelMeteoriteAnimation2Eat");
    
    auto levelMeteoriteAnimation2No = Animation::create();
    levelMeteoriteAnimation2No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite2/levelMeteorite2_3.png");
    levelMeteoriteAnimation2No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite2/levelMeteorite2_4.png");
    levelMeteoriteAnimation2No->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation2No->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation2No, "LevelMeteoriteAnimation2No");
    
    // 三级陨石
    auto levelMeteoriteAnimation3Eat = Animation::create();
    levelMeteoriteAnimation3Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite3/levelMeteorite3_1.png");
    levelMeteoriteAnimation3Eat->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite3/levelMeteorite3_2.png");
    levelMeteoriteAnimation3Eat->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation3Eat->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation3Eat, "LevelMeteoriteAnimation3Eat");
    
    auto levelMeteoriteAnimation3No = Animation::create();
    levelMeteoriteAnimation3No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite3/levelMeteorite3_3.png");
    levelMeteoriteAnimation3No->addSpriteFrameWithFile("publish/image/levelMeteoriteAnimation/levelMeteorite3/levelMeteorite3_4.png");
    levelMeteoriteAnimation3No->setRestoreOriginalFrame(true);
    levelMeteoriteAnimation3No->setDelayPerUnit(animationDelay);
    AnimationCache::getInstance()->addAnimation(levelMeteoriteAnimation3No, "LevelMeteoriteAnimation3No");

}

//----------------------------------------------------------------------------------------------------
void GRLoadingScene::startLoading(float time)
{
    this->getChildByTag(2)->setVisible(false);
    this->unschedule(schedule_selector(GRLoadingScene::startLoading));
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_LOGIN);
}
