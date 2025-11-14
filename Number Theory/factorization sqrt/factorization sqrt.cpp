vector<pair<int, int> > factorization(int n){
    int m=n;
    vector<pair<int,int> > ans(0);
    int last=-1;
    for(int i=0;i<pr.size() && m!=1 && pr[i]*pr[i]<=m;i++){
        while(m%pr[i]==0){
            if(last==pr[i]){
                ans[ans.size()-1].second++;
            }
            else{
                ans.push_back({pr[i], 1});
                last=pr[i];
            }
            m/=pr[i];
        }
    }
    if(m!=1){
        ans.push_back({m, 1});
    }
    return ans;
}//{prime, deg}
