#include <bits/stdc++.h>

using namespace std;

bool debug = false;

bool isVisitable(vector<int>&visited, int cur_position, int n) {
	for(int i = 0; i < n; i++) {
		if(visited[cur_position]) {
			return false;
		}
	}
	return true;
}

void recursiveVisit(vector<vector<int>>&map, int &minTotalCost, int totalCost, int cur_position, int n, vector<int>&visited, int count) {
	// if(debug) {
	// 	cout << "min Cost: " << minTotalCost << " totalCost: " << totalCost << " current position: " << cur_position << " count: " << count << endl;
	// }

	if(count > n) {
		return;
	}

	if(count == n) {
		if(totalCost < minTotalCost) {
			minTotalCost = totalCost;
		}
		return;
	}

	for(int i = 0; i < n; i++) {
		visited[cur_position] = 1;
		if(isVisitable(visited, i, n)) {
			if(debug) {
				cout << "min Cost: " << minTotalCost << " totalCost: " << totalCost + map[cur_position][i] << " current position: " << cur_position << " i: " << i << " count: " << count + 1<< endl;
			}
			recursiveVisit(map, minTotalCost, totalCost + map[cur_position][i], i, n, visited, count + 1);
		}
		visited[cur_position] = 0;
	}
	return;
}

int main() {
	int n;
	cin >> n;

	vector<vector<int>>map(n, vector<int>(n));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int minTotalCost = INT_MAX;
	vector<int>visited(n, 0);
	for(int i = 0; i < n; i++) {
		recursiveVisit(map, minTotalCost, 0, i, n, visited, 1);
	}
	
	cout << minTotalCost << endl;
	
	return 0;
}