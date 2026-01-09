//2469. Convert the Temperature

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public: 
    vector<double> convertTemperature(double celsius) {
        double c = celsius * 100;
        long temp = (long)(c + 0.00001) + 27315;
        double kelvin = (double)temp / 100.000000;
        c = celsius * 900;
        temp = (long)(c + 0.00001) + 16000;
        double fahrenheit = (double)temp / 500.000000;
        return {kelvin, fahrenheit};
    }
};

int main() {
    Solution sol;
    double test1 = 35.12;
    vector<double> result1 = sol.convertTemperature(test1);
    cout << "Test 1: Kelvin = " << result1[0] << ", Fahrenheit = " << result1[1] << endl;  // Expected: [308.27000,95.21600]

    double test2 = 122.11;
    vector<double> result2 = sol.convertTemperature(test2);
    cout << "Test 2: Kelvin = " << result2[0] << ", Fahrenheit = " << result2[1] << endl;  // Expected: [395.260, 251.798]

    return 0;
}
