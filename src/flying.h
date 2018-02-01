#include "main.h"

#ifndef FLYING_H
#define FLYING_H


class Flying {
public:
    Flying() {}
    Flying(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void rotate();
    void set_position(float x, float y);
    void tick();
    float speed;

    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // FLYING_H
