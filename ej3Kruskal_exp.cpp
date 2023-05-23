#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std;


struct oficina{
    int x,y;
};

double distancia(oficina a, oficina b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

struct DSU_no_rank{
    
        DSU_no_rank(int n){
            padre = vector<int>(n);
            for(int v = 0; v < n; v++) padre[v] = v;
        }
    
        int find(int v){
            if(v == padre[v]) return v;
            return padre[v] = find(padre[v]);
        }
    
        void unite(int u, int v){
            u = find(u), v = find(v);
            if(u == v) return;
            padre[v] = padre[u];
        }
    
        vector<int> padre;
    };

struct DSU_no_path_compression{
    
        DSU_no_path_compression(int n){
            padre = vector<int>(n);
            for(int v = 0; v < n; v++) padre[v] = v;
        }
    
        int find(int v){
            if(v == padre[v]) return v;
            return find(padre[v]);
        }
    
        void unite(int u, int v){
            u = find(u), v = find(v);
            if(u == v) return;
            padre[v] = padre[u];
        }
    
        vector<int> padre;
    };

void kruskal(int n,vector<tuple<pair<double,bool>,int,int>> &E, vector<pair<double,bool>> &res){
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            res.push_back(c);
        }
    }
    if(aristas != n-1){
        cout<<"IMPOSSIBLE\n";
    }
    return;
}

void kruskal_no_rank (int n,vector<tuple<pair<double,bool>,int,int>> &E, vector<pair<double,bool>> &res){
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU_no_rank dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            res.push_back(c);
        }
    }
    if(aristas != n-1){
        cout<<"IMPOSSIBLE\n";
    }
    return;

}

void kruskal_no_path_compression (int n,vector<tuple<pair<double,bool>,int,int>> &E, vector<pair<double,bool>> &res){
    sort(E.begin(),E.end());
    int aristas = 0;
    DSU_no_path_compression dsu(n);
    for(auto [c,u,v] : E){
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            aristas++;
            res.push_back(c);
        }
    }
    if(aristas != n-1){
        cout<<"IMPOSSIBLE\n";
    }
    return;
}

void kruskal_dense(int n, vector<tuple<pair<double, bool>, int, int>>& E, vector<pair<double, bool>>& res) {
    priority_queue<tuple<pair<double, bool>, int, int>, vector<tuple<pair<double, bool>, int, int>>, greater<tuple<pair<double, bool>, int, int>>> pq;
    for (auto& edge : E) {
        pq.push(edge);
    }
    
    int aristas = 0;
    DSU dsu(n);
    while (!pq.empty() && aristas < n - 1) {
        auto [c, u, v] = pq.top();
        pq.pop();
        
        // If (u, v) is a safe edge
        if (dsu.find(u) != dsu.find(v)) {
            // Add the edge
            dsu.unite(u, v);
            aristas++;
            res.push_back(c);
        }
    }
    
    if (aristas != n - 1) {
        cout << "IMPOSSIBLE\n";
    }
}

int main(){
    int c,N,R,W,U,V;
    cin>>c;
    //inicializo matriz de tamaño N*N
    auto time_start = chrono::high_resolution_clock::now();
    auto time_start_no_rank = chrono::high_resolution_clock::now();
    auto time_start_no_path_compression = chrono::high_resolution_clock::now();
    auto time_start_dense = chrono::high_resolution_clock::now();

    auto time_end = chrono::high_resolution_clock::now();
    auto time_end_no_rank = chrono::high_resolution_clock::now();
    auto time_end_no_path_compression = chrono::high_resolution_clock::now();
    auto time_end_dense = chrono::high_resolution_clock::now();
    vector<oficina> oficinas;
    int x=1;
    while(c--){

        cin>>N>>R>>W>>U>>V;
        oficinas.clear();
        while(N--){
            int x,y;
            cin>>x>>y;
            oficinas.push_back({x,y});
        }
        N = oficinas.size();


        vector<tuple<pair<double,bool>,int,int>> E;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                double dist = distancia(oficinas[i],oficinas[j]);
                bool utp;
                //si la distancia es < R entonces me fijo cual me conviene
                if(dist<=R && U<=V){
                    dist = U*dist;
                    utp = true;
                }else{
                    dist = V*dist;
                    utp = false;
                }
                E.push_back({{dist,utp},i,j});
            }
        }
        time_start = chrono::high_resolution_clock::now();
        vector<pair<double,bool>> res;
        kruskal(N,E,res);
        double totalUtp = 0;
        double totalFibra = 0;
        
        for(int i=0;i<res.size()-(W-1);i++){
            if(res[i].second){
                totalUtp+=res[i].first;
            }else{
                totalFibra+=res[i].first;
            }
        }
        time_end = chrono::high_resolution_clock::now();

        time_start_no_path_compression = chrono::high_resolution_clock::now();
        vector<pair<double,bool>> res_no_path_compression;
        kruskal_no_path_compression(N,E,res_no_path_compression);
        double totalUtp_no_path_compression = 0;
        double totalFibra_no_path_compression = 0;

        for(int i=0;i<res_no_path_compression.size()-(W-1);i++){
            if(res_no_path_compression[i].second){
                totalUtp_no_path_compression+=res_no_path_compression[i].first;
            }else{
                totalFibra_no_path_compression+=res_no_path_compression[i].first;
            }
        }
        time_end_no_path_compression = chrono::high_resolution_clock::now();


        time_start_no_rank = chrono::high_resolution_clock::now();
        vector<pair<double,bool>> res_no_rank;
        kruskal_no_rank(N,E,res_no_rank);
        double totalUtp_no_rank = 0;
        double totalFibra_no_rank = 0;

        for(int i=0;i<res_no_rank.size()-(W-1);i++){
            if(res_no_rank[i].second){
                totalUtp_no_rank+=res_no_rank[i].first;
            }else{
                totalFibra_no_rank+=res_no_rank[i].first;
            }
        }
        time_end_no_rank = chrono::high_resolution_clock::now();

        time_start_dense = chrono::high_resolution_clock::now();
        vector<pair<double,bool>> res_dense;
        kruskal_dense(N,E,res_dense);
        double totalUtp_dense = 0;
        double totalFibra_dense = 0;

        for(int i=0;i<res_dense.size()-(W-1);i++){
            if(res_dense[i].second){
                totalUtp_dense+=res_dense[i].first;
            }else{
                totalFibra_dense+=res_dense[i].first;
            }
        }
        time_end_dense = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);
        auto duration_no_rank = chrono::duration_cast<std::chrono::microseconds>(time_end_no_rank - time_start_no_rank);
        auto duration_no_path_compression = chrono::duration_cast<std::chrono::microseconds>(time_end_no_path_compression - time_start_no_path_compression);
        auto duration_dense = chrono::duration_cast<std::chrono::microseconds>(time_end_dense - time_start_dense);
        ofstream myfile;
        myfile.open ("ej3_times.txt", ios::app);
        myfile << duration.count()<<" " << c << endl;
        myfile << duration_no_rank.count()<<" " << c << endl;
        myfile << duration_no_path_compression.count()<<" " << c << endl;
        myfile << duration_dense.count()<<" " << c << endl;
        myfile.close();
        x++;
    }
    return 0;
}