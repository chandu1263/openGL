#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *leg1;
    VAO *leg2;
};

#endif // TRAMPOLINE_H
