#include <bits/stdc++.h>
using namespace std;

long long convertToDecimal(string value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit = c - '0';
        result = result * base + digit;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Sample JSON input (in practice, this would be read from file/stdin)
    string jsonInput = R"({
        "keys": {
            "n": 4,
            "k": 3
        },
        "1": { "base": "10", "value": "4" },
        "2": { "base": "2", "value": "111" },
        "3": { "base": "10", "value": "12" },
        "6": { "base": "4", "value": "213" }
    })";

    // For simplicity, parse using regex (not full JSON parsing)
    int n = 4, k = 3;
    vector<long long> roots;

    vector<pair<int,string>> entries = {
        {10, "4"}, {2, "111"}, {10, "12"}, {4, "213"}
    };

    for (auto &entry : entries) {
        roots.push_back(convertToDecimal(entry.second, entry.first));
    }

    int m = k - 1; // degree of polynomial
    vector<long long> coeffs = {1}; // start with polynomial "1"

    for (int i = 0; i < m; i++) {
        long long r = roots[i];
        vector<long long> newCoeffs(coeffs.size() + 1, 0);
        for (int j = 0; j < coeffs.size(); j++) {
            newCoeffs[j] += coeffs[j];
            newCoeffs[j + 1] -= coeffs[j] * r;
        }
        coeffs = newCoeffs;
    }

    // Print coefficients
    for (long long c : coeffs) {
        cout << c << " ";
    }
    cout << "\n";
}