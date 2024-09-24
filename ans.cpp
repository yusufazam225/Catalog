#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;


long long decodeValue(const std::string &value, int base) {
    long long result = 0;
    int power = 0;
    for (int i = value.size() - 1; i >= 0; --i) {
        char digit = value[i];
        if (digit >= '0' && digit <= '9') {
            result += (digit - '0') * pow(base, power);
        } else if (digit >= 'A' && digit <= 'F') {
            result += (digit - 'A' + 10) * pow(base, power);
        }
        ++power;
    }
    return result;
}


double lagrangeInterpolation(const std::vector<std::pair<int, long long>> &points) {
    double constantTerm = 0.0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        double term = points[i].second;  
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= (0 - points[j].first) * 1.0 / (points[i].first - points[j].first);
            }
        }
        constantTerm += term;
    }
    return constantTerm;
}

int main() {
   
    std::ifstream file("test_case.json");
    json input;
    file >> input;

   
    std::vector<std::pair<int, long long>> points;

   
    for (auto it = input.begin(); it != input.end(); ++it) {
        if (it.key() == "keys") continue;  

        int x = std::stoi(it.key());      
        int base = std::stoi(it.value()["base"].get<std::string>()); 
        std::string value = it.value()["value"];   

        long long y = decodeValue(value, base);   
        points.push_back({x, y});
    }

        double secretC = lagrangeInterpolation(points);


    std::cout << "The constant term (c) is: " << secretC << std::endl;

    return 0;
}
