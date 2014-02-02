// Created by Luke on 13-12-2.
//


#include "EntityTest.h"
#include "smartfish.h"

USING_NS_SF;

EntityTest::EntityTest( )
{
	Entity *entity = Entity::create( "world" );

	RowSpatialManager *rowSpatialManager = RowSpatialManager::getInstance( );
	rowSpatialManager->setup( 10, 10 );
	for ( int i = 0; i < 10; i++ )
	{
		for ( int j = 0; j < 10; j++ )
		{
			RowSpatialObjectComponent *rowSpatialObjectComponent = new RowSpatialObjectComponent( );
			rowSpatialObjectComponent->setOwner( entity );
			rowSpatialObjectComponent->setRenderCol( i );
			rowSpatialObjectComponent->setRenderRow( j );
			rowSpatialObjectComponent->setRenderRow( j );
			rowSpatialManager->addSpatialObject( rowSpatialObjectComponent );
		}
	}
	entity->retain( );

}

EntityTest::~EntityTest( )
{

}
