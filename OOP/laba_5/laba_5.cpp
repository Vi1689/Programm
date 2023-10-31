#include <cmath>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Figyra {
public:
    Figyra()
    {
        x = rand() % 10;
        y = rand() % 10;
    }

    Figyra(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    virtual void print_P() const = 0;
    virtual void print_S() const = 0;

protected:
    int x;
    int y;
};

class Linia : public Figyra {
private:
    static inline unsigned count_l;
    static inline unsigned count{};

protected:
    int x1, y1;
    float size;

public:
    Linia(int x, int y, int x1, int y1)
    {
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->size = Size(x, y, x1, y1);
        count_l++;
        count++;
    }

    Linia()
    {
        int x = rand() % 10, y = rand() % 10, x1 = rand() % 10,
            y1 = rand() % 10;
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->size = Size(x, y, x1, y1);
        count_l++;
        count++;
    }

    float Size(int x, int y, int x1, int y1)
    {
        return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    }

    void print_size()
    {
        cout << "Длина линии = " << size << "\n";
    }

    void print_S() const override
    {
        cout << 0 << "\n";
    }

    void print_P() const override
    {
        cout << 0 << "\n";
    }

    void print()
    {
        printf("Текущее количество линий - %d\nЛиний было создано - %d\n",
               count_l,
               count);
    }

    ~Linia()
    {
        count_l--;
    }
};

class Square : public Linia {
private:
    static inline unsigned count_q{};
    static inline unsigned count{};

protected:
    float p;
    float s;
    int x2, y2, x3, y3;
    float size1, size2, size3;

public:
    Square(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
    {
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->size = Size(x, y, x1, y1);
        this->size1 = Size(x1, y1, x2, y2);
        this->size2 = Size(x2, y2, x3, y3);
        this->size3 = Size(x3, y3, x, y);
        S_Square();
        P_Square();
        count_q++;
        count++;
    }

    Square()
    {
        int x = rand() % 10, y = rand() % 10, x1 = rand() % 10,
            y1 = rand() % 10, x2 = rand() % 10, y2 = rand() % 10,
            x3 = rand() % 10, y3 = rand() % 10;
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->size = Size(x, y, x1, y1);
        this->size1 = Size(x1, y1, x2, y2);
        this->size2 = Size(x2, y2, x3, y3);
        this->size3 = Size(x3, y3, x, y);
        S_Square();
        P_Square();
        count_q++;
        count++;
    }

    void S_Square()
    {
        this->s = size * size1;
    }

    void P_Square()
    {
        this->p = size + size1 + size2 + size3;
    }

    void print_S() const override
    {
        cout << "Площадь квадрата = " << s << "\n";
    }

    void print_P() const override
    {
        cout << "Периметор квадрата = " << p << "\n";
    }

    void print()
    {
        printf("Текущее количество квадратов - %d\nКвадратов было создано - "
               "%d\n",
               count_q,
               count);
    }

    ~Square()
    {
        count_q--;
    }
};

class Rectangle : public Square {
private:
    static inline unsigned count_r{};
    static inline unsigned count{};

public:
    Rectangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
    {
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->size = Size(x, y, x1, y1);
        this->size1 = Size(x1, y1, x2, y2);
        this->size2 = Size(x2, y2, x3, y3);
        this->size3 = Size(x3, y3, x, y);
        S_Square();
        P_Square();
        count_r++;
        count++;
    }

    Rectangle()
    {
        int x = rand() % 10, y = rand() % 10, x1 = rand() % 10,
            y1 = rand() % 10, x2 = rand() % 10, y2 = rand() % 10,
            x3 = rand() % 10, y3 = rand() % 10;
        this->x = x;
        this->y = y;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->size = Size(x, y, x1, y1);
        this->size1 = Size(x1, y1, x2, y2);
        this->size2 = Size(x2, y2, x3, y3);
        this->size3 = Size(x3, y3, x, y);
        S_Square();
        P_Square();
        count_r++;
        count++;
    }

    void print_S() const override
    {
        cout << "Площадь прямоугольника = " << s << "\n";
    }

    void print_P() const override
    {
        cout << "Периметор прямоугольника = " << p << "\n";
    }

    void print()
    {
        printf("Текущее количество прямоугольников - %d\nПрямоугольников было "
               "создано - %d\n",
               count_r,
               count);
    }

    ~Rectangle()
    {
        count_r--;
    }
};

class Circle : public Figyra {
private:
    static inline unsigned count_c{};
    static inline unsigned count{};

protected:
    float r, s, p, R;

public:
    Circle(int x, int y, float r)
    {
        this->x = x;
        this->y = y;
        this->r = r;
        this->R = r;
        S_circle();
        P_circle();
        count_c++;
        count++;
    }

    Circle()
    {
        this->x = rand() % 10;
        this->y = rand() % 10;
        this->r = rand() % 10;
        S_circle();
        P_circle();
        count_c++;
        count++;
    }

    void S_circle()
    {
        this->s = 3.14 * r * R;
    }

    void P_circle()
    {
        this->p = 4 * (3.14 * r * R + (r - R)) / (r + R);
    }

    void print_S() const override
    {
        cout << "Площадь круга = " << s << "\n";
    }

    void print_P() const override
    {
        cout << "Периметор круга = " << p << "\n";
    }

    void print()
    {
        printf("Текущее количество кругов - %d\nКругов было создано - %d\n",
               count_c,
               count);
    }

    ~Circle()
    {
        count_c--;
    }
};

class Ellipse : public Circle {
private:
    static inline unsigned count_e{};
    static inline unsigned count{};

private:
    float R;

public:
    Ellipse(int x, int y, float r, float R)
    {
        this->x = x;
        this->y = y;
        this->r = r;
        this->R = R;
        S_circle();
        P_circle();
        count_e++;
        count++;
    }

    Ellipse()
    {
        int x = rand() % 10, y = rand() % 10, R = rand() % 10, r = rand() % 10;
        this->x = x;
        this->y = y;
        this->r = r;
        this->R = R;
        S_circle();
        P_circle();
        count_e++;
        count++;
    }

    void print_S() const override
    {
        cout << "Площадь эллипса = " << s << "\n";
    }

    void print_P() const override
    {
        cout << "Периметор эллипса = " << p << "\n";
    }

    void print()
    {
        printf("Текущее количество эллипсов - %d\nЭллипсов было создано - %d\n",
               count_e,
               count);
    }

    ~Ellipse()
    {
        count_e--;
    }
};

int main()
{
    Rectangle a(1, 1, 1, 4, 2, 4, 2, 1);
    Rectangle a1;
    a.print();
    Rectangle* b;
    a.print();
    Rectangle* c = new Rectangle;
    a.print();
    Figyra** d = new Figyra*[4];
    d[0] = new Square(1, 1, 1, 4, 4, 4, 4, 1);
    d[1] = new Rectangle(1, 1, 1, 4, 4, 4, 4, 1);
    d[2] = new Circle(10, 10, 10);
    d[3] = new Ellipse(10, 10, 10, 10);
    a.print();
    for (int i = 0; i < 4; ++i) {
        d[i]->print_P();
        d[i]->print_S();
    }
    for (int i = 0; i < 4; ++i) {
        delete[] d[i];
    }
    delete[] d;
    a.print();
    return 0;
}
