#include <iostream>
#include <vector>

using namespace std;

void longest_common_seq(double* X, double* Y, int** length, int** direction, int size_X, int size_Y);
void print_LCS(double* X, int** length, int** direction, int i, int j);

int main(){
    double X[] = {1.0, 4.0, 6.0, 2.0, 8.0, 1.0, 5.0, 6.0};
    double Y[] = {1.0, 6.0, 9.0, 8.0, 5.0, 1.0, 6, 3, 2};
    int size_X = sizeof(X) / sizeof(X[0]);
    int size_Y = sizeof(Y) / sizeof(Y[0]);

    int** length = new int*[size_X + 1];
    int** direction = new int*[size_X + 1];
    for(int i=0; i<size_X+1; i++){
        length[i] = new int[size_Y + 1];
        direction[i] = new int[size_Y + 1];
    }

    longest_common_seq(X, Y, length, direction, size_X, size_Y);

    for(int i=0; i < size_X+1; i++){
        delete[] length[i];
        delete[] direction[i];
    }
    delete[] length;
    delete[] direction;

    return 0;
}

void longest_common_seq(double* X, double* Y, int** length, int** direction, int size_X, int size_Y){
    // Initialize the length and direction arrays
    for(int i=0; i<size_X+1; i++){
        length[i][0] = 0;
    }
    for(int i=0; i<size_Y+1; i++){
        length[0][i] = 0;
    }

    // Compute the LCS table
    for(int i=1; i<size_X+1; i++){
        for(int j=1; j<size_Y+1; j++){
            if(X[i-1] == Y[j-1]){
                length[i][j] = length[i-1][j-1] + 1;
                direction[i][j] = 0;  // "up-left arrow"
            }
            else if(length[i-1][j] >= length[i][j-1]){
                length[i][j] = length[i-1][j];
                direction[i][j] = 1;  // "up arrow"
            }
            else{
                length[i][j] = length[i][j-1];
                direction[i][j] = 2;  // "left arrow"
            }
        }
    }
    print_LCS(X, length, direction, size_X, size_Y);
    cout << endl;
}

void print_LCS(double* X, int** length, int** direction, int i, int j){
    if(i == 0 || j == 0){
        return;
    }
    if(direction[i][j] == 0){
        print_LCS(X, length, direction, i-1, j-1);
        cout << X[i-1] << " ";
    }
    else if(direction[i][j] == 1){
        print_LCS(X, length, direction, i-1, j);
    }
    else{
        print_LCS(X, length, direction, i, j-1);
    }
}
