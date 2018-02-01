#include "pacs.h"
#include "main.h"

Pacs::Pacs(float x, float y, color_t color,float r,double speed,int a) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->appear=1;
    this->speed=speed;
    this->r=r;
    GLfloat vertex_buffer_data[360*9];
    float angle=0;
    this->a=a;

    for(int i=0;i<360*9*5/6;i++)
    {
            vertex_buffer_data[i++]=0.0f;
            vertex_buffer_data[i++]=0.0f;
            vertex_buffer_data[i++]=0.0f;

            vertex_buffer_data[i++]=r*cos(angle);
            vertex_buffer_data[i++]= r*sin(angle);
            vertex_buffer_data[i++]=0.0f;


            vertex_buffer_data[i++]= r*cos(angle+M_PI/180);
            vertex_buffer_data[i++]= r*sin(angle+M_PI/180);
            vertex_buffer_data[i]=0.0f;

           angle+=M_PI/180;
     }

     this->object[0] = create3DObject(GL_TRIANGLES, 360*3*5/6, vertex_buffer_data,color , GL_FILL);
    if(a)
    {
        GLfloat buffer_data[]={
            r*sqrt(2),0,0,
            0,r*sqrt(2),0,
            r*sqrt(2)+0.05,0.05,0,

            r*sqrt(2)+0.05,0.05,0,
            0,r*sqrt(2),0,
            0.05,r*sqrt(2)+0.05,0,

        };
        this->slope=rand()%2;
        if(slope)
            this->rotation=90;
         this->object[1]=create3DObject(GL_TRIANGLES,6,buffer_data,COLOR_BROWN,GL_FILL);
    }





}

void Pacs::draw(glm::mat4 VP,int a) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

        draw3DObject(this->object[0]);
        if(a)
            draw3DObject(this->object[1]);
}

void Pacs::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Pacs::tick()
{
    this->position.x += speed;
}



bounding_box_t Pacs::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->r};
    return bbox;
}
