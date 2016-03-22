//
//  GRBlackholeLayer.cpp
//  Gravity
//
//
//

#include "GRBlackholeLayer.h"
#include "GRMessageInfo.h"

//----------------------------------------------------------------------------------------------------
GRBlackholeLayer* GRBlackholeLayer::create()
{
    GRBlackholeLayer* layer = new GRBlackholeLayer;
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
/*bool GRBlackholeLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    
    
    this->initAnimation();
    
    return true;
}*/

//----------------------------------------------------------------------------------------------------
void GRBlackholeLayer::initAnimation(void)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("publish/BlackholeAnimation.ExportJson");
    this->attractSpeed = 50;
}

//----------------------------------------------------------------------------------------------------
void GRBlackholeLayer::addProps(int location)
{
    /*auto armature = Armature::create("BlackholeAnimation");
    armature->getAnimation()->playByIndex(0);
    armature->setScale(0.5);
    armature->setTag(BlackholeTag::Black_Hole);
    armature->setPosition(Point(location, -armature->getContentSize().height));
    this->addChild(armature);
    this->armatureVector.pushBack(armature);
        
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(5.0f, Point(armature->getPositionX(), this->gameSize.height+armature->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRBlackholeLayer::removeProps, this));
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    armature->runAction(sequence);
    armature->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));*/
    
    auto sprite = Sprite::create("publish/image/buttons/blackhole.png");
    sprite->setPosition(Point(location, -sprite->getContentSize().height));
    sprite->setScale(0.8f);
    sprite->setTag(BlackholeTag::Black_Hole);
    this->addChild(sprite);
    this->propVector.pushBack(sprite);
    
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(5.0f, Point(sprite->getPositionX(), this->gameSize.height+sprite->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRBlackholeLayer::removeProps, this));
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    sprite->runAction(sequence);
    sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
    
    //if (this->attractSpeed > 1) this->attractSpeed--;
}

//----------------------------------------------------------------------------------------------------
void GRBlackholeLayer::handleCollision(void)
{
    Vector<Sprite*> tempSpriteVector = GRActorLayer::getInstance()->getActors();
    
    this->attractActor();
    if (this->checkCollision())
    {
        for (auto& propArmature : this->propVector)
        {
            propArmature->stopAllActions();
            propArmature->runAction(RepeatForever::create(RotateBy::create(0.1f, 360)));
        }
        /*tempSprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
        
        for (auto& actorSprite : tempSpriteVector)
        {
            actorSprite->runAction(MoveTo::create(1.0f, tempSprite->getPosition()));
        }*/

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_OVER);
    }
}

//----------------------------------------------------------------------------------------------------
bool GRBlackholeLayer::checkCollision(void)
{
    // 如果Layer中没有道具则返回
    if (this->propVector.empty()) return false;
    Vector<Sprite*> tempArmature = GRActorLayer::getInstance()->getActors();
    
    for (auto& propArmature : this->propVector)
    {
        Rect propRect = propArmature->getBoundingBox();
        Point propPoint = this->convertToWorldSpace(propRect.origin);
        int propRadius = propRect.size.width < propRect.size.height ? propRect.size.width : propRect.size.height;
        propRadius = propRadius/8;
        
        for (auto& actorArmature : tempArmature)
        {
            Rect actorRect = actorArmature->getBoundingBox();
            Point actorPoint = this->convertToWorldSpace(actorRect.origin);
            int actorRadius = actorRect.size.width < actorRect.size.height ? actorRect.size.width : actorRect.size.height;
            actorRadius = actorRadius/8;
            //Point actorPoint = Point(actorArmature->getBoundingBox().getMidX(), actorArmature->getBoundingBox().getMidY());
            //float actorRadius = actorArmature->getBoundingBox().getMaxX() - actorArmature->getBoundingBox().getMinX();
            
            if (this->isIntersected(actorPoint, actorRadius, propPoint, propRadius))
            {
                this->removeProps(propArmature);
                return true;
            }
        }
    }
    
    return false;
}

//----------------------------------------------------------------------------------------------------
void GRBlackholeLayer::attractActor(void)
{
    Sprite* tempSprite = dynamic_cast<Sprite*>(this->getChildByTag(BlackholeTag::Black_Hole));
    if (!tempSprite) return;
    int blackholePositionX = tempSprite->getPositionX();
    
    Vector<Sprite*> tempArmatureVector = GRActorLayer::getInstance()->getActors();
    int deltX = 0;
    for (auto& actorArmature : tempArmatureVector)
    {
        deltX = (actorArmature->getPositionX() - blackholePositionX)/this->attractSpeed;
        actorArmature->setPositionX(actorArmature->getPositionX() - deltX);
    }
}