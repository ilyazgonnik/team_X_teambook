pair<vector<int>, vector<int>> dijkstra(const vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INF);
    vector<int> parents(n, -1);
    
    distances[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, start));
    
    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        int current_distance = -pq.top().first;
        pq.pop();
        
        // Пропускаем устаревшие записи в очереди
        if (current_distance > distances[current_vertex]) {
            continue;
        }
        
        // Обходим всех соседей текущей вершины
        for (const auto& edge : graph[current_vertex]) {
            int neighbor = edge.first;
            int edge_weight = edge.second;
            
            // Релаксация ребра
            if (distances[current_vertex] + edge_weight < distances[neighbor]) {
                distances[neighbor] = distances[current_vertex] + edge_weight;
                parents[neighbor] = current_vertex;
                pq.push(make_pair(-distances[neighbor], neighbor));
            }
        }
    }
    
    return make_pair(distances, parents);
}
