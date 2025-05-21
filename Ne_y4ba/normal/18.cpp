// Решена

#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

enum TYPE { NUM, ADD, SUB, MUL, DEV, LB, RB, END };

struct token {
    char id;
    long double value;
};

class Parser {
private:
    std::vector<token> set_tokens;
    size_t current_token;
    token lookahead;

    std::stack<long double> number;
    std::stack<char> operand;

    void operation(char op)
    {
        long double b = number.top();
        number.pop();
        long double a = number.top();
        number.pop();
        operand.pop();
        switch (op) {
        case '+':
            number.push(a + b);
            break;
        case '-':
            number.push(a - b);
            break;
        case '*':
            number.push(a * b);
            break;
        case '/':
            if (b == 0) {
                std::cout << "WRONG\n";
                std::exit(0);
            }
            number.push(a / b);
            break;
        }
    }

    void unary_minus()
    {
        if (!operand.empty()) {
            if (operand.top() == '~') {
                long double a = number.top();
                number.pop();
                operand.pop();
                number.push(a * -1);
            }
        }
    }

    void score()
    {
        if (!operand.empty()) {
            if (operand.top() == '*') {
                operation('*');
            } else if (operand.top() == '/') {
                operation('/');
            } else if (operand.top() == '-') {
                operation('-');
            } else if (operand.top() == '+') {
                operation('+');
            }
        }
    }

    void expr()
    {
        term();
        rest_expr();
    }

    void rest_expr()
    {
        readtoken();
        if (lookahead.id == ADD) {
            next_token();
            unary_minus();
            term();
            unary_minus();
            operand.push('+');
            rest_expr();
        } else if (lookahead.id == SUB) {
            next_token();
            unary_minus();
            term();
            unary_minus();
            operand.push('-');
            score();
            rest_expr();
        } else {
            return;
        }
    }

    void term()
    {
        primary();
        rest_term();
    }

    void rest_term()
    {
        readtoken();
        if (lookahead.id == MUL) {
            next_token();
            unary_minus();
            primary();
            unary_minus();
            operand.push('*');
            score();
            rest_term();
        } else if (lookahead.id == DEV) {
            next_token();
            unary_minus();
            primary();
            unary_minus();
            operand.push('/');
            score();
            rest_term();
        } else {
            return;
        }
    }

    void primary()
    {
        readtoken();
        if (lookahead.id == NUM) {
            number.push(lookahead.value);
            next_token();
        } else if (lookahead.id == SUB) {
            operand.push('~');
            next_token();
            primary();
        } else if (lookahead.id == LB) {
            operand.push('(');
            next_token();
            expr();
            while (operand.top() != '(') {
                unary_minus();
                score();
            }
            operand.pop();
            next_token();
        } else {
            std::cout << "WRONG\n";
            std::exit(0);
        }
    }

    void next_token()
    {
        current_token++;
    }

    void readtoken()
    {
        if (current_token >= set_tokens.size()) {
            std::cout << "WRONG\n";
            std::exit(0);
        }
        lookahead = set_tokens[current_token];
    }

    void splitting_into_tokens()
    {
        char c;
        long double num;

        while ((c = std::cin.get()) != '\n') {
            if (isdigit(c) || c == '.') {
                std::cin.unget();
                if (std::cin >> num) {
                    set_tokens.push_back({NUM, num});
                }
            } else if (c == '+') {
                set_tokens.push_back({ADD, '+'});
            } else if (c == '-') {
                set_tokens.push_back({SUB, '-'});
            } else if (c == '*') {
                set_tokens.push_back({MUL, '*'});
            } else if (c == '/') {
                set_tokens.push_back({DEV, '/'});
            } else if (c == '(') {
                set_tokens.push_back({LB, '('});
            } else if (c == ')') {
                set_tokens.push_back({RB, ')'});
            } else if (c == ' ') {
                continue;
            } else {
                std::cout << "WRONG\n";
                std::exit(0);
            }
        }
        set_tokens.push_back({END, 0});
    }

    void check()
    {
        splitting_into_tokens();
        size_t count_lb = 0, count_rb = 0;
        for (const auto [id, value] : set_tokens) {
            count_lb += id == LB;
            count_rb += id == RB;
            if (count_rb > count_lb) {
                std::cout << "WRONG\n";
                std::exit(0);
            }
        }
        if (count_lb != count_rb) {
            std::cout << "WRONG\n";
            std::exit(0);
        }

        for (size_t i = 0; i < set_tokens.size() - 1; ++i) {
            if (set_tokens[i].id == NUM && set_tokens[i + 1].id == NUM) {
                std::cout << "WRONG\n";
                std::exit(0);
            }
        }
    }

public:
    Parser()
    {
    }

    void parse()
    {
        check();
        current_token = 0;
        readtoken();
        expr();
    }

    long double calc()
    {
        while (!operand.empty()) {
            unary_minus();
            score();
        }
        return number.top();
        return 0;
    }

    ~Parser()
    {
    }
};

int main()
{
    Parser parser;
    parser.parse();
    std::cout << parser.calc() << '\n';
    std::exit(0);
}