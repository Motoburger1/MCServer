#include "Globals.h"

#include "FallingBlock.h"
#include "World.h"
#include "ClientHandle.h"


CLASS_DEFINITION( cFallingBlock, cEntity )


cFallingBlock::cFallingBlock(const Vector3i & a_BlockPosition, BLOCKTYPE a_BlockType)
	: super( a_BlockPosition.x + 0.5f, a_BlockPosition.y + 0.5f, a_BlockPosition.z + 0.5f )
	, m_BlockType( a_BlockType )
	, m_OriginalPosition( a_BlockPosition )
	, m_SpeedY( 0 )
{
}





cFallingBlock::~cFallingBlock()
{
}





void cFallingBlock::Initialize(cWorld * a_World)
{
	super::Initialize( a_World );
	a_World->BroadcastSpawn(*this);
}





void cFallingBlock::SpawnOn(cClientHandle & a_ClientHandle)
{
	a_ClientHandle.SendSpawnObject(*this, 70, m_BlockType, 0, 0, 0);
}





void cFallingBlock::Tick(float a_Dt)
{
	float MilliDt = a_Dt * 0.001f;
	m_SpeedY -= MilliDt * 9.8f;
	m_Pos.y += m_SpeedY * MilliDt;

	//GetWorld()->BroadcastTeleportEntity(*this); // Testing position

	Vector3i BlockPos( m_OriginalPosition.x, (int)(m_Pos.y-0.5), m_OriginalPosition.z );
	if( !IsPassable( GetWorld()->GetBlock( BlockPos ) ) )
	{
		Destroy();
		GetWorld()->SetBlock( BlockPos.x, BlockPos.y+1, BlockPos.z, m_BlockType, 0 );
	}
}