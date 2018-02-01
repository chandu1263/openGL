#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    speedy = .01;
    const float teeta = 8 * acos(-1.0) / 900 ;
    float alpha=0.0;
    float r = 0.25;
    int index=0;
    GLfloat vertex_buffer_data[2700] ;
    for(int j=0;j<6;j++)
    {
      index=0;
          for(int i=0;i<150;i++)
      		{
            if(i%3==0)
            {
              vertex_buffer_data[index++]=0.0;
              vertex_buffer_data[index++]=0.0;
              vertex_buffer_data[index++]=0.0;
            }
            else
            {
              vertex_buffer_data[index++]=r*cos(alpha);
              vertex_buffer_data[index++]=r*sin(alpha);
              vertex_buffer_data[index++]=0.0;
              if(i%3==1)
              {
                alpha=alpha+teeta;
              }
            }


          }
          if(j==0)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_RED, GL_FILL);
          }
          if(j==1)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_GREEN, GL_FILL);
          }
          if(j==2)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
          }
          if(j==3)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_BLUE, GL_FILL);
          }
          if(j==4)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
          }
          if(j==5)
          {
            this->object[j] = create3DObject(GL_TRIANGLES, 150, vertex_buffer_data, COLOR_GREY, GL_FILL);
          }
    }
    /*    -0.2, -0.2 , 0, // vertex 1
        0.2,  -0.2 , 0, // vertex 2
        0.2,  0.2  , 0, // vertex 3

        0.2,  0.2  , 0, // vertex 3
        -0.2, 0.2  , 0, // vertex 4
        -0.2, -0.2 ,  0 // vertex 1*/
      //this->object = create3DObject(GL_TRIANGLES, 900, vertex_buffer_data, COLOR_GREY, GL_FILL)  ;
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<6;i++)
    {
       draw3DObject(this->object[i]);
     }

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if(this->tramp == 1)
    {
      this->speedy -= 10 * 1/60.0 ;
      this->position.y += (speedy*1/60.0) - ( 30 * 1/60.0 * 1/60.0);
    }
    if(this->goingup == 1)
    {
      //printf("Entered tick ");
      this->speedy -= 10 * 1/60.0 ;
      this->position.y += (speedy*1/60.0) - ( 30 * 1/60.0 * 1/60.0);
    }
    this->position.x -= speed;

    //this->position.y -= speed;
}

void Ball::rotate(){
  this->rotation+=1;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
