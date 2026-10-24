//Name: Parker Babb
// dijsktras.cpp

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> 
#include <climits>

using namespace std; 

//Vector declaration from Geeks for Geeks
//Uses ADJ list with (neighbor, weight) as pairs
//parent is node last visited, -1 for source node
vector<int> dijkstra(vector<vector<pair<int,int> > >& adj, int src, vector <int>& parent) { 

	int n = adj.size(); 
	
	vector<int> cost(n, -1); // -1 = not yet reached
	vector<bool> finalized(n, false); // true when cheapest cost found
	parent.assign(n, -1);

	//Ordered by cost
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int,int> > > frontier;

	cost[src] = 0;
	frontier.push(make_pair(0, src)); 

	while (!frontier.empty()) { 
		int u = frontier.top().second;
		frontier.pop();

		if (finalized[u]) {
			continue;
		}
		finalized[u] = true;

		//Try to improve cost of each neighbor through U
		for (size_t i = 0; i < adj[u].size(); i++) { 
			int v = adj[u][i].first;
			if (finalized[v]) { 
				continue;
			}

			int through_u = cost[u] + adj[u][i].second;

			//If v new or cheaper, take path
			if (cost[v] == -1 || through_u < cost[v]) { 
				cost[v] = through_u;
				parent[v] = u;
				frontier.push(make_pair(through_u, v)); 
			}
		}
	}

	return cost; 

}




int main(int argc, char *argv[]) {

	int tiles_n; 
	if (!(cin >> tiles_n))
		return 1; 
	
	vector<int> tile_cost(256,0); //indexed w/ char node
	for (int i = 0; i < tiles_n; i++) { 
		char name;
		int cost;
		cin >> name >> cost; 
		tile_cost[name] = cost; 
	}

	//Read in map
	int rows, cols;
	cin >> rows >> cols; 

	//cost of leaving node v 
	vector<int> cost_at(rows * cols); 
	for (int r = 0; r < rows; r++) { 
		for (int c = 0; c < cols; c++) { 
			char t;
			cin >> t;
			cost_at[r * cols + c] = tile_cost[t]; //Google 1D indexing methods
		}
	}

	int sr, sc, er ,ec;
	cin >> sr >> sc >> er >> ec; 

	int src = sr * cols + sc; 
	int goal = er * cols + ec; 

	//adj list
	vector<vector<pair<int, int> > > adj(rows * cols); 

	const int dr[4] = {-1, 1, 0, 0};
	const int dc[4] = {0, 0, -1, 1};

	//Claude explaination on common ways to generate and check neighboring cells in an adj list. 
	for (int r = 0; r < rows; r++) { 
		for (int c = 0; c < cols; c++) { 
			int u = r * cols + c; 
			for (int k = 0; k < 4; k++) { 
				int nr = r + dr[k];
				int nc = c + dc[k]; 
				if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) { //Ignore neighbors outside of map
					continue;
				}
				int v = nr * cols + nc; 
				adj[u].push_back(make_pair(v, cost_at[u]));
			}
		}
	}

	//Run Dijkstra's
	vector<int> prev;
	vector<int> dist = dijkstra(adj, src, prev); 
	
	//Print cost
	cout << dist[goal] << endl;

	//Build path from goal -> start, print reverse
	vector<int> path;
	for (int v = goal; v != -1; v = prev[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());

	//Convert 1D index back to 2D, Googled how to do this
	for (size_t i = 0; i < path.size(); i++) { 
		cout << path[i] / cols << " " << path[i] % cols << endl;
	}


    return 0;
}

