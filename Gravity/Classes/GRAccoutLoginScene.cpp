//
//  GRAccountLoginScene.cpp
//  Gravity
//
//
//

#include "GRAccoutLoginScene.h"
#include "GRMessageInfo.h"
#include "GRPopLayer.h"

//----------------------------------------------------------------------------------------------------
Scene* GRAccoutLoginScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GRAccoutLoginScene::create();
    
    scene->addChild(layer);
    return scene;
}

//----------------------------------------------------------------------------------------------------
bool GRAccoutLoginScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->addLoginButton();
    
    return true;
}

//----------------------------------------------------------------------------------------------------
void GRAccoutLoginScene::addLoginButton(void)
{
    this->loginUI=GUIReader::getInstance()->widgetFromJsonFile("GloginUI/GloginUI_1.json");
    if(!this->loginUI) return;
		 this->addChild(this->loginUI);
   
	this->confirmButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->loginUI, "confirmbtn"));
	if (this->confirmButton)
    {
      this->confirmButton->addTouchEventListener(this, toucheventselector(GRAccoutLoginScene::confirmButtonCallback));
    }
	
	this->cancelButton = dynamic_cast<Button*>(Helper::seekWidgetByName(this->loginUI, "cancelbtn"));
	if (this->cancelButton)
    {
      this->cancelButton->addTouchEventListener(this, toucheventselector(GRAccoutLoginScene::cancelButtonCallback));
    }
	this->account_text = dynamic_cast<TextField*>(Helper::seekWidgetByName(this->loginUI, "account"));
	this->password_text = dynamic_cast<TextField*>(Helper::seekWidgetByName(this->loginUI, "password"));

}

//----------------------------------------------------------------------------------------------------
void GRAccoutLoginScene::confirmButtonCallback(CCObject* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED){

		std::string account=this->account_text->getStringValue();
		std::string password=this->password_text->getStringValue();
		CCDictionary* pDict = CCDictionary::createWithContentsOfFile("data.xml");  
		CCArray* aAccout = new CCArray();  
        aAccout->retain();  
        aAccout = (CCArray*)pDict->objectForKey("account");
		CCArray* aPassword = new CCArray();  
        aPassword->retain();  
        aPassword = (CCArray*)pDict->objectForKey("password");
 
		bool findflag=false;
        for (int i = 0;i < aAccout->count();i++)  
        {  
			std::string astr=((CCString*)aAccout->objectAtIndex(i))->getCString();
			std::string pstr=((CCString*)aPassword->objectAtIndex(i))->getCString();
			if(account==astr&&password==pstr){
				findflag=true;
			}
        }  
		if(!findflag){
			auto popscene=GRPopLayer::create();
			this->addChild(popscene);
		}else{
			//跳转到主界面
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_OPERATOR);
		}

	}

}

//----------------------------------------------------------------------------------------------------
void GRAccoutLoginScene::cancelButtonCallback(CCObject* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED){
		 Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MES_ADD_LOGIN);
		//返回上一页界面
	}
}
