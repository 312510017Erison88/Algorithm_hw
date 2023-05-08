#include <iostream>

using namespace std;

int Cut_Rod(int* price, int n);
// goal: write the top-down and bottom-up method to get max and min price as well as the way you cut
int main(){
    int price[] = {1,5,8,9,10,17,17,20,24,30};
    int maxprice;
    maxprice = Cut_Rod(price, 4);
    cout << maxprice << endl;
    
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