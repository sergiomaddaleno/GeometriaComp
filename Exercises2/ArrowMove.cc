#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>

#include "..\smf\smfLibrary.h"

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int kNVertices=3;
esat::Vec2 g_circle[kNVertices];

esat::Vec2 scale = {40.0f, 15.0f}; //Tamaño hor y vert
esat::Vec2 initPos = {400.0f, 300.0f};
esat::Vec2 tr_circle[kNVertices];

struct Mat3{float d[9];};

float posX=0, posY=0, speed=0, maxSpeed=10, minSpeed=0.14, angle=10.0f;

Mat3 Mat3MultiplyMat3(struct Mat3 v, struct Mat3 w) {
  Mat3 result;

    result.d[0] = v.d[0]*w.d[0] + v.d[1]*w.d[3] + v.d[2]*w.d[6];
    result.d[1] = v.d[0]*w.d[1] + v.d[1]*w.d[4] + v.d[2]*w.d[7];
    result.d[2] = v.d[0]*w.d[2] + v.d[1]*w.d[5] + v.d[2]*w.d[8];
    result.d[3] = v.d[3]*w.d[0] + v.d[4]*w.d[3] + v.d[5]*w.d[6];
    result.d[4] = v.d[3]*w.d[1] + v.d[4]*w.d[4] + v.d[5]*w.d[7];
    result.d[5] = v.d[3]*w.d[2] + v.d[4]*w.d[5] + v.d[5]*w.d[8];
    result.d[6] = v.d[6]*w.d[0] + v.d[7]*w.d[3] + v.d[8]*w.d[6];
    result.d[7] = v.d[6]*w.d[1] + v.d[7]*w.d[4] + v.d[8]*w.d[7];
    result.d[8] = v.d[6]*w.d[2] + v.d[7]*w.d[5] + v.d[8]*w.d[8];

  return result;
}

Mat3 Mat3Rotate(Mat3 m, float angle) {
    float c = cos(angle * PI / 180.0);
    float s = sin(angle * PI / 180.0);

    Mat3 rotateMatrix = {
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    };

    // Se aplica la rotación primero y luego la escala
    return Mat3MultiplyMat3(rotateMatrix, m);
}

void InitCircle(){

    float radians_between_vertices = 6.28f / (float) kNVertices; //2*pi = 6.28

    for (int i=0; i<kNVertices; ++i){

       g_circle[i] = { (float) cos(radians_between_vertices * i ),
                       (float) sin(radians_between_vertices * i )};
    }
    
}

void FirstDraw(){
  
  for (int i=0; i<kNVertices; i++){
    tr_circle[i] = {g_circle[i].x * scale.x + initPos.x ,
                    g_circle[i].y * scale.y + initPos.y};
  }
  posX = initPos.x;
  posY = initPos.y;

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_circle[0].x, kNVertices);

}

void UpdateSpeed(){
    
  float radians_between_vertices = 6.28f / (float) kNVertices; //2*pi = 6.28

  if(esat::IsKeyPressed('W')){
    if(speed <= maxSpeed){ speed = speed + 0.15;}
  }else{
    if(speed > minSpeed){ speed = speed - 0.15;}
  }  
  posX = posX - speed;
  //posY = posY + speed;
}

void UpdateSpin(){
  
  if(esat::IsKeyPressed('D')){
    
    Mat3 matrixToRotate = {g_circle[0].x, 0, 0, g_circle[0].y, 0, 0, 0, 0, 0};
    //printf("%f %f\n", g_circle[0].x, g_circle[0].y);
    //printf("%f %f\n", matrixToRotate.d[0], matrixToRotate.d[1]);

    Mat3 rotatedMatrix = Mat3Rotate(matrixToRotate, angle);
    g_circle[0].x = rotatedMatrix.d[0];
    g_circle[0].y = rotatedMatrix.d[3];
    //printf("%f %f\n\n", g_circle[0].x, g_circle[0].y);
    //printf("%f %f\n\n", rotatedMatrix.d[0], rotatedMatrix.d[1]);
    

    matrixToRotate = {g_circle[1].x, 0, 0, g_circle[1].y, 0, 0, 0, 0, 0};
    rotatedMatrix = Mat3Rotate(matrixToRotate, angle);
    g_circle[1].x = rotatedMatrix.d[0];
    g_circle[1].y = rotatedMatrix.d[3];

    matrixToRotate = {g_circle[2].x, 0, 0, g_circle[2].y, 0, 0, 0, 0, 0};
    rotatedMatrix = Mat3Rotate(matrixToRotate, angle);
    g_circle[2].x = rotatedMatrix.d[0];
    g_circle[2].y = rotatedMatrix.d[3];
    
  }
}


void Draw(){
  //Cuando sale de la ventana
  if(posX > 800){posX = 0;}   if(posX < 0 ){posX = 800;} 
  if(posY > 600){posY = 0;}   if(posY < 0 ){posY = 600;}

  for (int i=0; i<kNVertices; i++){
      tr_circle[i] = {g_circle[i].x * scale.x + posX,
                      g_circle[i].y * scale.y + posY};
  }
  //printf("%d\n", posX);
  
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_circle[0].x, kNVertices);

  //printf("%f %f %f\n", g_circle[0].x, g_circle[1].x, g_circle[2].x);
  //printf("%f %f %f\n\n", g_circle[0].y, g_circle[1].y, g_circle[2].y);
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
  InitCircle();
  FirstDraw();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    UpdateSpeed();
    UpdateSpin();
    Draw();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}