//
//  GRBlackholeLayer.cpp
//  Gravity
//
//
//

#include "GRLevelMeteoriteLayer.h"
#include "GRMessageInfo.h"

//----------------------------------------------------------------------------------------------------
GRLevelMeteoriteLayer* GRLevelMeteoriteLayer::create()
{
    GRLevelMeteoriteLayer* layer = new GRLevelMeteoriteLayer;
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else
    {
        CC_SAFE_DELETE(layer);
        return NULL;
    }
}

//----------------------------------------------------------------------------------------------------
bool GRLevelMeteoriteLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->gameSize = Director::getInstance()->getWinSize();
    
    this->currentMeteoriteLevel = MeteoriteLevel::M_LEVEL_ONE;
    this->eatNumbers = 0;
    this->targetNumbers = 0;
    
    //this->initAnimation();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRLevelMeteoriteLayer::initAnimation(void)
{

}

//----------------------------------------------------------------------------------------------------
void GRLevelMeteoriteLayer::addProps(int location)
{
    int actorLevel = GRActorLayer::getInstance()->getCurrentActorLevel();
    if (this->currentMeteoriteLevel <= actorLevel) {
        switch (this->currentMeteoriteLevel) {
            case 1  : break;
            case 2  : this->animationString = "LevelMeteoriteAnimation2Eat";
                      break;
            case 3  : this->animationString = "LevelMeteoriteAnimation3Eat";
                      break;
            default : break;
        }
    }
    else
    {
        switch (this->currentMeteoriteLevel) {
            case 1  : break;
            case 2  : this->animationString = "LevelMeteoriteAnimation2No";
                      break;
            case 3  : this->animationString = "LevelMeteoriteAnimation3No";
                      break;
            default : break;
        }
    }
    
    auto sprite = Sprite::create("publish/image/levelMeteoriteAnimation/levelMeteorite1/levelMeteorite1_1.png");
    sprite->setPosition(Point(location, -sprite->getContentSize().height));
    sprite->setScale(0.8f);
    this->addChild(sprite);
    this->propVector.pushBack(sprite);
    
    auto animateAction = Animate::create(AnimationCache::getInstance()->getAnimation(this->animationString));
    sprite->runAction(RepeatForever::create(animateAction));
    
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(4.0f, Point(sprite->getPositionX(), this->gameSize.height+sprite->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRLevelMeteoriteLayer::removeProps, this));
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    sprite->runAction(sequence);
}

//----------------------------------------------------------------------------------------------------
void GRLevelMeteoriteLayer::setCurrentMeteoriteLevel(int level)
{
    if (level > 0) {
        this->currentMeteoriteLevel = level;
        switch (level) {
            case 1  : this->targetNumbers = 2;
                      this->animationString = "LevelMeteoriteAnimation1Eat";
                      break;
            case 2  : this->targetNumbers = 4;
                      this->animationString = "LevelMeteoriteAnimation2No";
                      break;
            case 3  : this->targetNumbers = 6;
                      this->animationString = "LevelMeteoriteAnimation3No";
                      break;
            default : break;
        }
    }
}

//----------------------------------------------------------------------------------------------------
void GRLevelMeteoriteLayer::handleCollision(void)
{
    if (this->checkCollision())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/eat.mp3");
        int actorLevel = GRActorLayer::getInstance()->getCurrentActorLevel();
        if (this->currentMeteoriteLevel <= actorLevel) {
            this->eatNumbers++;
            if (this->currentMeteoriteLevel == actorLevel) GRActorLayer::getInstance()->updateTargetMeteoriteNumber();
            
            if (this->eatNumbers == this->targetNumbers) {
                GRActorLayer::getInstance()->setCurrentActorLevel(++actorLevel);
                GRActorLayer::getInstance()->setTargetMeteoriteNumber();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/upgrate.mp3");
            }
        }
        else
        {
            if (actorLevel > ActorLevel::A_LEVEL_ONE) {
                GRActorLayer::getInstance()->setCurrentActorLevel(--actorLevel);
                GRActorLayer::getInstance()->setTargetMeteoriteNumber();
            }
            else Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_OVER);
        }
    }
}

//----------------------------------------------------------------------------------------------------
bool GRLevelMeteoriteLayer::checkCollision(void)
{
    // 如果Layer中没有道具则返回
    if (this->propVector.empty()) return false;
    Vector<Sprite*> tempActorSprite = GRActorLayer::getInstance()->getActors();
    
    for (auto& propTempSprite : this->propVector)
    {
        Rect propRect = propTempSprite->getBoundingBox();
        Point propPoint = this->convertToWorldSpace(propRect.origin);
        int propRadius = propRect.size.width < propRect.size.height ? propRect.size.width : propRect.size.height;
        propRadius = propRadius/3;
        
        for (auto& actorSprite : tempActorSprite)
        {
            Rect actorRect = actorSprite->getBoundingBox();
            Point actorPoint = this->convertToWorldSpace(actorRect.origin);
            int actorRadius = actorRect.size.width < actorRect.size.height ? actorRect.size.width : actorRect.size.height;
            actorRadius = actorRadius/3;
            
            if (this->isIntersected(actorPoint, actorRadius, propPoint, propRadius))
            {
                this->removeProps(propTempSprite);
                return true;
            }
        }
    }
    
    return false;
}