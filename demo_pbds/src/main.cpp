//#include <bits/extc++.h>
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;

//#define el '\n'
//#define cl putchar('\n');
//#define pb push_back
//#define x first
//#define y second
//#define rep(i, a, b) for (int i = (a); i <= (b); i++)

//typedef pair<int, int> PII;
//int main(int argc, char *argv[])
//{
////  __gnu_cxx::random_sample hh;
//  __gnu_pbds::basic_branch bb;
////  bb.node_update

//  return 0;
//}



#include<bits/stdc++.h>
#include<bits/extc++.h>

#define int long long
using namespace __gnu_pbds;
using namespace std;

/// register 将变量保留在寄存器

#define FOR(i,a,b) for(register int i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(register int i=(a),i##i=(b);i>=i##i;--i)
#define REP(u) for(register int i=head[u];i;i=e[i].nxt)
#define File_1(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define File_2(a) freopen(a".in","r",stdin)
using ll=long long;

inline int read(){
    int ret=0,f=0;char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=1;ch=getchar();}
    while(ch>='0' && ch<='9'){ret=(ret<<1)+(ret<<3)+(ch^48);ch=getchar();}
    return f?-ret:ret;
}

int T,n;

tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> bbt;

inline void solve(){
    n=read();
    FOR(i,1,n){
        ll opt=read(),x=read(),ans;
        if(opt==1) bbt.insert((x<<20)+i);
        if(opt==2) bbt.erase(bbt.lower_bound(x<<20));
        if(opt==3) printf("%lld\n",bbt.order_of_key(x<<20)+1);
        if(opt==4) ans=*bbt.find_by_order(x-1),printf("%lld\n",ans>>20);
        if(opt==5) ans=*--bbt.lower_bound(x<<20),printf("%lld\n",ans>>20);
        if(opt==6) ans=*bbt.upper_bound((x<<20)+n),printf("%lld\n",ans>>20);
    }
}

signed main(){
//    File_1("lab");
    T=1;
    while(T--) solve();
//    fprintf(stderr, "%f\n", 1.0*clock()/CLOCKS_PER_SEC);

    return 0;
}
