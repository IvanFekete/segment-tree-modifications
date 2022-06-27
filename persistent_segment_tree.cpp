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

void build(int &v, int l, int r) {
    v = ++lastNode;
    if (l == r) {
        t[v].val = a[l];
    } else {
        int m = (l + r) / 2;
        build(t[v].l, l, m);
        build(t[v].r, m + 1, r);
        t[v].val = f(t[t[v].l].val, t[t[v].r].val);
    }
}
void update(int old, int &nw, int l, int r, int pos, int val) {
    nw = ++lastNode;
    t[nw] = t[old];

    if (l == r) {
        t[nw].val = val;
    } else {
        int m = (l + r) / 2;
        if (pos <= m) {
            update(t[old].l, t[nw].l, l, m, pos, val);
        } else {
            update(t[old].r, t[nw].r, m + 1, r, pos, val);
        }
        t[nw].val = f(t[t[nw].l].val, t[t[nw].r].val);
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

int root[N];

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), m = atoi(argv[2]);
    srand(n ^ m);
    for (int i = 1; i <= n; i++) {
        a[i] = 1 + rand() % 100;
    }

    cout << fixed << setprecision(6);
    clock_t start = clock();
    build(root[0], 1, n);
    clock_t build = clock();
    cout << "Build finished in " << double(build - start) / CLOCKS_PER_SEC << endl;
    for (int i  = 1; i <= m; i++) {
        int type = rand() % 3;
        if (type == 0) {
            int pos = 1 + rand() % n;
            int val = 1 + rand() % 100;
            update(root[i - 1], root[i], 1, n, pos, val);
        } else if (type == 1) {
            int l = 1 + rand() % n;
            int r = l + rand() % (n - l + 1);
            root[i] = root[i - 1];
            get(root[i], 1, n, l, r);
        } else {
            int version = rand() % i;
            root[i] = version;
        }
    }

    clock_t finish = clock();

    cout << "Queries answered in " << double(finish - build) / CLOCKS_PER_SEC << endl;

    return 0;
}