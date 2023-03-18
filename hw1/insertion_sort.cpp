#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

//function declaration
void InsertionSort(int *arr, int arrlen);
void Merge(int *arr, int head, int mid, int tail);
void MergeSort(int *arr, int head, int tail);

int main(){
    double START, END;
    int size;
    cout << "input an integer for an array size, and press crtl+d to exit:";
    while(cin >> size){
        //insertion sort
        int *a = new int[size];
        for(int i=0; i<size; i++){
            a[i] = rand()%size;
        }
        START = clock();
        InsertionSort(a, size);
        END = clock();
        cout << endl << "insertion sort程式執行所花費:" << (double)clock()/CLOCKS_PER_SEC << " S";
        cout << endl << "insertion sort進行運算所花費的時間:" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
        delete [] a;
        a = NULL;
        //print a[]
        /*
        for(int i=0; i<size; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        */

        //Mergesort
        int *b = new int[size];
        for(int i=0; i<size; i++){
            b[i] = rand()%size;
        }
        START = clock();
        MergeSort(b, 0, size-1);
        END = clock();
        cout << endl << "mergesort程式執行所花費:" << (double)clock()/CLOCKS_PER_SEC << " S";
        cout << endl << "mergesort進行運算所花費的時間:" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
        delete [] b;
        b = NULL;
        /*
        //print b[]
        for(int i=0; i<size; i++){
            cout << b[i] << " ";
        }
        */
    }

    return 0;
}

//below is Insertion sort 
void InsertionSort(int *arr, int arrlen){
    int key = 0;
    for(int j=0; j<arrlen; j++){
        key = arr[j];   //temporarily store the array
        //insert arr[j] into the sorted a[1,2,...]
        int i = j-1;
        while(i>=0 && arr[i]>key){
            arr[i+1] = arr[i];
            i = i-1;
        }
        arr[i+1] = key;
    }
}


// below is Merge sort
void Merge(int *arr, int head, int mid, int tail){
    int llen = mid-head+1, rlen = tail-mid;
    int *leftarr = new int [llen];
    int *rightarr = new int [rlen];
    int leftind = 0, rightind = 0;
    int h = head;

    // initialize the array
    for(int i=0; i<llen; i++){
        leftarr[i] = arr[head+i];
    }
    for(int i=0; i<rlen; i++){
        rightarr[i] = arr[mid+i+1];
    }

    while(leftind<llen && rightind<rlen){
        if(leftarr[leftind] < rightarr[rightind]){
            arr[h] = leftarr[leftind];
            leftind++;
        }
        else{
            arr[h] = rightarr[rightind];
            rightind++;
        }
        h++;
    }
    while(leftind<llen){
        arr[h] = leftarr[leftind];
        leftind++;
        h++;
    }
    while(rightind<rlen){
        arr[h] = rightarr[rightind];
        rightind++;
        h++;
    }
    //delete the dynamic array
    delete [] leftarr;
    delete [] rightarr;
    leftarr = NULL;
    rightarr = NULL;
}

void MergeSort(int *arr, int head, int tail){
    if(head<tail){
        int mid = (head+tail)/2;
        MergeSort(arr, head, mid);      //sort the left array
        MergeSort(arr, mid+1, tail);    //sort the right array
        Merge(arr, head, mid, tail);
    }
}