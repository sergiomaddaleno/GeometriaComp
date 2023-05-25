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
float mPosX;
float mPosY;

float arrow[] = {
0.0f, 1.0f,
1.0f, 0.0f,
0.0f, -3.0f,
-1.0f, 0.0f };

float square[] = {
-1.0f, -1.0f,
1.0f, -1.0f,
1.0f, 1.0f,
-1.0f, 1.0f,
-1.0f, -1.0f };

const int kNumberPoints = 6;

float circle_coords[kNumberPoints * 2] = { 0.0f };
float transformed_coords[20] = { 0.0f };
const float kCircunference = 2*PI;

float offsetX=0, offsetY=0, radius=35;

void InitCircle(float *circle) {
	float portion = kCircunference / kNumberPoints;
	for (int i = 0; i < kNumberPoints; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void DrawCenterHex(const float *shape_coords, float scale, float angle, float posX, float posY) {

	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<kNumberPoints; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

void DrawCenterSquare(float scale, float angle, float posX, float posY) {

	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<4; ++i) {
		esat::Vec3 p = { square[i * 2], square[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_coords, 4);
}

void DrawArrowUpDown(float scale, float angle, float posX, float posY) {

    for(int i=-4; i<=4; i=i+2){
        for(int j=-1; j<=1; j=j+2){

			//matriz rombos
            esat::Mat3 m = esat::Mat3Identity();
			if(j==-1){m = esat::Mat3Multiply(esat::Mat3Rotate(PI), m);}
			m = esat::Mat3Multiply(esat::Mat3Translate(i, j*10.0f),m);
	        m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	        m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	        for (int j=0; j<4; ++j) {
	        	esat::Vec3 p = { arrow[j * 2], arrow[j * 2 + 1], 1.0f };
	        	esat::Vec3 result = esat::Mat3TransformVec3(m, p);
	        	transformed_coords[j * 2] = result.x;
	        	transformed_coords[j * 2 + 1] = result.y;
	        }

	        esat::DrawSetStrokeColor(255, 255, 255);
	        esat::DrawSetFillColor(0, 0, 0, 0);
	        esat::DrawSolidPath(transformed_coords, 4);
        }
    }
}   

void DrawArrowLeftRight(float scale, float angle, float posX, float posY) {

    for(int i=-4; i<=4; i=i+2){
        for(int j=-1; j<=1; j=j+2){

            esat::Mat3 m = esat::Mat3Identity();
			if(j==1){m = esat::Mat3Multiply(esat::Mat3Rotate(PI), m);}
			m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
			m = esat::Mat3Multiply(esat::Mat3Translate(j*10.0f, i),m);
	        m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	        m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	        for (int j=0; j<4; ++j) {
	        	esat::Vec3 p = { arrow[j * 2], arrow[j * 2 + 1], 1.0f };
	        	esat::Vec3 result = esat::Mat3TransformVec3(m, p);
	        	transformed_coords[j * 2] = result.x;
	        	transformed_coords[j * 2 + 1] = result.y;
	        }

	        esat::DrawSetStrokeColor(255, 255, 255);
	        esat::DrawSetFillColor(0, 0, 0, 0);
	        esat::DrawSolidPath(transformed_coords, 4);
        }
    }
}   

void DrawLongArrow(float posX, float posY) {

	for(int i=0; i<=4; i++){

    	esat::Mat3 m = esat::Mat3Identity();
    	m = esat::Mat3Multiply(esat::Mat3Scale(15, 40), m);
		m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -150.0f),m);
		m = esat::Mat3Multiply(esat::Mat3Rotate((PI/4)+(i*PI/2)), m);
    	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);
	
		for (int j=0; j<4; ++j) {
    		esat::Vec3 p = { arrow[j * 2], arrow[j * 2 + 1], 1.0f };
    		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
    	  	transformed_coords[j * 2] = result.x;
    	  	transformed_coords[j * 2 + 1] = result.y;
    	}

    	esat::DrawSetStrokeColor(255, 255, 255);
    	esat::DrawSetFillColor(0, 0, 0, 0);
    	esat::DrawSolidPath(transformed_coords, 4);   
	}
} 

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitCircle(circle_coords);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    mPosX = esat::MousePositionX();
    mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawCenterHex(circle_coords, 50.0f, 0.0f, mPosX, mPosY);
    DrawCenterSquare(50.0f, 0.0f, mPosX, mPosY);
    DrawArrowUpDown(9.0f, 0.0f, mPosX, mPosY);
	DrawArrowLeftRight(9.0f, PI/2, mPosX, mPosY);
	DrawLongArrow(mPosX, mPosY);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}