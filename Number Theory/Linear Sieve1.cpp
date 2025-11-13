const int sieve_C = 1e7+5;
vector<int> pr(0);//простые числа до C (не вкл)
vector<int> lp(sieve_C);//минимальный простой делитель 

bool ab_le_c(int a, int b, int c){
   int x=c/b;
   if(x>a){
       return true;
   }
   else{
       if(x<a){
           return false;
       }
       else{
           if(c%b==0){
               return false;
           }
           else{
               return true;
           }
       }
   }
}//ab<c

void linear_sieve(){
    for (int i = 2; i < sieve_C; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && ab_le_c(pr[j], i, sieve_C); ++j) {
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

int number_div(int n){
    if(n>1){
        auto v=factorization(n);
        int ans=1;
        for(auto pp: v){
            ans*=(pp.second+1);
        }
        return ans;
    }
    else{
        return 1;
    }
}

vector<int> all_div(int n){
    auto v=factorization(n);
    int k=v.size();
    vector<int> index(k); int d=1;
    vector<int> max_ind(k);
    for(int i=0;i<k;i++){
        max_ind[i]=v[i].second;
    }
    vector<int> ans(0);ans.push_back(1);
    while(max_ind!=index){
        int i=0;
        while(true){
            if(index[i]<max_ind[i]){
                index[i]++;
                d*=v[i].first;
                break;
            }
            else{
                while(index[i]>0){
                    d/=v[i].first;
                    index[i]--;
                }
                i++;
            }
        }
        ans.push_back(d);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	linear_sieve();
    return 0;
}	
