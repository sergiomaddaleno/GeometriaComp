#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"
//#include "vector.cc"
#include <math.h>
#define PI 3.14159265
const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;
//float offset=20;

float MposX=esat::MousePositionX();
float MposY=esat::MousePositionY();
const int kNVertices=30;
float g_circle[kNVertices*2];

//Puntoa - Puntob, calcular length del vector, if(length<(KR1 + KR2) ees colision)
void InitFCircle(){

    float angle_between_vertices = 6.28f / (float) kNVertices;
    //printf("%f \n", angle_between_vertices);
    for (int i=0; i<kNVertices; ++i){
    
      g_circle[i * 2] = cos(angle_between_vertices * i) * 100.0f + 400.0f; //x
      g_circle[i * 2 + 1] = sin(angle_between_vertices * i) * 100.0f + 300.0f; //y
      //printf("%f \n", g_circle[i * 2]);
      //printf("%f \n", g_circle[i * 2 + 1]);
    }
    //printf("\n");
}

void DrawFCircle(){
  esat::DrawSetStrokeColor(100,0,0);
  esat::DrawSetFillColor(50,0,0);
  esat::DrawSolidPath(g_circle, kNVertices);
}

void DrawSecCircle(){
}

void DetectCircle(){
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  InitFCircle();

  esat::WindowInit(kWindowWidth, kWindowHeight);
  WindowSetMouseVisibility(true);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    DrawFCircle();

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}
