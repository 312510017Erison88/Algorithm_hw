#include <iostream>
#include <float.h>
#include <cstring>

using namespace std;

void OptimalBST(double* probabilities, double* dummyKeys, int numKeys, double** expectedCost, double** cumulative_P, int** root);

int main(){
    double probabilities[] = {0.0, 0.15, 0.10, 0.05, 0.10, 0.20};  // probabilities
    double dummyKeys[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};  // dummy keys
    int numKeys = sizeof(probabilities) / sizeof(probabilities[0]) - 1;  // number of keys
    double** expectedCost;
    double** cumulative_P;
    int** root;

    expectedCost = new double *[numKeys+2];
    cumulative_P = new double *[numKeys+2];
    root = new int *[numKeys+1];
    for(int i = 0; i < numKeys + 2; i++){
    	expectedCost[i] = new double [numKeys + 1];
    	cumulative_P[i] = new double [numKeys + 1];
	}
	for(int i = 0; i < numKeys + 1; i++){
		root[i] = new int [numKeys + 1];
	}

	memset(expectedCost, 0.0, sizeof(expectedCost));
	memset(cumulative_P, 0.0, sizeof(cumulative_P));
	memset(root, 0, sizeof(root));

    OptimalBST(probabilities, dummyKeys, numKeys, expectedCost, cumulative_P, root);

    for(int i = 0; i < numKeys + 2; i++){
		delete [] expectedCost[i];
		delete [] cumulative_P[i];
	}
	for(int i = 0; i < numKeys + 1; i++){
		delete [] root[i];
	}
	
	delete [] expectedCost, cumulative_P, root;

    return 0;
}


void OptimalBST(double* probabilities, double* dummyKeys, int numKeys, double** expectedCost, double** cumulative_P, int** root){
    // Initialize base cases for empty subtrees
    for(int i = 1; i <= numKeys+1; i++){
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
                if(cost <= expectedCost[i][j]){
                    expectedCost[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Print the requirement
    cout << "Smallest search cost = " << expectedCost[1][numKeys];
	cout << "\nRoot = " << root[1][numKeys] << endl;

    // Print the expected cost and root table
    cout << "Expected Cost Table (e):" << endl;
    for(int i = 1; i <= numKeys+1; i++){
        for(int j = 0; j <= numKeys; j++){
            cout << expectedCost[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nRoot Table (root):" << endl;
    for(int i = 1; i <= numKeys; i++){
        for(int j = 1; j <= numKeys; j++){
            cout << root[i][j] << "\t";
        }
        cout << endl;
    }
}
/*
// pseudo code 
Optimal_BST(p, q, n){
    Let e[1...n+1, 0...n], w[1...n+1, 0...n], and root[1...n, 1..n] be a new tables
    for i=1 to n+1
        e[i, i-1] = qi-1
        w[i, i-1] = qi-1
    for l=1 to n
        for i=1 to n-l-1
            j = i+l-1
            e[i,j] = 1000000
            w[i,j] = w[i, j-1] + pj + qj
            for r=i to j
                t = e[i, r-1] + e[i, j-1] + w[i, j]
                if t<=e[i,j]
                    e[i, j] = t
                    root[i,j] r
    return e and root
}
*/