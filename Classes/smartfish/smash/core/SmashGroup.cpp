//
//  SmashGroup.cpp
//  Smash
//
//  Created by Luke on 13-3-17.
//
//

#include "SmashGroup.h"
#include "Smash.h"

NS_SF_BEGIN
		SmashGroup::SmashGroup( ):SmashObject( )
		{

		}

		smartfish::SmashGroup *SmashGroup::create( std::string name )
		{
			SmashGroup *group = new SmashGroup( );
			if ( group->initWithName( name ) )
			{
				group->initialize( );
			}
			return group;
		}

		SmashGroup::~SmashGroup( )
		{
			for ( std::vector<SmashObject * >::iterator iter = items.begin( ); iter != items.end( ); )
			{
				if ( *iter )
				{
					SmashObject *p = *iter;
					iter = items.erase( iter );
					delete p;
				}
				else
				{
					iter++;
				}
			}
			items.clear( );
		}

		void SmashGroup::initialize( )
		{
			if ( getOwningGroup( ) == NULL)
			{
				setOwningGroup( Smash::getRootGroup() );
			}
			SmashObject::initialize( );
		}

		void SmashGroup::destory( )
		{
			SmashObject::destory( );
			for ( std::vector<SmashObject *>::iterator it = items.begin( ); it != items.end( ); ++it )
			{
				SmashObject *smashObject = *it;
				if ( smashObject )
				{
					smashObject->destory( );
				}
			}
			items.clear( );
		}

		void SmashGroup::noteRemove( smartfish::SmashObject *object )
		{
			for ( std::vector<SmashObject * >::iterator iter = items.begin( ); iter != items.end( ); /*++iter*/)
			{
				if ( object == *iter )
				{
					iter = items.erase( iter );
				}
				else
				{
					iter++;
				}
			}
		}

		void SmashGroup::noteAdd( smartfish::SmashObject *object )
		{
			items.push_back( object );
		}

		int SmashGroup::size( )
		{
			return items.size( );
		}

		/**
		 * Does this SmashGroup directly contain the specified object?
		 */
		bool SmashGroup::contains( smartfish::SmashObject *object )
		{
			return ( object->getOwningGroup( ) == this );
		}

		smartfish::SmashObject *SmashGroup::lookup( std::string name )
		{
			for ( std::vector<smartfish::SmashObject * >::iterator iter = items.begin( ); iter != items.end( ); ++iter )
			{
				smartfish::SmashObject *object = *iter;
				if ( name.compare( object->getName( ) ) == 0 )
				{
					return *iter;
				}
			}
			printf( "lookup failed! Entity by the name does not exist\n" );
			assert(false);
			return NULL;
		}

		NS_SF_END
