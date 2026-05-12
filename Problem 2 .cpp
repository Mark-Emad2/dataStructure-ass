#include <iostream>
using namespace std;

class RotatedBinarySearch {
private:
    int comparisonCount = 0;

public:

    int searchInRotatedArray(int array[], int size, int target) {

        int left = 0;
        int right = size - 1;

        while (left <= right) {

            int middle = left + (right - left) / 2;

            comparisonCount++;

            if (array[middle] == target) {
                return middle;
            }

            if (array[left] == array[middle] &&
                array[middle] == array[right]) {

                left++;
                right--;
            }

            else if (array[left] <= array[middle]) {

                if (target >= array[left] &&
                    target < array[middle]) {

                    right = middle - 1;
                }
                else {
                    left = middle + 1;
                }
            }

            else {

                if (target > array[middle] &&
                    target <= array[right]) {

                    left = middle + 1;
                }
                else {
                    right = middle - 1;
                }
            }
        }

        return -1;
    }

    void printComparisons() {
        cout << "Total Comparisons: "
             << comparisonCount << endl;
    }
};

int main() {

    int rotatedArray[] = {5, 6, 7, 1, 2, 3, 4, 4};

    int arraySize =
        sizeof(rotatedArray) / sizeof(rotatedArray[0]);

    int targetValue = 3;

    RotatedBinarySearch binarySearchObject;

    int resultIndex =
        binarySearchObject.searchInRotatedArray(
            rotatedArray,
            arraySize,
            targetValue
        );

    if (resultIndex != -1) {

        cout << "Element found at index: "
             << resultIndex << endl;
    }
    else {

        cout << "Element not found" << endl;
    }

    binarySearchObject.printComparisons();

    cout << "Best Case Complexity: O(1)" << endl;
    cout << "Worst Case Complexity: O(n)" << endl;

    return 0;
}
