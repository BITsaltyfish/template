class int2{
	int x;
	int2(int _x){x=_x;}
	public void set(int _x){x=_x;}
}
class TreapNode{
	int x=0,son=0,rep=0,rnd=0;
	int2 l=new int2(0),r=new int2(0);
	TreapNode(int _x){l.set(0);r.set(0);son=rep=1;rnd=new Random().nextInt(2147483647);x=_x;}
}
class Treap{
	int treesize=0;
	int2 root=new int2(0);
	TreapNode[] t=new TreapNode[2000001];
	Treap() {t[0]=new TreapNode(0);t[0].son=t[0].rep=t[0].rnd=0;}
	public void insert(int x){Insert(root,x);}
	public int delete(int x){return Delete(root,x);}
	public int get_succ(int x){return Get_Succ(root,x);}
	public int get_pred(int x){return Get_Pred(root,x);}
	public int ask_kth(int x){return Ask_Kth(root,x);}
	public int ask_rank(int x){return Ask_Rank(root,x);}
	private void update(int k){t[k].son=t[t[k].l.x].son+t[t[k].r.x].son+t[k].rep;}
	private void right_rotate(int2 k){int tt=t[k.x].l.x;t[k.x].l.set(t[tt].r.x);t[tt].r.set(k.x);update(k.x);update(tt);k.set(tt);}
    private void left_rotate(int2 k){int tt=t[k.x].r.x;t[k.x].r.set(t[tt].l.x);t[tt].l.set(k.x);update(k.x);update(tt);k.set(tt);}
    private void Insert(int2 k,int x)
	{
		if (k.x==0)
		{
			k.set(++treesize);
			t[treesize]=new TreapNode(x);
			return;
		}
		t[k.x].son++;
		if (x==t[k.x].x) {t[k.x].rep++;return;}
		if (x<t[k.x].x) {Insert(t[k.x].l,x);if (t[t[k.x].l.x].rnd<t[k.x].rnd)right_rotate(k);}
		else if (x>t[k.x].x) {Insert(t[k.x].r,x);if (t[t[k.x].r.x].rnd<t[k.x].rnd)left_rotate(k);}
	}
	private int Delete(int2 k,int x)
	{
		if (k.x==0)return 0;
		if (x==t[k.x].x)
		{
			if (t[k.x].rep>1){t[k.x].rep--;t[k.x].son--;return 1;}
			if (t[k.x].l.x==0||t[k.x].r.x==0){k.set(t[k.x].l.x+t[k.x].r.x);return 1;}
			if (t[t[k.x].l.x].rnd<t[t[k.x].r.x].rnd){right_rotate(k);return Delete(k,x);}
			left_rotate(k);return Delete(k,x);
		}
		int res;
		if (x<t[k.x].x){res=Delete(t[k.x].l,x);if (res!=0)t[k.x].son--;return res;}
		res=Delete(t[k.x].r,x);if (res!=0)t[k.x].son--;return res;
	}
	private int Get_Succ(int2 k,int x)
	{
		if (k.x==0)return -1;
		int sv;
		if (x<t[k.x].x) {sv=Get_Succ(t[k.x].l,x);return sv==-1?t[k.x].x:sv;}
		return Get_Succ(t[k.x].r,x);
	}
	private int Get_Pred(int2 k,int x)
	{
		if (k.x==0)return -1;
		int sv;
		if (x>t[k.x].x) {sv=Get_Pred(t[k.x].r,x);return sv==-1?t[k.x].x:sv;}
		return Get_Pred(t[k.x].l,x);
	}
	private int Ask_Kth(int2 k,int x)
	{
		if (k.x==0)return -1;
		if (x<=t[t[k.x].l.x].son)return Ask_Kth(t[k.x].l,x);
		if (x>t[t[k.x].l.x].son+t[k.x].rep)return Ask_Kth(t[k.x].r,x-t[t[k.x].l.x].son-t[k.x].rep);
		return t[k.x].x;
	}
	private int Ask_Rank(int2 k,int x)
	{
		if (k.x==0)return -1;
		if (x==t[k.x].x)return t[t[k.x].l.x].son+1;
		if (x<t[k.x].x)return Ask_Rank(t[k.x].l,x);
		return t[t[k.x].l.x].son+t[k.x].rep+Ask_Rank(t[k.x].r,x);
	}
}