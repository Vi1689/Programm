// Решена

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::map<std::string, int> сollecting_responses;

int counter(
        std::unordered_map<std::string, std::vector<std::string>>& lines,
        int count,
        const std::string root)
{
    int akk = lines[root].size();
    for (const auto& i : lines[root]) {
        akk += counter(lines, akk, i);
    }
    сollecting_responses[root] = akk;
    return akk;
}

int main()
{
    int n;
    std::cin >> n;
    std::unordered_map<std::string, std::vector<std::string>> lines;
    std::unordered_set<std::string> childrens;
    std::unordered_set<std::string> parents;

    while (--n) {
        std::string children, parent;
        std::cin >> children >> parent;
        childrens.insert(children);
        parents.insert(parent);
        lines[parent].push_back(children);
    }

    std::string root;
    for (const auto& i : parents) {
        if (childrens.find(i) == childrens.end()) {
            root = i;
            break;
        }
    }

    counter(lines, 0, root);

    for (const auto& [a, b] : сollecting_responses) {
        std::cout << a << " " << b << "\n";
    }

    return 0;
}