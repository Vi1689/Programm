#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int fakt(int a) {
  int sum = 1;
  for (int i = 1; i <= a; ++i) {
    sum *= i;
  }
  return sum;
}

double table(vector<double> y, int k, bool flag) {
  int i = 0;
  for (; i < k; ++i) {
    for (int j = 0; j < y.size() - i - 1; ++j) {
      y[j] = y[j + 1] - y[j];
    }
  }
  if (flag) {
    return y[0];
  } else {
    return y[y.size() - i - 1];
  }
}

double pervaia(double x_x, vector<double> x, vector<double> y) {
  double sum = 0.0, q = (x_x - x[0]) / 25.0, q_sum = 1.0, y_y = y[0];
  for (int i = 1; i < y.size(); ++i) {
    q_sum *= q - i + 1;
    sum += table(y, i, true) / (fakt(i) * 1.0) * q_sum;
  }
  return sum + y_y;
}

double vtoraia(double x_x, vector<double> x, vector<double> y) {
  int n = y.size() - 1;
  double sum = 0.0, q = (x_x - x[n]) / 25.0, q_sum = 1.0, y_y = y[n];
  for (int i = 1; i < y.size(); ++i) {
    q_sum *= q + i - 1;
    sum += table(y, i, false) / (fakt(i) * 1.0) * q_sum;
  }
  return sum + y_y;
}

int main() {
  vector<double> x;
  vector<double> y;
  ifstream Test("lab_6/Coordinates.txt");
  ofstream Out("lab_6/Coordinates_new.txt");
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

  double x_x, y_y;
  // printf("Введите значение x\nx = ");
  // cin >> x_x;
  // cout << "\n";
  x_x = 12;
  y_y = pervaia(x_x, x, y);
  Out << x_x << " " << y_y << "\n";
  x_x = 90;
  y_y = vtoraia(x_x, x, y);
  Out << x_x << " " << y_y << "\n";
  Test.close();
  Out.close();
}
