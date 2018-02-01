#include "pond.h"
#include "main.h"

Pond::Pond(float x,float y,color_t color,float r) {

    this->position = glm::vec3(x, y, 0);
    this->rotation=0;
    this->r=r;


    GLfloat vertex_buffer_data[180*9];

    float angle=0;

    for(int i=0;i<180*9;i++)
    {
        vertex_buffer_data[i++]=0.0f;
        vertex_buffer_data[i++]=0.0f;
        vertex_buffer_data[i++]=0.0f;

        vertex_buffer_data[i++]=r*cos(angle);
        vertex_buffer_data[i++]= r*sin(angle);
        vertex_buffer_data[i++]=0.0f;


        vertex_buffer_data[i++]= r*cos(angle-M_PI/180);
        vertex_buffer_data[i++]= r*sin(angle-M_PI/180);
        vertex_buffer_data[i]=0.0f;

       angle-=M_PI/180;
    }
    this->object= create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color , GL_FILL);


}
void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
       draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t  Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t pbox = { x, y, 1 };
    return pbox;
}
