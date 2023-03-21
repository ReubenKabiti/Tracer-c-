#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <cmath>
#include "hitable.h"

class Sphere : public Hitable
{
private:
    glm::vec3 m_center;
    float m_radius;
    glm::vec4 m_color;

public:
    Sphere(glm::vec3 center, float radius, glm::vec4 color);
    virtual std::vector<HitInfo> hit(Ray &ray) override;
    inline glm::vec3 &center() { return m_center; }
};

#endif // SPHERE_H
