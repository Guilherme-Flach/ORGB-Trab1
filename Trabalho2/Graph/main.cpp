#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <vector>
#include <bits/stdc++.h>

std::mt19937 rng;
int seed = 0;

int random(const int i, const int c, const int min, const int max) {
    rng.seed(seed + (i + 1) * (c + 1));
    std::uniform_int_distribution distribution(min, max);
    return distribution(rng);
}

class Graph {
    std::vector<std::set<int> > adjacencyList;

public:
    explicit Graph(const int n) {
        adjacencyList.resize(n);
    }

    static Graph generateGraph(const int n) {
        Graph graph(n);
        for (int i = 0; i < n; i++) {
            auto attempts = random(i, 0, 0, n - 1);
            std::set<int> connected;
            int c = 0;
            while (attempts-- > 0) {
                if (const int v = random(i, c++, 0, n - 1); connected.find(v) == connected.end()) {
                    graph.addEdge(i, v);
                    connected.insert(v);
                }
            }
        }
        return graph;
    }

    void addEdge(const int v, const int w) {
        if (v == w)
            return;
        adjacencyList[v].insert(w);
        adjacencyList[w].insert(v);
    }

    [[nodiscard]] std::vector<float> dijkstra(const int source) const {
        std::vector distances(adjacencyList.size(), INFINITY);
        std::set<int> visited;
        std::stack<int> stack;
        stack.push(source);
        distances[source] = 0;
        while (!stack.empty()) {
            const auto v = stack.top();
            stack.pop();
            if (visited.find(v) != visited.end())
                continue;
            visited.insert(v);
            for (const auto &it: adjacencyList[v]) {
                if (visited.find(it) == visited.end()) {
                    stack.push(it);
                    if (const float newDistance = distances[v] + 1; newDistance < distances[it])
                        distances[it] = newDistance;
                }
            }
        }
        return distances;
    }

    void depthSearch(const std::function<void(int)> &onElement) {
        if (adjacencyList.empty())
            return;
        std::set<int> visited;
        std::stack<int> stack;
        stack.push(0);
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            if (visited.find(v) != visited.end())
                continue;
            visited.insert(v);
            onElement(v);
            for (const int &it: adjacencyList[v]) {
                if (visited.find(it) == visited.end())
                    stack.push(it);
            }
        }
    }

    void breadthSearch(const std::function<void(int)> &onElement) {
        if (adjacencyList.empty())
            return;
        std::set<int> visited;
        std::list<int> queue;
        queue.push_back(0);
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop_front();
            if (visited.find(v) != visited.end())
                continue;
            visited.insert(v);
            onElement(v);
            for (const int &it: adjacencyList[v]) {
                if (visited.find(it) == visited.end())
                    queue.push_back(it);
            }
        }
    }
};

int main() {
    std::cout <<
            "Greetings, traveler! The purpose of this program is to measure the performance with different graph algorithms."
            << std::endl;
    std::cout << "Firstly, enter the seed for the random generation: ";
    std::cin >> seed;
    if(seed == 0)
        seed += 1;
    std::cout << "Enter the number of vertices: ";
    std::cout << std::endl;
    int n;
    std::cin >> n;
    const auto beforeAll = std::chrono::high_resolution_clock::now();
    std::cout << "Generating graph with " << n << " vertices..." << std::endl;
    Graph graph = Graph::generateGraph(n);
    std::cout << "Graph generated." << std::endl;
    std::cout << std::endl;
    std::cout << "Starting depth search..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> results;
    graph.depthSearch([&results](int v) {
        results.emplace_back(v);
    });
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Depth search finished in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).
            count()
            << " nanosecond(s)." << std::endl;
    std::cout << "Elements discovered: ";
    for (const auto &it: results)
        std::cout << it << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Starting breadth search..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    results.clear();
    graph.breadthSearch([&results](int v) {
        results.emplace_back(v);
    });
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Breadth search finished in "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanosecond(s)."
            << std::endl;
    std::cout << "Elements discovered: ";
    for (const auto &it: results)
        std::cout << it << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Starting Dijkstra algorithm..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    const auto dijkstra = graph.dijkstra(0);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Dijkstra algorithm finished in "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanosecond(s)."
            << std::endl;
    std::cout << "Distances to root: " << std::endl;
    for (const auto &it: dijkstra)
        if (it != INFINITY)
            std::cout << &it - &dijkstra[0] << ": " << it << " " << std::endl;
    const auto afterAll = std::chrono::high_resolution_clock::now();
    const auto totalElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(afterAll - beforeAll).count();
    std::cout << std::endl << "Total elapsed time: " << totalElapsed << " millisecond(s)." << std::endl;
    return 0;
}
