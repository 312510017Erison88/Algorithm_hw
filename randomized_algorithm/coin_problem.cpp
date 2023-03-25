#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int interview(int best, int i);
int* Randomized_hire(int *A, int size);
int N;  // the total exchange number

int main(){
    int size = 10;
    int best = 0;
    int *candidate = new int[size];
    for(int i=0; i<size; i++){
        candidate[i] = rand()%size;
    }
    
    int* new_candidate = Randomized_hire(candidate, size);
    delete[] candidate;
    candidate = new_candidate;
    
    for(int i=0; i<size; i++){
        cout << candidate[i] << " ";
    }
    cout << endl;
    for(int i=0; i<size; i++){
        best = interview(best, candidate[i]);
    }
    cout << "The best candidate is: " << best << endl;
    cout << "The total number of exchange is: " << N << endl;
    delete [] candidate;
    candidate = NULL;

    return 0;
}

int interview(int best, int i){
    if(i>best){
        best = i;
        N++;
    }
    return best;
}

int* Randomized_hire(int* A, int size) {
    srand(time(NULL));  // 初始化隨機數種子
    int* B = new int[size];
    memcpy(B, A, sizeof(int) * size);  // 創建一個新數組B，其元素與A相同

    for(int i=0; i<size; i++){
        int j = rand()%(size-i)+i;  // 生成i到size-1之間的隨機數
        swap(B[i], B[j]);  // 將B[i]與B[j]交換
    }
    return B;
}