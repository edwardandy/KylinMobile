// Created by Luke on 13-9-10.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __ArmatureRenderer_H_
#define __ArmatureRenderer_H_

#include <iostream>
#include "../DisplayObjectRenderer.h"
#include "CocoStudio/Armature/CCArmature.h"
#include "../../core/SmashMacros.h"

USING_NS_CC_EXT;
USING_NS_CC;
NS_SF_BEGIN
		class ArmatureRenderer : public DisplayObjectRenderer
		{
		public:
			ArmatureRenderer( );

			virtual ~ArmatureRenderer( );

			virtual void onRemove( );

			virtual void onFrame( float deltaTime );

			virtual void onAdd( );

			static ArmatureRenderer *create( const char *name, int zOrder = 0 );

			virtual bool init( const char *name, int zOrder = 0 );

			//! A weak reference to the CCArmature
			CC_SYNTHESIZE_READONLY(CCArmature *, m_pArmature, Armature);
		};

NS_SF_END

#endif //__ArmatureRenderer_H_
