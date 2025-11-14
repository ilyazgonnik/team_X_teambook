const int sieve_C = 1e7+5;
vector<int> pr(0);//primes up to C (not incl.)
vector<int> lp(sieve_C);//minimal prime divisor

void linear_sieve(){
    for (int i = 2; i < sieve_C; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && (pr[j]*i<sieve_C); ++j) {
            lp[pr[j] * i] = pr[j];
        }
    }
}

vector<pair<int, int> > factorization(int n){
    vector<pair<int, int> > ans(0);
    int last=-1;
    int nn=n;
    while(nn!=1){
        if(last!=lp[nn]){
            ans.push_back({lp[nn], 1});
            last=lp[nn];
        }
        else{
            ans[ans.size()-1].second++;
        }
        nn/=lp[nn];
    }
    return ans;
}
