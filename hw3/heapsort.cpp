#include <iostream>

using namespace std;

//forward declaration
void MaxHeapify(int *arr, int n, int i);
void Build_Max_Heap(int *arr, int n);
void Heapsort(int *arr, int n);

int main(int argc, char ** argv){
    int a[7] = {1,2,5,3,4,7,6};

    Heapsort(a, 7);
    //print a[]
    for(int i=0; i<7; i++){
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "this is the the last line!" << endl;

    return 0;
}

void MaxHeapify(int *arr, int n, int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left<n && arr[left]>arr[largest]){
        largest = left;
    }

    if (right<n && arr[right]>arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, n, largest);
    }
}

void Build_Max_Heap(int *arr, int n){
    for(int i=n/2-1; i>=0; i--){
        MaxHeapify(arr, n, i);
    }
}

void Heapsort(int *arr, int n){
    Build_Max_Heap(arr, n);
    for (int i=n-1; i>=1; i--){
        swap(arr[0], arr[i]);
        MaxHeapify(arr, i, 0);
    }
}