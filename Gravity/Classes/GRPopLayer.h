/*对话框场景类的头文件*/
#ifndef _POP_SCENE_H_
#define _POP_SCENE_H_
#include "cocos2d.h"

using namespace cocos2d;

class GRPopLayer : public CCLayer
{
public:
	bool init();
	static GRPopLayer* create();
private:

	//在弹出的对话框上加俩个按钮，以下的函数是对应的按钮的处理事件
	void yesButton(CCObject * object);
	//设置对话框的文本内容
	void setContent();
	//m_size代表的是对话框背景的大小
	CCSize m_size;
	//对话框的背景精灵
	CCSprite * m_bgSprite;
};
#endif