//
//  GRGameScene.h
//  GravityTemplate
//
//
//

#ifndef GravityTemplate_GRGameScene_h
#define GravityTemplate_GRGameScene_h

#include "cocos2d.h"
#include "GRActorLayer.h"
#include "GRStarLayer.h"
#include "GRMeteoriteLayer.h"
#include "GRBlackholeLayer.h" //add by philo
#include "GRLevelMeteoriteLayer.h" //add by philo
#include "GRWormholeLayer.h"

USING_NS_CC;

// 定义两层背景层
enum BackgroundTag
{
    BACKGROUND_A = 1,
    BACKGROUND_B = 2,
};

class GRGameScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRGameScene);
    
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
    void addMeteoriteCallback(float time);
    
    /// 添加黑洞回调函数
    void addBlackholeCallback(float time);
    
    /// 添加虫洞回调函数
    void addWormholeCallback(float time);
    
    void addLevelOneMeteoriteCallback(float time);
    
    void addLevelTwoMeteoriteCallback(float time);
    
    void addLevelThreeMeteoriteCallback(float time);
    
    /// 碰撞检测回调函数
    void checkCollision(float time);
    
    /// 返回一个合适的道具添加位置
    int getComfortableLocation(void);
    
    /// 保存当前场景
    void saveCurrentSceneCallback(EventCustom* event);
    
    /// 处理游戏结束
    void handleGameOverSceneCallback(EventCustom* event);
    
    void sendGameOverMessageCallback(float time);
    
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
    
    GRPropBaseLayer* pStarLayer;
    
    GRPropBaseLayer* pMeteoriteLayer;
    
    GRPropBaseLayer* pBlackholeLayer;
    
    GRPropBaseLayer* pWormholeLayer;
    
    GRPropBaseLayer* pLevelOneMeteoriteLayer;
    
    GRPropBaseLayer* pLevelTwoMeteoriteLayer;
    
    GRPropBaseLayer* pLevelThreeMeteoriteLayer;
};


#endif
