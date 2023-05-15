#include <iostream>

using namespace std;

void longest_common_seq(double* X, double* Y, int** length, int** direction, int size_X, int size_Y);
void print_LCS(double* X, int** length, int** direction, int i, int j, double* result);

int main(){
    double X[] = {1.0, 4.0, 6.0, 2.0, 8.0, 1.0, 5.0, 6.0};
    double Y[] = {1.0, 6.0, 9.0, 8.0, 5.0, 1.0, 6, 3, 2};
    double Z[] = {1, 5, 6, 8, 1, 22};
    int size_X = sizeof(X) / sizeof(X[0]);
    int size_Y = sizeof(Y) / sizeof(Y[0]);
    int size_Z = sizeof(Z) / sizeof(Z[0]);

    int** length = new int*[size_X + 1];
    int** direction = new int*[size_X + 1];
    for(int i=0; i<size_X+1; i++){
        length[i] = new int[size_Y + 1];
        direction[i] = new int[size_Y + 1];
    }

    int** length_2 = new int*[size_X + 1];
    int** direction_2 = new int*[size_X + 1];
    for(int i=0; i<size_X+1; i++){
        length_2[i] = new int[size_Z + 1];
        direction_2[i] = new int[size_Z + 1];
    }

    longest_common_seq(X, Y, length, direction, size_X, size_Y);
    int lcs_length = length[size_X][size_Y];
    double* result1 = new double[lcs_length];
    print_LCS(X, length, direction, size_X, size_Y, result1);
    cout << endl;

    longest_common_seq(X, Z, length_2, direction_2, size_X, size_Z);
    int lcs_length2 = length[size_X][size_Z];
    double* result2 = new double[lcs_length2];
    print_LCS(X, length_2, direction_2, size_X, size_Z, result2);
    cout << endl;

    int** length_3 = new int*[lcs_length + 1];
    int** direction_3 = new int*[lcs_length + 1];
    for(int i = 0; i < lcs_length + 1; i++){
        length_3[i] = new int[lcs_length2 + 1];
        direction_3[i] = new int[lcs_length2 + 1];
    }

    longest_common_seq(result1, result2, length_3, direction_3, lcs_length, lcs_length2);
    int final_length = length_3[lcs_length][lcs_length2];
    double* final_result = new double[final_length];
    print_LCS(result1, length_3, direction_3, lcs_length, lcs_length2, final_result);
    cout << endl;

    // Free the dynamically allocated memory
    for(int i=0; i < size_X+1; i++){
        delete[] length[i];
        delete[] direction[i];
    }
    delete[] length;
    delete[] direction;

    for(int i=0; i < size_X+1; i++){
        delete[] length_2[i];
        delete[] direction_2[i];
    }
    delete[] length_2;
    delete[] direction_2;
    delete[] result1;
    delete[] result2;

    for(int i = 0; i < lcs_length + 1; i++){
        delete[] length_3[i];
        delete[] direction_3[i];
    }
    delete[] length_3;
    delete[] direction_3;
    delete[] final_result;

    return 0;
}

// Compute the longest common subsequence
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
                direction[i][j] = 0;  // Store as "up-left arrow"
            }
            else if(length[i-1][j] >= length[i][j-1]){
                length[i][j] = length[i-1][j];
                direction[i][j] = 1;  // Store as "up arrow"
            }
            else{
                length[i][j] = length[i][j-1];
                direction[i][j] = 2;  // Store as "left arrow"
            }
        }
    }
    //print_LCS(X, length, direction, size_X, size_Y);
    //cout << endl;
}

// Print the result
void print_LCS(double* X, int** length, int** direction, int i, int j, double* result){
    if(i == 0 || j == 0){
        return;
    }
    if(direction[i][j] == 0){
        print_LCS(X, length, direction, i-1, j-1, result);
        cout << X[i-1] << " ";
        result[length[i][j]-1] = X[i-1];   //wierd!
    }
    else if(direction[i][j] == 1){
        print_LCS(X, length, direction, i-1, j, result);
    }
    else{
        print_LCS(X, length, direction, i, j-1, result);
    }
}
