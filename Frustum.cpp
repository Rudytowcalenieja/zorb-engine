//#include "Frustum.h"
//
//struct Plane
//{
//    glm::vec3 normal;
//    float distance;
//
//    Plane() = default;
//
//    Plane(const glm::vec3& point, const glm::vec3& n)
//    {
//        normal = glm::normalize(n);
//        distance = glm::dot(normal, point);
//    }
//};
//
//struct Frustum
//{
//    Plane topFace;
//    Plane bottomFace;
//
//    Plane rightFace;
//    Plane leftFace;
//
//    Plane farFace;
//    Plane nearFace;
//};
//
//Frustum createFrustumFromCamera(Camera& cam, float aspect, float fovY,
//    float zNear, float zFar)
//{
//    Frustum     frustum;
//    const float halfVSide = zFar * tanf(fovY * .5f);
//    const float halfHSide = halfVSide * aspect;
//    const glm::vec3 frontMultFar = zFar * cam.GetFront();
//
//    frustum.nearFace = { cam.GetPos() + zNear * cam.GetFront(), cam.GetFront()};
//    frustum.farFace = { cam.GetPos() + frontMultFar, -cam.GetFront()};
//    frustum.rightFace = { cam.GetPos(),
//                            glm::cross(frontMultFar - cam.GetRight() * halfHSide, cam.GetUp()) };
//    frustum.leftFace = { cam.GetPos(),
//                            glm::cross(cam.GetUp(),frontMultFar + cam.GetRight() * halfHSide)};
//    frustum.topFace = { cam.GetPos(),
//                            glm::cross(cam.GetRight(), frontMultFar - cam.GetUp() * halfVSide) };
//    frustum.bottomFace = { cam.GetPos(),
//                            glm::cross(frontMultFar + cam.GetUp() * halfVSide, cam.GetRight()) };
//
//    return frustum;
//}
//
//struct BoundingVolume
//{
//    virtual bool isOnFrustum(const Frustum& camFrustum,
//        const glm::mat4& modelTransform) const = 0;
//};
//
//struct Transform
//{
//    /*SPACE INFORMATION*/
//    //Local space information
//    glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
//    glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
//    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
//
//    //Global space information concatenate in matrix
//    glm::mat4 modelMatrix = glm::mat4(1.0f);
//
//    glm::mat4 getLocalModelMatrix()
//    {
//        const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
//            glm::radians(eulerRot.x),
//            glm::vec3(1.0f, 0.0f, 0.0f));
//        const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
//            glm::radians(eulerRot.y),
//            glm::vec3(0.0f, 1.0f, 0.0f));
//        const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
//            glm::radians(eulerRot.z),
//            glm::vec3(0.0f, 0.0f, 1.0f));
//
//        // Y * X * Z
//        const glm::mat4 roationMatrix = transformY * transformX * transformZ;
//
//        // translation * rotation * scale (also know as TRS matrix)
//        return glm::translate(glm::mat4(1.0f), pos) *
//            roationMatrix *
//            glm::scale(glm::mat4(1.0f), scale);
//    }
//
//    void updateSelfAndChild()
//    {
//        if (parent)
//            modelMatrix = parent->modelMatrix * getLocalModelMatrix();
//        else
//            modelMatrix = getLocalModelMatrix();
//
//        for (auto&& child : children)
//        {
//            child->updateSelfAndChild();
//        }
//    }
//};
//
//struct AABB : public BoundingVolume
//{
//    glm::vec3 center{ 0.f, 0.f, 0.f };
//    glm::vec3 extents{ 0.f, 0.f, 0.f };
//
//    AABB(const glm::vec3& min, const glm::vec3& max)
//        : BoundingVolume{},
//        center{ (max + min) * 0.5f },
//        extents{ max.x - center.x, max.y - center.y, max.z - center.z }
//    {
//    }
//
//    AABB(const glm::vec3& inCenter, float iI, float iJ, float iK)
//        : BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
//    {
//    }
//};
//
//bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
//{
//    //Get global scale thanks to our transform
//    const glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };
//
//    // Scaled orientation
//    const glm::vec3 right = transform.getRight() * extents.x;
//    const glm::vec3 up = transform.getUp() * extents.y;
//    const glm::vec3 forward = transform.getForward() * extents.z;
//
//    const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
//        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
//        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));
//
//    const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
//        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
//        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));
//
//    const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
//        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
//        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));
//
//    //We not need to divise scale because it's based on the half extention of the AABB
//    const AABB globalAABB(globalCenter, newIi, newIj, newIk);
//
//    return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
//        globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
//        globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
//        globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
//        globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
//        globalAABB.isOnOrForwardPlane(camFrustum.farFace));
//};

#include <glm/glm.hpp>

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

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;
};

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