#pragma once

#include <glm/glm.hpp>

struct AABB
{
	glm::vec3 min;
	glm::vec3 max;
};

struct Plane
{
	glm::vec3 normal;
	float d;

	float Distance(const glm::vec3& p) const
	{
		return glm::dot(normal, p) + d;
	}

	void Normalize()
	{
		float len = glm::length(normal);
		normal /= len;
		d /= len;
	}
};

struct Frustum
{
	Plane planes[6];

	enum
	{
		LEFT = 0,
		RIGHT,
		BOTTOM,
		TOP,
		NEAR_,
		FAR_
	};

	void Update(const glm::mat4& vp)
	{
		// Left
		planes[LEFT].normal.x = vp[0][3] + vp[0][0];
		planes[LEFT].normal.y = vp[1][3] + vp[1][0];
		planes[LEFT].normal.z = vp[2][3] + vp[2][0];
		planes[LEFT].d = vp[3][3] + vp[3][0];

		// Right
		planes[RIGHT].normal.x = vp[0][3] - vp[0][0];
		planes[RIGHT].normal.y = vp[1][3] - vp[1][0];
		planes[RIGHT].normal.z = vp[2][3] - vp[2][0];
		planes[RIGHT].d = vp[3][3] - vp[3][0];

		// Bottom
		planes[BOTTOM].normal.x = vp[0][3] + vp[0][1];
		planes[BOTTOM].normal.y = vp[1][3] + vp[1][1];
		planes[BOTTOM].normal.z = vp[2][3] + vp[2][1];
		planes[BOTTOM].d = vp[3][3] + vp[3][1];

		// Top
		planes[TOP].normal.x = vp[0][3] - vp[0][1];
		planes[TOP].normal.y = vp[1][3] - vp[1][1];
		planes[TOP].normal.z = vp[2][3] - vp[2][1];
		planes[TOP].d = vp[3][3] - vp[3][1];

		// Near
		planes[NEAR_].normal.x = vp[0][3] + vp[0][2];
		planes[NEAR_].normal.y = vp[1][3] + vp[1][2];
		planes[NEAR_].normal.z = vp[2][3] + vp[2][2];
		planes[NEAR_].d = vp[3][3] + vp[3][2];

		// Far
		planes[FAR_].normal.x = vp[0][3] - vp[0][2];
		planes[FAR_].normal.y = vp[1][3] - vp[1][2];
		planes[FAR_].normal.z = vp[2][3] - vp[2][2];
		planes[FAR_].d = vp[3][3] - vp[3][2];

		for (int i = 0; i < 6; i++)
			planes[i].Normalize();
	}
};

bool IsVisible(const AABB& box, const Frustum& frustum);