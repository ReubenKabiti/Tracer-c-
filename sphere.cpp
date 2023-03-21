#include "sphere.h"

Sphere::Sphere(glm::vec3 center, float radius, glm::vec4 color)
    : m_center(center),
      m_radius(radius),
      m_color(color)
{

}

std::vector<HitInfo> Sphere::hit(Ray &ray)
{
    glm::vec3 oc = ray.origin() - m_center;

    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(ray.direction(), oc);
    float c = glm::dot(oc, oc) - pow(m_radius, 2);

    float descriminant = b * b - 4.0f * a * c;

    std::vector<HitInfo> hitInfos;
    if (descriminant < 0)
        return hitInfos;
    float t0 = (-b - sqrt(descriminant)) / (2.0f * a);
    float t1 = (-b + sqrt(descriminant)) / (2.0f * a);

    glm::vec3 n0 = glm::normalize(ray.getPointAt(t0) - m_center);
    glm::vec3 n1 = glm::normalize(ray.getPointAt(t1) - m_center);

    hitInfos.push_back(HitInfo(t0, n0, m_color));
    hitInfos.push_back(HitInfo(t1, n1, m_color));
    return hitInfos;
}
