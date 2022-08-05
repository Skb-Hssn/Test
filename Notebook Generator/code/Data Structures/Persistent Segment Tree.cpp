const int N = 1e5 + 5;
using ll = long long;

struct node {
  ll sum;
  int L, R;
  node(ll sum = 0, int L = -1, int R = -1){
    sum = sum, L = L, R = R;
  }
} t[N * 25];

int root[N];
int node_cnt;

void build(int rt, int l, int r){
  if(l == r) return void(t[rt] = node(0));
  int m = l + r >> 1;
  t[rt].L = ++node_cnt; t[rt].R = ++node_cnt;
  build(t[rt].L, l, m); build(t[rt].R, m + 1, r);
}

void update(int &rt, int l, int r, int pos, ll v){
  t[++node_cnt] = t[rt];
  t[rt = node_cnt].sum += v;
  if(l == r) return;
  int m = l + r >> 1;
  if(pos <= m) update(t[rt].L, l, m, pos, v);
  else update(t[rt].R, m + 1, r, pos, v);
}

// a = root[l - 1], b = root[r]
int lesscnt(int a, int b, int l, int r, int k){
  if(r <= k) return t[b].sum - t[a].sum;
  int m = l + r >> 1;
  if(k <= m) return lesscnt(t[a].L, t[b].L, l, m, k);
  return lesscnt(t[a].L, t[b].L, l, m, k) + 
         lesscnt(t[a].R, t[b].R, m + 1, r, k);
}

int kthnum(int a, int b, int l, int r, int k){
  if(l == r) return l;
  int m = l + r >> 1, lval = t[t[b].L].sum - t[t[a].L].sum;
  if(lval >= k) return kthnum(t[a].L, t[b].L, l, m, k);
  return kthnum(t[a].R, t[b].R, m + 1, r, k - lval);
}

int main() {
  //initialize : build with root[0]
  root[0] = ++node_cnt;
  build(root[0], 1, n);
  //When need to update -
  root[i] = root[i - 1];
  update(root[i]...);
}