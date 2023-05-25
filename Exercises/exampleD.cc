#include <stdio.h>

namespace EMK {
struct Vec2 {
  float x, y;
};

struct Mat2 {
  /*
    m = 0 2
        1 3
  */
  float m[4];
};

Vec2 Vec2MultMat2Vec2(Mat2 mat, Vec2 vec) {
  Vec2 tmp = {
    mat.m[0] * vec.x + mat.m[2] * vec.y,
    mat.m[1] * vec.x + mat.m[3] * vec.y
  };
  return tmp;
};

void Vec2Print(Vec2 v) {
  printf("[X]: %f [Y]: %f\n", v.x, v.y);
}
}

int main(int argc, char** argv) {
  EMK::Vec2 v = { 2.0f, 1.0f };
  /*
    m1 = 1.0f 0.0f
         2.0f 1.0f
  */
  EMK::Mat2 m1 = { 1.0f, 2.0f, 0.0f, 1.0f };
  /*
    m2 = 2.0f 3.0f
         0.0f 2.0f
  */
  EMK::Mat2 m2 = { 2.0f, 0.0f, 3.0f, 2.0f };

  /*
    v1 = m1 * v
     1.0f 0.0f  *  2.0f
     2.0f 1.0f     1.0f
  */
  EMK::Vec2 v1 = EMK::Vec2MultMat2Vec2(m1, v);
  /*
    v2 = m2 * v
     2.0f 3.0f  *  2.0f
     0.0f 2.0f     1.0f
  */
  EMK::Vec2 v2 = EMK::Vec2MultMat2Vec2(m2, v);

  EMK::Vec2Print(v1);
  EMK::Vec2Print(v2);

  return 0;
}