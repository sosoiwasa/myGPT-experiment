#include <iostream>
#include <stack>
#include <sstream>
#include <string>

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double performOperation(const std::string& op, double val1, double val2) {
    if (op == "+") return val1 + val2;
    if (op == "-") return val1 - val2;
    if (op == "*") return val1 * val2;
    if (op == "/") return val1 / val2;
    return 0; // Should not reach here if input is valid
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"RPN expression\"" << std::endl;
        return 1;
    }

    std::istringstream iss(argv[1]);
    std::string token;
    std::stack<double> values;

    while (iss >> token) {
        if (isdigit(token[0])) {
            int num = std::atoi(token.c_str());
            if (num >= 10) {
                std::cerr << "Error: Number in expression is greater than or equal to 10." << std::endl;
                return 1;
            } else if (num < 0) {
                std::cerr << "Error: Number in expression is invalid." << std::endl;
                return 1;
            }
            values.push(static_cast<double>(num));
        } else if (isOperator(token)) {
            if (values.size() < 2) {
                std::cerr << "Error: Invalid expression." << std::endl;
                return 1;
            }
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            values.push(performOperation(token, val1, val2));
        } else {
            std::cerr << "Error: Invalid token '" << token << "'." << std::endl;
            return 1;
        }
    }

    if (values.size() != 1) {
        std::cerr << "Error: Invalid expression." << std::endl;
        return 1;
    }

    std::cout << values.top() << std::endl;
    return 0;
}
