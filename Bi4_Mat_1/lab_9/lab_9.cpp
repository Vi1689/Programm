#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

double f(double x, double y) { return 6 * x * x + 5 * y * x; }

int main() {
  std::ofstream Out("lab_9/output.txt");
  int n;
  double h, x, y;
  std::cout << "Введите размер шара h = ";
  std::cin >> h;
  std::cout << "\nВведите количество итераций n = ";
  std::cin >> n;
  std::cout << "\nВведите начальные координаты x и y ";
  std::cin >> x >> y;
  while (n--) {
    /*
    double k1 = f(x, y);
    double k2 = f(x + h / 2.0, y + h / 2.0 * k1);
    double k3 = f(x + h / 2.0, y + h / 2.0 * k2);
    double k4 = f(x + h, y + h * k3);
    y += h / 6.0 * f(x, y) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
    */
    y += y + h * f(x, y);
    x += h;
    Out << x << " " << y << "\n";
  }
  Out.close();
  return 0;
}