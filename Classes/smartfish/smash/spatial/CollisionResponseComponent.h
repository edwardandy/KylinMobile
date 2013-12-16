//
// Created by Luke on 13-11-22.
//



#ifndef __CollisionResponseComponent_H_
#define __CollisionResponseComponent_H_

#include "../strategy/StrategyContainingComponent.h"
#include "RowSpatialObjectComponent.h"
#include "../conditional/Conditional.h"
#include "../util/ObjectType.h"
NS_SF_BEGIN
		class CollisionResponseComponent : public smartfish::StrategyContainingComponent
		{
		public:
			CollisionResponseComponent( );

			virtual ~CollisionResponseComponent( );

			virtual void onAdd( );

			virtual void onRemove( );

			virtual void onTick( float deltaTime );

			RowSpatialObjectComponent *getSpatial( ) const
			{
				return m_Spatial;
			}

			void setSpatial( RowSpatialObjectComponent *m_Spatial )
			{
				CollisionResponseComponent::m_Spatial = m_Spatial;
			}

			RowSpatialManager *getRowSpatialManager( ) const
			{
				return m_RowSpatialManager;
			}

			void setRowSpatialManager( RowSpatialManager *m_RowSpatialManager )
			{
				CollisionResponseComponent::m_RowSpatialManager = m_RowSpatialManager;
			}

			ObjectType *getObjectMask( ) const
			{
				return m_ObjectMask;
			}

			void setObjectMask( ObjectType *value )
			{
				value->retain( );
				CollisionResponseComponent::m_ObjectMask = value;
			}

			Conditional *getConditional( ) const
			{
				return m_Conditional;
			}

			void setConditional( Conditional *m_Conditional )
			{
				CollisionResponseComponent::m_Conditional = m_Conditional;
			}
		private:
			void checkCollision( );
		private:
			RowSpatialObjectComponent* m_Spatial;
			RowSpatialManager* m_RowSpatialManager;
			ObjectType* m_ObjectMask;
			Conditional* m_Conditional;

			cocos2d::CCArray* m_CollisionResults;
			bool m_IsConditionalTrue;

			int minCol;
			int maxCol;
			int minRow;
			int maxRow;
		protected:
			virtual void onStop( );

			virtual void onResume( );
		};

		NS_SF_END


#endif //__CollisionResponseComponent_H_
