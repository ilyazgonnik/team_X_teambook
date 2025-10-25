vector<int> occurences(string &sample, string &s){
    string t=sample+'@'+s;
    auto z=z_function(t);
    vector<int> ans(0);
    for(int i=sample.size()+1;i<t.size();i++){
        if(z[i]>=sample.size()){
            ans.push_back(i-sample.size()-1);
        }
    }
    return ans;
}//строки не должны содержать @
