#pragma once

class LayerManager
{
public:

	LayerManager();

	~LayerManager();

	// 0-0 레이어간의 충돌을 제외한 모든 레이어들의 충돌을 비활성화 합니다.
	void Reset();

	// A 레이어와 B 레이어의 충돌을 설정합니다.
	// A, B 는 32보다 작은 정수여야 합니다.
	// 이후 Collider 컴포넌트에 대해서 ApplyLayer 함수를 호출합니다.
	void SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision);

	// A 레이어와 B 레이어의 충돌을 확인합니다.
	// A, B 는 32보다 작은 정수여야 합니다.
	bool IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB);

	// 레이어의 충돌 비트를 반환합니다.
	PxU32 GetCollisionBits(unsigned int layerIndex) const;

private:

	PxU32 m_filter[PhysicsLayerMax];
};

