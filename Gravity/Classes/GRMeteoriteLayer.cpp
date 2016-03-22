//
//  GRMeteoriteLayer.cpp
//  Gravity
//
//
//

#include "GRMeteoriteLayer.h"
#include "GRMessageInfo.h"

//----------------------------------------------------------------------------------------------------
GRMeteoriteLayer* GRMeteoriteLayer::create()
{
    GRMeteoriteLayer* layer = new GRMeteoriteLayer;
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
void GRMeteoriteLayer::initAnimation(void)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("publish/MeteoriteAnimation1.ExportJson");
}

//----------------------------------------------------------------------------------------------------
void GRMeteoriteLayer::addProps(int location)
{
    /*auto armature = Armature::create("MeteoriteAnimation1");
    armature->getAnimation()->playByIndex(0);
    armature->setPosition(Point(location, -armature->getContentSize().height));
    this->addChild(armature);
    this->propVector.pushBack(armature);
        
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(5.0f, Point(armature->getPositionX(), this->gameSize.height+armature->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRMeteoriteLayer::removeProps, this));
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    armature->runAction(sequence);
    armature->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));*/
    
    auto sprite = Sprite::create("publish/image/buttons/Meteorite.png");
    sprite->setPosition(Point(location, -sprite->getContentSize().height));
    sprite->setScale(0.6f);
    this->addChild(sprite);
    this->propVector.pushBack(sprite);
    
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(4.0f, Point(sprite->getPositionX(), this->gameSize.height+sprite->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRMeteoriteLayer::removeProps, this));
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    sprite->runAction(sequence);
    sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
}

//----------------------------------------------------------------------------------------------------
void GRMeteoriteLayer::handleCollision(void)
{
    if (this->checkCollision())
    {
        int actorLevel = GRActorLayer::getInstance()->getCurrentActorLevel();
        if (actorLevel > ActorLevel::A_LEVEL_ONE) {
            GRActorLayer::getInstance()->setCurrentActorLevel(--actorLevel);
        }
        else Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_GAME_OVER);
    }
}

//----------------------------------------------------------------------------------------------------
bool GRMeteoriteLayer::checkCollision(void)
{
    // 如果Layer中没有道具则返回
    if (this->propVector.empty()) return false;
    Vector<Sprite*> tempArmature = GRActorLayer::getInstance()->getActors();
    
    for (auto& propArmature : this->propVector)
    {
        
        Rect propRect = propArmature->getBoundingBox();
        Point propPoint = this->convertToWorldSpace(propRect.origin);
        int propRadius = propRect.size.width < propRect.size.height ? propRect.size.width : propRect.size.height;
        propRadius = propRadius*2/5;
        
        for (auto& actorArmature : tempArmature)
        {
            Rect actorRect = actorArmature->getBoundingBox();
            Point actorPoint = this->convertToWorldSpace(actorRect.origin);
            int actorRadius = actorRect.size.width < actorRect.size.height ? actorRect.size.width : actorRect.size.height;
            actorRadius = actorRadius*2/5;
            
            if (this->isIntersected(actorPoint, actorRadius, propPoint, propRadius))
            {
                this->removeProps(propArmature);
                
                /*auto explosionParticle = ParticleExplosion::createWithTotalParticles(10);
                explosionParticle->setScale(1.0f);
                this->addChild(explosionParticle, 12);
                explosionParticle->setTexture(Director::getInstance()->getTextureCache()->addImage("image/Meteorite.png"));
                explosionParticle->setPosition(propArmature->getPosition());*/
                
                return true;
            }
        }
    }
    
    return false;
}


