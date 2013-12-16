//
//  Entity.cpp
//  Smash
//
//  Created by Luke on 13-3-17.
//
//

#include <assert.h>
#include "Entity.h"
#include "EntityComponent.h"
#include "cocos2d.h"

NS_SF_BEGIN
		Entity::Entity( ):smartfish::SmashObject( )
		{
			mDeferring = true;
			isRunning = false;
		}

		Entity::~Entity( )
		{
			CCLOG("~Entity");
			for ( std::map<std::string, EntityComponent * >::iterator iter = mComponents.begin( ); iter != mComponents.end( ); )
			{
				if ( iter->second )
				{
					EntityComponent *p = iter->second;
					p->setOwner( NULL );
					CC_SAFE_DELETE(p);
				}
				else
				{
					iter++;
				}
			}
			mComponents.clear( );
		}

		smartfish::Entity *smartfish::Entity::create( std::string name )
		{
			Entity *entity = new Entity( );
			if ( entity->initWithName( name ) )
			{
				return entity;
			}
			return NULL;
		}

		void Entity::initialize( )
		{
			SmashObject::initialize( );

			// Stop deferring and let init happen.
			setDeferring( false );
			isRunning = true;
		}

		void Entity::destory( )
		{
//			CCLOG("Entity::destory start,name:%s", this->getName( ).c_str( ));
			for ( std::map<std::string, EntityComponent * >::iterator iter = mComponents.begin( ); iter != mComponents.end( ); ++iter )
			{
				if ( iter->second )
				{
					EntityComponent *component = iter->second;
					if ( component )
					{
						component->doRemove( );
					}
					else
					{
						CCLOG("[Entity.destory] component is null");
					}
				}
			}
			SmashObject::destory( );
			this->release( );
//			CCLOG("Entity::destory end");
		}

		void Entity::stop( )
		{
			if ( isRunning )
			{
				isRunning = false;
				for ( std::map<std::string, EntityComponent * >::iterator iter = mComponents.begin( ); iter != mComponents.end( ); ++iter )
				{
					if ( iter->second )
					{
						EntityComponent *component = iter->second;
						if ( component )
						{
							component->doStop( );
						}
						else
						{
							CCLOG("[Entity.stop] component is null");
						}
					}
				}
			}
		}

		void Entity::resume( )
		{
			if ( !isRunning )
			{
				isRunning = true;
				for ( std::map<std::string, EntityComponent * >::iterator iter = mComponents.begin( ); iter != mComponents.end( ); ++iter )
				{
					if ( iter->second )
					{
						EntityComponent *component = iter->second;
						if ( component )
						{
							component->doResume( );
						}
						else
						{
							CCLOG("[Entity.stop] component is null");
						}
					}
				}
			}
		}

		void Entity::setDeferring( bool value )
		{
			if ( mDeferring && value == false )
			{
				// Loop as long as we keep finding deferred stuff, the
				// dictionary delete operations can mess up ordering so we have
				// to check to avoid missing stuff. This is a little lame but
				// our previous implementation involved allocating lots of
				// temporary helper objects, which this avoids, so there you go.
//				bool foundDeferred = true;
//				while ( foundDeferred )
//				{
//					foundDeferred = false;
				for ( std::map<std::string, EntityComponent *>::iterator iter = mComponents.begin( ); iter != mComponents.end( ); )
				{
					std::string key = iter->first;
					std::string letter = key.substr( 0, 1 );
					if ( letter != "!" )
					{
						++iter;
					}
					else
					{
						// It's a deferral, so init it...
//							printf("entity:%s,component:%s\n",this->getName( ).c_str( ),iter->second->getName( ).c_str( ));
						doInitialize( iter->second );
						mComponents.erase( iter++ );
						// Indicate we found stuff so keep looking. Otherwise
						// we may miss some.
//							foundDeferred = true;
					}
				}
//				}
			}
			mDeferring = value;
		}

		bool Entity::getDeferring( )
		{
			return mDeferring;
		}

		void Entity::addComponent( smartfish::EntityComponent *component, std::string name )
		{
			if ( !name.empty( ) )
			{
				component->setName( name );
			}
			if ( component->getName( ).empty( ) )
			{
				printf( "Can't add component with no name." );
				assert(false);
			}
			if ( mComponents.find( component->getName( ) ) != mComponents.end( ) || mComponents.find( "!" + component->getName( ) ) != mComponents.end( ) )
			{
				printf( "Can not add a name already exists." );
				assert(false);
			}

			component->retain( );
			mComponents[ name ] = component;
			component->setOwner( this );

			// is there a way to  set field directly when the component is present?
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			//    if(hasOwnProperty(component.name))
			//       this[component.name] = component;
			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

			// Defer or add now.
			if ( mDeferring )
				mComponents[ "!" + component->getName( ) ] = component;
			else
				doInitialize( component );
		}

		void Entity::removeComponent( smartfish::EntityComponent *component )
		{
			if ( component->getOwner( ) != this )
			{
				printf( "Tried to remove a component that does not belong to this Entity." );
				assert(false);
			}

			std::map<std::string, EntityComponent *>::iterator iter = mComponents.find( component->getName( ) );
			if ( iter != mComponents.end( ) )
			{
				mComponents.erase( iter );
			}

			component->doRemove( );
			component->setOwner( NULL );
			component->release( );
		}


		void Entity::removeComponentByName( std::string value )
		{
			EntityComponent *component = lookupComponent( value );
			if ( component == NULL)
			{
				printf( "Tried to remove a component that does not exist in this entity." );
				return;
			}
			removeComponent(component);
		}

		void Entity::doInitialize( EntityComponent *component )
		{
			component->setOwner( this );
			component->doAdd( );
		}

		EntityComponent *Entity::lookupComponent( std::string name )
		{
			if ( mComponents.find( name ) != mComponents.end( ) )
			{
				return mComponents[ name ];
			}
			else
			{
				return NULL;
			}
		}

		EntityComponent *Entity::lookupComponentByEntity( std::string name, std::string entityName )
		{
			smartfish::Entity *entity = lookupEntityFromGroup( entityName );
			if ( entity == NULL)
			{
				return NULL;
			}
			return entity->lookupComponent( name );
		}

		std::vector<EntityComponent * > Entity::getAllComponents( )
		{
			std::vector<EntityComponent * > out;
			for ( std::map<std::string, EntityComponent *>::iterator iter = mComponents.begin( ); iter != mComponents.end( ); ++iter )
			{
				out.push_back( iter->second );
			}
			return out;
		}

		smartfish::Entity *Entity::lookupEntityFromGroup( std::string name )
		{
			if ( this->getOwningGroup( ) == NULL)
			{
				return NULL;
			}
			Entity *entity = dynamic_cast<smartfish::Entity * >(this->getOwningGroup( )->lookup( name ));
			return entity;
		}

		NS_SF_END
