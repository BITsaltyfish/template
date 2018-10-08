/*
 * 不要在函数里或者main里开Treap<int>T,开不下 放全局的
 * T.clear()清空
 * T.insert(x)插入
 * T.del(x)删除，没有成功删除返回false
 * T.pred(x)返回第一个小于x的数，T.pred(x+1)返回第一个小等于x的数
 * T.succ(x)返回第一个大于x的数，T.succ(x-1)返回第一个大等于x的数
 * T.ask_kth(x)返回第x小的数
 * T.ask_rank(x)返回x的排名是第几小
 */
template<class Tdata>
class Treap {
public:
#define Treap_size 200010 /* 记得改这个东西 */
#define NotFound (Tdata)-1
    struct treap_point {
        int l, r, rep, son, rnd;
        Tdata x;
    } t[Treap_size];
    int treesz, root;
    void update(int k) {
        t[k].son = t[t[k].l].son + t[t[k].r].son + t[k].rep;
    }
    void right_rotate(int &k) {
        int tt = t[k].l;
        t[k].l = t[tt].r;
        t[tt].r = k;
        update(k);
        update(tt);
        k = tt;
    }
    void left_rotate(int &k) {
        int tt = t[k].r;
        t[k].r = t[tt].l;
        t[tt].l = k;
        update(k);
        update(tt);
        k = tt;
    }
    void insert_to_tree(int &k, Tdata x) {
        if (!k) {
            k = ++treesz;
            t[k].x = x;
            t[k].rnd = rand();
            t[k].son = t[k].rep = 1;
            t[k].l = t[k].r = 0;
            return;
        }
        t[k].son++;
        if (x == t[k].x) {
            t[k].rep++;
            return;
        }
        if (x < t[k].x) {
            insert_to_tree(t[k].l, x);
            if (t[t[k].l].rnd < t[k].rnd)right_rotate(k);
        }
        if (x > t[k].x) {
            insert_to_tree(t[k].r, x);
            if (t[t[k].r].rnd < t[k].rnd)left_rotate(k);
        }
    }
    bool delete_from_tree(int &k, Tdata x) {
        if (!k)return false;
        if (x == t[k].x) {
            if (t[k].rep > 1) {
                t[k].rep--;
                t[k].son--;
                return true;
            }
            if (!t[k].l || !t[k].r) {
                k = t[k].l + t[k].r;
                return true;
            }
            if (t[t[k].l].rnd < t[t[k].r].rnd) {
                right_rotate(k);
                return delete_from_tree(k, x);
            }
            left_rotate(k);
            return delete_from_tree(k, x);
        }
        bool res;
        if (x < t[k].x) {
            res = delete_from_tree(t[k].l, x);
            if (res)t[k].son--;
            return res;
        }
        res = delete_from_tree(t[k].r, x);
        if (res)t[k].son--;
        return res;
    }
    Tdata get_succ_in_tree(int k, Tdata x) {
        if (!k) return NotFound;
        Tdata sv;
        if (x < t[k].x) {
            sv = get_succ_in_tree(t[k].l, x);
            return sv == NotFound ? t[k].x : sv;
        }
        return get_succ_in_tree(t[k].r, x);
    }
    Tdata get_pred_in_tree(int k, Tdata x) {
        if(!k) return NotFound;
        Tdata sv;
        if (x > t[k].x) {
            sv = get_pred_in_tree(t[k].r, x);
            return sv == NotFound ? t[k].x : sv;
        }
        return get_pred_in_tree(t[k].l, x);
    }
    Tdata ask_kth_in_tree(int k, int x) {
        if (!k) return NotFound;
        if (x <= t[t[k].l].son) return ask_kth_in_tree(t[k].l, x);
        if (x > t[t[k].l].son + t[k].rep) return ask_kth_in_tree(t[k].r, x - t[t[k].l].son - t[k].rep);
        return t[k].x;
    }
    int ask_rank_in_tree(int k, Tdata x) {
        if (!k) return -1;
        if (x == t[k].x) return t[t[k].l].son + 1;
        if (x < t[k].x) return ask_rank_in_tree(t[k].l, x);
        return t[t[k].l].son + t[k].rep + ask_rank_in_tree(t[k].r, x);
    }
    Treap() {
        treesz = root = 0;
    }
    void clear() {
        treesz = root = 0;
    }
    void insert(Tdata x) {
        insert_to_tree(root, x);
    }
    bool del(Tdata x) {
        return delete_from_tree(root, x);
    }
    Tdata pred(Tdata x) {
        return get_pred_in_tree(root, x);
    }
    Tdata succ(Tdata x) {
        return get_succ_in_tree(root, x);
    }
    Tdata ask_kth(int x) {
        return ask_kth_in_tree(root, x);
    }
    int ask_rank(Tdata x) {
        return ask_rank_in_tree(root, x);
    }
#undef NotFound
#undef Treap_size
};
Treap<int>T;