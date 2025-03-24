#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

enum TYPE { NUM, ADD, SUB, MUL, DEV, LB, RB };

struct token {
    char id;
    int value;
};

class Parser {
private:
    std::vector<token> set_tokens;
    size_t count;
    token lookahead;

    std::stack<long> number;
    std::stack<char> operand;

    void operation(char op)
    {
        long b = number.top();
        number.pop();
        long a = number.top();
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
            if (!b) {
                std::cout << "WRONG\n";
                std::exit(0);
            }
            number.push(a / b);
            break;
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
            } else if (operand.top() == '~') {
                long a = number.top();
                number.pop();
                operand.pop();
                number.push(a * -1);
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
        while (true) {
            if (lookahead.id == ADD) {
                match(lookahead);
                score();
                term();
                score();
                operand.push('+');
                rest_expr();
            } else if (lookahead.id == SUB) {
                match(lookahead);
                score();
                term();
                score();
                operand.push('-');
                rest_expr();
            } else {
                return;
            }
        }
    }

    void term()
    {
        primary();
        rest_term();
    }

    void rest_term()
    {
        while (true) {
            if (lookahead.id == MUL) {
                match(lookahead);
                score();
                primary();
                score();
                operand.push('*');
                rest_term();
            } else if (lookahead.id == DEV) {
                match(lookahead);
                score();
                primary();
                score();
                operand.push('/');
                rest_term();
            } else {
                return;
            }
        }
    }

    void primary()
    {
        if (lookahead.id == NUM) {
            number.push(lookahead.value);
            match(lookahead);
        } else if (lookahead.id == SUB) {
            operand.push('~');
            match(lookahead);
            primary();
        } else if (lookahead.id == LB) {
            operand.push('(');
            match(lookahead);
            expr();
            while (operand.top() != '(') {
                score();
            }
            operand.pop();
            match(lookahead);
        } else {
            std::cout << "WRONG\n";
            std::exit(0);
        }
    }

    void match(token ch)
    {
        if (lookahead.id == ch.id) {
            lookahead = readChar();
        } else {
            std::cout << "WRONG\n";
            std::exit(0);
        }
    }

    token readChar()
    {
        if (count > set_tokens.size()) {
            std::cout << "WRONG\n";
            std::exit(0);
        }
        return set_tokens[count++];
    }

    void splitting_into_tokens()
    {
        char c;
        int num;

        while ((c = std::cin.get()) != '\n') {
            if (isdigit(c)) {
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
        count = 0;
        lookahead = readChar();
        expr();
    }

    long calc()
    {
        while (!operand.empty()) {
            score();
        }
        return number.top();
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