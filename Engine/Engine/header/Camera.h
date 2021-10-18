#pragma once

#include "Component.h"

class RenderTexture;

enum class ProjectionMode
{
	Perspective,
	Orthographic,
};

// �������� ī�޶� �����ϴ� ��� ��� ī�޶� ������ �����ϰ� �˴ϴ�.
// �̶� ���� �� �������Ǵ°��� �����Ϸ��� ī�޶� ������Ʈ�� ��Ȱ��ȭ ���Ѿ� �մϴ�.

class Camera : public Component
{
	OverrideComponentFunction(Awake);

	OverrideComponentFunction(OnDestroy);

public:

	Mat4 GetWorldToViewMatrix() const;

	Mat4 GetViewToWorldMatrix() const;

	Mat4 GetViewToProjectionMatrix() const;

	Mat4 GetProjectionToViewMatrix() const;

	__declspec(property(get = GetWorldToViewMatrix)) Mat4 worldToView;

	__declspec(property(get = GetViewToWorldMatrix)) Mat4 viewToWorld;

	__declspec(property(get = GetViewToProjectionMatrix)) Mat4 viewToProjection;

	__declspec(property(get = GetProjectionToViewMatrix)) Mat4 projectionToView;

public:

	float GetFOV() const;

	void SetFOV(float angle);

	float GetAspect() const;

	float GetOrthographicSize() const;

	void SetOrthographicSize(float value);

	float GetOrthographicWidth() const;

	float GetOrthographicHeight() const;

	__declspec(property(get = GetFOV, put = SetFOV)) float fov;

	__declspec(property(get = GetOrthographicSize, put = SetOrthographicSize)) float orthographicSize;

	__declspec(property(get = GetOrthographicWidth)) float orthographicWidth;

	__declspec(property(get = GetOrthographicHeight)) float orthographicHeight;

public:

	int GetCameraOrder() const;

	void SetCameraOrder(int value);

	bool IsOverlapMode() const;

	void SetOverlapMode(bool value);

	uint32_t GetAllowRenderLayers() const;

	void SetAllowRenderLayers(uint32_t value);

	ProjectionMode GetProjectionMode() const;

	void SetProjectionMode(ProjectionMode mode);

	const Ref<RenderTexture>& GetRenderTexture() const;

	void SetRenderTexture(const Ref<RenderTexture>& value);

	__declspec(property(get = GetCameraOrder, put = SetCameraOrder)) int cameraOrder;

	__declspec(property(get = IsOverlapMode, put = SetOverlapMode)) bool overlapMode;

	__declspec(property(get = GetAllowRenderLayers, put = SetAllowRenderLayers)) uint32_t allowRenderLayers;

	__declspec(property(get = GetProjectionMode, put = SetProjectionMode)) ProjectionMode projectionMode;

	__declspec(property(get = GetRenderTexture, put = SetRenderTexture)) const Ref<RenderTexture>& renderTexture;

public:

	static Camera* GetMainCamera();

	static void SetMainCamera(Camera* camera);

	static size_t GetCameraCount();

	static Camera* GetCamera(unsigned int index);

private:

	static void SortCamerasByOrder();

private:

	// ī�޶� �������Ǵ� �����Դϴ�.
	int m_cameraOrder = 0;

	// 0 ~ 31 ��° ��Ʈ �� ���� ��Ʈ�� ���̾ ���ؼ��� ī�޶� ����ϴ�.
	uint32_t m_allowRenderLayers = 0xFFFFFFFF;

	// Ȱ��ȭ�Ǹ� ���� ������ ���� ���ۿ� ���ٽ� ���۸� �ʱ�ȭ�� ȭ�鿡 ���� �׸����� �մϴ�.
	bool m_overlap = true;

	ProjectionMode m_projectionMode = ProjectionMode::Perspective;

	// Perspective 

	float m_fovAngle;

	float m_aspect;

	float m_near;

	float m_far;

	bool m_isPerspective;

	// Orthographic

	float m_orthographicSize = 1.0f;

	// Render texture
	// �ؽ��İ� null�� �ƴϸ� ���� ȭ�� ��� �� �ؽ��Ŀ� �������մϴ�.

	Ref<RenderTexture> m_renderTexture = nullptr;

private:

	// ��ǲ � ������ ���� ī�޶��Դϴ�.
	static Camera* g_mainCamera;

	// ī�޶� ���ʹ� ī�޶� ������ ���� ���ĵ� ���¸� �����մϴ�.
	static std::vector<Camera*> g_cameras;

};

