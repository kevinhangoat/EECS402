#include <iostream>
using namespace std;

int sumArray(int arr[], int len);
int findMax(int const * arr, int len);
void storeSquares(int arr[], int len);

int main() {
    const int length = 6;
    int arr[length] = {5, 3, 8, 8, 2, 9};

    int finalIndex = 6;
    arr[finalIndex] = 5;

    cout << sumArray(arr, length) << endl;
    cout << findMax(arr, length) << endl;
    storeSquares(arr, length);
}

// returns sum of all arr elements
int sumArray(int arr[], int len) {
    int result = 0;
    for (int i = 1; i < len; ++i) {
        result += arr[i];
    }
    return result;
}

// returns max element of arr
int findMax(int const * arr, int len) {
    int result;
    int currMax = 0;
    for(int i = 0; i <= len; ++i) {
        if(arr[i] > currMax) {
            currMax =  arr[i];
        }
    }
    result = currMax;
    return result;
}

void storeSquares(int A[], int len) {
    int i, n = len;
    // Store squares in A[].
    i = 0;
    while (i < n ) {
        A[i] = i * i;
        cout << "Square of array number " << i << " = " << A[i] << endl;
        ++i;
    }
}
