#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double Aitken(double x_x, double y_y, vector<double> x, vector<double> y, int k,
              int l) {
  if (l == k) {
    return y[k];
  }
  y_y = (Aitken(x_x, y_y, x, y, k, l - 1) * (x_x - x[l]) -
         Aitken(x_x, y_y, x, y, k + 1, l) * (x_x - x[k])) /
        (x[k] - x[l]);
  return y_y;
}

int main() {
  vector<double> x;
  vector<double> y;
  ifstream Test("lab_5/Coordinates.txt");
  ofstream Out("lab_5/Coordinates_new.txt");
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
  /*
  double x_x = 2, y_y = 0.0;
  y_y = Aitken(x_x, y_y, x, y, 0, x.size() - 1);
  Out << x_x << " " << y_y << "\n";
  */
  double e;
  cin >> e;
  for (int i = 0; i < x.size() - 1; ++i) {
    Out << x[i] << " " << y[i] << "\n";
    double x_x = x[i] + e, y_y = 0.0;
    while (x_x < x[i + 1]) {
      y_y = Aitken(x_x, y_y, x, y, 0, x.size() - 1);
      Out << x_x << " " << y_y << "\n";
      x_x += e;
      y_y = 0.0;
    }
  }
  Out << x[x.size() - 1] << " " << y[y.size() - 1] << "\n";
  Test.close();
  Out.close();
}
