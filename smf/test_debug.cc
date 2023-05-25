#include <stdio.h>
#include <stdlib.h>

int GetData() {
  return 12;
}

int FillArray(float* my_array) {
  int data = 10;
  for (int i = 0; i < 6; ++i) {
    my_array[i] = (float) i;
  }
  data = GetData();
  return data;
}

void PrintArray(float* my_array) {
  for (int i = 0; i < 6; ++i) {
    printf("%f\n", my_array[i]);
  }
}

int main(int argc, char** argv) {
  int data = 6;
  int another_data = 6;
  float* my_array = (float*) calloc(6, sizeof(float));
  data = FillArray(my_array);
  PrintArray(my_array);

  if (nullptr != my_array) {
    free(my_array);
    my_array = nullptr;
  }
  return 0;
}
