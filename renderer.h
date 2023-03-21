#ifndef RENDERER_H
#define RENDERER_H
#include <cstdint>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <string.h>
#include <iostream>
#include <cmath>
#include "hitable.h"

class Image
{
private:
    uint32_t m_width, m_height;
    sf::Uint8 *m_pixels;

public:
    Image() = default;

    ~Image()
    {
        delete[] m_pixels;
    }

    void create(uint32_t width, uint32_t height)
    {
        m_width = width;
        m_height = height;

        m_pixels = new sf::Uint8[width * height * 4];
    }

    std::shared_ptr<sf::Texture> texture()
    {
        std::shared_ptr<sf::Texture> tex = std::make_shared<sf::Texture>();
        tex->create(m_width, m_height);
        tex->update(m_pixels);
        return tex;
    }

    void setAt(uint32_t x, uint32_t y, glm::vec4 color)
    {
        color = glm::clamp(color, glm::vec4(0, 0, 0, 0), glm::vec4(1, 1, 1, 1));

        int r = (sf::Uint8)(color.r * 255);
        int g = (sf::Uint8)(color.g * 255);
        int b = (sf::Uint8)(color.b * 255);
        int a = (sf::Uint8)(color.a * 255);
        int offset = 4 * (m_width * y + x);

        m_pixels[offset] = r;
        m_pixels[offset + 1] = g;
        m_pixels[offset + 2] = b;
        m_pixels[offset + 3] = a;
    }

    void clear()
    {
        for (uint32_t x = 0; x < m_width * m_height * 4; x++)
        {
            m_pixels[x] = 0;
        }
    }
};


class Renderer
{
private:
    uint32_t m_width, m_height;
    Image m_image;


public:
    struct
    {
        float fov = M_PI / 3.0;
        float flen = 1.0f / (2.0f * tan(fov));
        glm::vec3 camera_position {0, 0, flen};
        glm::vec3 right{1, 0, 0};
        glm::vec3 upvec{0, 1, 0};
        glm::vec3 lookat{0, 0, -1};
        glm::vec4 black {0};
        glm::vec3 lightDirection{0, -1, -1};
        float aspect;
    } info;

    Renderer(uint32_t width, uint32_t height);
    Image &render(const std::vector<Hitable*> &objects);
    glm::vec4 perPixel(float u, float v, const std::vector<Hitable*> &objects);
    uint32_t width() const;
    uint32_t height() const;
};

#endif // RENDERER_H
