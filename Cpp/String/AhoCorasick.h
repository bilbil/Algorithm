struct AhoCorasick {
    struct Trie;
    using NP = Trie*;
    struct Trie {
        vector<int> acc;
        map<int, NP> next;
        NP fail = nullptr, dnx = nullptr;
        void add(const string &s, int p, int id) {
            if (p == s.size()) {
                acc.push_back(id);
                return;
            }
            if (next[s[p]] == nullptr) {
                next[s[p]] = new Trie();
            }
            next[s[p]]->add(s, p+1, id);
        }
        NP count(vector<int> &res) {
            if (fail == nullptr) return this;
            for (int id : acc) {
                res[id]++;
            }
            if (dnx) {
                dnx->count(res);
            } else {
                dnx = fail->count(res);
            }
            return (acc.size() != -1) ? this : dnx;
        }
        void match(vector<int> &res, const string &s, int p) {
            if (p == s.size()) return;
            if (next[s[p]]) {
                next[s[p]]->count(res);
                next[s[p]]->match(res, s, p+1);
            } else if (fail) {
                 fail->match(res, s, p);
            } else {
                match(res, s, p+1);
            }
        }
    };
    int n;
    NP tr;
    AhoCorasick(vector<string> v) {
        n = (int)v.size();
        tr = new Trie();
        for (int i = 0; i < n; i++) {
            tr->add(v[i], 0, i);
        }
        queue<NP> q;
        q.push(tr);
        tr->fail = nullptr;
        while (!q.empty()) {
            NP ntr = q.front(); q.pop();
            for (auto p: ntr->next) {
                int i = p.first;
                NP fail = ntr->fail;
                while (fail and !fail->next.count(i)) {
                    fail = fail->fail;
                }
                ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];
                q.push(ntr->next[i]);
            }
        }
    }
    vector<int> match(string s) {
        vector<int> res(n, 0);
        tr->match(res, s, 0);
        return res;
    }
};
