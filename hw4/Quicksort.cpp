#include <iostream>

using namespace std;

void QuickSort(int* arr, int low, int high);
int Partition(int* arr, int low, int high);

int main(){
    int a[8] = {3,4,5,6,4,2,4,3};
    QuickSort(a, 0, 7);
    for(int i=0; i<8; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "hi" << endl;
    return 0;
}

void QuickSort(int* arr, int low, int high){
    if(low<high){
        int pi = Partition(arr, low, high);  // calculate Partition position
        QuickSort(arr, low, pi-1);  //  sort Partition leftside recursively
        QuickSort(arr, pi+1, high);  // sort Partition rightside recursively
    }
}

int Partition(int* arr, int low, int high){
    int pivot = arr[high];  // set the last element to be pivot
    int i = low-1;  // i is the index of smaller element

    for(int j=low; j<high; j++){
        // 如果當前的元素 <= pivot，則將其放到 smaller element 的區間中
        if(arr[j]<=pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);  // 最後將 pivot 放到 i+1 的位置上
    return i+1;
}
/*
Partition function是Quick sort演算法的核心，其功能是將數列劃分成兩個部分，一部分是小於等於基準點的元素，另一部分是大於基準點的元素。Partition function的實現方法有很多種，以下是一種簡單的方法：
1.將最右邊的元素設為pivot。
2.設置兩個指針，i和j，分別指向數列的最左端和pivot之前的元素。
3.從左往右掃描數列，當遇到一個小於等於pivot的元素時，就將其與指針i所指的元素交換，然後將指針i向右移動一位。
4.當指針j遇到一個大於pivot的元素時，就將其與指針i所指的元素交換，然後將指針j向左移動一位。
5.當指針j遇到一個小於等於pivot的元素時，就繼續向左移動，直到指針i和指針j相遇為止。
6.將pivot與指針i所指的元素交換，此時數列被劃分成了兩個部分，小於等於pivot的元素和大於pivot的元素。
*/