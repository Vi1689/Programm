#include <cmath>
#include <iostream>
#include <string>
#include <time.h>

class node {
protected:
    int x, y;
    node()
    {
        this->x = rand() % 10;
        this->y = rand() % 10;
    }

    virtual void print() const = 0;
};

class malina : public node {
private:
    int time;

public:
    malina()
    {
        this->x = rand() % 10;
        this->y = rand() % 10;
    }

    ~malina()
    {
    }
};

class belka : protected node {
private:
    float food;

public:
    belka()
    {
        this->x = rand() % 10;
        this->y = rand() % 10;
        this->food = 0.7;
    }

    void moving()
    {
        int temp = rand() % 4;
        switch (temp) {
        case 0:
            this->y++;
            this->x--;
            break;
        case 1:
            this->y--;
            this->x--;
            break;
        case 2:
            this->x++;
            this->y++;
            break;
        case 3:
            this->x++;
            this->y--;
            break;
        default:
            throw "Error";
        }
    }
    void print() const override
    {
        std::cout << x << " " << y << "\n";
    }

    ~belka()
    {
    }
};

class sobol : public node {
private:
    float food;

public:
    sobol()
    {
        this->x = rand() % 10;
        this->y = rand() % 10;
        this->food = 0.7;
    }

    void moving()
    {
        int temp = rand() % 4;
        switch (temp) {
        case 0:
            this->y++;
            break;
        case 1:
            this->y--;
            break;
        case 2:
            this->x++;
            break;
        case 3:
            this->x--;
            break;
        default:
            throw "Error";
        }
    }

    void print() const override
    {
        std::cout << x << " " << y << "\n";
    }

    ~sobol()
    {
    }
};