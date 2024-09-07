# Thuật toán Floyd-Warshall

---
tags:
  - Dịch
e_maxx_link: floyd_warshall_algorithm
---

# Thuật toán Floyd-Warshall

Cho một đồ thị có trọng số có hướng hoặc vô hướng $G$ với $n$ đỉnh.
Nhiệm vụ là tìm độ dài của đường đi ngắn nhất $d_{ij}$ giữa mỗi cặp đỉnh $i$ và $j$.

Đồ thị có thể có các cạnh có trọng số âm, nhưng không có chu trình có trọng số âm.

Nếu có một chu trình âm như vậy, bạn có thể chỉ cần đi qua chu trình này lặp đi lặp lại, trong mỗi lần lặp lại, làm cho chi phí của đường đi nhỏ hơn.
Vì vậy, bạn có thể làm cho các đường dẫn nhất định nhỏ tùy ý, hoặc nói cách khác là đường dẫn ngắn nhất không xác định.
Điều đó tự động có nghĩa là một đồ thị vô hướng không thể có bất kỳ cạnh nào có trọng số âm, vì một cạnh như vậy đã tạo thành một chu trình âm vì bạn có thể di chuyển qua lại dọc theo cạnh đó bao lâu tùy thích.

Thuật toán này cũng có thể được sử dụng để phát hiện sự hiện diện của các chu trình âm.
Đồ thị có chu trình âm nếu ở cuối thuật toán, khoảng cách từ một đỉnh $v$ đến chính nó là âm.

Thuật toán này đã được xuất bản đồng thời trong các bài báo của Robert Floyd và Stephen Warshall vào năm 1962.
Tuy nhiên, vào năm 1959, Bernard Roy đã xuất bản về cơ bản là cùng một thuật toán, nhưng ấn phẩm của ông đã không được chú ý.

## Mô tả thuật toán

Ý tưởng chính của thuật toán là phân vùng quá trình tìm đường đi ngắn nhất giữa hai đỉnh bất kỳ thành một số giai đoạn tăng dần.

Hãy đánh số các đỉnh bắt đầu từ 1 đến $n$.
Ma trận khoảng cách là $d[ ][ ]$.

Trước giai đoạn thứ $k$ ($k = 1 \dots n$), $d[i][j]$ cho bất kỳ đỉnh $i$ và $j$ nào lưu trữ độ dài của đường đi ngắn nhất giữa đỉnh $i$ và đỉnh $j$, chỉ chứa các đỉnh $\{1, 2, ..., k-1\}$ làm đỉnh bên trong trong đường dẫn.

Nói cách khác, trước giai đoạn thứ $k$, giá trị của $d[i][j]$ bằng với độ dài của đường đi ngắn nhất từ ​​đỉnh $i$ đến đỉnh $j$, nếu đường đi này chỉ được phép đi vào đỉnh có số nhỏ hơn $k$ (điểm đầu và điểm cuối của đường đi không bị hạn chế bởi thuộc tính này).

Rất dễ dàng để đảm bảo rằng thuộc tính này giữ cho giai đoạn đầu tiên. Đối với $k = 0$, chúng ta có thể điền vào ma trận với $d[i][j] = w_{i j}$ nếu tồn tại một cạnh giữa $i$ và $j$ với trọng số $w_{i j}$ và $d[i][j] = \infty$ nếu không tồn tại một cạnh.
Trong thực tế, $\infty$ sẽ là một số giá trị cao.
Như chúng ta sẽ thấy sau, đây là một yêu cầu đối với thuật toán.

Giả sử bây giờ chúng ta đang ở giai đoạn thứ $k$ và chúng ta muốn tính toán ma trận $d[ ][ ]$ sao cho nó đáp ứng các yêu cầu cho giai đoạn thứ $(k + 1)$.
Chúng ta phải sửa khoảng cách cho một số cặp đỉnh $(i, j)$.
Có hai trường hợp khác nhau cơ bản:

*   Đường đi ngắn nhất từ ​​đỉnh $i$ đến đỉnh $j$ với các đỉnh bên trong từ tập hợp $\{1, 2, \dots, k\}$ trùng với đường đi ngắn nhất với các đỉnh bên trong từ tập hợp $\{1, 2, \dots, k-1\}$.

    Trong trường hợp này, $d[i][j]$ sẽ không thay đổi trong quá trình chuyển đổi.

*   Đường dẫn ngắn nhất với các đỉnh bên trong từ $\{1, 2, \dots, k\}$ ngắn hơn.

    Điều này có nghĩa là đường dẫn mới, ngắn hơn đi qua đỉnh $k$.
    Điều này có nghĩa là chúng ta có thể chia đường đi ngắn nhất giữa $i$ và $j$ thành hai đường đi:
    đường đi giữa $i$ và $k$, và đường đi giữa $k$ và $j$.
    Rõ ràng là cả hai đường đi này chỉ sử dụng các đỉnh bên trong của $\{1, 2, \dots, k-1\}$ và là những đường đi ngắn nhất như vậy về mặt đó.
    Do đó, chúng ta đã tính toán độ dài của các đường dẫn đó trước đó và chúng ta có thể tính toán độ dài của đường đi ngắn nhất giữa $i$ và $j$ là $d[i][k] + d[k][j]$.

Kết hợp hai trường hợp này, chúng ta thấy rằng chúng ta có thể tính toán lại độ dài của tất cả các cặp $(i, j)$ trong giai đoạn thứ $k$ theo cách sau:

$$d_{\text{new}}[i][j] = min(d[i][j], d[i][k] + d[k][j])$$

Do đó, tất cả công việc cần thiết trong giai đoạn thứ $k$ là lặp lại tất cả các cặp đỉnh và tính toán lại độ dài của đường đi ngắn nhất giữa chúng.
Kết quả là, sau giai đoạn thứ $n$, giá trị $d[i][j]$ trong ma trận khoảng cách là độ dài của đường đi ngắn nhất giữa $i$ và $j$, hoặc là $\infty$ nếu đường đi giữa các đỉnh $i$ và $j$ không tồn tại.

Nhận xét cuối cùng - chúng ta không cần tạo một ma trận khoảng cách riêng $d_{\text{new}}[ ][ ]$ để tạm thời lưu trữ các đường đi ngắn nhất của giai đoạn thứ $k$, tức là tất cả các thay đổi có thể được thực hiện trực tiếp trong ma trận $d[ ][ ]$ ở bất kỳ giai đoạn nào.
Trên thực tế, ở bất kỳ giai đoạn thứ $k$ nào, chúng ta đang cải thiện nhiều nhất khoảng cách của bất kỳ đường dẫn nào trong ma trận khoảng cách, do đó chúng ta không thể làm xấu đi độ dài của đường dẫn ngắn nhất cho bất kỳ cặp đỉnh nào sẽ được xử lý trong giai đoạn thứ $(k+1)$ hoặc sau đó.

Độ phức tạp thời gian của thuật toán này rõ ràng là $O(n^3)$.

## Triển khai

Cho $d[][]$ là một mảng 2D có kích thước $n \times n$, được điền theo giai đoạn thứ $0$ như đã giải thích trước đó.
Ngoài ra, chúng ta sẽ đặt $d[i][i] = 0$ cho bất kỳ $i$ nào ở giai đoạn thứ $0$.

Sau đó, thuật toán được triển khai như sau:

```cpp
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}
```

Giả định rằng nếu không có cạnh nào giữa hai đỉnh $i$ và $j$ bất kỳ, thì ma trận tại $d[i][j]$ chứa một số lớn (đủ lớn để nó lớn hơn độ dài của bất kỳ đường dẫn nào trong đồ thị này).
Khi đó, cạnh này sẽ luôn không có lợi để đi và thuật toán sẽ hoạt động chính xác.

Tuy nhiên, nếu có các cạnh có trọng số âm trong đồ thị, thì phải thực hiện các biện pháp đặc biệt.
Nếu không, các giá trị kết quả trong ma trận có thể có dạng $\infty - 1$,  $\infty - 2$, v.v., điều này, tất nhiên, vẫn chỉ ra rằng giữa các đỉnh tương ứng không tồn tại đường đi.
Do đó, nếu đồ thị có các cạnh có trọng số âm, thì tốt hơn hết là viết thuật toán Floyd-Warshall theo cách sau, để nó không thực hiện chuyển đổi bằng cách sử dụng các đường dẫn không tồn tại.

```cpp
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}
```

## Khôi phục chuỗi các đỉnh trong đường đi ngắn nhất

Rất dễ dàng để duy trì thông tin bổ sung mà với thông tin đó, có thể truy xuất đường đi ngắn nhất giữa hai đỉnh nhất định bất kỳ dưới dạng chuỗi các đỉnh.

Đối với điều này, ngoài ma trận khoảng cách $d[ ][ ]$, ma trận tổ tiên $p[ ][ ]$ phải được duy trì, ma trận này sẽ chứa số của giai đoạn mà khoảng cách ngắn nhất giữa hai đỉnh được sửa đổi lần cuối.
Rõ ràng là số của giai đoạn không gì khác hơn là một đỉnh ở giữa đường đi ngắn nhất mong muốn.
Bây giờ chúng ta chỉ cần tìm đường đi ngắn nhất giữa các đỉnh $i$ và $p[i][j]$ và giữa $p[i][j]$ và $j$.
Điều này dẫn đến một thuật toán tái tạo đệ quy đơn giản của đường đi ngắn nhất.

## Trường hợp trọng số thực

Nếu trọng số của các cạnh không phải là số nguyên mà là số thực, thì cần phải tính đến các lỗi xảy ra khi làm việc với các kiểu dấu phẩy động.

Thuật toán Floyd-Warshall có tác dụng khó chịu là các lỗi tích lũy rất nhanh.
Trên thực tế, nếu có lỗi trong giai đoạn đầu tiên là $\delta$, lỗi này có thể lan truyền sang lần lặp thứ hai là $2 \delta$, sang lần lặp thứ ba là $4 \delta$, v.v.

Để tránh điều này, thuật toán có thể được sửa đổi để tính đến lỗi (EPS = $\delta$) bằng cách sử dụng so sánh sau:

```cpp
if (d[i][k] + d[k][j] < d[i][j] - EPS)
    d[i][j] = d[i][k] + d[k][j]; 
```

## Trường hợp chu trình âm

Về mặt hình thức, thuật toán Floyd-Warshall không áp dụng cho các đồ thị chứa chu trình có trọng số âm.
Nhưng đối với tất cả các cặp đỉnh $i$ và $j$ mà không tồn tại đường dẫn bắt đầu từ $i$, đi qua chu trình âm và kết thúc tại $j$, thuật toán vẫn hoạt động chính xác.

Đối với cặp đỉnh mà câu trả lời không tồn tại (do sự hiện diện của chu trình âm trong đường dẫn giữa chúng), thuật toán Floyd sẽ lưu trữ bất kỳ số nào (có thể rất âm, nhưng không nhất thiết) trong ma trận khoảng cách.
Tuy nhiên, có thể cải thiện thuật toán Floyd-Warshall, sao cho nó xử lý cẩn thận các cặp đỉnh như vậy và xuất ra chúng, ví dụ như $-\text{INF}$.

Điều này có thể được thực hiện theo cách sau:
hãy chạy thuật toán Floyd-Warshall thông thường cho một đồ thị nhất định.
Khi đó, đường đi ngắn nhất giữa các đỉnh $i$ và $j$ không tồn tại, nếu và chỉ khi, có một đỉnh $t$ có thể đạt được từ $i$ và cũng từ $j$, mà $d[t][t] < 0$.

Ngoài ra, khi sử dụng thuật toán Floyd-Warshall cho các đồ thị có chu trình âm, chúng ta nên nhớ rằng có thể phát sinh các tình huống mà khoảng cách có thể nhanh chóng chuyển sang âm theo cấp số nhân.
Do đó, tràn số nguyên phải được xử lý bằng cách giới hạn khoảng cách tối thiểu bằng một số giá trị (ví dụ: $-\text{INF}$).

Để tìm hiểu thêm về cách tìm chu trình âm trong đồ thị, hãy xem bài viết riêng [Tìm chu trình âm trong đồ thị](finding-negative-cycle-in-graph.md).

## Bài tập thực hành
 - [UVA: Page Hopping](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=762)
 - [SPOJ: Possible Friends](http://www.spoj.com/problems/SOCIALNE/)
 - [CODEFORCES: Greg and Graph](http://codeforces.com/problemset/problem/295/B)
 - [SPOJ: CHICAGO - 106 miles to Chicago](http://www.spoj.com/problems/CHICAGO/)
 * [UVA 10724 - Road Construction](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1665)
 * [UVA  117 - The Postal Worker Rings Once](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=53)
 * [Codeforces - Traveling Graph](http://codeforces.com/problemset/problem/21/D)
 * [UVA - 1198 - The Geodetic Set Problem](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3639)
 * [UVA - 10048 - Audiophobia](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=989)
 * [UVA - 125 - Numbering Paths](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=61)
 * [LOJ - Travel Company](http://lightoj.com/volume_showproblem.php?problem=1221)
 * [UVA 423 - MPI Maelstrom](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=364)
 * [UVA 1416 - Warfare And Logistics](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4162)
 * [UVA 1233 - USHER](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3674)
 * [UVA 10793 - The Orc Attack](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1734)
 * [UVA 10099 The Tourist Guide](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1040)
 * [UVA 869 - Airline Comparison](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=810)
 * [UVA 13211 - Geonosis](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5134)
 * [SPOJ - Defend the Rohan](http://www.spoj.com/problems/ROHAAN/)
 * [Codeforces - Roads in Berland](http://codeforces.com/contest/25/problem/C)
 * [Codeforces - String Problem](http://codeforces.com/contest/33/problem/B)
 * [GYM - Manic Moving (C)](http://codeforces.com/gym/101223)
 * [SPOJ - Arbitrage](http://www.spoj.com/problems/ARBITRAG/)
 * [UVA - 12179 - Randomly-priced Tickets](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3331)
 * [LOJ - 1086 - Jogging Trails](http://lightoj.com/volume_showproblem.php?problem=1086)
 * [SPOJ - Ingredients](http://www.spoj.com/problems/INGRED/)
 * [CSES - Shortest Routes II](https://cses.fi/problemset/task/1672)

--- 


