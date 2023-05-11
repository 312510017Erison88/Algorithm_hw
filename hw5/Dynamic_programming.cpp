#include <iostream>
#include <vector>
#define LIMIT 10

using namespace std;

struct Bottom_up{
    int max_price;
    int min_price;
    vector <int> max_cut_posi;
    vector <int> min_cut_posi;
};

int Cut_Rod(int* price, int n);
int Memorized_Cut_Rod(int* price, int n);
int Memorized_Cut_Rod_Aux(int* price, int n, int* table);
Bottom_up Bottom_up_Cut_Rod(int* price, int n);

// goal: write the top-down and bottom-up method to get max and min price as well as the way you cut
int main(){
    int price[] = {1,5,8,9,10,17,17,20,24,30};

    int maxprice = Cut_Rod(price, 4);
    int maxprice_2 = Memorized_Cut_Rod(price, 4);
    Bottom_up price_3 = Bottom_up_Cut_Rod(price, 12);
    cout << maxprice << endl;
    cout << maxprice_2 << endl;
    //////////////////////////////////////////////////
    cout << "maximum price: " << price_3.max_price << endl;
    cout << "切法: ";
    for (int i = 0; i < price_3.max_cut_posi.size(); i++){
        cout << price_3.max_cut_posi[i] << " ";
    }
    cout << endl;
    //////////////////////////////////////////////////////
    cout << "minimum price: " << price_3.min_price << endl;
    cout << "切法: ";
    for (int i = 0; i < price_3.min_cut_posi.size(); i++){
        cout << price_3.min_cut_posi[i] << " ";
    }
    cout << endl;
    
    return 0;
}

int Cut_Rod(int* price, int n){
    int q = 100000000;
    if(n==0){       // size=0, then terminate
        return 0;
    }
    else{
        for(int i=0; i<n; i++){
            q = min(q, price[i] + Cut_Rod(price, n-i-1));
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

Bottom_up Bottom_up_Cut_Rod(int* price, int n){
    Bottom_up box;
    int* max_table = new int[n+1];
    int* min_table = new int[n+1];
    vector <int> max_cut_position;
    vector <int> min_cut_position;
    max_table[0] = 0;
    min_table[0] = 0;

    for(int i=1; i<=n; i++){            // record the table
        int max_price = -100000;
        int min_price = 100000;
        int max_cutIndex = 0;
        int min_cutIndex = 0;
        if(i > LIMIT){
            for(int j=0; j<LIMIT; j++){
                int max_current_price = price[j] + max_table[i-j-1];
                int min_current_price = price[j] + min_table[i-j-1];
                if(max_current_price > max_price){
                    max_price = max_current_price;
                    max_cutIndex = j;
                }
                if(min_current_price < min_price){
                    min_price = min_current_price;
                    min_cutIndex = j;
                }
            }
        }
        else{
            for(int j=0; j<i; j++){
                int max_current_price = price[j] + max_table[i-j-1];
                int min_current_price = price[j] + min_table[i-j-1];
                if(max_current_price > max_price){
                    max_price = max_current_price;
                    max_cutIndex = j;
                }
                if(min_current_price < min_price){
                    min_price = min_current_price;
                    min_cutIndex = j;
                }
            }
        }
        
        max_table[i] = max_price;
        min_table[i] = min_price; 
        max_cut_position.push_back(max_cutIndex+1);
        min_cut_position.push_back(min_cutIndex+1);
    }
    
    box.max_price = max_table[n];
    box.min_price = min_table[n];
    box.max_cut_posi = max_cut_position;
    box.min_cut_posi = min_cut_position;
    //////////////////////////
    cout << "Bottom Up:" << endl;
    cout << "total length: " << n <<endl;
    cout << "maximum price: " << max_table[n] << endl;
    cout << "切法: ";
    int length = n;
    int count = 0;
    while(length > 0){
        cout << max_cut_position[length -1] << " ";
        length -= max_cut_position[length-1];
        count ++;
    }
    cout << endl;
    cout << "number of pieces:" << count << endl;

    cout << "minimum price: " << min_table[n] << endl;
    cout << "切法: ";
    length = n;
    count = 0;
    while (length > 0) {
        cout << min_cut_position[length - 1] << " ";
        length -= min_cut_position[length - 1];
        count++;
    }
    cout << endl;
    cout << "number of pieces: " << count << endl;
    //////////////////////////////
    delete[] max_table;
    delete[] min_table;

    return box;
}