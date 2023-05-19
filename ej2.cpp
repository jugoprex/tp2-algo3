#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> adj, adj_rev;

vector<bool> used;
vector<long long> order, component;
vector<vector<long long>> dag;
vector<bool> visited;
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
    component.push_back(v);

    for (auto u : adj_rev[v]){
        if (!used[u])
            dfs2(u);
    }
}

void dfs3(long long v) {
    visited[v] = true;
    for (long long u : dag[v]) {
        if (!visited[u])
            dfs3(u);
    }
    
}

void topological_sort() {
    visited.assign(dag.size(), false);
    for (long long i = 0; i < dag.size(); i++) {
        if (!visited[i]){
            dfs3(i);
            res.push_back(i);
        }
    }
}

int main() {
    long long n,m;
    cin>>n>>m;
    
    adj.resize(n);
    adj_rev.resize(n);
   
    while(m--) {
        long long a, b;
        cin>>a>>b;
        a--;
        b--;
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
    
    used.assign(n, false);
    for (long long i = 0; i < n; i++){
        if (!used[i])
            dfs1(i);
    }
    used.assign(n, false);
    reverse(order.begin(), order.end());
    vector<long long> temp(n);

    for (auto v : order){
        if (!used[v]) {
            dfs2 (v);
            for(long long u : component){
                temp[u] = v;
            }
            component.clear();
        }
    }
    
    for(long long i =0;i<n;i++){
        if(temp[i]==i){
            component.push_back(i);
        }
    }
    dag.resize(component.size());
    vector<long long> posOcupada(n);
    for(long long i =0;i<component.size();i++){
        posOcupada[component[i]] = i;
    }

    for(long long i =0;i<n;i++){
        for(long long j =0;j<adj[i].size();j++){
            if(temp[i]!=temp[adj[i][j]]){
                dag[posOcupada[temp[i]]].push_back(posOcupada[temp[adj[i][j]]]);
            }
        }
    }

    topological_sort();
    cout<<res.size()<<endl;
    for(long long i =0;i<res.size();i++){
        cout<<component[res[i]]+1<<" ";
    }
    
    return 0;
    
}