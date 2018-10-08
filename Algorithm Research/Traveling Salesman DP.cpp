#include <bits/stdc++.h>

using namespace std;

bool debug = false;

vector<int>toBinary(int x, int n) {
	vector<int>res(n, 0);
	int i = 0;
	 while (i < n) { 
        res[n - i - 1] = x % 2; 
        x = x / 2; 
        i++; 
    } 
    return res;
}

bool isVisitable(int visited, int cur_position, int n) {
	vector<int>res = toBinary(visited, n);
	if(res[cur_position]) {
		return false;
	}
	return true;
}

bool isAllVisited(vector<int>visited) {
	for(int i = 0; i < visited.size(); i++) {
		if(visited[i] == 0) {
			return false;
		}
	}
	return true;
}

int toDecimal(vector<int>x) {
	int res = 0;
	for(int i = 0; i < x.size(); i++) {
		if(x[i] == 1) {
			res += (1 << (x.size() - i - 1));
		}
	}
	return res;
}

int changeStatusCurPosition(int visited, int cur_position, int n, int change) {
	vector<int>tmp = toBinary(visited, n);
	tmp[cur_position] = change;
	return toDecimal(tmp);
}

int recursiveVisit(vector<vector<int>>&map, int cur_position, int n, int visited, vector<vector<int>>&totalCost) {
	if(debug) {
		cout << "cur cost: " << totalCost[cur_position][visited] <<  " current position: " << cur_position << " visited: " << visited << endl;
	}

	if(isAllVisited(toBinary(changeStatusCurPosition(visited, cur_position, n, 1), n))) {
		return 0;
	}

	if(totalCost[cur_position][visited] != -1) {
		return totalCost[cur_position][visited];
	}

	totalCost[cur_position][visited] = INT_MAX;

	int newVisited = changeStatusCurPosition(visited, cur_position, n, 1);

	for(int i = 0; i < n; i++) {
		if(isVisitable(newVisited, i, n)) {
			totalCost[cur_position][visited] = min(totalCost[cur_position][visited], map[cur_position][i] + recursiveVisit(map, i, n, newVisited, totalCost));
			if(debug) {
				cout << "cur cost: " << totalCost[cur_position][visited] <<  " current position: " << cur_position << " i: " << i << endl;
			}
		}
	}

	return totalCost[cur_position][visited];
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
	vector<vector<int>>totalCost(n, vector<int>(1 << 16, -1));

	for(int i = 0; i < n; i++) {
		minTotalCost = min(minTotalCost, recursiveVisit(map, i, n, 0, totalCost));
	}
	
	cout << minTotalCost << endl;
	
	return 0;
}