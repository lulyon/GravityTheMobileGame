//
//  GRStarLayer.cpp
//  Gravity
//
//
//

#include "GRStarLayer.h"


//----------------------------------------------------------------------------------------------------
GRStarLayer* GRStarLayer::create()
{
    GRStarLayer* layer = new GRStarLayer;
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
void GRStarLayer::initAnimation(void)
{
    //ArmatureDataManager::getInstance()->addArmatureFileInfo("publish/starAnimation10.png", "publish/starAnimation10.plist", "publish/starAnimation1.ExportJson");
}

//----------------------------------------------------------------------------------------------------
void GRStarLayer::addProps(int location)
{
    /*int direction = 0;
    if (location <= this->gameSize.width/2) direction = -1;
    else direction = 1;
    
    for (int i=0; i<10; i++)
    {
        auto armature = Armature::create("starAnimation1");
        armature->getAnimation()->playByIndex(0);
        
        int halfWidthOfStar = armature->getContentSize().width/2;
        location += direction * halfWidthOfStar;
       
        if (location >= (this->gameSize.width - halfWidthOfStar))
        {
            location = this->gameSize.width - halfWidthOfStar;
            direction = -1 * direction;
        }
        if (location <= halfWidthOfStar)
        {
            location = halfWidthOfStar;
            direction = -1 * direction;
        }
            
        
        armature->setPosition(Point(location, -i*armature->getContentSize().height));
        this->addChild(armature);
        this->armatureVector.pushBack(armature);
        
        // 定义道具的两个动作：向屏幕上方移动、结束
        auto moveAction = MoveTo::create(3.5f+i*0.3, Point(armature->getPositionX(), this->gameSize.height+armature->getContentSize().height));
        auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRStarLayer::removeProps, this));
    
        auto sequence = Sequence::create(moveAction, doneAction, NULL);
        armature->runAction(sequence);
    }*/
    
    int direction = 0;
    if (location <= this->gameSize.width/2) direction = -1;
    else direction = 1;
    
    for (int i=0; i<10; i++)
    {
        auto sprite = Sprite::create("publish/image/star/star1.png");
        
        int halfWidthOfStar = sprite->getContentSize().width/2;
        location += direction * halfWidthOfStar;
        
        if (location >= (this->gameSize.width - halfWidthOfStar))
        {
            location = this->gameSize.width - halfWidthOfStar;
            direction = -1 * direction;
        }
        if (location <= halfWidthOfStar)
        {
            location = halfWidthOfStar;
            direction = -1 * direction;
        }
        
        sprite->setPosition(Point(location, -i*sprite->getContentSize().height));
        this->addChild(sprite);
        this->propVector.pushBack(sprite);
        
        // 定义道具的两个动作：向屏幕上方移动、结束
        auto moveAction = MoveTo::create(3.5f+i*0.3, Point(sprite->getPositionX(), this->gameSize.height+sprite->getContentSize().height));
        auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRStarLayer::removeProps, this));
        
        auto sequence = Sequence::create(moveAction, doneAction, NULL);
        sprite->runAction(sequence);
        auto animateAction = Animate::create(AnimationCache::getInstance()->getAnimation("StarAnimation"));
        sprite->runAction(RepeatForever::create(animateAction));
    }
}

//----------------------------------------------------------------------------------------------------
void GRStarLayer::handleCollision(void)
{
    Vector<Sprite*> tempArmature = GRActorLayer::getInstance()->getActors();
    if (this->checkCollision())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/eat.mp3");
        GRActorLayer::getInstance()->setCurrentActorScore();
        /*for (auto& actorArmature : tempArmature) {
            //actorArmature->getAnimation()->setAnimationData(ArmatureDataManager::getInstance()->getArmatureData);
            actorArmature->stopAllActions();
        }*/
    }
}