# Tìm giao điểm của hai đoạn thẳng (Finding intersection of two segments)

---
tags:
  - Dịch
e_maxx_link: segments_intersection
---

# Tìm giao điểm của hai đoạn thẳng

Bạn được cho hai đoạn thẳng AB và CD, được mô tả dưới dạng cặp điểm cuối của chúng. Mỗi đoạn thẳng có thể là một điểm duy nhất nếu các điểm cuối của nó giống nhau.
Bạn phải tìm giao điểm của các đoạn thẳng này, có thể trống (nếu các đoạn thẳng không giao nhau), một điểm duy nhất hoặc một đoạn thẳng (nếu các đoạn thẳng đã cho trùng nhau).

## Giải pháp

Chúng ta có thể tìm điểm giao nhau của các đoạn thẳng theo cách tương tự như [giao điểm của các đường thẳng](lines-intersection.md):
xây dựng lại phương trình đường thẳng từ các điểm cuối của đoạn thẳng và kiểm tra xem chúng có song song hay không.

Nếu các đường thẳng không song song, chúng ta cần tìm điểm giao nhau của chúng và kiểm tra xem nó có thuộc cả hai đoạn thẳng hay không
(để làm điều này, chỉ cần xác minh rằng điểm giao nhau thuộc về mỗi đoạn thẳng được chiếu trên trục X và Y).
Trong trường hợp này, câu trả lời sẽ là "không giao nhau" hoặc điểm giao nhau duy nhất của các đường thẳng.

Trường hợp các đường thẳng song song phức tạp hơn một chút (trường hợp một hoặc nhiều đoạn thẳng là một điểm duy nhất cũng thuộc về trường hợp này).
Trong trường hợp này, chúng ta cần kiểm tra xem cả hai đoạn thẳng có thuộc cùng một đường thẳng hay không.
Nếu không, câu trả lời là "không giao nhau".
Nếu có, câu trả lời là giao điểm của các đoạn thẳng thuộc cùng một đường thẳng, thu được bằng cách
sắp xếp các điểm cuối của cả hai đoạn thẳng theo thứ tự tăng dần của tọa độ nhất định và lấy điểm cuối bên phải nhất của các điểm cuối bên trái và điểm cuối bên trái nhất của các điểm cuối bên phải.

Nếu cả hai đoạn thẳng là các điểm đơn lẻ, thì các điểm này phải giống hệt nhau và việc thực hiện kiểm tra này riêng biệt là hợp lý.

Ở đầu thuật toán, hãy thêm một kiểm tra hộp giới hạn - điều này là cần thiết cho trường hợp khi các đoạn thẳng thuộc cùng một đường thẳng,
và (là một kiểm tra nhẹ) nó cho phép thuật toán hoạt động nhanh hơn trung bình trên các bài kiểm tra ngẫu nhiên.


## Triển khai

Dưới đây là cách triển khai, bao gồm tất cả các hàm trợ giúp để xử lý đường thẳng và đoạn thẳng.

Hàm chính `intersect` trả về true nếu các đoạn thẳng có giao điểm khác rỗng,
và lưu trữ các điểm cuối của đoạn thẳng giao nhau trong các đối số `left` và `right`.
Nếu câu trả lời là một điểm duy nhất, các giá trị được ghi vào `left` và `right` sẽ giống nhau.

```{.cpp file=segment_intersection}
const double EPS = 1E-9;

struct pt {
    double x, y;

    bool operator<(const pt& p) const
    {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }
};

struct line {
    double a, b, c;

    line() {}
    line(pt p, pt q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(pt p) const { return a * p.x + b * p.y + c; }
};

double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

inline bool betw(double l, double r, double x)
{
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

bool intersect(pt a, pt b, pt c, pt d, pt& left, pt& right)
{
    if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
        return false;
    line m(a, b);
    line n(c, d);
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS) {
        if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
            return false;
        if (b < a)
            swap(a, b);
        if (d < c)
            swap(c, d);
        left = max(a, c);
        right = min(b, d);
        return true;
    } else {
        left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
        left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
        return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
               betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
    }
}
```

--- 
