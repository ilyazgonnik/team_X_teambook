vector<int> shifts(vector<int> &a, vector<int> &b){
    int k=a.size();
    vector<int> s(3*k);
    for(int i=0;i<k;i++){
        s[i]=a[i];
        s[i+k]=b[i];
        s[i+2*k]=b[i];
    }
    vector<int> z=z_function(s);
    vector<int> ans(0);
    for(int j=0;j<k;j++){
        if(z[k+j]>=k){
            ans.push_back(j);
        }
    }
    return ans;
}//строка a в строку b в положительном направлении (a+shift=b) 
