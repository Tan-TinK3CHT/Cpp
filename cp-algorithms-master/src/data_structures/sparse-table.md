# Bảng thưa (Sparse Table)

---
tags:
  - Dịch
e_maxx_link: sprague_grundy
---

# Bảng thưa (Sparse Table)

Bảng thưa (Sparse Table) là một cấu trúc dữ liệu cho phép trả lời các truy vấn phạm vi.
Nó có thể trả lời hầu hết các truy vấn phạm vi trong $O(\log n)$, nhưng sức mạnh thực sự của nó là trả lời các truy vấn giá trị nhỏ nhất trong phạm vi (hoặc các truy vấn giá trị lớn nhất trong phạm vi tương đương).
Đối với những truy vấn đó, nó có thể tính toán câu trả lời trong thời gian $O(1)$.

Hạn chế duy nhất của cấu trúc dữ liệu này là nó chỉ có thể được sử dụng trên các mảng _bất biến_ (immutable).
Điều này có nghĩa là mảng không thể được thay đổi giữa hai truy vấn.
Nếu bất kỳ phần tử nào trong mảng thay đổi, toàn bộ cấu trúc dữ liệu phải được tính toán lại.

## Trực giác

Bất kỳ số không âm nào cũng có thể được biểu diễn duy nhất dưới dạng tổng của các lũy thừa giảm dần của hai.
Đây chỉ là một biến thể của biểu diễn nhị phân của một số.
Ví dụ: $13 = (1101)_2 = 8 + 4 + 1$.
Đối với một số $x$, có thể có nhiều nhất $\lceil \log_2 x \rceil$ số hạng.

Theo cùng một lý luận, bất kỳ khoảng nào cũng có thể được biểu diễn duy nhất dưới dạng hợp của các khoảng có độ dài là lũy thừa giảm dần của hai.
Ví dụ: $[2, 14] = [2, 9] \cup [10, 13] \cup [14, 14]$, trong đó toàn bộ khoảng có độ dài 13 và các khoảng riêng lẻ có độ dài lần lượt là 8, 4 và 1.
Và cũng ở đây, hợp bao gồm nhiều nhất $\lceil \log_2(\text{độ dài khoảng})\rceil$ khoảng.

Ý tưởng chính đằng sau Bảng thưa là tính toán trước tất cả các câu trả lời cho các truy vấn phạm vi với độ dài là lũy thừa của hai.
Sau đó, một truy vấn phạm vi khác có thể được trả lời bằng cách chia phạm vi thành các phạm vi có độ dài là lũy thừa của hai, tra cứu các câu trả lời được tính toán trước và kết hợp chúng để nhận được câu trả lời đầy đủ.

## Tính toán trước

Chúng ta sẽ sử dụng một mảng hai chiều để lưu trữ các câu trả lời cho các truy vấn được tính toán trước.
$\text{st}[i][j]$ sẽ lưu trữ câu trả lời cho phạm vi $[j, j + 2^i - 1]$ có độ dài $2^i$.
Kích thước của mảng hai chiều sẽ là $(K + 1) \times \text{MAXN}$, trong đó $\text{MAXN}$ là độ dài mảng lớn nhất có thể.
$\text{K}$ phải thỏa mãn $\text{K} \ge \lfloor \log_2 \text{MAXN} \rfloor$, vì $2^{\lfloor \log_2 \text{MAXN} \rfloor}$ là phạm vi lũy thừa của hai lớn nhất mà chúng ta phải hỗ trợ.
Đối với các mảng có độ dài hợp lý (tối đa $10^7$ phần tử), $K = 25$ là một giá trị tốt.

Chiều $\text{MAXN}$ đứng thứ hai để cho phép truy cập bộ nhớ liên tiếp (thân thiện với bộ nhớ đệm).

```{.cpp file=sparsetable_definition}
int st[K + 1][MAXN];
```

Vì phạm vi $[j, j + 2^i - 1]$ có độ dài $2^i$ được chia độc đáo thành các phạm vi $[j, j + 2^{i - 1} - 1]$ và $[j + 2^{i - 1}, j + 2^i - 1]$, cả hai đều có độ dài $2^{i - 1}$, chúng ta có thể tạo bảng một cách hiệu quả bằng cách sử dụng quy hoạch động:

```{.cpp file=sparsetable_generation}
std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
```

Hàm $f$ sẽ phụ thuộc vào loại truy vấn.
Đối với các truy vấn tổng phạm vi, nó sẽ tính tổng, đối với các truy vấn giá trị nhỏ nhất trong phạm vi, nó sẽ tính giá trị nhỏ nhất.

Độ phức tạp thời gian của việc tính toán trước là $O(\text{N} \log \text{N})$.

## Truy vấn tổng phạm vi

Đối với loại truy vấn này, chúng ta muốn tìm tổng của tất cả các giá trị trong một phạm vi.
Do đó, định nghĩa tự nhiên của hàm $f$ là $f(x, y) = x + y$.
Chúng ta có thể xây dựng cấu trúc dữ liệu với:

```{.cpp file=sparsetable_sum_generation}
long long st[K + 1][MAXN];

std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << (i - 1))];
```

Để trả lời truy vấn tổng cho phạm vi $[L, R]$, chúng ta lặp qua tất cả các lũy thừa của hai, bắt đầu từ lũy thừa lớn nhất.
Ngay sau khi lũy thừa của hai $2^i$ nhỏ hơn hoặc bằng độ dài của phạm vi ($= R - L + 1$), chúng ta xử lý phần đầu tiên của phạm vi $[L, L + 2^i - 1]$ và tiếp tục với phạm vi còn lại $[L + 2^i, R]$.

```{.cpp file=sparsetable_sum_query}
long long sum = 0;
for (int i = K; i >= 0; i--) {
    if ((1 << i) <= R - L + 1) {
        sum += st[i][L];
        L += 1 << i;
    }
}
```

Độ phức tạp thời gian cho Truy vấn tổng phạm vi là $O(K) = O(\log \text{MAXN})$.

## Truy vấn giá trị nhỏ nhất trong phạm vi (RMQ)

Đây là những truy vấn mà Bảng thưa tỏa sáng.
Khi tính toán giá trị nhỏ nhất của một phạm vi, không quan trọng chúng ta xử lý một giá trị trong phạm vi một hay hai lần.
Do đó, thay vì chia một phạm vi thành nhiều phạm vi, chúng ta cũng có thể chia phạm vi thành chỉ hai phạm vi chồng chéo với độ dài là lũy thừa của hai.
Ví dụ: chúng ta có thể chia phạm vi $[1, 6]$ thành các phạm vi $[1, 4]$ và $[3, 6]$.
Giá trị nhỏ nhất trong phạm vi của $[1, 6]$ rõ ràng giống với giá trị nhỏ nhất trong phạm vi của $[1, 4]$ và giá trị nhỏ nhất trong phạm vi của $[3, 6]$.
Vì vậy, chúng ta có thể tính toán giá trị nhỏ nhất của phạm vi $[L, R]$ bằng:

$$\min(\text{st}[i][L], \text{st}[i][R - 2^i + 1]) \quad \text{ trong đó } i = \log_2(R - L + 1)$$

Điều này yêu cầu chúng ta có thể tính toán $\log_2(R - L + 1)$ nhanh chóng.
Bạn có thể thực hiện điều đó bằng cách tính toán trước tất cả các logarit:

```{.cpp file=sparse_table_log_table}
int lg[MAXN+1];
lg[1] = 0;
for (int i = 2; i <= MAXN; i++)
    lg[i] = lg[i/2] + 1;
```
Ngoài ra, logarit có thể được tính toán nhanh chóng trong không gian và thời gian không đổi:
```c++
// C++20
#include <bit>
int log2_floor(unsigned long i) {
    return std::bit_width(i) - 1;
}

// trước C++20
int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}
```
[Điểm chuẩn này](https://quick-bench.com/q/Zghbdj_TEkmw4XG2nqOpD3tsJ8U) cho thấy rằng việc sử dụng mảng `lg` chậm hơn vì bộ nhớ đệm bị lỗi.

Sau đó, chúng ta cần tính toán trước cấu trúc Bảng thưa. Lần này chúng ta định nghĩa $f$ bằng $f(x, y) = \min(x, y)$.

```{.cpp file=sparse_table_minimum_generation}
int st[K + 1][MAXN];

std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
```

Và giá trị nhỏ nhất của một phạm vi $[L, R]$ có thể được tính toán bằng:

```{.cpp file=sparse_table_minimum_query}
int i = lg[R - L + 1];
int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);
```

Độ phức tạp thời gian cho Truy vấn giá trị nhỏ nhất trong phạm vi là $O(1)$.

## Cấu trúc dữ liệu tương tự hỗ trợ nhiều loại truy vấn hơn

Một trong những điểm yếu chính của cách tiếp cận $O(1)$ được thảo luận trong phần trước là cách tiếp cận này chỉ hỗ trợ các truy vấn của [hàm lũy đẳng](https://en.wikipedia.org/wiki/Idempotence).
Tức là nó hoạt động rất tốt cho các truy vấn giá trị nhỏ nhất trong phạm vi, nhưng không thể trả lời các truy vấn tổng phạm vi bằng cách sử dụng cách tiếp cận này.

Có các cấu trúc dữ liệu tương tự có thể xử lý bất kỳ loại hàm kết hợp nào và trả lời các truy vấn phạm vi trong $O(1)$.
Một trong số chúng được gọi là [Bảng thưa rời rạc](https://discuss.codechef.com/questions/117696/tutorial-disjoint-sparse-table).
Một cái khác sẽ là [Cây Sqrt](sqrt-tree.md).

## Bài tập thực hành

* [SPOJ - RMQSQ](http://www.spoj.com/problems/RMQSQ/)
* [SPOJ - THRBL](http://www.spoj.com/problems/THRBL/)
* [Codechef - MSTICK](https://www.codechef.com/problems/MSTICK)
* [Codechef - SEAD](https://www.codechef.com/problems/SEAD)
* [Codeforces - CGCDSSQ](http://codeforces.com/contest/475/problem/D)
* [Codeforces - R2D2 and Droid Army](http://codeforces.com/problemset/problem/514/D)
* [Codeforces - Maximum of Maximums of Minimums](http://codeforces.com/problemset/problem/872/B)
* [SPOJ - Miraculous](http://www.spoj.com/problems/TNVFC1M/)
* [DevSkill - Multiplication Interval (lưu trữ)](http://web.archive.org/web/20200922003506/https://devskill.com/CodingProblems/ViewProblem/19)
* [Codeforces - Animals and Puzzles](http://codeforces.com/contest/713/problem/D)
* [Codeforces - Trains and Statistics](http://codeforces.com/contest/675/problem/E)
* [SPOJ - Postering](http://www.spoj.com/problems/POSTERIN/)
* [SPOJ - Negative Score](http://www.spoj.com/problems/RPLN/)
* [SPOJ - A Famous City](http://www.spoj.com/problems/CITY2/)
* [SPOJ - Diferencija](http://www.spoj.com/problems/DIFERENC/)
* [Codeforces - Turn off the TV](http://codeforces.com/contest/863/problem/E)
* [Codeforces - Map](http://codeforces.com/contest/15/problem/D)
* [Codeforces - Awards for Contestants](http://codeforces.com/contest/873/problem/E)
* [Codeforces - Longest Regular Bracket Sequence](http://codeforces.com/contest/5/problem/C)
* [Codeforces - Array Stabilization (GCD version)](http://codeforces.com/problemset/problem/1547/F)


---

