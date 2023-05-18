#include <iostream>
#include <climits>

using namespace std;

void OptimalBST(int probabilities[], int dummyKeys[], int numKeys);

int main(){
    int probabilities[] = {0, 10, 20, 30, 40};  // probabilities
    int dummyKeys[] = {5, 10, 15, 20, 25};  // dummy keys
    int numKeys = sizeof(probabilities) / sizeof(probabilities[0]) - 1;  // number of keys

    OptimalBST(probabilities, dummyKeys, numKeys);
    
    cout << "hi!" << endl;
    return 0;
}


void OptimalBST(int probabilities[], int dummyKeys[], int numKeys){
    int expectedCost[numKeys+2][numKeys+1];  // expected cost table
    int cumulativeProbability[numKeys+2][numKeys+1];  // cumulative probability table
    int root[numKeys+1][numKeys+1];  // root table

    // Initialize base cases for empty subtrees
    for (int i = 1; i <= numKeys+1; i++) {
        expectedCost[i][i-1] = dummyKeys[i-1];
        cumulativeProbability[i][i-1] = dummyKeys[i-1];
    }

    // Build optimal BST using dynamic programming
    for(int l = 1; l <= numKeys; l++){
        for(int i = 1; i <= numKeys - l + 1; i++){
            int j = i + l - 1;
            expectedCost[i][j] = INT_MAX;  // initialize expected cost to a large value
            cumulativeProbability[i][j] = cumulativeProbability[i][j-1] + probabilities[j] + dummyKeys[j];

            // Find the optimal root for the subtree rooted at i, j
            for(int r = i; r <= j; r++){
                int cost = expectedCost[i][r-1] + expectedCost[r+1][j] + cumulativeProbability[i][j];
                if(cost <= expectedCost[i][j]){
                    expectedCost[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

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