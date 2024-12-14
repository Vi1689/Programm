// Решена

#include <iostream>
#include <vector>

int main()
{
    int vvod;
    std::vector<int> sequence;
    while (std::cin >> vvod) {
        if (vvod == -2000000000) {
            break;
        }
        sequence.push_back(vvod);
    }

    size_t size = sequence.size() - 1;
    size_t a = 0, b = 0, c = 0, d = 0, e = 0;
    for (size_t i = 0; i < size; ++i) {
        a += (sequence[i] == sequence[i + 1]);
        b += (sequence[i] <= sequence[i + 1]);
        c += (sequence[i] < sequence[i + 1]);
        d += (sequence[i] >= sequence[i + 1]);
        e += (sequence[i] > sequence[i + 1]);
    }

    if (a == size) {
        std::cout << "CONSTANT\n";
    } else if (c == size) {
        std::cout << "ASCENDING\n";
    } else if (b == size) {
        std::cout << "WEAKLY ASCENDING\n";
    } else if (e == size) {
        std::cout << "DESCENDING\n";
    } else if (d == size) {
        std::cout << "WEAKLY DESCENDING\n";
    } else {
        std::cout << "RANDOM\n";
    }

    return 0;
}