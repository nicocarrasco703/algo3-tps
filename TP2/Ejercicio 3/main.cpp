// Modems
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<tuple<int, int>> localizacion;
int n, r, w, u, v;
int componentes;
double costoUTP, costoFibra; 
const char UTP = 'U';
const char Fibra = 'F';
int caso = 0;
vector<vector<int>> kruskalgrafo;

struct arista{
    double costo;
    int x, y;
    char tipo;
};

bool orden(arista a, arista b){
    return a.costo < b.costo;
}

struct DSU{

    DSU(int k){
        padre = rank = vector<int>(k);
        for(int b = 0; b < k; b++) padre[b] = b;
    }

    int find(int b){
        if(b == padre[b]) return b;
        return padre[b] = find(padre[b]);
    }

    void unite(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return;
        if(rank[a] < rank[b]) swap(a,b);
        padre[b] = padre[a];
        rank[a] = max(rank[a],rank[b]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal(vector<arista> &grafo){
    sort(grafo.begin(),grafo.end(), orden);
    DSU dsu(n);
    for(auto k : grafo){
        int x = k.x;
        int y = k.y;
        if(dsu.find(x) != dsu.find(y)){
            dsu.unite(x,y);
            (k.tipo == UTP) ? costoUTP += k.costo : costoFibra += k.costo;
            kruskalgrafo[x].push_back(y);
            componentes--;
            if (componentes == w){
                break;
            }
        }
    }
}

double distancia(int x1, int y1, int x2, int y2){
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

vector<arista> init_grafo(vector<tuple<int, int>> &p){
    double costo;
    char tipo;
    vector<arista> aristas;
    for(int i = 0; i < p.size(); i++){
        for(int j = i+1; j < p.size(); j++){
            int x1 = get<0>(p[i]);
            int y1 = get<1>(p[i]);
            int x2 = get<0>(p[j]);
            int y2 = get<1>(p[j]);
            double d = distancia(x1, y1, x2, y2);
            if(d <= r){
                costo = u * d;
                tipo = UTP;
            } else {
                costo = v * d;
                tipo = Fibra;
            }
            arista cable = {costo, x1, y1, tipo};
            aristas.push_back(cable);
        }
    }
    return aristas;
}

void imprimirCaso(){
    cout << "Caso #" << caso << ": " << setprecision(3) << fixed << costoUTP << " " << setprecision(3) << fixed << costoFibra << endl;
}


int main() {
    int cantCasos;
    cin >> cantCasos;
    vector<arista> grafo;
    for(int i = 0; i < cantCasos; i++){
        caso ++;
        costoUTP = 0;
        costoFibra = 0;
        cin >> n >> r >> w >> u >> v;
        kruskalgrafo = vector<vector<int>>(n);
        componentes = n;
        localizacion.clear();
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            localizacion.push_back({x, y});
        }
        grafo = init_grafo(localizacion);
        kruskal(grafo);
        imprimirCaso();
    }

    return 0;
} 