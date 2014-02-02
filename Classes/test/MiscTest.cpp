// Created by Luke on 13-11-29.
//


#include "MiscTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

MiscTest::MiscTest( )
{
	createScene( );

	armatureTest( );
}

MiscTest::~MiscTest( )
{

}

void MiscTest::createScene( )
{
	m_Layer = new CCLayer( );
	m_Layer->retain( );
	CCScene *scene = new CCScene( );
	scene->retain( );
	scene->addChild( m_Layer );
	CCDirector::sharedDirector( )->pushScene( scene );
}

void MiscTest::armatureTest( )
{
	CCArmatureDataManager::sharedArmatureDataManager( )->addArmatureFileInfo( "soldier.png", "soldier.plist", "skeleton.xml" );

	CCBatchNode* batchNode = CCBatchNode::create();
	m_Layer->addChild(batchNode);

	int i = 0;
	while(i<500)
	{
		cocos2d::extension::CCArmature *m_pArmature = cocos2d::extension::CCArmature::create( "Enemy" );
		m_pArmature->getAnimation( )->playByIndex( 0, 0, 0, 1 );
		m_pArmature->setAnchorPoint( CCPoint( 0.5, 0.5 ) );
		m_pArmature->ignoreAnchorPointForPosition( true );
		m_pArmature->setPosition( ccp( 50 + 50*int(i/15) , 100 + (i%15)*50) );

		CCBone* foot = m_pArmature->getBone( "foot" );
		if( foot )
		{
			foot->getChildArmature()->getAnimation()->playByIndex( 0, 0, 0, 1 );
		}

		m_Layer->addChild( m_pArmature );
		i++;
	}


}
