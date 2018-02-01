#include "spikes.h"
#include "main.h"


float temp;
Spikes::Spikes(float x, float y, color_t color)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation=0;
    speed=0.005;
    temp=speed;

    static const GLfloat vertex_buffer_data[] = {
        -0.75, 0, 0, // vertex 1
        -0.75,  0.5, 0, // vertex 2
        -0.25,  0, 0, // vertex 3

        -0.25,  0, 0, // vertex 3
        -0.25, 0.5, 0, // vertex 4
        0.25, 0, 0,// vertex 1

        0.25,0,0,
        0.25,0.5,0,
        0.75,0,0,
    };

   this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Spikes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spikes::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Spikes::tick() {
    this->position.x += speed;
    if(this->position.x>=-2.5)
    {
        speed=-temp;
        this->position.x+=speed;
    }
    if(this->position.x<=-4.5)
    {
        speed=temp;
        this->position.x+=speed;
    }




    // this->position.y -= speed;
}
bool Spikes::detect_collide(bounding_box_t a, bounding_box_t b) {
    if(abs(a.x-b.x)<=0.75 && abs(a.y-b.y)<=1)
    {

    //return (abs(a.x - x) * 2 < (a.width + b.width)) &&
       //    (abs(a.y - b.y) * 2 < (a.height + b.height));
        return true;
    }
    else
        return false;
}

bounding_box_t Spikes::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
