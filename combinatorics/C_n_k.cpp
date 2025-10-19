int fastpow(int a,int b)
    {
        if(a==0){return 0;}
        if(b==0){return 1;}
        int c=fastpow(a,b/2);
        if(b%2==0)
        {
            return (c*c)%mod;
        }
        return (((c*c)%mod)*a)%mod;
    }
    int C(int n,int k,vector<int> &fact)
    {
        return (fact[n]*fastpow(( (fact[k])*fact[n-k])%mod,mod-2))%mod;
    }
//нужно предпосчет fact
