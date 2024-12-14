// Решена

#include <iostream>
#include <vector>

template <typename T>
class heap {
private:
    std::vector<T> a;

    size_t left(size_t arg)
    {
        return arg * 2;
    }

    size_t right(size_t arg)
    {
        return arg * 2 + 1;
    }

    size_t parent(size_t arg)
    {
        return arg / 2;
    }

    void HeapUp(size_t arg)
    {
        while (arg > 1 && a[parent(arg)] < a[arg]) {
            std::swap(a[parent(arg)], a[arg]);
            arg = parent(arg);
        }
    }

    void HeapDown()
    {
        size_t i = 1;
        while (i < a.size()) {
            size_t l = left(i), r = right(i), largest = i;
            if (r <= a.size()) {
                if (a[r] > a[l]) {
                    if (r <= a.size() && a[r] > a[largest]) {
                        largest = r;
                    } else if (l <= a.size() && a[l] > a[largest]) {
                        largest = l;
                    }
                } else {
                    if (l <= a.size() && a[l] > a[largest]) {
                        largest = l;
                    } else if (r <= a.size() && a[r] > a[largest]) {
                        largest = r;
                    }
                }
            } else {
                if (l <= a.size() && a[l] > a[largest]) {
                    largest = l;
                } else if (r <= a.size() && a[r] > a[largest]) {
                    largest = r;
                }
            }
            if (largest != i) {
                std::swap(a[i], a[largest]);
                i = largest;
            } else {
                break;
            }
        }
    }

public:
    heap()
    {
        a.push_back(0);
    }

    void insert(T arg)
    {
        a.push_back(arg);
        HeapUp(a.size() - 1);
    }

    T deletemax()
    {
        T max = a[1];
        a[1] = a[a.size() - 1];
        a.pop_back();
        HeapDown();
        return max;
    }

    int max()
    {
        return a[1];
    }
};

int main()
{
    heap<long int> h;
    int n;
    std::cin >> n;
    while (n--) {
        int a;
        std::cin >> a;
        if (a) {
            std::cout << h.deletemax() << "\n";
        } else {
            long int num;
            std::cin >> num;
            h.insert(num);
        }
    }
    return 0;
}