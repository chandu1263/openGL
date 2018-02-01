#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    //speed = 0.01 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.06)));
    //speed_t = 0.01;
    #define PI 3.14
    GLfloat vertex_buffer_data[100010];
    vertex_buffer_data[0] = 0.0f;
    vertex_buffer_data[1] = 0.0f;
    vertex_buffer_data[2] = 0.0f;
    vertex_buffer_data[3] = 0.0f;
    vertex_buffer_data[4] = 0.75f;
    vertex_buffer_data[5] = 0.0f;
    int n = 40;

    float angle = 2*PI/n;
    int i;float p=0,q=0.75;
    vertex_buffer_data[6]=cos(angle)*p - sin(angle)*q;
    vertex_buffer_data[7]=sin(angle)*p + cos(angle)*q;
    vertex_buffer_data[8]=0.0f;
    p = vertex_buffer_data[6];
    q = vertex_buffer_data[7];
    for(i=1;i<=n;i++)
    {
        vertex_buffer_data[9*i]=0.0f;
        vertex_buffer_data[9*i+1]=0.0f;
        vertex_buffer_data[9*i+2]=0.0f;
        vertex_buffer_data[9*i+3]=p;
        vertex_buffer_data[9*i+4]=q;
        vertex_buffer_data[9*i+5]=0.0f;
        vertex_buffer_data[9*i+6]=cos(angle)*p - sin(angle)*q;
        vertex_buffer_data[9*i+7]=sin(angle)*p + cos(angle)*q;
        vertex_buffer_data[9*i+8]=0.0f;
        p = vertex_buffer_data[9*i+6];
        q = vertex_buffer_data[9*i+7];

    }
    GLfloat leg1_vertex_buffer_data[] = {
        0.75f, 0.0f, 0.0f,
        0.75f, -1.0f, 0.0f,
        0.85f, -1.0f, 0.0f,
        0.75f, 0.0f, 0.0f,
        0.85f, -1.0f, 0.0f,
        0.85f, 0.0f, 0.0f
    };
    this->leg1 = create3DObject(GL_TRIANGLES, 3*2, leg1_vertex_buffer_data, color, GL_FILL);

    GLfloat leg2_vertex_buffer_data[] = {
        -0.75f, 0.0f, 0.0f,
        -0.75f, -1.0f, 0.0f,
        -0.85f, -1.0f, 0.0f,
        -0.75f, 0.0f, 0.0f,
        -0.85f, -1.0f, 0.0f,
        -0.85f, 0.0f, 0.0f
    };
    this->leg2 = create3DObject(GL_TRIANGLES, 3*2, leg2_vertex_buffer_data, color, GL_FILL);

    this->object = create3DObject(GL_TRIANGLES, 3*(20), vertex_buffer_data+9*10, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));//center of rotation(0,0) and rotation axis(z)
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->leg1);
    draw3DObject(this->leg2);

}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Trampoline::tick() {
    //this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1.5, 0.3 };
    return bbox;
}
