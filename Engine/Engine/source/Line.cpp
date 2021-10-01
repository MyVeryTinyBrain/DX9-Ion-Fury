#include "EngineBase.h"
#include "Line.h"
#include "GraphicDevice.h"

void Line::DrawLine(const Vec3& start, const Vec3& end, const Color& color, float width)
{
	auto line = GraphicDevice::GetInstance()->GetLine();
	auto device = GraphicDevice::GetInstance()->GetDevice();

	Mat4 view, proj, transform;

	device->GetTransform(D3DTS_VIEW, &view);
	device->GetTransform(D3DTS_PROJECTION, &proj);

	transform = view * proj;

	Vec3 points[2] = { start,end };

	line->SetWidth(width);
	line->Begin();
	line->DrawTransform(points, 2, &transform, color);
	line->End();
}

void Line::DrawLineArray(const Vec3* pointArray, size_t pointCount, const Color& color, float width)
{
	auto line = GraphicDevice::GetInstance()->GetLine();
	auto device = GraphicDevice::GetInstance()->GetDevice();

	Mat4 view, proj, transform;

	device->GetTransform(D3DTS_VIEW, &view);
	device->GetTransform(D3DTS_PROJECTION, &proj);

	transform = view * proj;

	line->SetWidth(width);
	line->Begin();
	line->DrawTransform(pointArray, (DWORD)pointCount, &transform, color);
	line->End();
}

void Line::DrawLineVector(const std::vector<Vec3>& pointVector, const Color& color, float width)
{
	auto line = GraphicDevice::GetInstance()->GetLine();
	auto device = GraphicDevice::GetInstance()->GetDevice();

	const size_t count = pointVector.size();

	if (count < 2)
		return;

	Mat4 view, proj, transform;

	device->GetTransform(D3DTS_VIEW, &view);
	device->GetTransform(D3DTS_PROJECTION, &proj);

	transform = view * proj;

	line->SetWidth(width);
	line->Begin();
	for (size_t i = 1; i < count; ++i)
	{
		DrawMultipleLinePart(transform, pointVector[i - 1] , pointVector[i], color);
	}
	line->End();
}

void Line::DrawLineList(const std::list<Vec3>& pointList, const Color& color, float width)
{
	auto line = GraphicDevice::GetInstance()->GetLine();
	auto device = GraphicDevice::GetInstance()->GetDevice();

	const size_t count = pointList.size();

	if (count < 2)
		return;

	Mat4 view, proj, transform;

	device->GetTransform(D3DTS_VIEW, &view);
	device->GetTransform(D3DTS_PROJECTION, &proj);

	transform = view * proj;

	auto it = pointList.begin();
	++it;

	line->SetWidth(width);
	line->Begin();
	for (; it != pointList.end(); ++it)
	{
		auto before = it;
		--before;

		DrawMultipleLinePart(transform, *before, *it, color);
	}
	line->End();
}

void Line::DrawMultipleLinePart(const Mat4& transform, const Vec3& start, const Vec3& end, const Color& color)
{
	auto line = GraphicDevice::GetInstance()->GetLine();

	Vec3 points[2] = { start,end };

	line->DrawTransform(points, 2, &transform, color);
}
