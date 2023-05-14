#include <iostream>
#include <vector>

using namespace std;

struct Table{
    vector<int> arrow;
    vector<int> length;
};

Table longest_common_seq(double X[], double Y[], int size_X, int size_Y);
void print_LCS(const Table& table, double X[], int i, int j);
int main(){
    double X[] = {1.0, 2.0, 3.0, 2.0, 4.0, 1.0, 2.0};
    double Y[] = {2.0, 4.0, 3.0, 1.0, 2.0, 1.0};
    int size_X = sizeof(X) / sizeof(X[0]);
    int size_Y = sizeof(Y) / sizeof(Y[0]);
    cout << size_X << " " << size_Y << endl;

    Table result = longest_common_seq(X, Y, size_X, size_Y);

    cout << "Longest Common Sequence: ";
    print_LCS(result, X, size_X, size_Y);
    cout << endl;

    return 0;
}

Table longest_common_seq(double X[], double Y[], int size_X, int size_Y){
    Table table;
    table.arrow.resize((size_X + 1) * (size_Y + 1));
    table.length.resize((size_X) * (size_Y)); // wierd for this line!

    // Initialize the first row and column of C to 0
    for(int i=0; i<size_X; i++){
        table.length[i] = 0;
    }
    for(int j=0; j<size_Y; j++){
        table.length[j * (size_X)] = 0;
    }
    cout << "good" << endl;

    // Compute the LCS table
    for(int i = 0; i < size_X; i++){
        for(int j = 0; j < size_Y; j++){
            if(X[i] == Y[j]){
                table.length[j * (size_X)+i] = table.length[(j-1) * (size_X) + (i-1)] + 1;
                table.arrow[j * (size_X+1)+i] = 0;  // "up-left arrow"
            }
            else if(table.length[(j) * (size_X) + (i-1)] >= table.length[(j-1) * (size_X) + i]){
                table.length[j * (size_X) + i] = table.length[j * (size_X) + (i-1)];
                table.arrow[j * (size_X+1) + i] = 1;  // "up arrow"
            }
            else{
                table.length[j * (size_X) + i] = table.length[j * (size_X) + (i-1)];
                table.arrow[j * (size_X+1) + i] = 2;  // "left arrow"
            }
        }
    }
    return table;
}

void print_LCS(const Table& table, double X[], int i, int j){
    if(i == 0 || j == 0){
        return;
    }
    if(table.arrow[j * (i+1) + i] == 0){
        print_LCS(table, X, i-1, j-1);
        cout << X[i-1] << " ";
    }
    else if(table.arrow[j * (i+1) + i] == 1){
        print_LCS(table, X, i-1, j);
    }
    else{
        print_LCS(table, X, i, j-1);
    }
}
