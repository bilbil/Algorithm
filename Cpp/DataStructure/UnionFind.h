/**
 * UnionFind
 */
struct UnionFind {
    vector<int> p, r;
    int gn;
    UnionFind(int N) {
        p.resize(N); r.resize(N);
        fill(p.begin(), p.end(), -1);
        fill(r.begin(), r.end(), 1);
        gn = N;
    }
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return; //same
        gn--;
        if (r[x] < r[y]) p[x] = y;
        else if (r[x] > r[y]) p[y] = x;
        else p[x] = y; r[x]++;
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) {
        return group(a) == group(b);
    }    
};
