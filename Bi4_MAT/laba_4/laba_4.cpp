#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

double InterPol(double x_x, double y_y, vector<double> x, vector<double> y)
{
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

int main()
{
    vector<double> x;
    vector<double> y;
    ifstream Test("laba_4/Coordinates.txt");
    ofstream Out("laba_4/Coordinates_new.txt");
    while (!Test.eof()) {
        double z;
        Test >> z;
        Out << z << " ";
        x.push_back(z);
        Test >> z;
        Out << z << "\n";
        y.push_back(z);
    }
    for (int i = 0; i < x.size(); ++i) {
        printf("x = %f  y = %f\n", x[i], y[i]);
    }
    double x_x = 2.56, y_y = 0.0;
    //cin >> x_x;
    y_y = InterPol(x_x, y_y, x, y);
    Out << x_x << " " << y_y << "\n";

    Test.close();
    Out.close();
}