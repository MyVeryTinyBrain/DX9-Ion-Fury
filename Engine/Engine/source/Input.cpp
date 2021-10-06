#include "EngineBase.h"
#include "Input.h"
#include "GraphicDevice.h"
#include "Camera.h"

#define Instance (g_instance)

ImplementSingletone(Input);

bool Input::GetKey(const Key& key)
{
	//return Instance.m_keyState[(unsigned char)key];
	return GetAsyncKeyState((int)key);
}

const bool& Input::GetKeyDown(const Key& key)
{
	return Instance.m_downState[(unsigned char)key];
}

const bool& Input::GetKeyUp(const Key& key)
{
	return Instance.m_upState[(unsigned char)key];
}

const float& Input::GetMouseWheelDelta()
{
	return Instance.m_wheelDelta;
}

Vec2 Input::GetMousePositionInViewport()
{
	POINT mouse;

	GetCursorPos(&mouse);

	ScreenToClient(GraphicDevice::GetInstance()->GetWindowHandle(), &mouse);

	return mouse;
}

Vec3 Input::GetMousePositionInProjSpace()
{
	auto device = GraphicDevice::GetInstance();
	Vec2 wndSize = device->GetClientSize();
	Vec2 mouse = GetMousePositionInViewport();

	return Vec3(mouse.x / wndSize.x * 2 - 1, 1 - mouse.y / wndSize.y * 2, 0);
}

Vec3 Input::GetMousePositionInViewSpace()
{
	Camera* mainCamera = Camera::GetMainCamera();

	if (!mainCamera)
		return Vec3::zero();

	Vec3 mouse = GetMousePositionInProjSpace();

	Mat4 projToView = mainCamera->projectionToView;

	return projToView.MultiplyPoint(mouse);
}

void Input::GetMouseWorldRay(Vec3& rayPoint, Vec3& rayDir)
{
	Camera* mainCamera = Camera::GetMainCamera();

	if (!mainCamera)
		return;

	Mat4 viewToWorld = mainCamera->viewToWorld;

	Vec3 mouse = GetMousePositionInViewSpace();

	Vec3 viewRayPoint = Vec3(0, 0, 0);
	Vec3 viewRayDir = mouse - viewRayPoint;
	viewRayDir.Normalize();

	rayPoint = viewToWorld.MultiplyPoint(viewRayPoint);
	rayDir = viewToWorld.MultiplyVector(viewRayDir);
}

void Input::WindowProcedure(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_LBUTTONDOWN:
			SetKeyDown((unsigned char)Key::LeftMouse);
			break;
		case WM_RBUTTONDOWN:
			SetKeyDown((unsigned char)Key::RightMouse);
			break;
		case WM_MBUTTONDOWN:
			SetKeyDown((unsigned char)Key::WhileMouse);
			break;
		case WM_LBUTTONUP:
			SetKeyUp((unsigned char)Key::LeftMouse);
			break;
		case WM_RBUTTONUP:
			SetKeyUp((unsigned char)Key::RightMouse);
			break;
		case WM_MBUTTONUP:
			SetKeyUp((unsigned char)Key::WhileMouse);
			break;
		case WM_MOUSEWHEEL:
			SetWheelDelta(HIWORD(wParam));
			break;
		case WM_KEYDOWN:
			SetKeyDown((unsigned char)wParam);
			break;
		case WM_KEYUP:
			SetKeyUp((unsigned char)wParam);
			break;
	}
}

void Input::SetUsed()
{
	if (m_hasDown)
		ZeroMemory(m_downState, sizeof(m_downState));

	if (m_hasUp)
		ZeroMemory(m_upState, sizeof(m_upState));

	m_hasDown = false;

	m_hasUp = false;

	m_wheelDelta = 0;
}

void Input::SetKeyDown(unsigned char key)
{
	if (m_keyState[key])
		return;

	m_hasDown = true;

	m_downState[key] = true;

	m_keyState[key] = true;
}

void Input::SetKeyUp(unsigned char key)
{
	if (!m_keyState[key])
		return;

	m_hasUp = true;

	m_upState[key] = true;

	m_keyState[key] = false;
}

void Input::SetWheelDelta(short wParamHiword)
{
	if (wParamHiword > 0) ++m_wheelDelta;
	else --m_wheelDelta;
}
