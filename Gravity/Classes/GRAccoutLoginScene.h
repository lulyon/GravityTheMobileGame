//
//  GRLoginScene.h
//  Gravity
//
//
//

#ifndef Gravity_GRAccountLoginScene_h
#define Gravity_GRAccountLoginScene_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

class GRAccoutLoginScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GRAccoutLoginScene);

private:
    void addLoginButton(void);
    void confirmButtonCallback(Object* pSender, TouchEventType type);
    void cancelButtonCallback(Object* pSender, TouchEventType type);

	Widget* loginUI;
	Button* confirmButton;
	Button* cancelButton;
	TextField* account_text;
	TextField* password_text;
 
};

#endif
