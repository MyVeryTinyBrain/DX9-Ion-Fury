#pragma once

// The whole vertices of arguments are must be world coordinates.

// These functions must be called within the event rendering function.

// It's better to call DrawLineArray(), If you want to draw multiple lines.
// DrawLine() calls 'Begin/End' on each invokes.

class Line
{
public:

	static void DrawLine(const Vec3& start, const Vec3& end, const Color& color, float width = 1);

	static void DrawLineArray(const Vec3* pointArray, size_t pointCount, const Color& color, float width = 1);

	static void DrawLineVector(const std::vector<Vec3>& pointVector, const Color& color, float width = 1);

	static void DrawLineList(const std::list<Vec3>& pointList, const Color& color, float width = 1);

private:

	static void DrawMultipleLinePart(const Mat4& transform, const Vec3& start, const Vec3& end, const Color& color);

private:

	Line();
};

