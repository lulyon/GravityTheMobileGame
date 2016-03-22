//
//  GRGameScene.cpp
//  GravityTemplate
//
//
//

#include "GRGameScene.h"
#include "GRMessageInfo.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRGameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer =  GRGameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRGameScene::init()
{
    if (!Layer::create()) {
        return false;
    }
    
    this->actorMoveScore = 0;
    this->backgroundMovingSpeed = 8;
    this->gameSize = Director::getInstance()->getWinSize();
    this->currentLocation = this->gameSize.width/2;
    
    this->initWidget();
    
    this->initProps();
    
    this->initCallback();

    return true;
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::initWidget(void)
{
    // 添加背景到场景中
    this->addBackground();
    
    // 添加分数文本
    this->actorScoreLabel = LabelTTF::create("Hello World", "Arial", 36);
    this->actorScoreLabel->setColor(Color3B(255, 255, 255));
    this->actorScoreLabel->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    this->actorScoreLabel->setPosition(Point(this->gameSize.width-20, this->gameSize.height-80));
    this->addChild(this->actorScoreLabel);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/gameBackground.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::initProps(void)
{
    // 演员
    auto actorLayer = GRActorLayer::create();
    
    // 星星
    auto starLayer = GRStarLayer::create();
    this->pStarLayer = starLayer;
    
    // 普通陨石
    auto meteoriteLayer = GRMeteoriteLayer::create();
    this->pMeteoriteLayer = meteoriteLayer;
    
    // 黑洞
    auto blackholeLayer = GRBlackholeLayer::create();
    this->pBlackholeLayer = blackholeLayer;
    
    // 虫洞
    auto wormholeLayer = GRWormholeLayer::create();
    this->pWormholeLayer = wormholeLayer;
    
    // 升级陨石一
    auto levelOneMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelOneMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_ONE);
    this->pLevelOneMeteoriteLayer = levelOneMeteoriteLayer;
    
    // 升级陨石二
    auto levelTwoMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelTwoMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_TWO);
    this->pLevelTwoMeteoriteLayer = levelTwoMeteoriteLayer;
    
    // 升级陨石三
    auto levelThreeMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelThreeMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_THREE);
    this->pLevelThreeMeteoriteLayer = levelThreeMeteoriteLayer;
    
    // 将各种道具加入场景
    this->addChild(starLayer);
    this->addChild(meteoriteLayer);
    this->addChild(blackholeLayer);
    this->addChild(wormholeLayer);
    this->addChild(levelOneMeteoriteLayer);
    this->addChild(levelTwoMeteoriteLayer);
    this->addChild(levelThreeMeteoriteLayer);
    
    this->addChild(actorLayer);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::initCallback(void)
{
    // 每帧调用以下函数
    this->schedule(schedule_selector(GRGameScene::backgroundMoving));
    this->schedule(schedule_selector(GRGameScene::checkCollision));
    
    this->schedule(schedule_selector(GRGameScene::addStarsCallback), 3.0f);
    this->schedule(schedule_selector(GRGameScene::addMeteoriteCallback), 5.0f);
    
    this->schedule(schedule_selector(GRGameScene::addLevelOneMeteoriteCallback), 6.0f);
    this->schedule(schedule_selector(GRGameScene::addLevelTwoMeteoriteCallback), 8.0f);
    this->schedule(schedule_selector(GRGameScene::addLevelThreeMeteoriteCallback), 10.0f);
    
    this->schedule(schedule_selector(GRGameScene::addBlackholeCallback), 15.0f);
    this->schedule(schedule_selector(GRGameScene::addWormholeCallback), 5.0f);
    
    // 添加保存场景回调函数
    auto saveSceneListener = EventListenerCustom::create(MES_SAVE_SCENE, CC_CALLBACK_1(GRGameScene::saveCurrentSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(saveSceneListener, 1);
    
    // 添加游戏结束回调函数
    auto gameOverListener = EventListenerCustom::create(MES_GAME_OVER, CC_CALLBACK_1(GRGameScene::handleGameOverSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameOverListener, 1);
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GRGameScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::checkCollision(float time)
{
    this->pStarLayer->handleCollision();
    this->pMeteoriteLayer->handleCollision();
    this->pBlackholeLayer->handleCollision();
    this->pWormholeLayer->handleCollision();
    
    this->pLevelOneMeteoriteLayer->handleCollision();
    this->pLevelTwoMeteoriteLayer->handleCollision();
    this->pLevelThreeMeteoriteLayer->handleCollision();
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addStarsCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pStarLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addBlackholeCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pBlackholeLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addWormholeCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pWormholeLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addLevelOneMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelOneMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addLevelTwoMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelTwoMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addLevelThreeMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelThreeMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::saveCurrentSceneCallback(EventCustom *event)
{
    this->removeChild(GRActorLayer::getInstance());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_TRANSITION);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::handleGameOverSceneCallback(EventCustom *event)
{
    this->unscheduleAllSelectors();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    GRActorLayer::getInstance()->setCurrentActorLevel(ActorLevel::A_LEVEL_OVER);
    this->schedule(schedule_selector(GRGameScene::sendGameOverMessageCallback), 4.0f);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::sendGameOverMessageCallback(float time)
{
    this->unscheduleAllSelectors();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_GAMEOVER);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
int GRGameScene::getComfortableLocation(void)
{
    int location = 0;
    int delta = this->gameSize.width/4;
    int minWidth = 20;
    int minX = minWidth;
    int maxX = this->gameSize.width - minWidth;
    srand(time(0));
    location = (rand()%(maxX-minX)) + minX;
    if (abs(this->currentLocation-location)<delta) {
        if ((location+delta)<this->gameSize.width) {
            location += delta;
        }
        else location -= delta;
    }
    
    this->currentLocation = location;
    return location;
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::addBackground(void)
{
    if (!system("publish/image/background/gameBackground.png")) return;
    
    // 添加背景图像A
    auto backgroundSpriteA = Sprite::create("publish/image/background/gameBackground.png");
    backgroundSpriteA->setTag(BackgroundTag::BACKGROUND_A);
    backgroundSpriteA->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    backgroundSpriteA->setPosition(Point(this->gameSize.width/2, this->gameSize.height));
    this->addChild(backgroundSpriteA);
    
    // 添加背景图像B
    auto backgroundSpriteB = Sprite::create("publish/image/background/gameBackground.png");
    backgroundSpriteB->setTag(BackgroundTag::BACKGROUND_B);
    backgroundSpriteB->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    backgroundSpriteB->setPosition(Point(this->gameSize.width/2, this->gameSize.height));
    this->addChild(backgroundSpriteB);
}

//----------------------------------------------------------------------------------------------------
void GRGameScene::backgroundMoving(float time)
{
    this->actorMoveScore += this->backgroundMovingSpeed/8;
    
    Sprite* pBackgroundA = static_cast<Sprite*>(this->getChildByTag(BackgroundTag::BACKGROUND_A));
    Sprite* pBackgroundB = static_cast<Sprite*>(this->getChildByTag(BackgroundTag::BACKGROUND_B));
    
    if (!pBackgroundA || !pBackgroundB) return;
    
    pBackgroundA->setPositionY(pBackgroundA->getPositionY() + this->backgroundMovingSpeed);
    pBackgroundB->setPositionY(pBackgroundA->getPositionY() - pBackgroundA->getContentSize().height);
    
    Point originPoint = Director::getInstance()->getVisibleOrigin();
    Size  visibleSize = Director::getInstance()->getVisibleSize();
    if (pBackgroundB->getPositionY() >= (originPoint.y + visibleSize.height))
    {
        pBackgroundA->setPositionY(originPoint.y + visibleSize.height);
    }
    
    if ((++this->updateCounts)%5 == 0)
    {
        auto string = String::createWithFormat("%d", this->actorMoveScore);
        this->actorScoreLabel->setString(string->getCString());
    }
}