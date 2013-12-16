//
// Created by Luke on 13-11-22.
//


#include "CollisionResponseComponent.h"
#include "RowSpatialManager.h"
#include "../strategy/CollisionResponseStrategy.h"

NS_SF_BEGIN
		CollisionResponseComponent::CollisionResponseComponent( )
		{
			m_Spatial = NULL;
			m_IsConditionalTrue = true;
			m_Conditional = NULL;
			m_ObjectMask = NULL;
			m_CollisionResults = NULL;
			minCol = -1;
			maxCol = -1;
			minRow = -1;
			maxRow = -1;
		}

		CollisionResponseComponent::~CollisionResponseComponent( )
		{
//			CCLOG( "~CollisionResponseComponent" );
			if ( m_CollisionResults )
			{
				m_CollisionResults->removeAllObjects( );
				m_CollisionResults->release( );
			}
			if ( m_ObjectMask )
			{
				m_ObjectMask->release( );
			}
			if ( m_Conditional )
			{
				m_Conditional->release( );
			}
			m_Spatial = NULL;
			m_RowSpatialManager = NULL;
		}

		void CollisionResponseComponent::onAdd( )
		{
			StrategyContainingComponent::onAdd( );
			m_Spatial = dynamic_cast<RowSpatialObjectComponent * >(this->getOwner( )->lookupComponent( "spatial" ));
			m_RowSpatialManager = dynamic_cast<RowSpatialManager * >(this->getOwner( )->lookupComponentByEntity( "rowSpatialManager", "world" ));
			m_CollisionResults = cocos2d::CCArray::create( );
			m_CollisionResults->retain( );
		}

		void CollisionResponseComponent::onRemove( )
		{
			StrategyContainingComponent::onRemove( );
		}


		void CollisionResponseComponent::onStop( )
		{
			StrategyContainingComponent::onStop( );
		}

		void CollisionResponseComponent::onResume( )
		{
			StrategyContainingComponent::onResume( );
		}

		void CollisionResponseComponent::checkCollision( )
		{
			if ( m_Conditional != NULL && !m_Conditional->isConditionalTrue( ) )
			{
				return;
			}
			if ( !m_IsConditionalTrue ) return;

			m_CollisionResults->removeAllObjects( );

			if ( !m_Spatial || !m_RowSpatialManager || !m_ObjectMask )
			{
				return;
			}
//			CCLog("minCol:%d,maxCol:%d,minRow:%d,maxRow:%d",m_Spatial->getMinCol( ),m_Spatial->getMaxCol( ),m_Spatial->getMinRow( ),m_Spatial->getMaxRow( ));
			bool foundAny = m_RowSpatialManager->querySpan( m_Spatial->getMinCol( ), m_Spatial->getMaxCol( ), m_Spatial->getMinRow( ), m_Spatial->getMaxRow( ), m_ObjectMask, m_CollisionResults , m_Spatial );
			if ( foundAny )
			{
				cocos2d::CCObject *object;
				CCARRAY_FOREACH(this->getStrategies( ), object)
					{
						CollisionResponseStrategy *strategy = ( CollisionResponseStrategy * ) object;
						if ( strategy == NULL)
						{
							continue;
						}
						strategy->onCollision( m_CollisionResults );
					}
			}
		}

		void CollisionResponseComponent::onTick( float deltaTime )
		{
//			CCLog("minCol:%d,maxCol:%d,minRow:%d,maxRow:%d",m_Spatial->getMinCol( ),m_Spatial->getMaxCol( ),m_Spatial->getMinRow( ),m_Spatial->getMaxRow( ));
			if(minCol != m_Spatial->getMinCol( ) || maxCol != m_Spatial->getMaxCol( ) || minRow != m_Spatial->getMinRow( ) || maxRow != m_Spatial->getMaxRow( ))
			{
				checkCollision( );
				minRow = m_Spatial->getMinRow( );
				minCol = m_Spatial->getMinCol( );
				maxCol = m_Spatial->getMaxCol( );
				maxRow = m_Spatial->getMaxRow( );
			}
			StrategyContainingComponent::onTick( deltaTime );
		}

		NS_SF_END