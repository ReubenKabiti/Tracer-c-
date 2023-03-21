#ifndef HITABLE_H
#define HITABLE_H
#include <glm/glm.hpp>
#include <vector>
#include "ray.h"

class HitInfo
{
public:
    float t;
    glm::vec3 normal;
    glm::vec4 color;

    HitInfo(float _t, glm::vec3 _n, glm::vec4 _c) : t(_t), normal(_n), color(_c){}
};

class Hitable
{
public:
    Hitable();
    virtual std::vector<HitInfo> hit(Ray &ray) = 0;
};

#endif // HITABLE_H
