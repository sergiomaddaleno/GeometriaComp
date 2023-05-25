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

const int kNVertices=4;
float g_circle[kNVertices * 2];



void InitCircle(){

    float angle_between_vertices = 6.28f / (float) kNVertices;
    //printf("%f \n", angle_between_vertices);
    for (int i=0; i<kNVertices; ++i){

       g_circle[i * 2] = cos(angle_between_vertices * i) * 90.0f + 400.0f; //x
       g_circle[i * 2 + 1] = sin(angle_between_vertices * i) * 90.0f + 300.0f; //y
       printf("%f \n", g_circle[i * 2]);
       printf("%f \n", g_circle[i * 2 + 1]);

    }
    printf("\n");
}


void DrawCircle(){

    esat::DrawSetStrokeColor(0,255,0);
    esat::DrawSetFillColor(255,255,255,0);
    esat::DrawSolidPath(g_circle, kNVertices);
}


int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
   for (int i=0; i<20; ++i){
        printf("[%d]: %f\n", i,  sin((double) i));
    }
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    InitCircle();
    DrawCircle();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}