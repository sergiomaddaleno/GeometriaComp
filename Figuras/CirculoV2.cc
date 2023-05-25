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

const int kNVertices=3;
esat::Vec2 g_circle[kNVertices];

//float g_circle[kNVertices * 2];

void InitCircle(){

    float radians_between_vertices = 6.28f / (float) kNVertices; //2*pi = 6.28

    for (int i=0; i<kNVertices; ++i){

       g_circle[i] = { (float) cos(radians_between_vertices * i + 0), // esat::Time para que se mueva y el color, para y
                       (float) sin(radians_between_vertices * i + esat::Time())}; // para x
    }
    
}

void UpdateDraw(esat::Vec2 scale = {100.0f, 100.0f}, 
                esat::Vec2 pos = {400.0f, 300.0f}){

  esat::Vec2 tr_circle[kNVertices];
  
  for (int i=0; i<kNVertices; i++){
    tr_circle[i] = {g_circle[i].x * scale.x + pos.x,
                    g_circle[i].y * scale.y + pos.y};
  }

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_circle[0].x, kNVertices);

}

/*void DrawCircle(){

    esat::DrawSetStrokeColor(0,255,0);
    esat::DrawSetFillColor(255,255,255,0);
    esat::DrawSolidPath(g_circle, kNVertices);
}*/



int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
   /*for (int i=0; i<20; ++i){
        printf("[%d]: %f\n", i,  sin((double) i));
    }*/
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    InitCircle();
    //DrawCircle();
    UpdateDraw();
    //UpdateDraw();
    //UpdateDraw();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}