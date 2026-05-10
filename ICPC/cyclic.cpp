#include <iostream>
#include <vector>
using namespace std;

void cyclicSort(vector<int>& arr) {
    int i = 0;
    while (i < arr.size()) {
        int correctIndex = arr[i] - 1;
        if (arr[i] != arr[correctIndex])
            swap(arr[i], arr[correctIndex]);
        else
            i++;
    }
}

int main() {
    vector<int> arr = {3, 5, 2, 1, 4};

    cyclicSort(arr);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    return 0;
}
