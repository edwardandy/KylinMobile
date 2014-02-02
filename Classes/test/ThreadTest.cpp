//
// Created by Luke on 13-11-17.
//


#include "ThreadTest.h"
#include "cocos2d.h"

ThreadTest::ThreadTest( )
{
	ThreadPool *pool = new ThreadPool( 4 );
	for ( int i = 0; i < 10; i++ )
	{
		if(i>=4)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			sleep( 1 );
#elseif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			Sleep(1);
#endif
		}
		ThreadTaskTest *task = new ThreadTaskTest( i );
		pool->addTask( task );
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sleep( 5 );
#elseif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Sleep(5);
#endif
	pool->clearAllThread();
}

ThreadTest::~ThreadTest( )
{

}

ThreadTaskTest::ThreadTaskTest( int id )
{
	this->id = id;
}

ThreadTaskTest::~ThreadTaskTest( )
{

}

void ThreadTaskTest::run( )
{
//	for(int i =0 ;i<1;i++)
//	{
//		cocos2d::CCLog( "%d===== gogogo ==== " ,id);
//	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sleep( 2 );
#elseif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Sleep(2);
#endif
}
