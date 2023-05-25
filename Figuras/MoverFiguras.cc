#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"
#include "esat/math.h"


const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

float speed=0.05;

const int kNTriangle = 3;
const int kNSquare = 4;
const int kNPentagon = 5;
const int kNStar = 10;
esat::Vec2 g_triangle[kNTriangle];
esat::Vec2 g_square[kNSquare];
esat::Vec2 g_pentagon[kNPentagon];
esat::Vec2 g_star[kNStar];



void InitShape(esat::Vec2 shape[], int n_vertices, float offset) {

  float angle_between_radians = 6.28f / (float) n_vertices;
  if (kNStar == n_vertices) {
    for (int i = 0; i < n_vertices; ++i) {
      if (i % 2 == 0) {
        shape[i] = { (float) cos(angle_between_radians * i + offset),
                      (float) sin(angle_between_radians * i + offset) };
      }
      else {
        shape[i] = { (float) cos(angle_between_radians * i + offset) * 0.6f,
                      (float) sin(angle_between_radians * i + offset) * 0.6f };
      }
    }
  }
  else {
    for (int i = 0; i < n_vertices; ++i) {
      shape[i] = { (float) cos(angle_between_radians * i + offset),
                    (float) sin(angle_between_radians * i + offset) };
    }
  }
}



void DrawShape(esat::Vec2* shape, int n_vertices,
                esat::Vec2 scale = { 180.0f, 180.0f },
                esat::Vec2 pos = { 400.0f, 300.0f}) {

  esat::Vec2 tr_points[kNStar];

  for (int i = 0; i < n_vertices; ++i) {
    tr_points[i] = { shape[i].x * scale.x + pos.x,
                     shape[i].y * scale.y + pos.y };
  }

  esat::DrawSetStrokeColor(255, 0, 0);
  esat::DrawSetFillColor(255, 255, 255, 0);
  esat::DrawSolidPath(&tr_points[0].x, n_vertices);

}



void MoveShape(esat::Vec2* shape, int n_vertices, float offset){

  for (int i=0; i<n_vertices; i++){
    shape[i].y += speed;

    printf("%f \n", shape[i].y);

    if ( (shape[i].y) >= 10){
      InitShape(shape, n_vertices, offset);
    }
  }
  printf("\n");
}


int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  unsigned char fps=60;

  esat::WindowInit(kWindowWidth, kWindowHeight);
  WindowSetMouseVisibility(true);



  InitShape(g_triangle, kNTriangle, - 1.57f);
  InitShape(g_square, kNSquare, - 0.78f);
  InitShape(g_pentagon, kNPentagon, - 1.57f);
  InitShape(g_star, kNStar, - 1.57f);



  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) &&
         esat::WindowIsOpened()) {
    last_time = esat::Time();

    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);



    DrawShape(g_triangle, kNTriangle, /*ancho ->*/{ 100.0f, 100.0f }, /*posiciones x,y ->*/{ 50.0f, -10.0f });
    
    DrawShape(g_square, kNSquare, { 100.0f, 100.0f }, { 600.0f, -10.0f });
    
    DrawShape(g_pentagon, kNPentagon, { 50.0f, 50.0f }, { 500.0f, -10.0f });
    DrawShape(g_pentagon, kNPentagon, { 100.0f, 100.0f }, { 400.0f, 0.0f });
    
    DrawShape(g_star, kNStar, { 25.0f, 25.0f }, { 700.0f, -10.0f });
    DrawShape(g_star, kNStar, { 45.0f, 45.0f }, { 150.0f, 0.0f });
    DrawShape(g_star, kNStar, { 75.0f, 75.0f }, { 250.0f, 0.0f });


    MoveShape(g_star, kNStar, - 1.57f);
    MoveShape(g_pentagon, kNPentagon, - 1.57f);
    MoveShape(g_square, kNSquare, -0.78f);
    MoveShape(g_triangle, kNTriangle, -1.57f);

    esat::DrawEnd();
    esat::WindowFrame();

  	do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}