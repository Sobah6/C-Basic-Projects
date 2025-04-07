#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// Forward declarations
double parseExpression(istringstream& in);

double parseNumber(istringstream& in) {
    double value;
    in >> value;
    return value;
}

double parseFactor(istringstream& in) {
    char c = in.peek();
    
    if (c == '(') {
        in.get(); // consume '('
        double value = parseExpression(in);
        in.get(); // consume ')'
        return value;
    } else if (c == '-') {
        in.get();
        return -parseFactor(in);
    } else {
        return parseNumber(in);
    }
}

double parsePower(istringstream& in) {
    double base = parseFactor(in);
    while (in.peek() == '^') {
        in.get();
        double exponent = parseFactor(in);
        base = pow(base, exponent);
    }
    return base;
}

double parseTerm(istringstream& in) {
    double value = parsePower(in);
    while (true) {
        char op = in.peek();
        if (op == '*' || op == '/' || op == '%') {
            in.get();
            double rhs = parsePower(in);
            if (op == '*') value *= rhs;
            else if (op == '/') value /= rhs;
            else value = fmod(value, rhs);
        } else {
            break;
        }
    }
    return value;
}

double parseExpression(istringstream& in) {
    double value = parseTerm(in);
    while (true) {
        char op = in.peek();
        if (op == '+' || op == '-') {
            in.get();
            double rhs = parseTerm(in);
            if (op == '+') value += rhs;
            else value -= rhs;
        } else {
            break;
        }
    }
    return value;
}

int main() {
    cout << "🧮 Advanced C++ Calculator\n";
    cout << "Supports +, -, *, /, %, ^ and ()\n";
    cout << "Type 'exit' to quit\n";

    string line;
    while (true) {
        cout << "\n>> ";
        getline(cin, line);
        if (line == "exit") break;

        istringstream in(line);
        try {
            double result = parseExpression(in);
            cout << "= " << result << "\n";
        } catch (...) {
            cout << "⚠️ Invalid expression!\n";
        }
    }

    return 0;
}
