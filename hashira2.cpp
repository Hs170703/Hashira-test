#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

// BigInt alias (Boost removed)
typedef long long BigInt;

// Convert string in arbitrary base to BigInt
BigInt convertToDecimal(const string &value, int base) {
    BigInt result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = 10 + (tolower(c) - 'a');
        else throw runtime_error("Invalid character in number");
        result = result * base + digit;
    }
    return result;
}

int main() {
    // Input JSON (replace with reading from file/stdin if needed)
    string input = R"({
        "keys": { "n": 10, "k": 7 },
        "1": { "base": "6", "value": "13444211440455345511" },
        "2": { "base": "15", "value": "aed7015a346d635" },
        "3": { "base": "15", "value": "6aeeb69631c227c" },
        "4": { "base": "16", "value": "e1b5e05623d881f" },
        "5": { "base": "8", "value": "316034514573652620673" },
        "6": { "base": "3", "value": "2122212201122002221120200210011020220200" },
        "7": { "base": "3", "value": "20120221122211000100210021102001201112121" },
        "8": { "base": "6", "value": "20220554335330240002224253" },
        "9": { "base": "12", "value": "45153788322a1255483" },
        "10": { "base": "7", "value": "1101613130313526312514143" }
    })";

    json j = json::parse(input);
    int k = j["keys"]["k"];
    int degree = k - 1;

    // Extract roots (convert first degree many)
    vector<BigInt> roots;
    vector<string> keys;
    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.key() == "keys") continue;
        keys.push_back(it.key());
    }
    sort(keys.begin(), keys.end(), [](const string &a, const string &b) {
        return stoi(a) < stoi(b);
    });

    for (int i = 0; i < degree; i++) {
        int base = stoi(j[keys[i]]["base"].get<string>());
        string value = j[keys[i]]["value"];
        roots.push_back(convertToDecimal(value, base));
    }

    // Polynomial coefficients
    vector<BigInt> coeffs(degree + 1, 0);
    coeffs[0] = 1;

    for (auto r : roots) {
        vector<BigInt> newCoeffs(degree + 1, 0);
        for (int i = 0; i <= degree; i++) {
            if (coeffs[i] == 0) continue;
            if (i + 1 <= degree)
                newCoeffs[i + 1] += coeffs[i];
            newCoeffs[i] += coeffs[i] * (-r);
        }
        coeffs = newCoeffs;
    }

    cout << "Polynomial coefficients (highest degree → constant):\n";
    for (int i = degree; i >= 0; i--) {
        cout << coeffs[i] << "\n";
    }

    return 0;
}
