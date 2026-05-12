#include <iostream>
using namespace std;




template <class T>
class Bitonic_Task {
private:
    int swaps;
    int comparisons;

    void bubble_sort(T data[], int n) {
        for (int i = 0; i < n-1 ;i++){
            for (int j= n-1;j>i;j--) {
                comparisons++;
                if (data[j]<data[j-1]) {
                    swap(data[j],data[j-1]);
                    swaps++;
                }
            }
        }
    }

    void reversed_selcetionSort(T data[],int n,int whole) {

        for (int i =n  ,j,least;i<whole-1;i++) {
            for (j=i+1 , least =i ;j<whole;j++) {
                comparisons++;
                if (data[j]>data[least]) {
                    least = j;
                }
            }
            if (least!=i) {
                swap(data[least],data[i]);
                swaps++;
            }
        }
    }
    int linear_search(T data[], int whole, T target) {

        for (int i=0 ;i<whole;i++) {
            if (data[i]==target) {
                return i;
            }
        }
        return -1;
    }

public:
    Bitonic_Task() : swaps(0) , comparisons(0){}

    int betonic(T data[],int n, T target) {

        swaps =0;
        comparisons=0;
        int indexing = n/2; //3
        bubble_sort(data, indexing);
        reversed_selcetionSort(data,indexing,n);

        int bitonic_value = linear_search(data,n,target);

        return  bitonic_value;
    }
    int getSwaps() const {return swaps;}
    int getComparisons() const {return comparisons;}

    void printArray(T const data[], int n) {
        cout << "(" ;
        for (int i=0;i<n;i++) {
            cout << data[i] << ",";
        }
        cout <<"\b)"<< endl;
    }
};


template <class T>
void test_case(string Test_name ,T arr[], int size, T target) {
    Bitonic_Task<T> out;

    cout << "----"<< Test_name <<"----" <<endl;
    cout << "Original Array : " ;
    out.printArray(arr,size);
    int bit_value = out.betonic(arr,size,target);
    cout << "Bitonic Array  : " ;
    out.printArray(arr,size);


    cout << "Total Number of swaps : " << out.getSwaps() << endl;
    cout << "Total Number of comparisons : " << out.getComparisons() << endl;

    if (bit_value==-1) {
        cout << "There is no such a value \n";
    } else {
        cout << "The  Target is: " << arr[bit_value] << " and it found at index : " << bit_value<<endl;
    }

    cout << "-----------------------------------------------------------------------\n";

}



int main() {
    int tst1[] = { 4, 1,  8, 6, 9, 3  ,12};
    int size1 = sizeof(tst1)/sizeof(tst1[0]);
    int target =12;
    test_case("Test 1: Target at the bitonic point",tst1,size1,target);

    int tst2[] = {10, 4, 15, 2, 8, 12};
    int size2 = sizeof(tst2)/sizeof(tst2[0]);
    target =4;
    test_case("Test 2: Target in Left Half", tst2, size2, target);

    int tst3[] = {3, 20, 11, 5, 2, 14};
    int size3 = sizeof(tst3)/sizeof(tst3[0]);
    target =5;
    test_case("Test 3: Target in Right Half", tst3, size3, target);

    int tst4[] = {1, 2, 3, 4, 5, 6};
    int size4 = sizeof(tst4)/sizeof(tst4[0]);
    target =99;
    test_case("Test 4: Target Not Present", tst4, size4, target);

    int tst5[] = {7, 2, 7, 3, 2, 10, 10};
    int size5=sizeof(tst5)/sizeof(tst5[0]);
    target =7;
    test_case("Test 5: Duplicate Elements", tst5, size5, target);

}