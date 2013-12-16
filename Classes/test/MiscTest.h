//
// Created by Luke on 13-11-29.
//



#ifndef __MiscTest_H_
#define __MiscTest_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class MiscTest
{
public:
	MiscTest();
	virtual ~MiscTest( );
private:
	void armatureTest();

	cocos2d::CCLayer* m_Layer;
	cocos2d::CCSpriteBatchNode* m_BatchNode;
	void createScene();
};


#endif //__MiscTest_H_
