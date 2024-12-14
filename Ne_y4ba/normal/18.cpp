#include <iostream>
#include <stack>
#include <string>

bool check(std::string& s)
{
    std::string allowed_characters = "1234567890+-*() ";
    for (const auto& i : s) {
        if (allowed_characters.find(i) == std::string::npos) {
            return true;
        }
    }

    size_t left_bracket = 0, right_bracket = 0;
    bool empty_brackets = false;
    for (const auto& i : s) {
        if (i == ' ') {
            continue;
        }
        if (i == '(') {
            left_bracket++;
            empty_brackets = true;
        } else if (i == ')') {
            right_bracket++;
            if (empty_brackets) {
                return true;
            }
        } else {
            empty_brackets = false;
        }
        if (right_bracket > left_bracket) {
            return true;
        }
    }

    bool num = false, a = false;
    for (const auto& i : s) {
        if (i == ' ') {
            if (num) {
                num = false;
                a = true;
            }
            continue;
        }

        if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6'
            || i == '7' || i == '8' || i == '9' || i == '0') {
            if (a) {
                return true;
            }
            num = true;
            a = false;
        } else {
            num = false;
            a = false;
        }
    }

    bool op = false, b = false;
    for (const auto& i : s) {
        if (i == ' ') {
            if (op) {
                num = false;
                b = true;
            }
            continue;
        }

        if (i == '+' || i == '-' || i == '*') {
            if (b) {    
                return true;
            }
            op = true;
            b = false;
        } else {
            op = false;
            b = false;
        }
    }

    return false;
}

void add_number(std::string& substring, std::stack<long int>& number)
{
    if (substring.length() > 0) {
        const auto temp = (stol(substring));
        substring.erase(0, substring.length());
        number.push(temp);
    }
}

int main()
{
    std::string s, substring;
    std::getline(std::cin, s);

    if (check(s)) {
        std::cout << "WRONG\n";
        return 0;
    }

    std::stack<long int> number;
    std::stack<char> operand;

    for (const auto& i : s) {
        if (i == ' ') {
            add_number(substring, number);
            continue;
        }
        if (i == '(') {
            operand.push(i);
        } else if (i == ')') {
            add_number(substring, number);
            while (operand.top() != '(') {
                if (operand.top() == '-') {
                    long b = number.top();
                    number.pop();
                    long a = number.top();
                    number.pop();
                    operand.pop();
                    number.push(a - b);
                } else if (operand.top() == '+') {
                    long b = number.top();
                    number.pop();
                    long a = number.top();
                    number.pop();
                    operand.pop();
                    number.push(a + b);
                } else {
                    long b = number.top();
                    number.pop();
                    long a = number.top();
                    number.pop();
                    operand.pop();
                    number.push(a * b);
                }
            }
            operand.pop();

        } else if (i == '+' || i == '*' || i == '-') {
            add_number(substring, number);
            if (!operand.empty()) {
                if (operand.top() == '*' && (i == '+' || i == '-')) {
                    long b = number.top();
                    number.pop();
                    long a = number.top();
                    number.pop();
                    operand.pop();
                    number.push(a * b);
                } else if (operand.top() == '-' && (i == '+' || i == '-')) {
                    long b = number.top();
                    number.pop();
                    long a = number.top();
                    number.pop();
                    operand.pop();
                    number.push(a - b);
                }
            }
            operand.push(i);
        } else {
            substring += i;
        }
    }

    add_number(substring, number);

    while (!operand.empty()) {
        if (operand.top() == '-') {
            long b = number.top();
            number.pop();
            long a = number.top();
            number.pop();
            operand.pop();
            number.push(a - b);
        } else if (operand.top() == '+') {
            long b = number.top();
            number.pop();
            long a = number.top();
            number.pop();
            operand.pop();
            number.push(a + b);
        } else {
            long b = number.top();
            number.pop();
            long a = number.top();
            number.pop();
            operand.pop();
            number.push(a * b);
        }
    }

    std::cout << number.top() << "\n";

    return 0;
}