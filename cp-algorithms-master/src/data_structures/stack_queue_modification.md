--- START OF FILE stack_queue_modification.md ---

---
tags:
  - Đã dịch
e_maxx_link: stacks_for_minima
---

# Stack tối thiểu / Queue tối thiểu

Trong bài viết này, chúng ta sẽ xem xét ba vấn đề:
đầu tiên, chúng ta sẽ sửa đổi một stack theo cách cho phép chúng ta tìm phần tử nhỏ nhất của stack trong $O(1)$, sau đó chúng ta sẽ làm điều tương tự với queue và cuối cùng chúng ta sẽ sử dụng các cấu trúc dữ liệu này để tìm giá trị nhỏ nhất trong tất cả các mảng con có độ dài cố định trong một mảng trong $O(n)$.

## Sửa đổi stack

Chúng ta muốn sửa đổi cấu trúc dữ liệu stack sao cho có thể tìm thấy phần tử nhỏ nhất trong stack trong thời gian $O(1)$, trong khi vẫn duy trì hành vi tiệm cận giống nhau để thêm và xóa các phần tử khỏi stack.
Nhắc lại nhanh, trên stack, chúng ta chỉ thêm và xóa các phần tử ở một đầu.

Để làm điều này, chúng ta sẽ không chỉ lưu trữ các phần tử trong stack, mà chúng ta sẽ lưu trữ chúng theo cặp: chính phần tử đó và giá trị nhỏ nhất trong stack bắt đầu từ phần tử này trở xuống.

```cpp
stack<pair<int, int>> st;
```

Rõ ràng là việc tìm giá trị nhỏ nhất trong toàn bộ stack chỉ bao gồm việc xem xét giá trị `stack.top().second`.

Rõ ràng là việc thêm hoặc xóa một phần tử mới vào stack có thể được thực hiện trong thời gian không đổi.

Triển khai:

* Thêm một phần tử:
```cpp
int new_min = st.empty() ? new_elem : min(new_elem, st.top().second);
st.push({new_elem, new_min});
```

* Xóa một phần tử:
```cpp
int removed_element = st.top().first;
st.pop();
```

* Tìm giá trị nhỏ nhất:
```cpp
int minimum = st.top().second;
```

## Sửa đổi queue (phương pháp 1)

Bây giờ chúng ta muốn đạt được các thao tác tương tự với một queue, tức là chúng ta muốn thêm các phần tử ở cuối và xóa chúng khỏi đầu.

Ở đây chúng ta xem xét một phương pháp đơn giản để sửa đổi queue.
Tuy nhiên, nó có một nhược điểm lớn, bởi vì queue đã sửa đổi sẽ thực sự không lưu trữ tất cả các phần tử.

Ý tưởng chính là chỉ lưu trữ các mục trong queue cần thiết để xác định giá trị nhỏ nhất.
Cụ thể, chúng ta sẽ giữ queue theo thứ tự không giảm (tức là giá trị nhỏ nhất sẽ được lưu trữ ở đầu), và tất nhiên không phải theo bất kỳ cách tùy ý nào, giá trị nhỏ nhất thực tế phải luôn được chứa trong queue.
Bằng cách này, phần tử nhỏ nhất sẽ luôn ở đầu queue.
Trước khi thêm một phần tử mới vào queue, chúng ta chỉ cần thực hiện "cắt":
chúng ta sẽ xóa tất cả các phần tử ở cuối queue lớn hơn phần tử mới và sau đó thêm phần tử mới vào queue.
Bằng cách này, chúng ta không phá vỡ thứ tự của queue và chúng ta cũng sẽ không mất phần tử hiện tại nếu nó là giá trị nhỏ nhất ở bất kỳ bước tiếp theo nào.
Tất cả các phần tử mà chúng ta đã xóa không bao giờ có thể là giá trị nhỏ nhất, vì vậy thao tác này được phép.
Khi chúng ta muốn trích xuất một phần tử từ đầu, nó thực sự có thể không có ở đó (vì chúng ta đã xóa nó trước đó trong khi thêm một phần tử nhỏ hơn).
Do đó, khi xóa một phần tử khỏi queue, chúng ta cần biết giá trị của phần tử đó.
Nếu đầu queue có cùng giá trị, chúng ta có thể xóa nó một cách an toàn, nếu không thì chúng ta không làm gì cả.

Hãy xem xét các triển khai của các thao tác trên:

```cpp
deque<int> q;
```

* Tìm giá trị nhỏ nhất:
```cpp
int minimum = q.front();
```

* Thêm một phần tử:
```cpp
while (!q.empty() && q.back() > new_element)
    q.pop_back();
q.push_back(new_element);
```

* Xóa một phần tử:
```cpp
if (!q.empty() && q.front() == remove_element)
    q.pop_front();
```

Rõ ràng là trung bình tất cả các thao tác này chỉ mất thời gian $O(1)$ (vì mọi phần tử chỉ có thể được đẩy và bật ra một lần).

## Sửa đổi queue (phương pháp 2)

Đây là một sửa đổi của phương pháp 1.
Chúng ta muốn có thể xóa các phần tử mà không cần biết phần tử nào chúng ta phải xóa.
Chúng ta có thể thực hiện điều đó bằng cách lưu trữ chỉ mục cho mỗi phần tử trong queue.
Và chúng ta cũng nhớ xem chúng ta đã thêm và xóa bao nhiêu phần tử.

```cpp
deque<pair<int, int>> q;
int cnt_added = 0;
int cnt_removed = 0;
```

* Tìm giá trị nhỏ nhất:
```cpp
int minimum = q.front().first;
```

* Thêm một phần tử:
```cpp
while (!q.empty() && q.back().first > new_element)
    q.pop_back();
q.push_back({new_element, cnt_added});
cnt_added++;
```

* Xóa một phần tử:
```cpp
if (!q.empty() && q.front().second == cnt_removed) 
    q.pop_front();
cnt_removed++;
```

## Sửa đổi queue (phương pháp 3)

Ở đây chúng ta xem xét một cách khác để sửa đổi queue để tìm giá trị nhỏ nhất trong $O(1)$.
Cách này hơi phức tạp hơn để triển khai, nhưng lần này chúng ta thực sự lưu trữ tất cả các phần tử.
Và chúng ta cũng có thể xóa một phần tử khỏi đầu mà không cần biết giá trị của nó.

Ý tưởng là giảm bài toán thành bài toán stack, bài toán đã được chúng ta giải quyết.
Vì vậy, chúng ta chỉ cần học cách mô phỏng một queue bằng cách sử dụng hai stack.

Chúng ta tạo hai stack, `s1` và `s2`.
Tất nhiên, các stack này sẽ ở dạng đã sửa đổi, để chúng ta có thể tìm giá trị nhỏ nhất trong $O(1)$.
Chúng ta sẽ thêm các phần tử mới vào stack `s1` và xóa các phần tử khỏi stack `s2`.
Nếu tại bất kỳ thời điểm nào stack `s2` trống, chúng ta sẽ di chuyển tất cả các phần tử từ `s1` sang `s2` (về cơ bản là đảo ngược thứ tự của các phần tử đó).
Cuối cùng, việc tìm giá trị nhỏ nhất trong queue chỉ bao gồm việc tìm giá trị nhỏ nhất của cả hai stack.

Do đó, chúng ta thực hiện tất cả các thao tác trong $O(1)$ trung bình (mỗi phần tử sẽ được thêm một lần vào stack `s1`, được chuyển một lần sang `s2` và được bật ra một lần khỏi `s2`).

Triển khai:

```cpp
stack<pair<int, int>> s1, s2;
```

* Tìm giá trị nhỏ nhất:
```cpp
if (s1.empty() || s2.empty()) 
    minimum = s1.empty() ? s2.top().second : s1.top().second;
else
    minimum = min(s1.top().second, s2.top().second);
```

* Thêm phần tử:
```cpp
int minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
s1.push({new_element, minimum});
```

* Xóa một phần tử:
```cpp
if (s2.empty()) {
    while (!s1.empty()) {
        int element = s1.top().first;
        s1.pop();
        int minimum = s2.empty() ? element : min(element, s2.top().second);
        s2.push({element, minimum});
    }
}
int remove_element = s2.top().first;
s2.pop();
```

## Tìm giá trị nhỏ nhất cho tất cả các mảng con có độ dài cố định

Giả sử chúng ta được cung cấp một mảng $A$ có độ dài $N$ và một $M \le N$ nhất định.
Chúng ta phải tìm giá trị nhỏ nhất của mỗi mảng con có độ dài $M$ trong mảng này, tức là chúng ta phải tìm:

$$\min_{0 \le i \le M-1} A[i], \min_{1 \le i \le M} A[i], \min_{2 \le i \le M+1} A[i],~\dots~, \min_{N-M \le i \le N-1} A[i]$$

Chúng ta phải giải quyết vấn đề này trong thời gian tuyến tính, tức là $O(n)$.

Chúng ta có thể sử dụng bất kỳ trong ba queue đã sửa đổi để giải quyết vấn đề.
Các giải pháp sẽ rõ ràng:
chúng ta thêm $M$ phần tử đầu tiên của mảng, tìm và xuất ra giá trị nhỏ nhất của nó, sau đó thêm phần tử tiếp theo vào queue và xóa phần tử đầu tiên của mảng, tìm và xuất ra giá trị nhỏ nhất của nó, v.v.
Vì tất cả các thao tác với queue được thực hiện trong thời gian không đổi trung bình, nên độ phức tạp của toàn bộ thuật toán sẽ là $O(n)$.

## Bài tập thực hành
* [Queries with Fixed Length](https://www.hackerrank.com/challenges/queries-with-fixed-length/problem)
* [Binary Land](https://www.codechef.com/MAY20A/problems/BINLAND)

