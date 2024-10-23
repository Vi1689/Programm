#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double InterPol(double x_x, double y_y, vector<double> x, vector<double> y) {
  double temp = 1.0, temp_1 = 1.0;
  for (int i = 0; i < y.size(); ++i) {
    for (int j = 0; j < x.size(); ++j) {
      if (j != i) {
        temp *= (x_x - x[j]);
        temp_1 *= (x[i] - x[j]);
      }
    }
    y_y += y[i] * temp / temp_1;
    temp = 1.0;
    temp_1 = 1.0;
  }
  return y_y;
}

int main() {
  vector<double> x;
  vector<double> y;
  ifstream Test("lab_4/Coordinates.txt");
  ofstream Out("lab_4/Coordinates_new.txt");
  while (!Test.eof()) {
    double z;
    Test >> z;
    if (Test.eof()) {
      break;
    }
    x.push_back(z);
    Test >> z;
    if (Test.eof()) {
      break;
    }
    y.push_back(z);
  }
  double e;
  cin >> e;
  for (int i = 0; i < x.size() - 1; ++i) {
    Out << x[i] << " " << y[i] << "\n";
    double x_x = x[i] + e, y_y = 0.0;
    while (x_x < x[i + 1]) {
      y_y = InterPol(x_x, y_y, x, y);
      Out << x_x << " " << y_y << "\n";
      x_x += e;
      y_y = 0.0;
    }
  }
  Out << x[x.size() - 1] << " " << y[y.size() - 1] << "\n";
  Test.close();
  Out.close();
}
