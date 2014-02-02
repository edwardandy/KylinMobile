
// Created by Luke on 13-8-20.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "DisplayObjectScene.h"
#include "DisplayObjectRenderer.h"
#include "VisibleRect.h"
#include "cocos2d.h"
#include "../time/AnimatedComponent.h"

USING_NS_CC;
NS_SF_BEGIN
		DisplayObjectScene::DisplayObjectScene( )
		{

		}

		DisplayObjectScene::~DisplayObjectScene( )
		{

		}

		void DisplayObjectScene::setSceneView( CCLayer *sceneView )
		{
			if( NULL == sceneView )
			{
				//	m_Container = CCLayerColor::create( ccc4(255,0,0,255) );
				m_Container = CCLayer::create( );
				m_Container->retain( );
				CCSize win = CCDirector::sharedDirector( )->getWinSize( );
				m_Container->setContentSize( win );
				//	m_Container->setPosition( Point(VisibleRect::leftBottom( ).x + 10 ,VisibleRect::leftBottom( ).y+10) );
				m_Container->setPosition( ccp(0,0) );
				m_Container->setAnchorPoint( ccp(0, 0) );
				m_Container->ignoreAnchorPointForPosition( false );
			}
			else
			{
				m_Container = sceneView;
			}

		}

		void DisplayObjectScene::add( DisplayObjectRenderer *renderer )
		{
			if ( m_Container )
			{
				renderer->retain( );
				m_Container->addChild( renderer->getDisplayObject( ), 1 );
			}
		}

		void DisplayObjectScene::remove( DisplayObjectRenderer *renderer )
		{
			if ( m_Container )
			{
				m_Container->removeChild( renderer->getDisplayObject( ) );
				renderer->release( );
			}
		}

		void DisplayObjectScene::onFrame( float deltaTime )
		{

		}

		void DisplayObjectScene::onAdd( )
		{
			EntityComponent::onAdd( );
		}

		void DisplayObjectScene::onRemove( )
		{
			EntityComponent::onRemove( );
		}


		void DisplayObjectScene::onStop( )
		{
			EntityComponent::onStop( );
		}

		void DisplayObjectScene::onResume( )
		{
			EntityComponent::onResume( );
		}

		NS_SF_END