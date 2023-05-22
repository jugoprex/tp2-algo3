#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> adj;

vector<bool> used;
vector<long long> order;

vector<long long> res;

void dfs1(long long v) {
    used[v] = true;

    for (auto u : adj[v]){
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(long long v) {
    used[v] = true;

    for (auto u : adj[v]){
        if (!used[u])
            dfs2(u);
    }
}


int main() {
    long long n,m;
    cin>>n>>m;
    
    adj.resize(n);
   
    while(m--) {
        long long a, b;
        cin>>a>>b;
        a--;
        b--;
        adj[a].push_back(b);
    }
    
    used.assign(n, false);
    for (long long i = 0; i < n; i++){
        if (!used[i])
            dfs1(i);
    }

    used.assign(n, false);
    reverse(order.begin(), order.end());
    for (auto v : order){
        if (!used[v]) {
            dfs2 (v);
            res.push_back(v);
        }
    }
    cout<<res.size()<<endl;
    reverse(res.begin(), res.end());
    for(auto i:res) {
        cout<<i+1<<" ";
    }

    

    
    return 0;
    
}