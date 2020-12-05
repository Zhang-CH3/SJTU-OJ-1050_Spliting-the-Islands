#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int MAXN = 100005;
int n, k, par[MAXN], offspr[MAXN];

struct Edge{
	int v;
};

vector<Edge> adj[MAXN];

void addEdge(int u, int v){
	adj[u].push_back((Edge){v});
	adj[v].push_back((Edge){u});
}

void dfs(int root, int fa){
	par[root] = fa;
	offspr[root]++;
	for(int i=0;i<adj[root].size();i++){
		if(adj[root][i].v == fa)continue;
		dfs(adj[root][i].v, root);
		offspr[root] += offspr[adj[root][i].v];
	}
}

bool check(int root){
	for(int i=0;i<adj[root].size();i++){
		int sum;
		int v = adj[root][i].v;
		if(v == par[root]) sum = n - offspr[root];
		else sum = offspr[v];
		if(sum > k) return false;
	}
	return true;
}

int main(){
	cin >> n >> k;
	int u, v;
	for(int i=1;i<n;i++){
		offspr[i] = 0;
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	offspr[n] = 0;
	dfs(1, -1);
	int ansnum = 0;
	for(int i=n;i>=1;i--){
		if(check(i)){
			printf("%d ", i);
			ansnum++;
		}
	}
	if(ansnum == 0)cout << "None" << endl;
	return 0;
} 
