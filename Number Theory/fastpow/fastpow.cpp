int po(int a,int b){
    int res=1;
    while(b) {if(b & 1) {res=(res*a)%mod;--b;} else {a=(a*a)%mod;b>>=1;}} return res;
}//fast_pow c __int128
