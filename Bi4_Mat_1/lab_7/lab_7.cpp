#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double f(double x) { return x * x * x * x * x * x / 6; }

double metod_pram() {
  int n = 10000000;
  double a = -1.0, b = 1.0, s = 0.0;
  double h = (b - a) / n;
  for (int i = 0; i < n; ++i) {
    s += (f(a) + f(a + h)) / 2;
  }
  s *= h;
  return s;
}

int main() {
  ofstream Out("lab_7/Coordinates_new.txt");
  double x_x, y_y;
  y_y = metod_pram();
  Out << "Площадь равна = " << fabsf(y_y) << "\n";
  Out.close();
}
