#include "main.h"

#ifndef PACS_H
#define PACS_H


class Pacs {
public:
    Pacs() {}
    Pacs(float x, float y, color_t color,float r,double speed,int a);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP,int a);
    void set_position(float x, float y);
    double speed;
    double speedy;
    int pacflag;
    float r;
    int a;
    int slope;
    void tick();
    int appear;
    bounding_box_t bounding_box();
private:
    VAO *object[2];
};

#endif // PACS_H
