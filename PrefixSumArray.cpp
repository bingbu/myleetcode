/*
Prefix Sum Array - Implementation
*/

#include <iostream>
#include <vector>
using namespace std;

class PrefixSum {
private:
    vector<int> prefixSums;
public:
    PrefixSum() {}
    PrefixSum(const vector<int>& array) {
        int n = array.size();
        prefixSums.resize(n);
        prefixSums[0] = array[0];
        for (int i = 1; i < n; ++i) {
            prefixSums[i] = prefixSums[i - 1] + array[i];
        }
    }

    int sumRange(const vector<int>& array, int left, int right) {
        int n = array.size();

        if (left < 0 || right >= n || left > right) {
            cerr << "Invalid indices for sumRange query." << endl;
            return 0;
        }

        if (prefixSums.empty()) {
            prefixSums.resize(n);
            prefixSums[0] = array[0];
            for (int i = 1; i < n; ++i) {
                prefixSums[i] = prefixSums[i - 1] + array[i];
            }
        }
        if (left == 0) {
            return prefixSums[right];
        }
        return prefixSums[right] - prefixSums[left - 1];
    }
};

int main() {
    PrefixSum psa;

    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;

    vector<int> array(n);
    for (int i = 0; i < n; i++) array[i] = i + 1;
    for (auto num : array) cout << num << " ";
    cout << endl;

    int left, right;
    cout << "Enter left and right indices for sum range query: ";
    cin >> left >> right;

    if (left < 0 || right >= n || left > right) {
            cerr << "Invalid indices for sumRange query." << endl;
            return 0;
    }

    cout << "Sum of elements from index " << left << " to " << right << " is: " << psa.sumRange(array, left, right) << endl;

    return  0;
}