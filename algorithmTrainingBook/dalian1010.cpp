#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cfloat>

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <functional>
#include <string>
#define EXP 1e-9
#define LL long long
#define PB push_back
#define N 100010

using namespace std;

#include <iostream>
using namespace std;


#define MAXN 100010
struct Node{
    int key, sz, cnt;
    Node *ch[2], *pnt;//左右儿子和父亲
    Node(){}
    Node(int x, int y, int z){
        key = x, sz = y, cnt = z;
    }
    void rs(){
        sz = ch[0]->sz + ch[1]->sz + cnt;
    }
}nil(0, 0, 0), *NIL = &nil;
struct Splay{//伸展树结构体类型
    Node *root;
    int ncnt;//计算key值不同的结点数，注意已经去重了
    Node nod[MAXN];
    void init(){// 首先要初始化
        root = NIL;
        ncnt = 0;
    }
    void rotate(Node *x, bool d){//旋转操作，d为true表示右旋
        Node *y = x->pnt;
        y->ch[!d] = x->ch[d];
        if (x->ch[d] != NIL)
            x->ch[d]->pnt = y;
        x->pnt = y->pnt;
        if (y->pnt != NIL){
            if (y == y->pnt->ch[d])
                y->pnt->ch[d] = x;
            else
                y->pnt->ch[!d] = x;
        }
        x->ch[d] = y;
        y->pnt = x;
        y->rs();
        x->rs();
    }
    void splay(Node *x, Node *target){//将x伸展到target的儿子位置处
        Node *y;
        while (x->pnt != target){
            y = x->pnt;
            if (x == y->ch[0]){
                if (y->pnt != target && y == y->pnt->ch[0])
                    rotate(y, true);
                rotate(x, true);
            }
            else{
                if (y->pnt != target && y == y->pnt->ch[1])
                    rotate(y, false);
                rotate(x, false);
            }
        }
        if (target == NIL)
            root = x;
    }
    /************************以上一般不用修改************************/
    void insert(int key){//插入一个值
        if (root == NIL){
            ncnt = 0;
            root = &nod[++ncnt];
            root->ch[0] = root->ch[1] = root->pnt = NIL;
            root->key = key;
            root->sz = root->cnt = 1;
            return;
        }
        Node *x = root, *y;
        while (1){
            x->sz++;
            if (key == x->key){
                x->cnt++;
                x->rs();
                y = x;
                break;
            }
            else if (key < x->key){
                if (x->ch[0] != NIL)
                    x = x->ch[0];
                else{
                    x->ch[0] = &nod[++ncnt];
                    y = x->ch[0];
                    y->key = key;
                    y->sz = y->cnt = 1;
                    y->ch[0] = y->ch[1] = NIL;
                    y->pnt = x;
                    break;
                }
            }
            else{
                if (x->ch[1] != NIL)
                    x = x->ch[1];
                else{
                    x->ch[1] = &nod[++ncnt];
                    y = x->ch[1];
                    y->key = key;
                    y->sz = y->cnt = 1;
                    y->ch[0] = y->ch[1] = NIL;
                    y->pnt = x;
                    break;
                }
            }
        }
        splay(y, NIL);
    }
    Node* search(int key){//查找一个值，返回指针
        if (root == NIL)
            return NIL;
        Node *x = root, *y = NIL;
        while (1){
            if (key == x->key){
                y = x;
                break;
            }
            else if (key > x->key){
                if (x->ch[1] != NIL)
                    x = x->ch[1];
                else
                    break;
            }
            else{
                if (x->ch[0] != NIL)
                    x = x->ch[0];
                else
                    break;
            }
        }
        splay(x, NIL);
        return y;
    }
    Node* searchmin(Node *x){//查找最小值，返回指针
        Node *y = x->pnt;
        while (x->ch[0] != NIL){//遍历到最左的儿子就是最小值
            x = x->ch[0];
        }
        splay(x, y);
        return x;
    }
    void del(int key){//删除一个值
        if (root == NIL)
            return;
        Node *x = search(key), *y;
        if (x == NIL)
            return;
        if (x->cnt > 1){
            x->cnt--;
            x->rs();
            return;
        }
        else if (x->ch[0] == NIL && x->ch[1] == NIL){
            init();
            return;
        }
        else if (x->ch[0] == NIL){
            root = x->ch[1];
            x->ch[1]->pnt = NIL;
            return;
        }
        else if (x->ch[1] == NIL){
            root = x->ch[0];
            x->ch[0]->pnt = NIL;
            return;
        }
        y = searchmin(x->ch[1]);
        y->pnt = NIL;
        y->ch[0] = x->ch[0];
        x->ch[0]->pnt = y;
        y->rs();
        root = y;
    }
    int rank(int key){//求结点高度 小于key的节点数
        Node *x = search(key);
        if (x == NIL)
            return 0;
        return x->ch[0]->sz/* + x->cnt*/;
    }
    Node* findk(int kth){//查找第k小的值
        if (root == NIL || kth > root->sz)
            return NIL;
        Node *x = root;
        while (1){
            if (x->ch[0]->sz +1 <= kth && kth <= x->ch[0]->sz + x->cnt)
                break;
            else if (kth <= x->ch[0]->sz)
                x = x->ch[0];
            else{
                kth -= x->ch[0]->sz + x->cnt;
                x = x->ch[1];
            }
        }
        splay(x, NIL);
        return x;
    }
}sp;

int f[N];
int ff(int x) {
    return f[x] == x ? x : (f[x] = ff(f[x]));
}
LL re, k;
int a[N];
vector<int> mp[N];
multiset<int> st;
void dfs(int root) {
    if(k / a[root] > 1e9) {
        re += st.size();
    } else {
    //    cout << "size=" << st.size() << endl;
        multiset<int>::iterator it = st.upper_bound( (int)(k / a[root]) );
        if(it == st.end()) {
            re += st.size();
        } else {
            re += sp.rank( *it );
        }
    }
    st.insert( a[root] );
    sp.insert( a[root] );
    for(int i = 0; i < mp[root].size(); ++i) {
        dfs( mp[root][i] );
    }
    sp.del( a[root] );
    st.erase( st.find(a[root] ) );
} 
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    int n, T;
    cin >> T;
    while(cin >> n >> k) {
        for(int i = 0; i < n; ++i) {
            cin >> a[i];  
            mp[i].clear();
            f[i] = i;
        }
        for(int i = 0; i < n-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            mp[u].push_back(v);
            f[v] = u;
        }
        int root = ff(0);
        re = 0;
        sp.init();
        dfs(root);
        cout << re << endl;
    }
    return 0;
}

