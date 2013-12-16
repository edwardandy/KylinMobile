// Created by Luke on 13-8-25.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <assert.h>
#include "RowSpatialManager.h"
#include "RowSpatialObjectComponent.h"
#include "../util/ObjectType.h"

NS_SF_BEGIN
		RowSpatialManager *RowSpatialManager::mInstance = NULL;

		RowSpatialManager::RowSpatialManager( )
		{
			m_Pool.clear( );
			needRemoveList = NULL;
		}

		RowSpatialManager::~RowSpatialManager( )
		{
			CCLOG("============================================ ~RowSpatialManager ============");
		}

		RowSpatialManager *RowSpatialManager::getInstance( )
		{
			if ( mInstance == NULL)
			{
				mInstance = new RowSpatialManager( );
			}

			return mInstance;
		}

		void RowSpatialManager::addSpatialObject( RowSpatialObjectComponent *value )
		{
			if ( value->getRow( ) < m_nRows && value->getCol( ) < m_nCols && value->getRow( ) >= 0 && value->getCol( ) >= 0 )
			{
				int index = value->getRow( ) * m_nCols + value->getCol( );
				if ( m_Pool.size( ) < index )
				{
					printf( "[RowSpatialManager] m_Pool index is out of range" );
					assert(false);
				}
				if ( std::find( m_Pool.at( index ).begin( ), m_Pool.at( index ).end( ), value ) == m_Pool.at( index ).end( ) )
				{
					m_Pool.at( index ).push_back( value );
				}
			}
//			else
//			{
//				printf( "[RowSpatialManager] index is out of range row:%d,col:%d", value->getRow( ), value->getCol( ) );
//				assert(value->getRow( ) >= 0 && value->getCol( ) >= 0);
//			}
		}

		void RowSpatialManager::fastRemove( RowSpatialObjectComponent *value )
		{
			int index = value->getRow( ) * m_nCols + value->getCol( );
			if ( m_Pool.size( ) > index )
			{
				std::vector<RowSpatialObjectComponent *>::iterator it = std::find( m_Pool.at( index ).begin( ), m_Pool.at( index ).end( ), value );
				if ( it != m_Pool.at( index ).end( ) )
				{
					m_Pool.at( index ).erase( it );
				}
			}
		}

		void RowSpatialManager::removeSpatialObject( RowSpatialObjectComponent *value )
		{
			if(needRemoveList == NULL)
			{
				needRemoveList = cocos2d::CCArray::create( );
				needRemoveList->retain();
				needRemoveList->removeAllObjects( );
			}
			if(needRemoveList->containsObject( value ) == false)
			{
				needRemoveList->addObject(value);
			}
		}

		void RowSpatialManager::setup( int rows, int cols )
		{
			m_nRows = rows;
			m_nCols = cols;
			m_nSize = m_nRows * m_nCols;
			std::vector<RowSpatialObjectComponent *> vector;
			for ( int j = 0; j < m_nSize; j++ )
			{
				m_Pool.push_back( vector );
			}
		}

		bool RowSpatialManager::querySpan( int minCol, int maxCol, int minRow, int maxRow, ObjectType *mask, cocos2d::CCArray *results ,RowSpatialObjectComponent* rectSpatial )
		{
//			CCLOG("minCol:%d,maxCol:%d,minRow:%d,maxRow:%d,",minCol,maxCol,minRow,maxRow);
			//out of the bound
			if(minCol >= m_nCols || minRow >= m_nRows)
			{
				return false;
			}
			minCol = std::max( minCol, 0 );
			maxCol = std::min( maxCol, m_nCols );
			minRow = std::max( minRow, 0 );
			maxRow = std::min( maxRow, m_nRows );
			bool foundAny = false;
			for ( int i = minRow; i < maxRow; i++ )
			{
				for ( int j = minCol; j < maxCol; j++ )
				{
					int index = i * m_nCols + j;
					for ( std::vector<RowSpatialObjectComponent *>::iterator iterator = m_Pool.at( index ).begin( ); iterator != m_Pool.at( index ).end( ); ++iterator )
					{
						RowSpatialObjectComponent *spatialObjectComponent = *iterator;
						if ( spatialObjectComponent && spatialObjectComponent->getOwner( ))
						{
							if(mask)
							{
								if(needRemoveList == NULL || (needRemoveList != NULL && needRemoveList->containsObject(spatialObjectComponent) == false))
								{
									if(spatialObjectComponent->getObjectType( )->overlaps( mask ))
									{
										if( rectSpatial == NULL || ( rectSpatial != NULL && rectSpatial->getRect( ).intersectsRect( spatialObjectComponent->getRect( ) )))
										{
											results->addObject( spatialObjectComponent );
											foundAny = true;
										}
									}
								}
							}
						}
					}
				}
			}
			if(needRemoveList != NULL && needRemoveList->count( ) > 0)
			{
				CCObject* pObject;
				CCARRAY_FOREACH(needRemoveList, pObject)
					{
						RowSpatialObjectComponent* spatial = (RowSpatialObjectComponent*)pObject;
						if(spatial)
						{
							fastRemove(spatial);
						}
					}
				needRemoveList->removeAllObjects( );
			}
			return foundAny;
		}

		NS_SF_END
