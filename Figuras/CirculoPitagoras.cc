#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <esat/window.h>

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int kNHeights=10;
esat::Vec2 g_circle[kNHeights*2];


void InitCircle(){

    float h = 1.0f;
    float co = h;
    float diff = (2.0f * h / (float) kNHeights);

    for (int i=0; i<kNHeights; ++i){
        float cc = sqrt(h * h - co * co);
        
        g_circle[i] = {cc, co};
        g_circle[i + kNHeights] = {-cc, -co};
        co -= diff;
    }
}

void UpdateDrawCircle(){

    esat::Vec2 tr_circle[kNHeights*2];

    for (int i=0; i<kNHeights * 2; ++i){
        tr_circle[i] = {g_circle[i].x * 180.0f + 400.0f,
                        g_circle[i].y * 180.0f + 300.0f};
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(&tr_circle[0].x, kNHeights * 2);
}

/*void UpdateDrawCircle(){

    for (int i=0; i<kNHeights * 2; ++i){
        float h = (float) kNHeights;
        float co = h - i;
        float cc = sqrt(h * h - co * co);

    esat::DrawSetStrokeColor(255, 255, 0);
    esat::DrawSetFillColor(0, 0, 0, 0);
    float x1 = 400.0f - cc;
    float x2 = 400.0f + cc;
    float y1 = 300.0f - co;
    float y2 = 300.0f + co;
    esat::DrawLine(x1, y1, x2, y2);
    }
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
    UpdateDrawCircle();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}