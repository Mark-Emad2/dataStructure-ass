#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class NextGreaterElement {

public:

    vector<int> findNextGreaterElements(
        vector<int>& numbers) {

        int arraySize = numbers.size();

        vector<int> result(arraySize, -1);

        stack<int> indexStack;

        for (int currentIndex = 0;
             currentIndex < 2 * arraySize;
             currentIndex++) {

            int currentValue =
                numbers[currentIndex % arraySize];

            while (!indexStack.empty() &&
                   numbers[indexStack.top()]
                   < currentValue) {

                result[indexStack.top()] =
                    currentValue;

                indexStack.pop();
            }

            if (currentIndex < arraySize) {

                indexStack.push(currentIndex);
            }
        }

        return result;
    }

    void printResult(vector<int>& result) {

        for (int value : result) {

            cout << value << " ";
        }

        cout << endl;
    }
};

int main() {

    NextGreaterElement nextGreaterObject;

    vector<int> firstArray = {1, 2, 1};

    vector<int> firstResult =
        nextGreaterObject.findNextGreaterElements(
            firstArray
        );

    cout << "Output 1: ";
    nextGreaterObject.printResult(firstResult);



    vector<int> secondArray = {1, 2, 3, 4, 3};

    vector<int> secondResult =
        nextGreaterObject.findNextGreaterElements(
            secondArray
        );

    cout << "Output 2: ";
    nextGreaterObject.printResult(secondResult);

    return 0;
}
