#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>

class Ray
{
private:
    glm::vec3 m_origin, m_direction;
public:
    Ray(glm::vec3 ori, glm::vec3 dir);
    const glm::vec3 &direction() const;

    glm::vec3 getPointAt(float t);
    const glm::vec3 &origin() const;
};

#endif // RAY_H
