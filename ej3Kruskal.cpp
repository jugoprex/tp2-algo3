#include <bits/stdc++.h>


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

int main(){
    int c,N,R,W,U,V;
    cin>>c;
    //inicializo matriz de tamaño N*N
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
        cout<<setprecision(3)<<fixed;
        cout<<"Caso #"<<x<<": "<<totalUtp<<" "<<totalFibra<<endl;
        x++;
    }
    return 0;
}