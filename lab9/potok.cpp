#include <vector>
#include <array>
#include <queue>
#include <iostream>


const int START = 0;


int main(){
    int n{};
    int m{};

    std::cin >> n >> m;
    std::vector<std::vector<std::array<long long, 3>>> graph(n);

    for (size_t i{}; i < m; i++){
        int id1{};
        int id2{};
        long long weight{};
        std::cin >> id1 >> id2 >> weight;
        id1--;
        id2--;
        graph[id1].push_back({id2, weight, weight});
        graph[id2].push_back({id1, weight, 0});
    }

    bool pathFound = true;

    while(pathFound){
        std::vector<bool>visited(n, false);
        std::vector<std::pair<int , long long>> path(n, {-1, -1});
        std::queue<int> q;

        visited[START] = true;

        q.push({START});
        while (q.size()){
            int node = q.front();
            q.pop();
            for (size_t i{}; i < graph[node].size(); i++){
                if (!visited[graph[node][i][0]] && graph[node][i][2] > 0){
                    long long edgeMin{};
                    if (graph[node][i][1] != graph[node][i][2] ){
                        edgeMin = std::min(graph[node][i][1], graph[node][i][2]);
                    } else if (graph[node][i][1] == graph[node][i][2]){


                    }
                    path[graph[node][i][0]] = {node, edgeMin};
                    visited[graph[node][i][0]] = true;
                    q.push(graph[node][i][0]);
                }
            }
        }

        long long minEl{};
        if (!visited[n - 1]){
            pathFound = false;
        } else{
            int id = n - 1;
            while (id != -1){
                if ()


            }




        }
    }


    return 0;
}