/*�Ի��򳡾����ͷ�ļ�*/
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

	//�ڵ����ĶԻ����ϼ�������ť�����µĺ����Ƕ�Ӧ�İ�ť�Ĵ����¼�
	void yesButton(CCObject * object);
	//���öԻ�����ı�����
	void setContent();
	//m_size������ǶԻ��򱳾��Ĵ�С
	CCSize m_size;
	//�Ի���ı�������
	CCSprite * m_bgSprite;
};
#endif