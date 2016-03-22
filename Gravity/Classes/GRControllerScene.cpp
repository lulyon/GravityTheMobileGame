//
//  ControllerScene.cpp
//  Gravity
//
//
//

#include "GRControllerScene.h"
#include "GRMessageInfo.h"

//----------------------------------------------------------------------------------------------------
GRControllerScene::GRControllerScene()
{
    // 初始化消息回调函数
    this->initMessageCallback();
}

//----------------------------------------------------------------------------------------------------
Scene* GRControllerScene::getLoadingScene(void)
{
    auto scene =  GRLoadingScene::createScene();
    return scene;
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::initMessageCallback()
{
    // 添加登陆场景回调函数
    auto loginListener = EventListenerCustom::create(MES_ADD_LOGIN, CC_CALLBACK_1(GRControllerScene::addLoginSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(loginListener, 1);
    
    // 添加帐号场景回调函数
    auto accountListener = EventListenerCustom::create(MES_ADD_ACCOUNT, CC_CALLBACK_1(GRControllerScene::addAccountSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(accountListener, 1);
    
    // 添加操作场景回调函数
    auto operationListener = EventListenerCustom::create(MES_ADD_OPERATOR, CC_CALLBACK_1(GRControllerScene::addOperationSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(operationListener, 1);
    
    // 添加角色选择场景回调函数
    auto actorSelectListener = EventListenerCustom::create(MES_ACTOR_SELECT, CC_CALLBACK_1(GRControllerScene::addActorSelectSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(actorSelectListener, 1);
    
    // 添加游戏开始回调函数
    auto gameStartListener = EventListenerCustom::create(MES_GAME_START, CC_CALLBACK_1(GRControllerScene::addGameStartSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameStartListener, 1);
    
    // 添加过渡场景回调函数
    auto transitionListener = EventListenerCustom::create(MES_ADD_TRANSITION, CC_CALLBACK_1(GRControllerScene::addTransitionSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(transitionListener, 1);
    
    // 添加虫洞场景回调函数
    auto wormholeListener = EventListenerCustom::create(MES_ADD_WORMHOLE, CC_CALLBACK_1(GRControllerScene::addWormholeSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(wormholeListener, 1);
    
    // 添加返回操作场景回调函数
    auto backOperationListener = EventListenerCustom::create(MES_BACK_OPERATION, CC_CALLBACK_1(GRControllerScene::backToOperationSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(backOperationListener, 1);
    
    // 添加游戏结束回调函数
    auto gameOverListener = EventListenerCustom::create(MES_ADD_GAMEOVER, CC_CALLBACK_1(GRControllerScene::addGameOverSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameOverListener, 1);
    
    auto story1Listener = EventListenerCustom::create(MES_ADD_STORY_ONE, CC_CALLBACK_1(GRControllerScene::addStoryOneSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(story1Listener, 1);
    
    auto story2Listener = EventListenerCustom::create(MES_ADD_STORY_TWO, CC_CALLBACK_1(GRControllerScene::addStoryTwoSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(story2Listener, 1);
    
    auto story3Listener = EventListenerCustom::create(MES_ADD_STORY_THREE, CC_CALLBACK_1(GRControllerScene::addStoryThreeSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(story3Listener, 1);
    
    auto story4Listener = EventListenerCustom::create(MES_ADD_STORY_FOUR, CC_CALLBACK_1(GRControllerScene::addStoryFourSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(story4Listener, 1);
    
    auto story5Listener = EventListenerCustom::create(MES_ADD_STORY_FIVE, CC_CALLBACK_1(GRControllerScene::addStoryFiveSceneCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(story5Listener, 1);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addLoginSceneCallback(EventCustom *event)
{
    auto loginScene    = GRLoginScene::createScene();
    auto animateScene  = TransitionFlipX::create(1.0f, loginScene);
    
    // 通过导演获取当前运行的场景
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addAccountSceneCallback(EventCustom* event)
{
    auto accountScene    = GRAccoutLoginScene::createScene();
    auto animateScene  = TransitionCrossFade::create(0.1f, accountScene);
    
    // 通过导演获取当前运行的场景
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addOperationSceneCallback(EventCustom* event)
{
    auto operationScene   = GROperationScene::createScene();
    auto animateScene  = TransitionSlideInL::create(0.3f, operationScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addActorSelectSceneCallback(EventCustom* event)
{
    auto actorSelectScene   = GRActorSelectScene::createScene();
    auto animateScene  = TransitionSlideInL::create(0.3f, actorSelectScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addGameStartSceneCallback(EventCustom* event)
{
    // 添加游戏场景
    auto gameScene = GRGameScene::createScene();
    auto animateScene  = TransitionSlideInL::create(0.3f, gameScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addTransitionSceneCallback(EventCustom *event)
{
    // 添加过渡场景
    auto transitionScene = GRTransitionScene::createScene();
    auto animateScene  = TransitionMoveInB::create(0.3f, transitionScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addWormholeSceneCallback(EventCustom *event)
{
    // 添加虫洞场景
    auto wormholeScene = GRWormholeScene::createScene();
    auto animateScene  = TransitionMoveInB::create(0.3f, wormholeScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addGameOverSceneCallback(EventCustom* event)
{
    auto gameoverScene   = GRGameOverScene::createScene();
    auto animateScene  = TransitionSlideInL::create(0.3f, gameoverScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::backToOperationSceneCallback(EventCustom* event)
{
    auto operationScene   = GROperationScene::createScene();
    auto animateScene  = TransitionSlideInL::create(0.3f, operationScene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addStoryOneSceneCallback(EventCustom *event)
{
    auto story1Scene   = GRStoryOneScene::createScene();
    auto animateScene  = TransitionShrinkGrow::create(1.0f, story1Scene);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addStoryTwoSceneCallback(EventCustom *event)
{
    auto story2Scene   = GRStoryTwoScene::createScene();
    auto animateScene  = TransitionPageTurn::create(1.0f, story2Scene, false);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addStoryThreeSceneCallback(EventCustom *event)
{
    auto story3Scene   = GRStoryThreeScene::createScene();
    auto animateScene  = TransitionPageTurn::create(1.0f, story3Scene, false);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addStoryFourSceneCallback(EventCustom *event)
{
    auto story4Scene   = GRStoryFourScene::createScene();
    auto animateScene  = TransitionPageTurn::create(1.0f, story4Scene, false);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
void GRControllerScene::addStoryFiveSceneCallback(EventCustom *event)
{
    auto story5Scene   = GRStoryFiveScene::createScene();
    auto animateScene  = TransitionPageTurn::create(1.0f, story5Scene, false);
    
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene) Director::getInstance()->replaceScene(animateScene);
    else              Director::getInstance()->runWithScene(animateScene);
}

//----------------------------------------------------------------------------------------------------
GRControllerScene::~GRControllerScene()
{
    
}