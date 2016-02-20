#include <iostream>
#include <fstream>
#include <string.h>
#include <deque>

#define MaxVnum 100
using namespace std;


class Graph {
private:
	int vetexnum;
	int adjacency[MaxVnum+1][MaxVnum+1];
public:
	Graph(const char *edgefilename);
	void findCComponent();
	void printadj();
};

void Graph::printadj() {
	for (int i = 1; i<=vetexnum; i++) {
		for (int j = i+1; j <= vetexnum; j++)
		{
			cout<<i << " "<<j<<" "<<adjacency[i][j]<<endl;
		}
	}

}

Graph::Graph(const char *edgefilename) {
	memset(adjacency,0,(MaxVnum+1)*(MaxVnum+1)*sizeof(int));
	ifstream edgefile(edgefilename);
	if (edgefile.is_open())
	{
		edgefile >> vetexnum;
		cout<<vetexnum<<endl;
		while(!edgefile.eof()) {
			int i,j,k;
			edgefile >> i >> j >> k;
			adjacency[i][j]=k;
		}
	}
}

void Graph::findCComponent() {
	//initialization
	int flag[MaxVnum+1];
	memset(flag,0,sizeof(int)*(MaxVnum+1));
	int componentID = 1;
	int remaining = vetexnum;
	deque<int> vqueue;
	vqueue.push_back(1);  //start from vertex 1
	while (!vqueue.empty()) {
		int visit = vqueue.front();
		vqueue.pop_front();
		remaining --;
		if (flag[visit] == 0) 
			flag[visit] = componentID;
		for (int i=1; i<=vetexnum; i++) {
			if (i!=visit && adjacency[visit][i]==1 && flag[i]==0)
				vqueue.push_back(i);
		}
		if(vqueue.empty()) {
			if (remaining>0) {
				for (int i = 1; i <= vetexnum; ++i)
				{
					if(flag[i]==0) {
						vqueue.push_back(i);
						componentID ++;
						break;
					}
				}
			}
		}
	}
	//print out connected component
	for (int i = 1; i <=componentID; i++) {
		cout<<"component: " << i <<": ";
		for (int j =1; j <=vetexnum; j++) {
			if (flag[j] == i)
				cout<<j<<" ";
		}
		cout<<endl;
	}
} 



int main() {
	Graph graph("edge.data");
	graph.printadj();
	graph.findCComponent();
}


