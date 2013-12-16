// Created by Luke on 13-9-10.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ArmatureRenderer.h"

NS_SF_BEGIN
		ArmatureRenderer::ArmatureRenderer( )
		{
			m_pArmature = NULL;
		}

		ArmatureRenderer::~ArmatureRenderer( )
		{
			m_pArmature = NULL;
		}

		void ArmatureRenderer::onRemove( )
		{
			DisplayObjectRenderer::onRemove( );
		}

		void ArmatureRenderer::onFrame( float deltaTime )
		{

		}

		void ArmatureRenderer::onAdd( )
		{
			DisplayObjectRenderer::onAdd( );
		}


		bool ArmatureRenderer::init( const char *name, int zOrder )
		{
			if ( m_pArmature )
			{
				removeChild( m_pArmature );
				m_pArmature = NULL;
			}
			m_pArmature = cocos2d::extension::CCArmature::create( name );
			m_pArmature->getAnimation( )->playByIndex( 0 );
			m_pArmature->setAnchorPoint( CCPoint(0, 0) );
			m_pArmature->ignoreAnchorPointForPosition( false );
			m_pArmature->retain( );

			addChild( m_pArmature, name, zOrder );
			return true;
		}

		ArmatureRenderer *ArmatureRenderer::create( const char *name, int zOrder )
		{
			ArmatureRenderer *render = new ArmatureRenderer( );
			render->init( name, zOrder );
			return render;
		}
NS_SF_END
