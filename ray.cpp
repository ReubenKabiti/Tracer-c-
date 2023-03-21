#include "ray.h"

const glm::vec3 &Ray::direction() const
{
    return m_direction;
}

glm::vec3 Ray::getPointAt(float t)
{
    return m_origin + m_direction * t;
}

const glm::vec3 &Ray::origin() const
{
    return m_origin;
}

Ray::Ray(glm::vec3 ori, glm::vec3 dir)
    : m_origin(ori),
      m_direction(dir)
{

}


