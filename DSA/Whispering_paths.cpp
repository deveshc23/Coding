#include<bits/stdc++.h>
using namespace std;
void dfs(int node,vector<vector<int>> &adj,vector<bool> &visited,vector<vector<int>> &paths){
    visited[node] = true;
    currentPath.insert(node);
    for(auto neighbor:adj[node]){
        
        if(!visited[neighbor]){
            dfs(neighbor,adj,visited,paths);
        }
    }
    paths.push_back(currentPath);
}
int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i=1;i<n;i++){
        pair<int,int> p;
        cin >> p.first >> p.second;
        adj[p.first].push_back(p.second);
        adj[p.second].push_back(p.first);
    }
    vector<bool> visited(n + 1, false);
    vector<vector<int>> paths;

    for(int i=0;i<m;i++){
        set<int> path;
        int len;
        cin >> len;
        for(int j=0;j<len;j++){
            int node;
            cin >> node;
            path.insert(node);
        }

    }
}