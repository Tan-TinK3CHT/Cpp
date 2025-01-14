# Cây hậu tố. Thuật toán Ukkonen

*Bài viết này là một đoạn sơ khai và không chứa bất kỳ mô tả nào. Để biết mô tả về thuật toán, hãy tham khảo các nguồn khác, chẳng hạn như [Thuật toán trên Chuỗi, Cây và Chuỗi](https://www.cs.cmu.edu/afs/cs/project/pscico-guyb/realworld/www/slidesF06/cmuonly/gusfield.pdf) của Dan Gusfield.*

Thuật toán này xây dựng một cây hậu tố cho một chuỗi $s$ đã cho có độ dài $n$ trong thời gian $O(n\log(k)))$, trong đó $k$ là kích thước của bảng chữ cái (nếu $k$ được coi là một hằng số, thì hành vi tiệm cận là tuyến tính).

Đầu vào của thuật toán là chuỗi $s$ và độ dài $n$ của nó, được truyền dưới dạng biến toàn cục.

Hàm chính `build_tree` xây dựng cây hậu tố. Nó được lưu trữ dưới dạng một mảng các cấu trúc `node`, trong đó `node[0]` là gốc của cây.

Để đơn giản hóa mã, các cạnh được lưu trữ trong cùng một cấu trúc: đối với mỗi đỉnh, cấu trúc `node` của nó lưu trữ thông tin về cạnh giữa nó và cha của nó. Nhìn chung, mỗi `node` lưu trữ các thông tin sau:

* `(l, r)` - ranh giới trái và phải của chuỗi con `s[l..r-1]` tương ứng với cạnh đến nút này,
* `par` - nút cha,
* `link` - liên kết hậu tố,
* `next` - danh sách các cạnh đi ra từ nút này.

```cpp
string s;
int n;
 
struct node {
	int l, r, par, link;
	map<char,int> next;
 
	node (int l=0, int r=0, int par=-1)
		: l(l), r(r), par(par), link(-1) {}
	int len()  {  return r - l;  }
	int &get (char c) {
		if (!next.count(c))  next[c] = -1;
		return next[c];
	}
};
node t[MAXN];
int sz;
 
struct state {
	int v, pos;
	state (int v, int pos) : v(v), pos(pos)  {}
};
state ptr (0, 0);
 
state go (state st, int l, int r) {
	while (l < r)
		if (st.pos == t[st.v].len()) {
			st = state (t[st.v].get( s[l] ), 0);
			if (st.v == -1)  return st;
		}
		else {
			if (s[ t[st.v].l + st.pos ] != s[l])
				return state (-1, -1);
			if (r-l < t[st.v].len() - st.pos)
				return state (st.v, st.pos + r-l);
			l += t[st.v].len() - st.pos;
			st.pos = t[st.v].len();
		}
	return st;
}
 
int split (state st) {
	if (st.pos == t[st.v].len())
		return st.v;
	if (st.pos == 0)
		return t[st.v].par;
	node v = t[st.v];
	int id = sz++;
	t[id] = node (v.l, v.l+st.pos, v.par);
	t[v.par].get( s[v.l] ) = id;
	t[id].get( s[v.l+st.pos] ) = st.v;
	t[st.v].par = id;
	t[st.v].l += st.pos;
	return id;
}
 
int get_link (int v) {
	if (t[v].link != -1)  return t[v].link;
	if (t[v].par == -1)  return 0;
	int to = get_link (t[v].par);
	return t[v].link = split (go (state(to,t[to].len()), t[v].l + (t[v].par==0), t[v].r));
}
 
void tree_extend (int pos) {
	for(;;) {
		state nptr = go (ptr, pos, pos+1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
 
		int mid = split (ptr);
		int leaf = sz++;
		t[leaf] = node (pos, n, mid);
		t[mid].get( s[pos] ) = leaf;
 
		ptr.v = get_link (mid);
		ptr.pos = t[ptr.v].len();
		if (!mid)  break;
	}
}
 
void build_tree() {
	sz = 1;
	for (int i=0; i<n; ++i)
		tree_extend (i);
}
```

## Triển khai nén

Cách triển khai nén này được đề xuất bởi [freopen](http://codeforces.com/profile/freopen).

```cpp
const int N=1000000,INF=1000000000;
string a;
int t[N][26],l[N],r[N],p[N],s[N],tv,tp,ts,la;
 
void ukkadd (int c) {
	suff:;
	if (r[tv]<tp) {
		if (t[tv][c]==-1) { t[tv][c]=ts;  l[ts]=la;
			p[ts++]=tv;  tv=s[tv];  tp=r[tv]+1;  goto suff; }
		tv=t[tv][c]; tp=l[tv];
	}
	if (tp==-1 || c==a[tp]-'a') tp++; else {
		l[ts+1]=la;  p[ts+1]=ts;
		l[ts]=l[tv];  r[ts]=tp-1;  p[ts]=p[tv];  t[ts][c]=ts+1;  t[ts][a[tp]-'a']=tv;
		l[tv]=tp;  p[tv]=ts;  t[p[ts]][a[l[ts]]-'a']=ts;  ts+=2;
		tv=s[p[ts-2]];  tp=l[ts-2];
		while (tp<=r[ts-2]) {  tv=t[tv][a[tp]-'a'];  tp+=r[tv]-l[tv]+1;}
		if (tp==r[ts-2]+1)  s[ts-2]=tv;  else s[ts-2]=ts; 
		tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
	}
}
 
void build() {
	ts=2;
	tv=0;
	tp=0;
	fill(r,r+N,(int)a.size()-1);
	s[0]=1;
	l[0]=-1;
	r[0]=-1;
	l[1]=-1;
	r[1]=-1;
	memset (t, -1, sizeof t);
	fill(t[1],t[1]+26,0);
	for (la=0; la<(int)a.size(); ++la)
		ukkadd (a[la]-'a');
}
```

Cùng một mã với nhận xét:

```cpp
const int N=1000000,    // số nút tối đa có thể có trong cây hậu tố
	INF=1000000000; // hằng số vô cực
string a;       // chuỗi đầu vào mà cây hậu tố đang được xây dựng
int t[N][26],   // mảng các phép chuyển đổi (trạng thái, chữ cái)
	l[N],   // ranh giới trái...
	r[N],   // ...và phải của chuỗi con của a tương ứng với cạnh đến
	p[N],   // cha của nút
	s[N],   // liên kết hậu tố
	tv,     // nút của hậu tố hiện tại (nếu chúng ta đang ở giữa cạnh, thì là nút thấp hơn của cạnh)
	tp,     // vị trí trong chuỗi tương ứng với vị trí trên cạnh (giữa l[tv] và r[tv], bao gồm cả hai)
	ts,     // số lượng nút
	la;     // ký tự hiện tại trong chuỗi
 
void ukkadd(int c) { // thêm ký tự s vào cây
	suff:;      // chúng ta sẽ quay lại đây sau mỗi lần chuyển đổi sang hậu tố (và sẽ thêm ký tự một lần nữa)
	if (r[tv]<tp) { // kiểm tra xem chúng ta có còn nằm trong ranh giới của cạnh hiện tại hay không
		// nếu không, hãy tìm cạnh tiếp theo. Nếu nó không tồn tại, hãy tạo một lá và thêm nó vào cây
		if (t[tv][c]==-1) {t[tv][c]=ts;l[ts]=la;p[ts++]=tv;tv=s[tv];tp=r[tv]+1;goto suff;}
		tv=t[tv][c];tp=l[tv];
	} // ngược lại, chỉ cần tiến hành đến cạnh tiếp theo
	if (tp==-1 || c==a[tp]-'a')
		tp++; // nếu chữ cái trên cạnh bằng c, hãy đi xuống cạnh đó
	else { 
		// ngược lại, chia cạnh thành hai với điểm giữa là nút ts
		l[ts]=l[tv];r[ts]=tp-1;p[ts]=p[tv];t[ts][a[tp]-'a']=tv;
		// thêm lá ts+1. Nó tương ứng với chuyển tiếp qua c.
		t[ts][c]=ts+1;l[ts+1]=la;p[ts+1]=ts;
		// cập nhật thông tin cho nút hiện tại - nhớ đánh dấu ts là cha của tv
		l[tv]=tp;p[tv]=ts;t[p[ts]][a[l[ts]]-'a']=ts;ts+=2;
		// chuẩn bị cho việc đi xuống
		// tp sẽ đánh dấu vị trí của chúng ta trong hậu tố hiện tại
		tv=s[p[ts-2]];tp=l[ts-2];
		// trong khi hậu tố hiện tại chưa kết thúc, hãy đi xuống
		while (tp<=r[ts-2]) {tv=t[tv][a[tp]-'a'];tp+=r[tv]-l[tv]+1;}
		// nếu chúng ta đang ở trong một nút, hãy thêm liên kết hậu tố vào đó, ngược lại hãy thêm liên kết vào ts
		// (chúng ta sẽ tạo ts trong lần lặp tiếp theo).
		if (tp==r[ts-2]+1) s[ts-2]=tv; else s[ts-2]=ts; 
		// thêm tp vào cạnh mới và quay lại để thêm chữ cái vào hậu tố
		tp=r[tv]-(tp-r[ts-2])+2;goto suff;
	}
}
 
void build() {
	ts=2;
	tv=0;
	tp=0;
	fill(r,r+N,(int)a.size()-1);
	// khởi tạo dữ liệu cho gốc của cây
	s[0]=1;
	l[0]=-1;
	r[0]=-1;
	l[1]=-1;
	r[1]=-1;
	memset (t, -1, sizeof t);
	fill(t[1],t[1]+26,0);
	// thêm văn bản vào cây, từng chữ cái một
	for (la=0; la<(int)a.size(); ++la)
		ukkadd (a[la]-'a');
}
```

## Bài tập thực hành

* [UVA 10679 - I Love Strings!!!](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620)

--- 
