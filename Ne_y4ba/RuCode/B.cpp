//  Решена

#include <iostream>
#include <string>

int main()
{
    std::string time;
    std::cin >> time;
    bool flag = false;
    for (const auto& i : time) {
        if (i == ':') {
            flag = true;
        }
    }

    if (flag) {
        int h = (time[0] - 48) * 10 + (time[1] - 48),
            c = (time[3] - 48) * 10 + (time[4] - 48),
            s = (time[6] - 48) * 10 + (time[7] - 48);

        printf("%d\n", h * 60 * 60 + c * 60 + s);
    } else {
        int tmp = strtol(time.c_str(), NULL, 10);
        int h = (tmp / (60 * 60)), c = (tmp - (h * 60 * 60)) / (60),
            s = (tmp - (h * 60 * 60) - (c * 60));

        printf("%02d:%02d:%02d\n", h, c, s);
    }

    return 0;
}