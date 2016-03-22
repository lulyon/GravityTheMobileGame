//
//  GRControllerScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRControllerScene_h
#define Gravity_GRControllerScene_h

#include "GRLoadingScene.h"
#include "GRLoginScene.h"
#include "GRAccoutLoginScene.h"
#include "GROperationScene.h"
#include "GRActorSelectScene.h"
#include "GRGameScene.h"
#include "GRTransitionScene.h"
#include "GRWormholeScene.h"
#include "GRGameOverScene.h"

#include "GRStoryOneScene.h"
#include "GRStoryTwoScene.h"
#include "GRStoryThreeScene.h"
#include "GRStoryFourScene.h"
#include "GRStoryFiveScene.h"

USING_NS_CC;

class GRControllerScene : public Ref
{
public:
    GRControllerScene();
    virtual ~GRControllerScene();
    
    /// 返回登陆场景
    Scene* getLoadingScene(void);
    
private:
    /// 初始化所有的消息回调函数
    void initMessageCallback(void);
    
    void addStoryOneSceneCallback(EventCustom* event);
    void addStoryTwoSceneCallback(EventCustom* event);
    void addStoryThreeSceneCallback(EventCustom* event);
    void addStoryFourSceneCallback(EventCustom* event);
    void addStoryFiveSceneCallback(EventCustom* event);
    
    /// 添加登陆场景
    void addLoginSceneCallback(EventCustom* event);
    /// 添加帐号
    void addAccountSceneCallback(EventCustom* event);
    /// 添加操作场景
    void addOperationSceneCallback(EventCustom* event);
    /// 添加演员选择场景
    void addActorSelectSceneCallback(EventCustom* event);
    /// 添加游戏场景
    void addGameStartSceneCallback(EventCustom* event);
    /// 处理游戏结束
    void addGameOverSceneCallback(EventCustom* event);
    /// 返回操作场景
    void backToOperationSceneCallback(EventCustom* event);
    
    /// 添加过渡场景
    void addTransitionSceneCallback(EventCustom* event);
    /// 添加虫洞场景
    void addWormholeSceneCallback(EventCustom* event);

private:
    
};


#endif
