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

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int kNVertices=40;

//Declaracion vertices
const int kNVerticesTriangle = 3;
esat::Vec2 g_Triangle[kNVertices];

const int kNVerticesSquare = 4;
esat::Vec2 g_square[kNVertices];

const int kNVerticesPentagon = 5;
esat::Vec2 g_pentagon[kNVertices];

const int kNVerticesStar = 10;
esat::Vec2 g_star[kNVertices];

float g_circle[kNVertices * 2];

void InitShapes(esat::Vec2* figure, int n_vertices = 10){

  float radians_between_vertices = 6.28f / (float) n_vertices; //2*pi = 6.28

  if (10 == n_vertices){
    for (int i=0; i<n_vertices; ++i){
      if (i % 2 == 0){
        figure[i] = { (float) cos(radians_between_vertices * i + offset), // esat::Time para que se mueva y el color, para y
                       (float) sin(radians_between_vertices * i + offset)}; // para x

      } else {figure[i] = (float) cos((radians_between_vertices * i + offset) * 0.6f), 
                          (float) sin((radians_between_vertices * i + offset) * 0.6f);}
    }
  }else {
    for (int i=0; i<n_vertices; ++i){
        figure[i] = { (float) cos(radians_between_vertices * i + offset), 
                      (float) sin(radians_between_vertices * i + offset)}; 
    }
  }
}

void UpdateDraw(esat::Vec2 circle[],
                int n_vertices = 10,
                esat::Vec2 scale = {100.0f, 100.0f},
                esat::Vec2 pos = {400.0f, 300.0f}){
  
  for (int i=0; i<n_vertices; i++){
    tr_circle[i] = { g_circle[i].x * scale.x + pos.x,
                     g_circle[i].y * scale.y + pos.y};
  }

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_circle[0].x, n_vertices);

}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
   /*for (int i=0; i<20; ++i){
        printf("[%d]: %f\n", i,  sin((double) i));
    }*/

  InitShapes(g_Triangle, kNVerticesTriangle, -1.57f); // pi partido 2 = -1.57
  InitShapes(g_square, kNVerticesSquare, -1.57f * 0.5f);
  InitShapes(g_pentagon, kNVerticesPentagon, -1.57f);
  InitShapes(g_star, kNVerticesStar, -1.57f);

  /*float data[] = {8.0f, 4.0f};
  printf("%d\n", sizeof(float));
  printf("%d\n", sizeof(date));*/

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    UpdateDraw(g_star, kNVerticesStar);
    UpdateDraw(g_square, kNVerticesSquare, {50.0f, 50.0f}, {200.0f, 200.0f});
    UpdateDraw(g_pentagon, kNVerticesTriangle, {75.0f, 75.0f}, {600.0f, 400.0f});
    UpdateDraw(g_Triangle, kNVerticesTriangle, {125.0f, 125.0f}, {150.0f, 450.0f});
    
    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}