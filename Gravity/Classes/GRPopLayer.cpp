//
//  GRPopLayer.cpp
//  Gravity
//
//
//
#include "GRPopLayer.h"

GRPopLayer* GRPopLayer::create()
{
    GRPopLayer* layer = new GRPopLayer;
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

bool GRPopLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		//设置这个层的背景图片，并且设置其位置为整个屏幕的中点
		CCSprite * background = CCSprite::create("input.png");
		m_bgSprite = background;
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);

		//获得背景图片的大小
		CCSize contentSize = background->getContentSize();
		m_size = contentSize;

		//添加俩个菜单在这个层中
		CCMenuItemImage * item1 = CCMenuItemImage::create("button.png","button_pressed.png","",this,menu_selector(GRPopLayer::yesButton));
	

		CCMenu * menu = CCMenu::create(item1,NULL,NULL);
		menu->alignItemsHorizontallyWithPadding(5);
		menu->setPosition(ccp(contentSize.width/2,contentSize.height/4));

		background->addChild(menu);

		//设置题目和文本内容
		this->setContent();

		this->setTouchEnabled(true);
		bRet = true;
	}
	while(0);

	return bRet;
}




//点击菜单按钮的时候调用的事件处理函数
void GRPopLayer::yesButton(CCObject * object)
{
	this->removeFromParentAndCleanup(true);
}


//设置层的内容
void GRPopLayer::setContent()
{

	CCDictionary* pDict = CCDictionary::createWithContentsOfFile("data.xml");
	std::string str = pDict->valueForKey("PopLayerText")->getCString();
	CCLabelTTF * content = CCLabelTTF::create(str,"",24);
	content->setPosition(ccp(m_size.width/2,m_size.height/2));
	//设置ttf的文本域
	content->setDimensions(CCSize(this->m_size.width-60,this->m_size.height-100));
	//设置ttf的水平对齐方式
    content->setHorizontalAlignment(kCCTextAlignmentLeft);

	m_bgSprite->addChild(content);
}