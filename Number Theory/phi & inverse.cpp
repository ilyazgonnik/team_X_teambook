__int128 one=1;

int po(int a,int b,int p){
    int res=1;
    while(b) {if(b & 1) {res=(res*one*a)%p;--b;} else {a=(a*one*a)%p;b>>=1;}} return res;
}//fast_pow c __int128
    
int phi(int n){
    if(n==1){
        return 0;
    }
    else{
        auto f=factorization(n);
        int ans=n;
        for(auto p: f){
            ans/=p.first;
            ans*=(p.first-1);
        }
        return ans;
    }
}
 
int inv(int a, int n){
    if(n==1){
        return 1;
    }
    else{
        return po(a, phi(n)-1, n);
    }
}//(a, n)=1;
