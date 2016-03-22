//
//  GRWormholeLayer.cpp
//  Gravity
//
//
//

#include "GRWormholeLayer.h"
#include "GRMessageInfo.h"

//----------------------------------------------------------------------------------------------------
GRWormholeLayer* GRWormholeLayer::create()
{
    GRWormholeLayer* layer = new GRWormholeLayer;
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
void GRWormholeLayer::initAnimation(void)
{
    //ArmatureDataManager::getInstance()->addArmatureFileInfo("publish/WormholeAnimation.ExportJson");
}

//----------------------------------------------------------------------------------------------------
void GRWormholeLayer::addProps(int location)
{
    auto sprite = Sprite::create("publish/image/buttons/wormhole.png");
    sprite->setPosition(Point(location, -sprite->getContentSize().height));
    sprite->setScale(0.8f);
    this->addChild(sprite);
    this->propVector.pushBack(sprite);
    
    // 定义道具的两个动作：向屏幕上方移动、结束
    auto moveAction = MoveTo::create(4.0f, Point(sprite->getPositionX(), this->gameSize.height+sprite->getContentSize().height));
    auto doneAction = CallFuncN::create(CC_CALLBACK_1(GRWormholeLayer::removeProps, this));
    moveAction->setTag(100);
    
    auto sequence = Sequence::create(moveAction, doneAction, NULL);
    sprite->runAction(sequence);
    sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
}

//----------------------------------------------------------------------------------------------------
void GRWormholeLayer::handleCollision(void)
{
    if (this->checkCollision())
    {
        
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_SAVE_SCENE);
    }
}

//----------------------------------------------------------------------------------------------------
void GRWormholeLayer::handleCollisionProp(Sprite* sprite)
{
    sprite->stopActionByTag(100);
    //sprite->setScale(10.0f);
    sprite->runAction(ScaleBy::create(5.0f, 5.0f));
    //sprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
    //this->removeProps(sprite);
}

