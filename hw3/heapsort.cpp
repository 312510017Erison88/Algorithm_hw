#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

//forward declaration
void MaxHeapify(int *arr, int n, int i);
void Build_Max_Heap(int *arr, int n);
void Heapsort(int *arr, int n);

int main(int argc, char ** argv){
    double START, END;
    int size;
    cout << "Input an integer for an array size, and press crtl+d to exit:";
    while(cin >> size){
        int *a = new int[size];
        for(int i=0; i<size; i++){
            a[i] = rand()%size;
        }
        START = clock();
        Heapsort(a, size);
        END = clock();
        cout << "整個程式執行時間:" << (double)clock()/CLOCKS_PER_SEC << " S" << endl;
        cout << "heapsort fuction進行運算的執行時間:" << (END-START) / CLOCKS_PER_SEC << " S" << endl;
        //print a[]
        
        for(int i=0; i<size; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        
        delete [] a;
        a = NULL;
        cout << "Input an integer for an array size, and press crtl+d to exit:";
    }

    return 0;
}

void MaxHeapify(int *arr, int n, int i){
    int largest = i;
    int left = 2*i+1;   
    int right = 2*i+2;

    // if left child is larger than root
    if(left<n && arr[left]>arr[largest]){
        largest = left;
    }
    // if right child is larger than largest so far
    if (right<n && arr[right]>arr[largest]) {
        largest = right;
    }
    // if largest is not root
    if (largest!=i){
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, n, largest);    // recursively heapify the affected sub-tree
    }
}

void Build_Max_Heap(int *arr, int n){
    // build heap(rearrange array)
    for(int i=n/2-1; i>=0; i--){
        MaxHeapify(arr, n, i);
    }
}

void Heapsort(int *arr, int n){
    Build_Max_Heap(arr, n);
    // one by one extract an element from heap
    for (int i=n-1; i>=1; i--){
        swap(arr[0], arr[i]);   // move current root to end
        MaxHeapify(arr, i, 0);  // call max heapify on the reduced heap
    }
}
/*
將Max-heap的root與最後一個節點交換，並排除最後一個節點，
剩下的數列仍是一個Max-heap。重複此操作，每次將剩下的節點轉化為Max-heap，直到數列被完全排序
*/