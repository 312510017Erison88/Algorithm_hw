#include <iostream>
#include <float.h>
#include <cstring>

using namespace std;

void OptimalBST(double* probabilities, double* dummyKeys, int numKeys, double** expectedCost, double** cumulative_P, int** root);
inline void Print_BST(int **r, int i, int j);
void FreeMemory(double**& array, int size);
void FreeMemory(int**& array, int size);

int main(){
    double probabilities[] = {0.0, 0.15, 0.10, 0.05, 0.10, 0.20};  // probabilities
    double dummyKeys[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};  // dummy keys
    int numKeys = sizeof(probabilities) / sizeof(probabilities[0]) - 1;  // number of keys

    double** expectedCost = new double*[numKeys+2];
    double** cumulative_P = new double*[numKeys+2];
    int** root = new int* [numKeys+1];

    for(int i=0; i<numKeys+2; i++){
    	expectedCost[i] = new double[numKeys+1]();  // () is to initialize the element to zero
    	cumulative_P[i] = new double[numKeys+1]();  // () is to initialize the element to zero
	}
	for(int i=0; i<numKeys+1; i++){
		root[i] = new int[numKeys+1]();
	}

    OptimalBST(probabilities, dummyKeys, numKeys, expectedCost, cumulative_P, root);

    FreeMemory(expectedCost, numKeys+2);
    FreeMemory(cumulative_P, numKeys+2);
    FreeMemory(root, numKeys+1);

    return 0;
}


void OptimalBST(double* probabilities, double* dummyKeys, int numKeys, double** expectedCost, double** cumulative_P, int** root){
    // Initialize base cases for empty subtrees
    for(int i=1; i<=numKeys+1; i++){
        expectedCost[i][i-1] = dummyKeys[i-1];
        cumulative_P[i][i-1] = dummyKeys[i-1];
    }

    // Build optimal BST using dynamic programming
    for(int l=1; l<=numKeys; l++){
        for(int i=1; i<=numKeys-l+1; i++){
            int j = i+l-1;
            expectedCost[i][j] = DBL_MAX;  // initialize expected cost to a large value
            cumulative_P[i][j] = cumulative_P[i][j-1] + probabilities[j] + dummyKeys[j];

            // Find the optimal root for the subtree rooted at i, j
            for(int r=i; r<=j; r++){
                double cost = expectedCost[i][r-1] + expectedCost[r+1][j] + cumulative_P[i][j];
                if(cost < expectedCost[i][j]){
                    expectedCost[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Print the requirement
    cout << "Smallest search cost = " << expectedCost[1][numKeys] << endl;
	cout << "Root = " << root[1][numKeys] << endl;

    
    // Print the expected cost and root table
    cout << "Expected Cost Table (e):" << endl;
    for(int i=1; i<=numKeys+1; i++){
        for(int j=0; j<=numKeys; j++){
            cout << expectedCost[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nRoot Table (root):" << endl;
    for(int i=1; i<=numKeys; i++){
        for(int j=1; j<=numKeys; j++){
            cout << root[i][j] << "\t";
        }
        cout << endl;
    }
    Print_BST(root, 1, numKeys);
}

inline void Print_BST(int **r, int i, int j){
	if(i < r[i][j]){
		int a = r[i][j];
		cout << "k" << r[i][a-1] << " is the left child of k" << r[i][j] << endl;
		Print_BST(r, i, a-1);
	}
	else{
		cout << "d" << r[i][j]-1 <<" is the left child of k" << r[i][j] << endl;
	}
	if(j > r[i][j]){
		int a = r[i][j];
		cout << "k" << r[a+1][j] << " is the right child of k" << r[i][j] << endl;
		Print_BST(r, a+1, j);
	}
	else{
		cout << "d" << j << " is the right child of k" << r[i][j] << endl;
	}
}

void FreeMemory(double**& array, int size){
    for(int i=0; i<size; i++){
        delete[] array[i];
    }
    delete[] array;
    array = NULL;
}

void FreeMemory(int**& array, int size){
    for(int i=0; i<size; i++){
        delete[] array[i];
    }
    delete[] array;
    array = NULL;
}