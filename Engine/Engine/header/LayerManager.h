#pragma once

class LayerManager
{
public:

	LayerManager();

	~LayerManager();

	// 0-0 ���̾�� �浹�� ������ ��� ���̾���� �浹�� ��Ȱ��ȭ �մϴ�.
	void Reset();

	// A ���̾�� B ���̾��� �浹�� �����մϴ�.
	// A, B �� 32���� ���� �������� �մϴ�.
	// ���� Collider ������Ʈ�� ���ؼ� ApplyLayer �Լ��� ȣ���մϴ�.
	void SetLayerCollisions(unsigned int layerIndexA, unsigned int layerIndexB, bool collision);

	// A ���̾�� B ���̾��� �浹�� Ȯ���մϴ�.
	// A, B �� 32���� ���� �������� �մϴ�.
	bool IsCollisionLayers(unsigned int layerIndexA, unsigned int layerIndexB);

	// ���̾��� �浹 ��Ʈ�� ��ȯ�մϴ�.
	PxU32 GetCollisionBits(unsigned int layerIndex) const;

private:

	PxU32 m_filter[PhysicsLayerMax];
};

