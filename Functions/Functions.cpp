#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
#define INF INT_MAX

using namespace std;

typedef pair<int, pair<int, int>> ppii;
typedef pair<int, int> pii;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void addEdge(vector<vector<int> >& adjList, int u, int v)
{
    adjList[u].push_back(v);
}

class MyFunctions {
public:

    static void insertionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int curr = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > curr) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = curr;
        }
    }

    void bfs(vector<vector<int> >& adjList, int startNode, vector<bool>& visited)
    {
        queue<int> q;
        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            for (int neighbor : adjList[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void dfs(vector<vector<int>>& graph, vector<bool>& visited, int current_node) {
        visited[current_node] = true;

        for (int neighbor : graph[current_node]) {
            if (!visited[neighbor]) {
                dfs(graph, visited, neighbor);
            }
        }
    }

    int djikstra(vector<vector<int>>& grafo, pii& inicio, pii& destino) {
        int tamx = grafo.size();
        int tamy = grafo[0].size();
        priority_queue<ppii, vector<ppii>, greater<ppii>>q;
        vector<vector<int>>dist(tamx, vector<int>(tamy, INF));
        q.push({ 0 ,inicio });
        dist[inicio.first][inicio.second] = 0;
        while (!q.empty()) {
            pii atual = q.top().second;
            int dA = q.top().first;
            q.pop();
            if (atual == destino) {
                return dist[destino.first][destino.second];
            }
            for (int i = 0; i < 4; i++) {
                pii vizinho = { atual.first + dx[i] , atual.second + dy[i] };
                int pesoVizinho = grafo[vizinho.first][vizinho.second] + dA;
                if (grafo[vizinho.first][vizinho.second] != -1 && pesoVizinho < dist[vizinho.first][vizinho.second]) {
                    q.push({ pesoVizinho ,vizinho });
                    dist[vizinho.first][vizinho.second] = pesoVizinho;
                }
            }
        }
        return -1;
    }

    //Do headSort
    void heapify(vector<int>& heap, int curr, int size) {
        int largest = curr;
        int l = 2 * curr + 1;
        int r = 2 * curr + 2;

        if (l < size && heap[l] > heap[largest]) {
            largest = l;
        }
        if (r < size && heap[r] > heap[largest]) {
            largest = r;
        }
        if (largest != curr) {
            swap(heap[curr], heap[largest]);

            heapify(heap, largest, size);
        }
    }

    void heapSort(vector<int>& list) {
        for (int i = list.size() / 2 - 1; i >= 0; i--) {
            heapify(list, i, list.size());
        }
        for (int i = list.size() - 1; i >= 0; --i) {
            swap(list[0], list[i]);
            heapify(list, 0, i);
        }
    }

    //Do quickSort
    int partition(vector<int>& array, int start, int end) {

        int pivot = array[end];
        int i = start - 1;
        for (int j = start; j <= end - 1; j++) {
            if (array[j] < pivot) {
                i++;
                swap(array[i], array[j]);
            }
        }
        i++;
        swap(array[i], array[end]);

        return i;
    }

    void quickSort(vector<int>& array, int start, int end) {

        if (end <= start) return;

        int pivot = partition(array, start, end);
        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);

    }

    //Do radixSort
    int getMax(vector<int>& array, int n) {
        int mx = array[0];
        for (int i = 1; i < n; i++) {
            if (array[i] > mx) {
                mx = array[i];
            }
        }
        return mx;
    }

    //Do radixSort
    void countSort(vector<int>& array, int n, int exp) {
        vector<int> output(n);
        vector<int> count(10, 0);

        for (int i = 0; i < n; i++) {
            count[(array[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(array[i] / exp) % 10] - 1] = array[i];
            count[(array[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            array[i] = output[i];
        }
    }

    void radixSort(vector<int>& array, int size) {
        int m = getMax(array, size);

        for (int exp = 1; m / exp > 0; exp *= 10) {
            countSort(array, size, exp);
        }
    }

    // Serve pra numero float, como "0.21"
    void bucketSort(vector<float>& array, int size) {

        vector<vector<float>> bucket(size);

        for (int i = 0; i < size; i++) {
            int bi = size * array[i];
            bucket[bi].push_back(array[i]);
        }

        int index = 0;
        for (int i = 0; i < size; i++) {
            sort(bucket[i].begin(), bucket[i].end());
            for (float num : bucket[i]) {
                array[index++] = num;
            }
        }

    }
};

MyFunctions functions;

int main() {

    return 0;
}
