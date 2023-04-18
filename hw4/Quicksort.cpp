#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void RM_QuickSort(int* arr, int low, int high);
int Partition(int* arr, int low, int high);
int Randomized_Partition(int* arr, int low, int high);
int Randomized_Pick(int low, int high);

int main(){
/*
    int a[10] = {2,4,5,1,3,3,7,6,8,9};
    RM_QuickSort(a, 0, 9);
    for(int i=0; i<10; i++){
        cout << a[i] << " ";
    }
    cout << endl;
*/
    double START, END;
    int size;
    cout << "Input an integer for an array size, and press crtl+d to exit:";
    while(cin >> size){
        int *a = new int[size];
        srand(time(NULL));
        for(int i=0; i<size; i++){
            a[i] = rand()%size;
        }
        START = clock();
        RM_QuickSort(a, 0, size-1);
        END = clock();
        //print a[]
        /*
        for(int i=0; i<size; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        */
        cout << "整個程式執行時間: " << (double)clock()/CLOCKS_PER_SEC << " S" << endl;
        cout << "heapsort fuction進行運算的執行時間: " << (END-START) / CLOCKS_PER_SEC << " S" << endl;
        
        delete [] a;
        a = NULL;
        cout << "Input an integer for an array size, and press crtl+d to exit:";
    }
    
    return 0;
}

void RM_QuickSort(int* arr, int low, int high){
    if(low<high){
        int pi = Randomized_Partition(arr, low, high);  // calculate Partition position
        RM_QuickSort(arr, low, pi-1);  //  sort Partition leftside recursively
        RM_QuickSort(arr, pi+1, high);  // sort Partition rightside recursively
    }
}

int Partition(int* arr, int low, int high){
    int pivot = arr[high];  // set the last element to be pivot
    int i = low-1;  // i is the index of smaller element

    for(int j=low; j<high; j++){
        // if current element <= pivot, then put it to smaller element section
        if(arr[j]<=pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);  // put pivot to position i+1 
    return i+1;
}

int Randomized_Partition(int* arr, int low, int high){
    int i = Randomized_Pick(low, high); // make i be a random number betwwen low to high
    swap(arr[i], arr[high]);            // make pivot be random number from the array
    return Partition(arr, low, high);
}

int Randomized_Pick(int low, int high){    // return a random number between low and high
    int n = (high-low)+1;
    srand(time(NULL));
    int RanIndex = rand() % n; 
    return RanIndex+low;
}


/*
Partition function是Quick sort演算法的核心，其功能是將數列劃分成兩個部分，一部分是小於等於基準點的元素，另一部分是大於基準點的元素。Partition function的實現方法有很多種，以下是一種簡單的方法：
1.將最右邊的元素設為pivot。
2.設置兩個指針，i和j，分別指向數列的最左端和pivot之前的元素。
3.從左往右掃描數列，當遇到一個小於等於pivot的元素時，就將其與指針i所指的元素交換，然後將指針i向右移動一位。
4.當指針j遇到一個大於pivot的元素時，do nothing，然後將指針j向左移動一位。
5.將pivot與指針i所指的元素交換，此時數列被劃分成了兩個部分，小於等於pivot的元素和大於pivot的元素。
*/