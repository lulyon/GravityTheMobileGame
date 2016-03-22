//
//  GameScene.cpp
//  GravityTemplate
//
//
//

#include "GRWormholeScene.h"

#include "SimpleAudioEngine.h"

//----------------------------------------------------------------------------------------------------
Scene* GRWormholeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer =  GRWormholeScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRWormholeScene::init()
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
void GRWormholeScene::initWidget(void)
{
    // 添加背景到场景中
    this->addBackground();
    
    // 添加分数文本
    this->actorScoreLabel = LabelTTF::create("Hello World", "Arial", 36);
    this->actorScoreLabel->setColor(Color3B(255, 255, 255));
    this->actorScoreLabel->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    this->actorScoreLabel->setPosition(Point(this->gameSize.width-20, this->gameSize.height-20));
    this->addChild(this->actorScoreLabel);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("publish/audio/background.mp3");
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::initProps(void)
{
    //auto actorLayer = GRActorLayer::create();
    auto starLayer = GRStarLayer::create();
    this->pStarLayer = starLayer;
    
    auto blackholeLayer = GRBlackholeLayer::create();
    this->pBlackholeLayer = blackholeLayer;
    
    auto levelOneMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelOneMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_ONE);
    this->pLevelOneMeteoriteLayer = levelOneMeteoriteLayer;
    
    auto levelTwoMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelTwoMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_TWO);
    this->pLevelTwoMeteoriteLayer = levelTwoMeteoriteLayer;
    
    auto levelThreeMeteoriteLayer = GRLevelMeteoriteLayer::create();
    levelThreeMeteoriteLayer->setCurrentMeteoriteLevel(MeteoriteLevel::M_LEVEL_THREE);
    this->pLevelThreeMeteoriteLayer = levelThreeMeteoriteLayer;
    
    this->addChild(starLayer);
    this->addChild(blackholeLayer);
    this->addChild(levelOneMeteoriteLayer);
    this->addChild(levelTwoMeteoriteLayer);
    this->addChild(levelThreeMeteoriteLayer);
    
    this->addChild(GRActorLayer::getInstance());
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::initCallback(void)
{
    // 每帧调用以下函数
    this->schedule(schedule_selector(GRWormholeScene::backgroundMoving));
    this->schedule(schedule_selector(GRWormholeScene::checkCollision));
    this->schedule(schedule_selector(GRWormholeScene::addStarsCallback), 5.0f);
    //this->schedule(schedule_selector(GRWormholeScene::addBlackholeCallback), 15.0f);
    this->schedule(schedule_selector(GRWormholeScene::addLevelOneMeteoriteCallback), 5.0f);
    this->schedule(schedule_selector(GRWormholeScene::addLevelTwoMeteoriteCallback), 8.0f);
    this->schedule(schedule_selector(GRWormholeScene::addLevelThreeMeteoriteCallback), 10.0f);
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GRWormholeScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::checkCollision(float time)
{
    this->pStarLayer->handleCollision();
    //this->pBlackholeLayer->handleCollision();
    
    this->pLevelOneMeteoriteLayer->handleCollision();
    this->pLevelTwoMeteoriteLayer->handleCollision();
    this->pLevelThreeMeteoriteLayer->handleCollision();
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addStarsCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pStarLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addBlackholeCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pBlackholeLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addLevelOneMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelOneMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addLevelTwoMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelTwoMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addLevelThreeMeteoriteCallback(float time)
{
    int location = this->getComfortableLocation();
    this->pLevelThreeMeteoriteLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::addSpaceshipCallback(float time)
{
    //int location = this->getComfortableLocation();
    //this->pSpaceshipLayer->addProps(location);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    Director::getInstance()->end();
}

//----------------------------------------------------------------------------------------------------
int GRWormholeScene::getComfortableLocation(void)
{
    int location = 0;
    int delta = this->gameSize.width/6;
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
void GRWormholeScene::addBackground(void)
{
    if (!system("publish/image/background/gameBackground.png")) return;
    
    // 添加背景图像A
    auto backgroundSpriteA = Sprite::create("publish/image/background/wormholeBackground.png");
    backgroundSpriteA->setTag(WBackgroundTag::W_BACKGROUND_A);
    backgroundSpriteA->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    backgroundSpriteA->setPosition(Point(this->gameSize.width/2, this->gameSize.height));
    this->addChild(backgroundSpriteA);
    
    // 添加背景图像B
    auto backgroundSpriteB = Sprite::create("publish/image/background/wormholeBackground.png");
    backgroundSpriteB->setTag(WBackgroundTag::W_BACKGROUND_B);
    backgroundSpriteB->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    backgroundSpriteB->setPosition(Point(this->gameSize.width/2, this->gameSize.height));
    this->addChild(backgroundSpriteB);
}

//----------------------------------------------------------------------------------------------------
void GRWormholeScene::backgroundMoving(float time)
{
    this->actorMoveScore += this->backgroundMovingSpeed/8;
    
    Sprite* pBackgroundA = static_cast<Sprite*>(this->getChildByTag(WBackgroundTag::W_BACKGROUND_A));
    Sprite* pBackgroundB = static_cast<Sprite*>(this->getChildByTag(WBackgroundTag::W_BACKGROUND_B));
    
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