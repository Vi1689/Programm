//  Решена

#include <cmath>
#include <iostream>

int main()
{
    int x, y, r;
    std::cin >> x >> y >> r;

    bool q = false, w = false, e = false, t = false, u = false;

    for (int i = 0; i < 360; ++i) {
        double angle = 2 * M_PI * i / 360;
        double a = x + r * cos(angle);
        double b = y + r * sin(angle);
        if (a > 0 && b > 0) {
            q = true;
        }
        if (a > 0 && b < 0) {
            w = true;
        }
        if (a < 0 && b > 0) {
            e = true;
        }
        if (a < 0 && b < 0) {
            t = true;
        }
        if (a == 0 || b == 0) {
            u = true;
        }
    }

    if (q + w + e + t >= 2) {
        u = true;
    }

    std::cout << (q + w + e + t + u) << '\n';

    return 0;
}