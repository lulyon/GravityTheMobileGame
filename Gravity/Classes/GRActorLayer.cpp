//
//  GRActorLayer.cpp
//  Gravity
//
//
//

#include "GRActorLayer.h"

GRActorLayer* GRActorLayer::sharedActor = NULL;

//----------------------------------------------------------------------------------------------------
GRActorLayer* GRActorLayer::create()
{
    GRActorLayer* layer = new GRActorLayer;
    if (layer && layer->init()) {
        //layer->autorelease();
        sharedActor = layer;
        return layer;
    }
    else
    {
        CC_SAFE_DELETE(layer);
        return NULL;
    }
}

//----------------------------------------------------------------------------------------------------
bool GRActorLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initAnimation();
    
    this->initActor();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::initActor(void)
{
    this->gameSize = Director::getInstance()->getWinSize();
    this->actorMoveSpeed = 20;
    this->currentActorLevel = ActorLevel::A_LEVEL_ONE;
    this->currentActorScore = 0;
    this->targetMeteoriteNumber = 2;
    
    // 添加演员
    auto sprite = Sprite::create("publish/image/actorAnimation/actorAnimation1_1.png");
    sprite->setPosition(Point(this->gameSize.width/2, this->gameSize.height*4/5));
    sprite->setScale(0.4f);
    sprite->setTag(ActorTag::SPACE_MAN);
    this->addChild(sprite);
    this->actorVector.pushBack(sprite);
    
    auto animateAction = Animate::create(AnimationCache::getInstance()->getAnimation("ActorAnimation1"));
    sprite->runAction(RepeatForever::create(animateAction));
    
    // 添加图标
    auto iconSprite = Sprite::create("publish/image/actorAnimation/actorAnimation2_1.png");
    iconSprite->setPosition(Point(45, this->gameSize.height-45));
    iconSprite->setTag(ActorIcon::ACTOR_ICON);
    iconSprite->setScale(0.2f);
    this->addChild(iconSprite);
    
    // 添加星星分数图标
    auto starScoreSprite = Sprite::create("publish/image/star/star1.png");
    starScoreSprite->setPosition(Point(this->gameSize.width - 125, this->gameSize.height-45));
    starScoreSprite->setScale(0.8f);
    this->addChild(starScoreSprite);
    
    // 添加星星分数
    this->scoreItem=LabelBMFont::create("0","fonts/font.fnt");
	this->scoreItem->setColor(Color3B(255,255,0));
	this->scoreItem->setPosition(Point(this->gameSize.width - 50,this->gameSize.height-45));
	this->addChild(this->scoreItem);
    this->scoreItem->setTag(ActorIcon::ACTOR_SCORE);
    String* scoreString=String::createWithFormat("%d",0);
    this->scoreItem->setString(scoreString->getCString());
    
    // 添加目标数量
    this->targetItem=LabelBMFont::create("0","fonts/font.fnt");
	this->targetItem->setColor(Color3B(255,255,0));
	this->targetItem->setPosition(Point(100,this->gameSize.height-45));
	this->addChild(this->targetItem);
    this->scoreItem->setTag(ActorIcon::ACTOR_TARGET);
    String* targetString=String::createWithFormat("%d",this->targetMeteoriteNumber);
    this->targetItem->setString(targetString->getCString());
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::onEnter()
{
    Layer::onEnter();
    this->schedule(schedule_selector(GRActorLayer::checkBoard));
    
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GRActorLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GRActorLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GRActorLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//----------------------------------------------------------------------------------------------------
GRActorLayer* GRActorLayer::getInstance(void)
{
    return sharedActor;
}

//----------------------------------------------------------------------------------------------------
Vector<Sprite*> GRActorLayer::getActors(void)
{
    return this->actorVector;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::setCurrentActorLevel(int level)
{
    if (level >= 0) this->currentActorLevel = level;
    this->updataArmature(level);
}

//----------------------------------------------------------------------------------------------------
int GRActorLayer::getCurrentActorLevel(void)
{
    return this->currentActorLevel;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::setCurrentActorScore(void)
{
    String* scoreString=String::createWithFormat("%d",++this->currentActorScore);
    this->scoreItem->setString(scoreString->getCString());
}

//----------------------------------------------------------------------------------------------------
int GRActorLayer::getCurrentActorScore(void)
{
    return this->currentActorScore;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::setTargetMeteoriteNumber(void)
{
    switch (this->currentActorLevel) {
        case 1  : this->targetMeteoriteNumber = 2;
                  break;
        case 2  : this->targetMeteoriteNumber = 4;
                  break;
        case 3  : this->targetMeteoriteNumber = 6;
                  break;
        default : break;
    }
    
    String* targetString=String::createWithFormat("%d",this->targetMeteoriteNumber);
    this->targetItem->setString(targetString->getCString());
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::updateTargetMeteoriteNumber(void)
{
    if (this->targetMeteoriteNumber > 0) {
        String* targetString=String::createWithFormat("%d",--this->targetMeteoriteNumber);
        this->targetItem->setString(targetString->getCString());
    }
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::updataArmature(int level)
{
    Sprite* iconSprite = dynamic_cast<Sprite*>(this->getChildByTag(ActorIcon::ACTOR_ICON));
    std::string actorString;
    switch (level)
    {
        case 0  : actorString = "ActorAnimation0";
                  break;
        case 1  : actorString = "ActorAnimation1";
                  iconSprite->setTexture("publish/image/actorAnimation/actorAnimation2_1.png");
                  break;
        case 2  : actorString = "ActorAnimation2";
                  iconSprite->setTexture("publish/image/actorAnimation/actorAnimation3_1.png");
                  break;
        case 3  : actorString = "ActorAnimation3";
                  iconSprite->setTexture("publish/image/actorAnimation/actorAnimation4_1.png");
                  break;
        case 4  : actorString = "ActorAnimation4";
                  break;
        default : break;
    }
    
    for (auto& actorSprite : this->actorVector)
    {
        actorSprite->stopAllActions();
        auto animateAction = Animate::create(AnimationCache::getInstance()->getAnimation(actorString));
        actorSprite->runAction(RepeatForever::create(animateAction));
    }
    
    /*Vector<Sprite*> tempVector;
    for (auto& actorSprite : this->actorVector)
    {
        auto armature = Armature::create(actorString);
        armature->getAnimation()->playByIndex(0);
        armature->setScale(0.5);
        armature->setPosition(actorArmature->getPosition());
        actorArmature->setVisible(false);
        this->addChild(armature);
        tempVector.pushBack(armature);
    }*/
    
}

//----------------------------------------------------------------------------------------------------
bool GRActorLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
    if (this->currentActorLevel == ActorLevel::A_LEVEL_OVER) return false;
    
    Armature* sprite = static_cast<Armature*>(this->getChildByTag(ActorTag::SPACE_MAN));
    Point touchPoint = touch->getLocation();
    
    if (touchPoint.y <= this->gameSize.height/6)
    {
        if (touchPoint.x < this->gameSize.width/2)
        {
            this->touchArea = TouchArea::TOUCH_LEFT;
            sprite->runAction(MoveBy::create(0.2, Point(-this->actorMoveSpeed, 0)));
            
        }
        else
        {
            this->touchArea = TouchArea::TOUCH_RIGHT;
            sprite->runAction(MoveBy::create(0.2, Point(this->actorMoveSpeed, 0)));
        }
        return true;
    }
    else return false;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (this->currentActorLevel == ActorLevel::A_LEVEL_OVER) return;
    
    Armature* sprite = static_cast<Armature*>(this->getChildByTag(ActorTag::SPACE_MAN));
    
    if (this->touchArea == TouchArea::TOUCH_LEFT)
        sprite->runAction(MoveBy::create(0.2, Point(-this->actorMoveSpeed, 0)));
    else if (this->touchArea == TouchArea::TOUCH_RIGHT)
        sprite->runAction(MoveBy::create(0.2, Point(this->actorMoveSpeed, 0)));
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    this->touchArea = TouchArea::TOUCH_NULL;
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::initAnimation(void)
{
    
}

//----------------------------------------------------------------------------------------------------
void GRActorLayer::checkBoard(float time)
{
    int actorLocationX = this->getChildByTag(ActorTag::SPACE_MAN)->getPositionX();
    int actorSizeWidth = this->getChildByTag(ActorTag::SPACE_MAN)->getBoundingBox().getMaxX() -this->getChildByTag(ActorTag::SPACE_MAN)->getBoundingBox().getMinX();
     
    if (actorLocationX < actorSizeWidth/2) actorLocationX = actorSizeWidth/2;
    else if (actorLocationX > this->gameSize.width - actorSizeWidth/2) actorLocationX = this->gameSize.width - actorSizeWidth/2;
     
    this->getChildByTag(ActorTag::SPACE_MAN)->setPositionX(actorLocationX);
}
