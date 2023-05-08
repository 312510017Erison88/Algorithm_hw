#include <iostream>

using namespace std;

int Cut_Rod(int* price, int n);
int Memorized_Cut_Rod(int* price, int n);
int Memorized_Cut_Rod_Aux(int* price, int n, int* table);
// goal: write the top-down and bottom-up method to get max and min price as well as the way you cut
int main(){
    int price[] = {1,5,8,9,10,17,17,20,24,30};

    int maxprice = Cut_Rod(price, 4);
    int maxprice_2 = Memorized_Cut_Rod(price, 4);
    cout << maxprice << endl;
    cout << maxprice_2 << endl;
    
    return 0;
}

int Cut_Rod(int* price, int n){
    int q = -100000000;
    if(n==0){       // size=0, then terminate
        return 0;
    }
    else{
        for(int i=0; i<n; i++){
            q = max(q, price[i] + Cut_Rod(price, n-i-1));
        }
    }
    return q;
}

int Memorized_Cut_Rod(int* price, int n){
    int* table = new int[n+1];
    table[0] = 0;
    for(int i=1; i<=n; i++){
        table[i] = -100000;
    }
    int result = Memorized_Cut_Rod_Aux(price, n, table);
    delete[] table;
    return result;
}

int Memorized_Cut_Rod_Aux(int* price, int n, int* table){
    if(table[n] >= 0){
        return table[n];
    }
    else{
        int q = -100000;
        for(int i=0; i<n; i++){
            q = max(q, price[i] + Memorized_Cut_Rod_Aux(price, n-i-1, table));
        }
        table[n] = q;
        return q;
    }
}