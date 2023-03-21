#include "renderer.h"
#include <random>
#include "ray.h"

uint32_t Renderer::width() const
{
    return m_width;
}

uint32_t Renderer::height() const
{
    return m_height;
}

Renderer::Renderer(uint32_t width, uint32_t height)
    : m_width(width),
      m_height(height)
{
    m_image.create(width, height);
    info.aspect = width / height;
}

Image &Renderer::render(const std::vector<Hitable*> &objects)
{
    m_image.clear();
    for (uint32_t y = 0; y < m_height; y++)
    {
        for (uint32_t x = 0; x < m_width; x++)
        {
            float u = x / (float)m_width;
            float v = (m_height - y) / (float)m_height;

            u = 2 * u - 1;
            v = 2 * v - 1;

            glm::vec4 color = perPixel(u, v, objects);
            m_image.setAt(x, y, color);
        }
    }
    return m_image;
}

glm::vec4 Renderer::perPixel(float u, float v, const std::vector<Hitable*> &objects)
{
    glm::vec3 pixelPos = info.right * u * info.aspect + info.upvec * v;
    glm::vec3 origin = info.camera_position;

    glm::vec3 direction = pixelPos - origin;

    Ray ray(origin, direction);

    std::vector<HitInfo> hitInfos;

    for (Hitable *object : objects)
    {
        auto hitInfosObj = object->hit(ray);
        for (auto &hI : hitInfosObj)
        {
            hitInfos.push_back(hI);
        }
    }
    if (hitInfos.size() == 0)
    {
        return info.black;
    }

    auto vecMin = [](std::vector<HitInfo> &hIs)
    {
        HitInfo hi = hIs[0];
        float smallestT = hi.t;
        for (unsigned int i = 1; i < hIs.size(); i++)
        {
            if (hIs[i].t < smallestT)
            {
                smallestT = hIs[i].t;
                hi = hIs[i];
            }
        }
        return hi;
    };

    HitInfo hi = vecMin(hitInfos);
    float f = glm::dot(hi.normal, -info.lightDirection);
    glm::vec4 color = hi.color * f;
    color.a = 1;
    return color;
}


sf::Uint8 *Image::pixels() const
{
    return m_pixels;
}
