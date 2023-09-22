#include "complexNumbers.h"

void sort(std::vector<Complex> &arr)
{
    int j;
    for (int i = 1; i < arr.size(); i++) {
        Complex temp = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j].Abs() > temp.Abs()) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
}

