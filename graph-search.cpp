#include<iostream>
#include<queue>
using namespace std;

#define MaxSize 1024


typedef struct _EdgeNode {
	int adjvex;
	int weight;
	struct _EdgeNode* next;
}EdgeNode;


typedef struct _VertexNode {
	char data;
	struct _EdgeNode* first;
}VertexNode, AdjList;

typedef struct _AdjListGraph {
	AdjList* adjlist;
	int vex;
	int edge;
}AdjListGraph;



void Init(AdjListGraph& G) {
	G.adjlist = new AdjList[MaxSize];
	G.edge = 0;
	G.vex = 0;

}

int Location(AdjListGraph& G, char vex) {
	for (int i = 0; i < G.edge; i++) {
		if (G.adjlist[i].data == vex)
			return i;
	}
	return -1;
}

void Create(AdjListGraph& G) {
	printf("[----- [CHEN YUXIANG]  [2020039089] -----]\n");
	cout << "Please enter the number of vertices and edges of the graph:" << endl;
	cin >> G.vex >> G.edge;

	cout << "Please enter the relevant vertex：" << endl;
	for (int i = 0; i < G.vex; i++) {
		cin >> G.adjlist[i].data;
		G.adjlist[i].first = NULL;
	}
	char v1, v2 = 0;
	int weight;
	int i1, i2;
	cout << "Please enter associated vertices and weights：" << endl;
	for (int i = 0; i < G.edge; i++) {
		cin >> v1 >> v2 >> weight;
		i1 = Location(G, v1);
		i2 = Location(G, v2);
		if (i1 != -1 && i2 != -1) {
			EdgeNode* temp = new EdgeNode;
			temp->adjvex = i2;
			temp->weight = weight;
			temp->next = G.adjlist[i1].first;
			G.adjlist[i1].first = temp;
		}
	}
}

bool visited[MaxSize];

void DFS(AdjListGraph& G, int v) {
	int next = -1;
	if (visited[v])
		return;
	cout << G.adjlist[v].data << " ";
	visited[v] = true;
	EdgeNode* temp = G.adjlist[v].first;
	while (temp) {
		next = temp->adjvex;
		temp = temp->next;
		if (visited[next] == false)
			DFS(G, next);
	}
}


void DFS_Main(AdjListGraph& G) {
	for (int i = 0; i < MaxSize; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.vex; i++) {
		if (visited[i] == false) {
			DFS(G, i);
		}
	}
}

int min_weight = 0x7FFFFFFF;
int steps = 0;  
int path[MaxSize] = { 0 };  
int shortest_path[MaxSize] = { 0 };


void DFS_find(AdjListGraph& G, int start, int end, int weights) {
	int cur = -1;
	if (start == end) {
		for (int i = 0; i < steps; i++) {
			cout << G.adjlist[path[i]].data << " ";
		}
		cout << "The path weight is：" << weights << endl;
		if (min_weight > weights) {
			min_weight = weights;
			memcpy(shortest_path, path, steps * sizeof(int));
		}
		return;
	}

	visited[start] = true;
	EdgeNode* temp = G.adjlist[start].first;
	while (temp) {
		int weight = temp->weight;
		cur = temp->adjvex;
		if (visited[cur] == false) {
			visited[cur] = true;
			path[steps++] = cur;
			DFS_find(G, cur, end, weights + weight);
			visited[cur] = false;
			path[--steps] = 0;
		}
		temp = temp->next;
	}
}




void BFS(AdjListGraph& G, int v) {
	queue<int>q;
	q.push(v);
	int cur;
	int next = -1;
	while (!q.empty()) {
		cur = q.front();
		if (visited[cur] == false) {
			cout << G.adjlist[cur].data << " ";
			visited[cur] = true;
		}
		q.pop();
		EdgeNode* temp = G.adjlist[cur].first;
		while (temp) {
			next = temp->adjvex;
			temp = temp->next;
			q.push(next);
		}
	}
}


void BFS_Main(AdjListGraph& G) {
	for (int i = 0; i < MaxSize; i++) {
		visited[i] = false;
	}
	for (int i = 0; i < G.vex; i++) {
		if (visited[i] == false) {
			BFS(G, i);
		}
	}
}
int main() {
	AdjListGraph G;
	Init(G);
	Create(G);
	char begin, end;
	cout << "Enter the start and end points of the search path" << endl;
	cin >> begin >> end;
	int b, e;
	b = Location(G, begin);
	e = Location(G, end);
	DFS_find(G, b, e, 0);
	system("pause");
	return 0;
}
