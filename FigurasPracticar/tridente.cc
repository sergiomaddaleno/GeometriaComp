#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <esat/window.h>

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int knPoints = 16;
const int kNumTridents = 6;
const int knPointstriangle = 3;
const float kCircunference = PI*2;

float transformed_coords[knPoints*2]={0.0f};

float circle_coords[knPointstriangle * 2]={0.0f};
float transformed_circle[knPointstriangle * 2]={0.0f};

float trident[] = {
2.0f, 0.0f, 
3.0f, 0.0f, 
3.0f, 4.0f, 
5.0f, 4.0f, 
5.0f, 8.0f, 
4.0f, 8.0f, 
4.0f, 6.0f, 
3.0f, 6.0f, 
3.0f, 13.0f,
2.0f, 13.0f,
2.0f, 6.0f,
1.0f, 6.0f,
1.0f, 8.0f,
0.0f, 8.0f,
0.0f, 4.0f,
2.0f, 4.0f };

void DrawTident(){

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<kNumTridents; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(-2.0f, 6.0f),m);
        m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, 10.0f),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumTridents) *-j),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

        for(int i=0; i<knPoints; i++){
            esat::Vec3 p = {trident[i * 2], trident[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
        }

        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0);
        esat::DrawSolidPath(transformed_coords, knPoints);
    }
}

void InitCircle() {
	float portion = kCircunference / knPointstriangle;
	for (int i = 0; i < 3; ++i) {
		circle_coords[i * 2] = cos(portion * i);
		circle_coords[i * 2 + 1] = sin(portion * i);
	}
}

void DrawTriangle(){
    
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<kNumTridents; j++){
        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Rotate(3.67), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(1.7f, 7.5f), m);
        m = esat::Mat3Multiply(esat::Mat3Scale(15.0f,20.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumTridents) *-j),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

        for(int i=0; i<knPointstriangle; i++){
            esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_circle[i * 2] = result.x;
            transformed_circle[i * 2 + 1] = result.y;
        }

        esat::DrawSetFillColor(0,0,0);
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSolidPath(transformed_circle, knPointstriangle);
    }
}
void DrawTriangle2(){
    
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<kNumTridents; j++){
        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Rotate(3.67), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(-1.2f, 7.5f), m);
        m = esat::Mat3Multiply(esat::Mat3Scale(15.0f,20.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumTridents) *-j),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

        for(int i=0; i<knPointstriangle; i++){
            esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_circle[i * 2] = result.x;
            transformed_circle[i * 2 + 1] = result.y;
        }

        esat::DrawSetFillColor(0,0,0);
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSolidPath(transformed_circle, knPointstriangle);
    }
}



int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

    InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawTident();
    DrawTriangle();
    DrawTriangle2();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}