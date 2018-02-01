#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void rotate();
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedy;
    int collide;
    int goingup;
    int random;
    int tramp;
    int inwater;
    int t;
    bounding_box_t bounding_box();
private:
    VAO *object[6];
};

#endif // BALL_H
