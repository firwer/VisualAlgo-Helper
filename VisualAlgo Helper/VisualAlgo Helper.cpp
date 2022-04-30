// VisualAlgo Helper.cpp : Hopefully this will help you with your visualgo quizzes or even midterms/finals (Online assessment)
// Author: Poh Wei Pin - Computer Engineering Undergraduate @ NUS
// Created for CS2040C 2122S2

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#define ll long long

using namespace std;
typedef vector<int> vi;

// UFDS & Kruskal Credits to: https://github.com/stevenhalim/cpbook-code
//Union Find - To use in MST
class UnionFind {                                // OOP style
private:
    vi p, rank, setSize;                           // vi p is the key part
    int numSets;
public:
    UnionFind(int N) {
        p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                           // optional speedup
        setSize.assign(N, 1);                        // optional feature
        numSets = N;                                 // optional feature
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if (isSameSet(i, j)) return;                 // i and j are in same set
        int x = findSet(i), y = findSet(j);          // find both rep items
        if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
        p[x] = y;                                    // set x under y
        if (rank[x] == rank[y]) ++rank[y];           // optional speedup
        setSize[y] += setSize[x];                    // combine set sizes at y
        --numSets;                                   // a union reduces numSets
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};



// Get MST of a given graph

void kruskal(vector<tuple<ll, ll, ll>> EL, ll V, ll E) {
    int mst_cost = 0, num_taken = 0;               // no edge has been taken
    UnionFind UF(V);                               // all V are disjoint sets
    // note: the runtime cost of UFDS is very light
    for (int i = 0; i < E; ++i) {                  // up to O(E)
        auto [w, u, v] = EL[i];                      // C++17 style
        if (UF.isSameSet(u, v)) continue;            // already in the same CC
        mst_cost += w;                               // add w of this edge
        UF.unionSet(u, v);                           // link them
        ++num_taken;                                 // 1 more edge is taken
        if (num_taken == V - 1) break;                 // optimization
    }
    // note: the number of disjoint sets must eventually be 1 for a valid MST
    printf("MST cost = %d (Kruskal's)\n", mst_cost);
}

void mst(ll V, ll E) {
    vector<tuple<ll,ll,ll>> EL(E);
    cout << "Enter each Edge as n1 n2 weight: " << endl;
    for (int i = 0; i < E; ++i) {
        cout << "Edge " << i << " : ";
        int u, v, w; cin >> u >> v >> w;  // read as (u, v, w)
        EL[i] = { w, u, v };  // reorder as (w, u, v)
    }
    sort(EL.begin(), EL.end());
    kruskal(EL, V, E);
}


void linearhash(vector<int> arr, int first) {
    for (auto i : arr) {
        cout << "Key: " << i << " => " << i % first << " " << ((i % first) + 1) % first << " " << ((i % first) + 2) % first << " " << ((i % first) + 3) % first << " " << ((i % first) + 4) % first << endl;
    }
}

void quadratichash(vector<int> arr, int first) {
    for (auto i : arr) {
        cout << "Key: " << i << " => " << i % first << " " << ((i % first) + (1*1)) % first << " " << ((i % first) + (2*2)) % first << " " << ((i % first) + (3*3)) % first << " " << ((i % first) + (4*4)) % first << endl;
    }
}


//DOUBLE HASHING FUNCTIONS
int firstfx(int key, int x) { //key%x
    return key % x;
}

int secondfx(int key, int val, int x) { //val - key%x 
    return val - (key % x);
}


void doublehash(vector<int> arr, int first, int second, int secondval) {
    cout << "   FIRST HASHING" << "||" << "SECOND HASHING: " << "(1) " << "(2) " << "(3) " << "(4) " << endl;
    
    for (auto i : arr) {
        cout << "key: " << i << " => " << firstfx(i, first) << "  " << (firstfx(i, first) + (1 * secondfx(i, secondval, second))) % first << "  " << (firstfx(i, first) + (2 * secondfx(i, secondval, second))) % first << "  " << (firstfx(i, first) + (3 * secondfx(i, secondval, second))) % first << "  " << (firstfx(i, first) + (4 * secondfx(i, secondval, second))) % first << endl;
    }

}


//SORTING PIVOT FINDER
void pivotfinder(vector<int> arr) {
    int pivots = 0;
    for (int i = 0; i < arr.size(); i++) {
        bool violated = false;
        for (int j = i; j >= 0; j--) {
            if (arr[j] >= arr[i] && j != i) {
                violated = true;
                break;
            }
        }
        if (violated) {
            continue;
        }
        else {
            for (int j = i; j < arr.size(); j++) {
                    if (arr[j] <= arr[i] && j != i) {
                        violated = true;
                        break;
                    }
                }
            if (violated) {
                continue;
            }
            else {
                pivots++;
            }
         }
    }
    cout << "***************************************************" << endl;
    cout << "Number of Pivots: " << pivots << endl;
    cout << "***************************************************" << endl;
}

// String Cleaner
void str2arr(string input, vector<int>& arr) {
    std::stringstream ss(input);

    for (int i; ss >> i;) {
        arr.push_back(i);
        if (ss.peek() == ',' || ss.peek() == '[' || ss.peek() == ']')
            ss.ignore();
    }
}

// All Sortings Functions

void insertioncomparisons(vector<int> arr) {
    int compare = 0;
    for (int i = 1; i < arr.size(); ++i) {
        int e = arr[i]; int j = i;
        while (j > 0) {
            compare++;
            if (arr[j - 1] > e) { // each execution of this if-statement is counted as one comparison
                arr[j] = arr[j - 1];
            }
            else {
                break;
            }
            j--;
        }
        arr[j] = e;
    }
    cout << "***************************************************" << endl;
    cout << "COMPARISONS Needed To FULLY sort using insertion SORT: " << compare << endl;
    cout << "***************************************************" << endl;
}

void optimizedbspass(vector<int> arr) {
    int j = 0;
    int passes = 0;
    bool swapped;
    do {
        swapped = false; ++j; // each time this line is executed is counted as one pass
        passes++;
        for (int i = 0; i < arr.size() - j; ++i)
            if (arr[i] > arr[i + 1]) { // each execution of this if-statement is counted as one comparison
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
    } while (swapped);
    cout << "***************************************************" << endl;
    cout <<"Passes Need To FULLY sort: " << passes << endl;
    cout << "***************************************************" << endl;

 }

void optimizedbscomparisons(vector<int> arr) {
    int j = 0;
    int compare = 0;
    bool swapped;
    do {
        swapped = false; ++j; // each time this line is executed is counted as one pass
        for (int i = 0; i < arr.size() - j; ++i) {
            compare++;
            if (arr[i] > arr[i + 1]) { // each execution of this if-statement is counted as one comparison
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
    cout << "***************************************************" << endl;
    cout << "Comparisons Need To FULLY sort: " << compare << endl;
    cout << "***************************************************" << endl;

}

void optimizedbsswap(vector<int> arr) {
    int j = 0;
    int swaps = 0;
    bool swapped;
    do {
        swapped = false; ++j; // each time this line is executed is counted as one pass
        for (int i = 0; i < arr.size() - j; ++i)
            if (arr[i] > arr[i + 1]) { // each execution of this if-statement is counted as one comparison
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swaps++;
                swapped = true;
            }
    } while (swapped);
    cout << "***************************************************" << endl;
    cout << "SWAPS Need To FULLY sort: " << swaps << endl;
    cout << "***************************************************" << endl;

}

int main()
{
    bool quit = false;
    while (!quit) {
        std::cout << "Menu" << endl;
        cout << "******************* SORTING **********************" << endl;
        cout << "1. Bubble Sort OPTIMIZED Passes Needed to sort FULLY" << endl;
        cout << "2. Bubble Sort Swaps Needed to sort FULLY" << endl;
        cout << "3. Insertion Sort Comparison Needed to sort FULLY" << endl;
        cout << "4. Bubble (NOT OPTIMIZED)/Selection Comparisons Needed to sort FULLY" << endl;
        cout << "5. Bubble Sort (OPTIMIZED) Comparisons Needed to sort FULLY" << endl;
        cout << "6. Quicksort Pivots Finder (Returns number of possible pivots in a given array)" << endl;
        cout << endl;
        cout << "******************** HASHING *********************" << endl;
        cout << "[ Returns all the possible hashing positions ]" << endl;
        cout << "7. Linear Hashing" << endl;
        cout << "8. Quadratic Hashing" << endl;
        cout << "9. Double Hashing" << endl;
        cout << "******************** GRAPHS *********************" << endl;
        cout << "10. MST Calculator" << endl;
        cout << "Enter Choice: ";
        int select; cin >> select;
        vector<int> arr;
        switch (select) {
        case 1: {
            cout << "Enter Array: (Accepted: [1,2,3,4] or 1,2,3 or 1 2 3)" << endl;
            cin.ignore();
            string input; getline(cin,input);
            str2arr(input, arr);
            optimizedbspass(arr);
            break;
        }
        case 2: {
            cout << "Enter Array: (Accepted: [1,2,3,4] or 1,2,3 or 1 2 3)" << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            optimizedbsswap(arr);
            break;
        }
        case 3: {
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            insertioncomparisons(arr);
            break;
        }
        case 4: {
            cout << "Enter Array SIZE:(NOTE: FOR UNOPTIMIZED BUBBLE AND SELECTION SORT ONLY) " << endl;
            cin.ignore();
            cout << "Size: ";
            int sizearr; cin >> sizearr;
            cout << "***************************************************" << endl;
            cout << "COMPARISONS needed To FULLY sort: " << (sizearr * (sizearr - 1)) / 2 << endl;
            cout << "***************************************************" << endl;
                
            }

            break;
        case 5: {
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            optimizedbscomparisons(arr);
            break;
        }
        case 6: {
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            pivotfinder(arr);
            break;
        }
        case 7: { // LINEAR HASHING
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            cout << "Enter Hashing Function: (key%X) (ENTER: X) ";
            int first;
            cin >> first;
            linearhash(arr, first);
            break;
        }
        case 8: { //QUADRATIC HASHING
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            str2arr(input, arr);
            cout << "Enter Hashing Function: (key%X) (ENTER: X) ";
            int first;
            cin >> first;
            quadratichash(arr, first);
            break;
        }
        case 9: { //DOUBLE HASHING
            cout << "Enter Array: " << endl;
            cin.ignore();
            string input; getline(cin, input);
            vector<int> firstv;
            vector<int> secondv;
            cout << "First Hashing Function: (key%X) (ENTER: X) ";
            int first;
            cin >> first;
            cout << "Second Hashing Function: (X - key%Y) (ENTER: X Y) ";
            int second, secondval;
            cin >> secondval >> second;
            str2arr(input, arr);
            doublehash(arr, first, second, secondval);
            break;
        }
        case 10: { //DOUBLE HASHING
            cout << "--- MST Calculator --- " << endl;
            bool invalid = true;
            ll V, E;
            while (invalid) {
                cout << "Enter number of vertices: ";
                cin >> V;
                if (V <= 0) {
                    cout << "Invalid! V must be more than 0" << endl;
                }
                else {
                    invalid = false;
                }
            }
            invalid = true;
            while (invalid) {
                cout << "Enter number of edges: ";
                cin >> E;
                if (E > V) {
                    cout << "Invalid! Number of edges cannot be more than V" << endl;
                }
                else {
                    invalid = false;
                }
            }
            mst(V, E);
            break;
        }
        }
    }
}