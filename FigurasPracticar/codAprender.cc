
//Codigo que me tengo que aprender

//Transformed coords, se aplica en todo
for (int i=0; i<kNumberPoints; ++i) {
            p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
            result = esat::Mat3TransformVec3(m, p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
}

//Dibujado de un circulo
void InitShapeCoords() {
	float portion = kCircunference / kNumberPoints;
	for(int i = 0; i < kNumberPoints; ++i) {
		circle_coords[i * 2] = cos(portion * i);
		circle_coords[i * 2 + 1] = sin(portion * i);
	}
}

//Dibujado de una estrella, usando lo del circulo
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

void DrawStar(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();
    float portion = kCircunference / 3;

    cont = cont + 0.2;
    if(cont>kNumberPoints){cont=0;}

    for(int j=0; j<3; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(transformed_coords[(int)cont * 2], transformed_coords[(int)cont * 2 + 1]), m);

        for(int i=0; i<kNumberPointsStar; i++){
            esat::Vec3 p = {star_coords[2 * i], star_coords[2 * i + 1], 1.0f};
            esat::Vec3 result = Mat3TransformVec3(m,p);
            transformed_star[2 * i] = result.x;
            transformed_star[2 * i + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_star, kNumberPointsStar);
    }
}

void DrawThreeCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / 3;

    for(int j=0; j<3; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(25.0f, 70.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

        for(int i=0; i<kNumberPoints; i++){
            esat::Vec3 p = {circle_coords[2 * i], circle_coords[2 * i + 1], 1.0f};
            esat::Vec3 result = Mat3TransformVec3(m,p);
            transformed_coords[2 * i] = result.x;
            transformed_coords[2 * i + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_coords, kNumberPoints);
        DrawStar();
    }
}