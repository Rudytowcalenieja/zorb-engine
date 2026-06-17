#include "Frustum.h"

bool IsVisible(const AABB& box, const Frustum& frustum)
{
    for (int i = 0; i < 6; i++)
    {
        const Plane& plane = frustum.planes[i];

        glm::vec3 p;

        p.x = (plane.normal.x >= 0.0f) ? box.max.x : box.min.x;
        p.y = (plane.normal.y >= 0.0f) ? box.max.y : box.min.y;
        p.z = (plane.normal.z >= 0.0f) ? box.max.z : box.min.z;

        if (plane.Distance(p) < 0.0f)
            return false;
    }

    return true;
}
