#include <iostream>
#include <iomanip>

using namespace std;

const int N = 1e7 + 10;
int t[4 * N], a[N], n;

int f(int a, int b) {
    return a + b;
}

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = a[l];
    } else {
        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = f(t[2 * v], t[2 * v + 1]);
    }
}

void update(int v, int l, int r, int pos, int val) {
    if (l == r) {
        t[v] = val;
    } else {
        int m = (l + r) / 2;
        if (pos <= m) {
            update(2 * v, l, m, pos, val);
        } else {
            update(2 * v + 1, m + 1, r, pos, val);
        }
        t[v] = f(t[2 * v], t[2 * v + 1]);
    }
}

int get(int v, int l, int r, int L, int R) {
    if (r < L || R < l || R < L) {
        return 0;
    }
    if (L <= l && r <= R) {
        return t[v];
    }

    int m = (l + r) / 2;
    return f(get(2 * v, l, m, L, R),
            get(2 * v + 1, m + 1, r, L, R));
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), m = atoi(argv[2]);
    srand(n ^ m);
    for (int i = 1; i <= n; i++) {
        a[i] = 1 + rand() % 100;
    }

    cout << fixed << setprecision(6);
    clock_t start = clock();
    build(1, 1, n);
    clock_t build = clock();
    cout << "Build finished in " << double(build - start) / CLOCKS_PER_SEC << endl;
    for (int i  = 1; i <= m; i++) {
        if (rand() % 2) {
            int pos = 1 + rand() % n;
            int val = 1 + rand() % 100;
            update(1, 1, n, pos, val);
        } else {
            int l = 1 + rand() % n;
            int r = l + rand() % (n - l + 1);
            get(1, 1, n, l, r);
        }
    }

    clock_t finish = clock();

    cout << "Queries answered in " << double(finish - build) / CLOCKS_PER_SEC << endl;

    return 0;
}