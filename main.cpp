#include <iostream>
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include <vector>
#include <algorithm>
#include <SOIL/SOIL.h>
#include "sphere.h"

static const uint32_t DISPLAY_WIDTH = 500;
static const uint32_t DISPLAY_HEIGHT = 500;

class Tracer
{
private:
    sf::RenderWindow *m_window = nullptr;
public:

    Tracer() = default;
    void run()
    {
        init();
        mainLoop();
        cleanUp();
    }

    void init()
    {
        m_window = new sf::RenderWindow{ {DISPLAY_WIDTH, DISPLAY_HEIGHT}, "Tracer"};
    }

    void mainLoop()
    {
        Renderer *renderer = nullptr;
        sf::Sprite sprite;

        std::vector<Hitable*> objects;
        Sphere s1(glm::vec3(0, 0, -1), 1, glm::vec4(1, 0, 0, 1));
        objects.push_back(&s1);

        while (m_window->isOpen())
        {
            sf::Event event;
            while(m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
                else if (event.type == sf::Event::Resized)
                {
                    delete renderer;
                    renderer = new Renderer(event.size.width, event.size.height);
                }
            }

            m_window->clear();
            Image &image = renderer->render(objects);
            auto texture = image.texture();
            SOIL_save_image("example.png", SOIL_SAVE_TYPE_BMP, DISPLAY_WIDTH, DISPLAY_HEIGHT, 4, image.pixels());
            sprite.setTexture(*texture);
            m_window->draw(sprite);
            m_window->display();
        }
        delete renderer;
    }

    void cleanUp()
    {
        delete m_window;
    }
};


int main()
{
    Tracer tracer;
    tracer.run();
    return 0;
}
