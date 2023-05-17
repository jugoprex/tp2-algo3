#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, adj_rev;

vector<bool> used;
vector<int> order, component;
vector<vector<int>> dag;
vector<bool> visited;
vector<int> res;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v]){
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v]){
        if (!used[u])
            dfs2(u);
    }
}

void dfs3(int v) {
    visited[v] = true;
    for (int u : dag[v]) {
        if (!visited[u])
            dfs3(u);
    }
    
}

void topological_sort() {
    visited.assign(dag.size(), false);
    for (int i = 0; i < dag.size(); i++) {
        if (!visited[i]){
            dfs3(i);
            res.push_back(i);
        }
    }
}

int main() {
    int n,m;
    int c;
    cin>>c;
    while(c--){
        cin>>n>>m;
    
        adj.resize(n);
        adj_rev.resize(n);
    
        while(m--) {
            int a, b;
            cin>>a>>b;
            a--;
            b--;
            adj[a].push_back(b);
            adj_rev[b].push_back(a);
        }
        
        used.assign(n, false);
        for (int i = 0; i < n; i++){
            if (!used[i])
                dfs1(i);
        }
        used.assign(n, false);
        reverse(order.begin(), order.end());
        vector<int> temp(n);

        for (auto v : order){
            if (!used[v]) {
                dfs2 (v);
                for(int u : component){
                    temp[u] = v;
                }
                component.clear();
            }
        }
        
        for(int i =0;i<n;i++){
            if(temp[i]==i){
                component.push_back(i);
            }
        }
        dag.resize(component.size());
        vector<int> posOcupada(n);
        for(int i =0;i<component.size();i++){
            posOcupada[component[i]] = i;
        }

        for(int i =0;i<n;i++){
            for(int j =0;j<adj[i].size();j++){
                if(temp[i]!=temp[adj[i][j]]){
                    dag[posOcupada[temp[i]]].push_back(posOcupada[temp[adj[i][j]]]);
                }
            }
        }

        topological_sort();
        cout<<res.size()<<endl;
        for(int i =0;i<res.size();i++){
            cout<<component[res[i]]+1<<" ";
        }
        cout<<endl;
        adj.clear();
        adj_rev.clear();
        used.clear();
        order.clear();
        component.clear();
        dag.clear();
        visited.clear();
        res.clear();
        }
    
    return 0;
}