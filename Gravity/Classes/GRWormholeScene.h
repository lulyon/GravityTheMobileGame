//
//  GRWormholeScene.h
//  GravityTemplate
//
//
//

#ifndef GravityTemplate_GRWormholeScene_h
#define GravityTemplate_GRWormholeScene_h

#include "cocos2d.h"
#include "GRActorLayer.h"
//#include "GRMeteoriteLayer.h"
#include "GRStarLayer.h"
#include "GRBlackholeLayer.h" //add by philo
#include "GRLevelMeteoriteLayer.h" //add by philo
//#include "GRParticleLayer.h"
#include "GRPropBaseLayer.h"

USING_NS_CC;

// 定义两层背景层
enum WBackgroundTag
{
    W_BACKGROUND_A = 1,
    W_BACKGROUND_B = 2,
};

class GRWormholeScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRWormholeScene);
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
private:
    void initWidget(void);
    
     void initProps(void);
    
    void initCallback(void);
    /// 添加游戏场景的背景图像
    void addBackground(void);
    /// 让背景图像运动起来
    void backgroundMoving(float time);
    
    /// 添加星星回调函数
    void addStarsCallback(float time);
    /// 添加陨石回调函数
    void addBlackholeCallback(float time);
    
    void addLevelOneMeteoriteCallback(float time);
    void addLevelTwoMeteoriteCallback(float time);
    void addLevelThreeMeteoriteCallback(float time);
    /// 添加飞船道具回调函数
    void addSpaceshipCallback(float time);
    /// 碰撞检测回调函数
    void checkCollision(float time);
    
    /// 返回一个合适的道具添加位置
    int getComfortableLocation(void);
    
private:
    /// 背景图像移动速度
    int backgroundMovingSpeed;
    /// 演员移动得分纪录
    int actorMoveScore;
    /// 游戏场景尺寸
    Size gameSize;
    
    long updateCounts;
    
    LabelTTF* actorScoreLabel;

    /// 最近一个道具添加的位置
    int currentLocation;
    
    GRPropBaseLayer* pBlackholeLayer;
    
    GRPropBaseLayer* pStarLayer;
    
    GRPropBaseLayer* pLevelOneMeteoriteLayer;
    GRPropBaseLayer* pLevelTwoMeteoriteLayer;
    GRPropBaseLayer* pLevelThreeMeteoriteLayer;
};


#endif
