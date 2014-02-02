//  ProcessManager.cpp
//  Smash
//
//  Created by Luke on 13-3-17.
//
//

#include "ProcessManager.h"
#include "TickedComponent.h"
#include "AnimatedComponent.h"

USING_NS_CC;
NS_SF_BEGIN
		ProcessManager *ProcessManager::mInstance = NULL;

		ProcessManager::ProcessManager( )
		:TICKS_PER_SECOND( 60 ),
		TICK_RATE( 1.0 / ( float ) TICKS_PER_SECOND ),
		TICK_RATE_MS( TICK_RATE * 1000 ),
		MAX_TICKS_PER_FRAME( 5 )
		{
			virtualTime = 0;
			lastTime = -1;
			elapsed = 0;
			started = false;
			disableSlowWarning = true;
			duringAdvance = false;

			animatedObjects.clear( );
			tickedObjects.clear( );

			m_pScheduler = new CCScheduler( );
			CCDirector::sharedDirector( )->getScheduler( )->scheduleUpdateForTarget( m_pScheduler, 0, false );
		}

		ProcessManager::~ProcessManager( )
		{
			animatedObjects.clear( );
			tickedObjects.clear( );
		}

		ProcessManager *ProcessManager::getInstance( )
		{
			if ( mInstance == NULL)
			{
				mInstance = new ProcessManager( );
			}
			return mInstance;
		}

		void ProcessManager::initialize( )
		{
			if ( !started )
			{
				start( );
			}
		}

		void ProcessManager::destory( )
		{
			if ( started )
			{
				stop( );
			}
		}

		void ProcessManager::set_timeScale( float value )
		{
			m_pScheduler->setTimeScale( value );
		}

		float ProcessManager::get_timeScale( )
		{
			return m_pScheduler->getTimeScale( );
		}

		void ProcessManager::start( )
		{
			if ( started )
			{
				CCLOG("[ProcessManager] The ProcessManager is already started.");
				return;
			}
			lastTime = -1.0;
			elapsed = 0.0;
			m_pScheduler->scheduleSelector( schedule_selector(ProcessManager::onFrame), this, TICK_RATE, kCCRepeatForever, 0.0f, false );
			started = true;
		}

		void ProcessManager::stop( )
		{
			if ( !started )
			{
				cocos2d::CCLog( "[ProcessManager] The ProcessManager isn't started." );
				return;
			}
			started = false;
			m_pScheduler->unscheduleSelector( schedule_selector(ProcessManager::onFrame), this );
		}

		bool ProcessManager::isTicking( )
		{
			return started;
		}

		void ProcessManager::addAnimatedObject( AnimatedComponent *object, float priority )
		{
			addObject( object, priority, animatedObjects );
		}

		void ProcessManager::addTickedObject( TickedComponent *object, float priority )
		{
			addObject( object, priority, tickedObjects );
		}

		void ProcessManager::addObject( CCObject *object, float priority, std::vector<ProcessObject *> &vector )
		{
			ProcessObject *processObject = new ProcessObject( );
			processObject->listener = object;
			processObject->priority = priority;
			processObject->shouldRemove = false;
			if ( duringAdvance )
			{
				processObject->vector = &vector;
				needAddList.push_back( processObject );
				return;
			}

			if ( !started )
			{
				start( );
			}
			std::vector<ProcessObject * >::iterator position = vector.end( );

			for ( std::vector<ProcessObject * >::iterator iter = vector.begin( ); iter != vector.end( ); ++iter )
			{
				if ( *iter == NULL)
				{
					continue;
				}
				if ( ( ( ProcessObject * ) *iter )->listener == object )
				{
					cocos2d::CCLog( "[ProcessManager] This object has already been added to the process manager." );
					return;
				}
				if ( ( ( ProcessObject * ) *iter )->priority < priority )
				{
					position = iter;
					break;
				}
			}

			if ( position >= vector.begin( ) && position < vector.end( ) )
			{
				vector.insert( position, processObject );
			}
			else
			{
				vector.push_back( processObject );
			}
		}

		void ProcessManager::removeAnimatedObject( smartfish::AnimatedComponent *object )
		{
			removeObject( object, animatedObjects );
		}

		void ProcessManager::removeTickedObject( TickedComponent *object )
		{
			removeObject( object, tickedObjects );
		}

		void ProcessManager::removeObject( void *object, std::vector<ProcessObject * > &vector )
		{
			if ( tickedObjects.size( ) + animatedObjects.size( ) == 1 )
			{
				stop( );
			}
			for ( std::vector<ProcessObject * >::iterator iter = vector.begin( ); iter != vector.end( );)
			{
				if ( *iter == NULL)
				{
					++iter;
					continue;
				}
				if ( ( ( ProcessObject * ) *iter )->listener == object )
				{
					( ( ProcessObject * ) *iter )->listener = NULL;
					if ( duringAdvance )
					{
						( ( ProcessObject * ) *iter )->shouldRemove = true;
						needPurgeEmpty = true;
						++iter;
					}
					else
					{
						iter = vector.erase( iter );
					}
					return;
				}
				else
				{
					++iter;
				}
			}
			cocos2d::CCLog( "[ProcessManager] This object has not been added to the process manager." );
		}

		void ProcessManager::onFrame( float dt )
		{
			virtualTime += dt;
//			cocos2d::CCLog("[ProcessManager] time:%f", virtualTime);
			if ( lastTime < 0 )
			{
				lastTime = virtualTime;
				return;
			}

			m_pScheduler->pauseTarget( this );

			frameCounter++;
			// Calculate time since last frame and advance that much.
			float deltaTime = float( virtualTime - lastTime ) * 1000 * get_timeScale( );
			advance( deltaTime );
			lastTime = virtualTime;

			m_pScheduler->resumeTarget( this );
		}

		void ProcessManager::advance( float deltaTime, bool suppressSafety )
		{
			elapsed += deltaTime;

			// Perform ticks, respecting tick caps.
			int tickCount = 0;
//			cocos2d::CCLog("elapsed:%f",elapsed);
//			cocos2d::CCLog("TICK_RATE_MS:%f",TICK_RATE_MS);
			while ( elapsed >= TICK_RATE_MS && ( suppressSafety || tickCount < MAX_TICKS_PER_FRAME ) )
			{
				fireTick( );
				tickCount++;
			}

			// Safety net - don't do more than a few ticks per frame to avoid death spirals.
			if ( tickCount >= MAX_TICKS_PER_FRAME && !suppressSafety && !disableSlowWarning )
			{
				// By default, only show when profiling.
				cocos2d::CCLog( "[ProcessManager]Exceeded maximum number of ticks for frame ( %f ms dropped) .", elapsed );
			}

			// Make sure that we don't fall behind too far. This helps correct
			// for short-term drops in framerate as well as the scenario where
			// we are consistently running behind.
			if ( elapsed < 0 )
			{
				elapsed = 0;
			}
			if ( elapsed > 0.3 )
			{
				elapsed = 0.3;
			}

			duringAdvance = true;

			for ( std::vector<smartfish::ProcessObject * >::iterator iter = animatedObjects.begin( ); iter != animatedObjects.end( ); ++iter )
			{
				ProcessObject *animatedObject = *iter;
				if ( animatedObject != NULL && animatedObject->shouldRemove == false)
				{
					( ( AnimatedComponent * ) animatedObject->listener )->onFrame( deltaTime );
				}
			}
			duringAdvance = false;


			// delete
			if ( needPurgeEmpty )
			{
				needPurgeEmpty = false;
				std::vector<smartfish::ProcessObject * >::iterator iter;
				for ( iter = animatedObjects.begin( ); iter != animatedObjects.end( ); )
				{
					if ( ( ( ProcessObject * ) *iter )->shouldRemove == true)
					{
						delete *iter;
						iter = animatedObjects.erase( iter );
					}
					else
					{
						++iter;
					}
				}

				for ( iter = tickedObjects.begin( ); iter != tickedObjects.end( ); )
				{
					if ( ( ( ProcessObject * ) *iter )->shouldRemove == true)
					{
						delete *iter;
						iter = tickedObjects.erase( iter );
					}
					else
					{
						++iter;
					}
				}
			}

			//add
			if ( needAddList.size( ) > 0 )
			{
				std::vector<smartfish::ProcessObject * >::iterator it;
				for ( it = needAddList.begin( ); it != needAddList.end( ); ++it )
				{
					ProcessObject *process = *it;
					addObject( process->listener, process->priority, *process->vector );
				}
			}
			needAddList.clear( );
		}

		void ProcessManager::fireTick( )
		{
			duringAdvance = true;

			for ( std::vector<smartfish::ProcessObject * >::iterator iter = tickedObjects.begin( ); iter != tickedObjects.end( ); ++iter )
			{
				ProcessObject *tickedObject = *iter;
				if ( tickedObject != NULL && tickedObject->shouldRemove == false)
				{
					( ( TickedComponent * ) tickedObject->listener )->onTick( TICK_RATE );
				}
			}
			duringAdvance = false;
			elapsed -= TICK_RATE_MS;
		}

		NS_SF_END
