#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

const double ae = 0.999;
const double ai = 0.999;
const double k = 0.042;
const double p = 0.952;
const double b = 0.999;
const double u = 0.0188;
const double c = 0;
const double E0 = 99;
const double R0 = 24;
const double S0 = 2798047;
const double I0 = 0;
const double D0 = 0;

double S(double sn, double in, double en, double rn, int n) {
  return -1 * (ai * sn * in / n + ae * sn * en / n);
}

double E(double sn, double in, double en, int n) {
  return (ai * sn * in / n + ae * sn * en / n) - (k + p) * en;
}

double I(double en, double in) { return k * en - b * in - u * in; }

double R(double in, double en, double rn) { return b * in + p * en; }

double D(double in) { return u * in; }

int main() {
  std::ofstream Out("kursach/test.txt");
  double s = S0, e = E0, i = I0, r = R0, d = D0;

  double h = 1;
  /*
    Out << "День | S | E | I | R | "
           "D\n------------------------------------------------------------------"
           "-----------------------------------------------\n";
  */
  for (int j = 0; j < 90; ++j) {
    double n = s + e + i + r + d;

    double ss, ee, ii, rr, dd;

    ss = S(s, i, e, r, n) + s * h;
    ee = E(s, i, e, n) + e * h;
    ii = I(e, i) + i * h;
    rr = R(i, e, r) + r * h;
    dd = D(i) + d * h;

    s += h * (S(ss, ii, ee, rr, n) + S(s, i, e, r, n)) / 2;
    e += h * (E(ss, ii, ee, n) + E(s, i, e, n)) / 2;
    i += h * (I(ee, ii) + I(e, i)) / 2;
    r += h * (R(ii, ee, rr) + R(i, e, r)) / 2;
    d += h * (D(ii) + D(i)) / 2;

    Out.precision(11);
    Out << j + 1 << " " << s << " " << e << " " << i << " " << r << " " << d
        << "\n";

    // y(i+1) = y(i) + h * f(x(i) * h / 2, y(i) + h / 2 * f (x(i), y(i)));

    /*
    Out << j + 1 << " | " << s << " | " << e << " | " << i << " | " << r
        << " | " << d
        << "\n-----------------------------------------------------------------"
           "------------------------------------------------\n";
    */
  }

  Out.close();
  return 0;
}
