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

const int kNumberPoints = 10;

float kCircunference = 2*PI;
float star_coords[2 * kNumberPoints] = {0.0f};
float transformed_coords[2 * kNumberPoints] = {0.0f};

float circle_coords[2 * 100] = {0.0f};
float transformed_circle[2 * 100] = {0.0f};

float i=0;

void InitStar(){

    float portion = kCircunference / kNumberPoints;
    for(int i=0; i<kNumberPoints; i++){
        if(i%2 == 0){
            star_coords[i * 2] = cos(portion * i);
            star_coords[i * 2 + 1] = sin(portion * i);
        }else{
            star_coords[i * 2] = cos(portion * i) * 0.5;
            star_coords[i * 2 + 1] = sin(portion * i) * 0.5;
        }
        
    }
}

void InitCircle(){
    float portion = kCircunference / 100;
    for(int i=0; i<100; i++){
        circle_coords[i * 2] = cos(portion * i);
        circle_coords[i * 2 + 1] = sin(portion * i);
    }
}

void DrawStar(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<kNumberPoints; i++){
        esat::Vec3 p = { star_coords[i * 2], star_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

void DrawCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(120.0f, 120.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<100; i++){
        esat::Vec3 p = { circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_circle[i * 2] = result.x;
		transformed_circle[i * 2 + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255, 255, 255, 0);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_circle, 100);
}

void DrawEarth(){

    i=i+0.5;
    if(i>=100){i=0;} 

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(30.0f, 30.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.003), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(transformed_circle[(int)i * 2], transformed_circle[(int)i * 2 + 1]),m);

    for(int i=0; i<kNumberPoints; i++){
        esat::Vec3 p = { star_coords[i * 2], star_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

void DrawCircleEarth(){

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(transformed_circle[(int)i * 2], transformed_circle[(int)i * 2 + 1]),m);

    for(int i=0; i<100; i++){
        esat::Vec3 p = { circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_circle[i * 2] = result.x;
		transformed_circle[i * 2 + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255, 255, 255, 0);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_circle, 100);
}

void DrawMoon(){

    i=i+0.6;
    if(i>=100){i=0;} 

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.006), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(transformed_circle[(int)i * 2], transformed_circle[(int)i * 2 + 1]),m);

    for(int i=0; i<kNumberPoints; i++){
        esat::Vec3 p = { star_coords[i * 2], star_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
    }
    esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
}


int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitStar();
  InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawStar();
    DrawCircle();

    DrawEarth();
    DrawCircleEarth();

    DrawMoon();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}