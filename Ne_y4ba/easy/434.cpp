// Решена

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<int>> combs;

void Enumeration(int sum, std::vector<int> comb)
{
    if (sum == 0) {
        combs.push_back(comb);
    }

    for (int i = std::min(sum, comb.back()); i > 0; --i) {
        comb.push_back(-1);
        comb.push_back(i);
        Enumeration(sum - i, comb);
        comb.pop_back();
        comb.pop_back();
    }
}

int main()
{
    int a;

    scanf("%d", &a);

    std::vector<int> arr;

    arr.push_back(a);

    Enumeration(a, arr);

    for (int i = combs.size() - 1; i >= 0; --i) {
        for (int j = 2; j < combs[i].size(); ++j) {
            if (combs[i][j] == -1) {
                printf(" + ");
            } else {
                printf("%d", combs[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}