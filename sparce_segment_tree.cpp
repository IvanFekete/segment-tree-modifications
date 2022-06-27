#include <iostream>
#include <iomanip>

using namespace std;

const int N = 1e7 + 10;
int a[N], n;

struct Node {
    int l, r;
    long long val;
} t[4 * N];
int lastNode = 0;

int f(int a, int b) {
    return a + b;
}

void update(int &v, int l, int r, int pos, int val) {
    if(v == 0) v = ++lastNode;

    if (l == r) {
        t[v].val = val;
    } else {
        int m = (l + r) / 2;
        if (pos <= m) {
            update(t[v].l, l, m, pos, val);
        } else {
            update(t[v].r, m + 1, r, pos, val);
        }
        t[v].val = f(t[t[v].l].val, t[t[v].r].val);
    }
}

int get(int v, int l, int r, int L, int R) {
    if (v == 0 || r < L || R < l || R < L) {
        return 0;
    }
    if (L <= l && r <= R) {
        return t[v].val;
    }

    int m = (l + r) / 2;
    return f(get(t[v].l, l, m, L, R),
             get(t[v].r, m + 1, r, L, R));
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), m = atoi(argv[2]);
    int root = 0;

    srand(n ^ m);
    cout << fixed << setprecision(6);
    clock_t start = clock();
    for (int i  = 1; i <= m; i++) {
        if (rand() % 2) {
            int pos = 1 + rand() % n;
            int val = 1 + rand() % 100;
            update(root, 1, n, pos, val);
        } else {
            int l = 1 + rand() % n;
            int r = l + rand() % (n - l + 1);
            get(root, 1, n, l, r);
        }
    }

    clock_t finish = clock();

    cout << "Queries answered in " << double(finish - start) / CLOCKS_PER_SEC << endl;

    return 0;
}