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
