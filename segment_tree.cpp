// Author: Piotr Borowski
// Code prepared for my lecture on segment trees 
//
// Segment tree with lazy propagation.
// Allows to:
// - add value v on interval [a, b] in O(logn)
// - get maximum on interval [a, b] in O(logn)
//
#include <bits/stdc++.h>
using namespace std;

const int R = 1 << 18;
int tree[2 * R], lazy[2 * R];

// propagation
void update(int id, int value) {
    tree[id] += value;
    lazy[id] += value;
}
void push(int id) {
    int left = 2 * id;
    int right = 2 * id + 1;
    
    update(left, lazy[id]);
    update(right, lazy[id]);
    
    lazy[id] = 0;
}

// returns maximum value on interval [begin, end]
int maxi(int begin, int end, int id = 1, int l = 1, int r = R) {
    if (begin > r) return -1e9;
    if (end < l) return -1e9;
    
    if (begin <= l && end >= r) {
        return tree[id];
    }
    
    push(id);
    
    int left = 2 * id;
    int right = 2 * id + 1;
    int middle = (l + r) / 2;
    return max(maxi(begin, end, left, l, middle),
                maxi(begin, end, right, middle + 1, r));
}

// add value to every position on interval [begin, end]
void add(int begin, int end, int value, int id = 1, int l = 1, int r = R) {
    if (begin > r) return;
    if (end < l) return;
    
    if (begin <= l && end >= r) {
        update(id, value);
        return;
    }
    
    push(id);
    
    int left = 2 * id;
    int right = 2 * id + 1;
    int middle = (l + r) / 2;
    add(begin, end, value, left, l, middle);
    add(begin, end, value, right, middle + 1, r);
    
    tree[id] = max(tree[left], tree[right]);
}

int main() {
    add(1, 3, 5);
    add(2, 4, 7);
    add(3, 5, -2);
    cout << maxi(2, 4) << endl;
    add(4, 5, 8);
    cout << maxi(2, 4) << endl;
        
    return 0;
}
