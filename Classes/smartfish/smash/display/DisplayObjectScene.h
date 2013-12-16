// Created by Luke on 13-8-20.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __IDisplayObjectScene_H_
#define __IDisplayObjectScene_H_

#include <iostream>
#include "cocos-ext.h"
#include "cocos2d.h"
#include "../time/AnimatedComponent.h"

USING_NS_CC;
NS_SF_BEGIN
		class DisplayObjectRenderer;

		class DisplayObjectScene : public smartfish::EntityComponent
		{
		public:
			DisplayObjectScene( );

			virtual ~DisplayObjectScene( );

			virtual void add( DisplayObjectRenderer *renderer );

			virtual void remove( DisplayObjectRenderer *renderer );

			virtual void onFrame( float deltaTime );

			virtual void onAdd( );

			virtual void onRemove( );

			virtual void setSceneView(CCLayer* sceneView);
		private:
			CCLayer *m_Container;
		protected:
			virtual void onStop( );

			virtual void onResume( );
		};

NS_SF_END
#endif //__IDisplayObjectScene_H_
