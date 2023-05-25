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

const float kCircunference = 2*PI;
const int kNumberPoints = 10;
const int kNumberPointsCircle = 180;
float count=0;

float star_coords[kNumberPoints * 2] = { 0.0f };
float circle_coords[kNumberPointsCircle * 2] = { 0.0f };
float transformed_star_coords[kNumberPoints * 2] = { 0.0f };
float transformed_circle_coords[kNumberPointsCircle * 2] = { 0.0f };

float offsetY=0, offsetX=0, kRadius=50;

void InitStarShape(float *star) {
	float portion = kCircunference / kNumberPoints;

	for (int i=0; i<kNumberPoints; ++i) {
        if (i%2 == 0) {
		    star[i * 2] = cos(portion * i) * kRadius;
	        star[i * 2 + 1] = sin(portion * i) * kRadius;
        }else{
            star[i * 2] = cos(portion * i) * kRadius * 0.5f;
	        star[i * 2 + 1] = sin(portion * i) * kRadius * 0.5f;
        }
	}

}

void InitCircleShape(float *circle) {
	float portion = kCircunference / kNumberPointsCircle;

	for (int i = 0; i < kNumberPointsCircle; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void DrawMoonShape(const float *shape_coords){

    count=count+0.5;
    if(count>=kNumberPointsCircle){count=0;}  
        
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(0.3f, 0.3f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.005), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(transformed_star_coords[(int)count * 2] , transformed_star_coords[(int)count * 2 +1]),m);
    
    for (int i=0; i<kNumberPoints; ++i) {
        esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        transformed_star_coords[i * 2] = result.x;
        transformed_star_coords[i * 2 + 1] = result.y;
    }
    
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_star_coords, kNumberPoints);
}

void DrawOrbitMoon(const float *shape_coords, float posX, float posY){

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<kNumberPointsCircle; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_star_coords[i * 2] = result.x;
		transformed_star_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255, 0);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_star_coords, kNumberPointsCircle);
}

void DrawEarthShape(const float *shape_coords){

    count=count+0.5;
    if(count>=kNumberPointsCircle){count=0;}  
        
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(0.5f, 0.5f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.003), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(transformed_circle_coords[(int) count * 2], transformed_circle_coords[(int) count * 2 + 1]),m);
    
    for (int i=0; i<kNumberPoints; ++i) {
        esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        transformed_star_coords[i * 2] = result.x;
        transformed_star_coords[i * 2 + 1] = result.y;
    }
    
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_star_coords, kNumberPoints);

}

void DrawSunShape(const float *shape_coords, float posX, float posY){
        
    esat::Vec3 p;
    esat::Vec3 result;

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

    for (int i=0; i<kNumberPoints; ++i) {
        p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        result = esat::Mat3TransformVec3(m, p);
        transformed_star_coords[i * 2] = result.x;
        transformed_star_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_star_coords, kNumberPoints);
}

void DrawOrbitEarth(const float *shape_coords, float posX, float posY){

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(150.0f, 150.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<kNumberPointsCircle; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_circle_coords[i * 2] = result.x;
		transformed_circle_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255, 0);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_star_coords, kNumberPointsCircle);       
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitStarShape(star_coords);
  InitCircleShape(circle_coords);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawSunShape(star_coords, mPosX, mPosY);
    DrawOrbitEarth(circle_coords, mPosX, mPosY);

    DrawEarthShape(star_coords);
    DrawOrbitMoon(circle_coords, transformed_circle_coords[(int) count * 2], transformed_circle_coords[(int) count * 2 + 1]);
    
    DrawMoonShape(star_coords);


    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}