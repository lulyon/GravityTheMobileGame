//
//  GRPropBaseLayer.cpp
//  Gravity
//
//
//

#include "GRPropBaseLayer.h"

//----------------------------------------------------------------------------------------------------
GRPropBaseLayer::GRPropBaseLayer()
{
    
}

//----------------------------------------------------------------------------------------------------
GRPropBaseLayer::~GRPropBaseLayer()
{
    
}

//----------------------------------------------------------------------------------------------------
GRPropBaseLayer* GRPropBaseLayer::create()
{
    GRPropBaseLayer* layer = new GRPropBaseLayer;
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
bool GRPropBaseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->gameSize = Director::getInstance()->getWinSize();
    
    this->initAnimation();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRPropBaseLayer::initAnimation(void)
{
    
}

//----------------------------------------------------------------------------------------------------
void GRPropBaseLayer::addProps(int location)
{
    
}

//----------------------------------------------------------------------------------------------------
void GRPropBaseLayer::handleCollision(void)
{
    //if (this->checkCollision()) return;
}

//----------------------------------------------------------------------------------------------------
bool GRPropBaseLayer::checkCollision(void)
{
    // 如果Layer中没有道具则返回
    if (this->propVector.empty()) return false;
    Vector<Sprite*> tempArmature = GRActorLayer::getInstance()->getActors();
    
    /*for (auto& propArmature : this->armatureVector)
    {
        Rect rect = propArmature->getBoundingBox();
        Point point = this->convertToWorldSpace(rect.origin);
        Rect propArmatureRect(point.x, point.y, rect.size.width, rect.size.height);
        
        for (auto& actorArmature : tempArmature)
        {
            if (actorArmature->getBoundingBox().intersectsRect(propArmatureRect))
            {
                this->removeProps(propArmature);
                return true;
            }
        }
    }*/
    
    for (auto& propArmature : this->propVector)
    {
        
        //Point propPoint = Point(propArmature->getBoundingBox().getMidX(), propArmature->getBoundingBox().getMidY());
        //float propRadius = propArmature->getBoundingBox().getMaxX() - propArmature->getBoundingBox().getMinX();
        
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
            //Point actorPoint = Point(actorArmature->getBoundingBox().getMidX(), actorArmature->getBoundingBox().getMidY());
            //float actorRadius = actorArmature->getBoundingBox().getMaxX() - actorArmature->getBoundingBox().getMinX();
            
            if (this->isIntersected(actorPoint, actorRadius, propPoint, propRadius))
            {
                this->handleCollisionProp(propArmature);
                return true;
            }
        }
    }
    
    return false;
}

//----------------------------------------------------------------------------------------------------
bool GRPropBaseLayer::isIntersected(Point p1, float r1, Point p2, float r2)
{
    if(sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2))>r1+r2) return false;
    else return true;
}

//----------------------------------------------------------------------------------------------------
void GRPropBaseLayer::handleCollisionProp(Sprite* sprite)
{
    this->removeProps(sprite);
}

//----------------------------------------------------------------------------------------------------
void GRPropBaseLayer::removeProps(Node *pNode)
{
    if (!pNode) return;
    
    Sprite* sprite = static_cast<Sprite*>(pNode);
    if (sprite)
    {
        sprite->stopAllActions();
        this->removeChild(sprite);
        this->propVector.eraseObject(sprite);
    }
}