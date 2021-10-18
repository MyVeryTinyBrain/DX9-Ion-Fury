#pragma once

#include "Component.h"

class RenderTexture;

enum class ProjectionMode
{
	Perspective,
	Orthographic,
};

// 여러대의 카메라가 존재하는 경우 모든 카메라가 렌더에 참여하게 됩니다.
// 이때 여러 번 렌더링되는것을 방지하려면 카메라 컴포넌트를 비활성화 시켜야 합니다.

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

	// 카메라가 렌더링되는 순서입니다.
	int m_cameraOrder = 0;

	// 0 ~ 31 번째 비트 중 켜진 비트의 레이어에 대해서만 카메라에 담습니다.
	uint32_t m_allowRenderLayers = 0xFFFFFFFF;

	// 활성화되면 메인 버퍼의 깊이 버퍼와 스텐실 버퍼를 초기화해 화면에 덮에 그리도록 합니다.
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
	// 텍스쳐가 null이 아니면 메인 화면 대신 이 텍스쳐에 렌더링합니다.

	Ref<RenderTexture> m_renderTexture = nullptr;

private:

	// 인풋 등에 참조될 메인 카메라입니다.
	static Camera* g_mainCamera;

	// 카메라 벡터는 카메라 순서에 의해 정렬된 상태를 유지합니다.
	static std::vector<Camera*> g_cameras;

};

