#include "main.h"

#ifndef spikes_H
#define spikes_H


class Spikes {
public:
    Spikes() {}
    Spikes(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float speed;
   bool detect_collide(bounding_box_t  a,bounding_box_t b);

    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif
