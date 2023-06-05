#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e18;

int n, m, s, t, k;


struct arista{
    ll costo;
    int from, to;
    
    bool operator<(const arista& otro) const {
        return costo < otro.costo;
    }
};

vector<ll> dijkstra(vector<vector<arista>> &grafo, int& src){
    //
    priority_queue<arista, vector<arista>, less<arista>> pq;
    vector<ll> dist(n+1, inf);

    pq.push({0, -1, src});
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().to;
        pq.pop();
        for (arista i : grafo[u]) {
            int v = i.to;
            ll peso = i.costo;
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], u, v});
            }
        }
    }
    return dist;
}

void seleccionarCandidata(vector<vector<arista>>& g, vector<vector<arista>>& g_inverso, vector<arista>& cand){
    vector<ll> distS = dijkstra(g, s);
    vector<ll> distT = dijkstra(g_inverso, t);
    ll min = distS[t];
    for(arista c : cand){
        int u = c.from;
        int v = c.to;
        ll nuevoMin = distS[u] + c.costo + distT[v];
        if (nuevoMin < min){
            min = nuevoMin;
        }
    }
    if(min == inf){
        cout << -1 << endl;
    }else{
        cout << min << endl;
    }
}


int main() {
    int cantCasos;
    cin >> cantCasos;
    vector<vector<arista>> grafo;
    vector<vector<arista>> grafo_inverso;
    vector<arista> candidatas;
    while(cantCasos--){
        cin >> n >> m >> k >> s >> t;
        grafo.clear();
        grafo_inverso.clear();
        candidatas.clear();
        grafo.resize(n+1);
        grafo_inverso.resize(n+1);

        // inicializar grafos
        for(int i = 0; i < m; i++){
            int x, y;
            ll c;
            cin >> x >> y >> c;
            arista a = {c, x, y};
            arista a_inversa = {c, y, x};
            grafo[x].push_back(a);
            grafo_inverso[y].push_back(a_inversa);
        }
        // inicializar calles candidatas
        for (int i = 0; i < k; i++)
        {
            int x, y;
            ll c;
            cin >> x >> y >> c;
            arista a = {c, x, y};
            candidatas.push_back(a);
        }
        // resolver

        seleccionarCandidata(grafo, grafo_inverso, candidatas);
    }

    return 0;
} 
