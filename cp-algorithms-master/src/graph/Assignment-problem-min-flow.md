# Giải bài toán gán bằng cách sử dụng luồng chi phí tối thiểu (min-cost-flow)

---
tags:
  - Dịch
e_maxx_link: assignment_mincostflow
---

# Giải bài toán gán bằng cách sử dụng luồng chi phí tối thiểu (min-cost-flow)

**Bài toán gán** (assignment problem) có hai cách phát biểu tương đương:

   - Cho một ma trận vuông $A[1..N, 1..N]$, bạn cần chọn $N$ phần tử trong đó sao cho mỗi hàng và cột chỉ được chọn đúng một phần tử và tổng giá trị của các phần tử này là nhỏ nhất.
   - Có $N$ đơn hàng và $N$ máy móc. Chi phí sản xuất trên mỗi máy được biết đối với mỗi đơn hàng. Mỗi máy chỉ có thể thực hiện một đơn hàng. Yêu cầu gán tất cả các đơn hàng cho các máy sao cho tổng chi phí là tối thiểu.

Ở đây, chúng ta sẽ xem xét giải pháp của bài toán dựa trên thuật toán tìm [luồng chi phí tối thiểu (min-cost-flow)](min_cost_flow.md), giải bài toán gán trong $\mathcal{O}(N^3)$.

## Mô tả

Hãy xây dựng một mạng hai phía (bipartite network): có một nguồn $S$, một đích $T$, ở phần đầu tiên có $N$ đỉnh (tương ứng với các hàng của ma trận hoặc đơn hàng), ở phần thứ hai cũng có $N$ đỉnh (tương ứng với các cột của ma trận hoặc máy móc). Giữa mỗi đỉnh $i$ của tập hợp thứ nhất và mỗi đỉnh $j$ của tập hợp thứ hai, chúng ta vẽ một cạnh có băng thông 1 và chi phí $A_{ij}$. Từ nguồn $S$, chúng ta vẽ các cạnh đến tất cả các đỉnh $i$ của tập hợp thứ nhất với băng thông 1 và chi phí 0. Chúng ta vẽ một cạnh có băng thông 1 và chi phí 0 từ mỗi đỉnh của tập hợp thứ hai $j$ đến đích $T$.

Chúng ta tìm trong mạng kết quả luồng tối đa có chi phí tối thiểu. Rõ ràng, giá trị của luồng sẽ là $N$. Hơn nữa, đối với mỗi đỉnh $i$ của đoạn đầu tiên, có chính xác một đỉnh $j$ của đoạn thứ hai, sao cho luồng $F_{ij}$ = 1. Cuối cùng, đây là sự tương ứng một-một giữa các đỉnh của đoạn đầu tiên và các đỉnh của phần thứ hai, là giải pháp cho bài toán (vì luồng tìm thấy có chi phí tối thiểu, thì tổng chi phí của các cạnh được chọn sẽ là thấp nhất có thể, là tiêu chí tối ưu).

Độ phức tạp của giải pháp này của bài toán gán phụ thuộc vào thuật toán mà theo đó việc tìm kiếm luồng tối đa có chi phí tối thiểu được thực hiện. Độ phức tạp sẽ là $\mathcal{O}(N^3)$ khi sử dụng [Dijkstra](dijkstra.md) hoặc $\mathcal{O}(N^4)$ khi sử dụng [Bellman-Ford](bellman_ford.md). Điều này là do luồng có kích thước $O(N)$ và mỗi lần lặp của thuật toán Dijkstra có thể được thực hiện trong $O(N^2)$, trong khi nó là $O(N^3)$ đối với Bellman-Ford.

## Triển khai

Việc triển khai được đưa ra ở đây khá dài, nó có thể được rút ngắn đáng kể.
Nó sử dụng [thuật toán SPFA](bellman_ford.md) để tìm đường đi ngắn nhất.

```cpp
const int INF = 1000 * 1000 * 1000;

vector<int> assignment(vector<vector<int>> a) {
    int n = a.size();
    int m = n * 2 + 2;
    vector<vector<int>> f(m, vector<int>(m));
    int s = m - 2, t = m - 1;
    int cost = 0;
    while (true) {
        vector<int> dist(m, INF);
        vector<int> p(m);
        vector<bool> inq(m, false);
        queue<int> q;
        dist[s] = 0;
        p[s] = -1;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            inq[v] = false;
            if (v == s) {
                for (int i = 0; i < n; ++i) {
                    if (f[s][i] == 0) {
                        dist[i] = 0;
                        p[i] = s;
                        inq[i] = true;
                        q.push(i);
                    }
                }
            } else {
                if (v < n) {
                    for (int j = n; j < n + n; ++j) {
                        if (f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n]) {
                            dist[j] = dist[v] + a[v][j - n];
                            p[j] = v;
                            if (!inq[j]) {
                                q.push(j);
                                inq[j] = true;
                            }
                        }
                    }
                } else {
                    for (int j = 0; j < n; ++j) {
                        if (f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n]) {
                            dist[j] = dist[v] - a[j][v - n];
                            p[j] = v;
                            if (!inq[j]) {
                                q.push(j);
                                inq[j] = true;
                            }
                        }
                    }
                }
            }
        }

        int curcost = INF;
        for (int i = n; i < n + n; ++i) {
            if (f[i][t] == 0 && dist[i] < curcost) {
                curcost = dist[i];
                p[t] = i;
            }
        }
        if (curcost == INF)
            break;
        cost += curcost;
        for (int cur = t; cur != -1; cur = p[cur]) {
            int prev = p[cur];
            if (prev != -1)
                f[cur][prev] = -(f[prev][cur] = 1);
        }
    }

    vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (f[i][j + n] == 1)
                answer[i] = j;
        }
    }
    return answer;
}
```

--- 



