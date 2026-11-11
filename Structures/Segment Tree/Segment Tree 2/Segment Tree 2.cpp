//changing value, result on segment
struct segment_tree{
    int N;
    vector<int> data, left, right;
    bool in(int v, int l, int r){
        return (left[v]>=l && right[v]<=r);
    }//Is the cone of v in [l, r)
    int operation(int now_left, int now_right){
        .return (now_left+now_right);   //+
        .return min(now_left, now_right);//min
        .return max(now_left, now_right);//max
        .return gcd(now_left, now_right);//gcd
        .return (now_left*now_right)%mod;//multiplcation by modulo
    }
    int neutral(){
        .return 0;//+
        .return inf;//min
        .return -inf;//max
        .return 0;//gcd
        .return 1;//multiplcation by modulo
    }
    bool intersect(int v, int l, int r){
        return !(left[v]>=r || right[v]<=l);
    }//Is the cone of v intersect with [l, r)
    void res_on_segment_help(int l, int r, int start, int &ans){
        if(start<N && l<r){
            if(in(start, l, r)){
                ans=operation(ans, data[start]);
            }
            else{
                if(intersect(start, l , r)){
                    start*=2;
                    int m=right[start];
                    res_on_segment_help(l, min(m, r), start, ans);
                    res_on_segment_help(max(l, m), r, start+1, ans);
                }
            }
        }
    }
    int res_on_segment(int l, int r){
        int ans=neutral();
        res_on_segment_help(l+(N/2), r+(N/2), 1, ans);
        return ans;
    }//[l, r) in the starting vector
    void changing_number(int pos, int new_value){
        pos+=(N/2);
        data[pos]=new_value; pos/=2;
        while(pos){
            data[pos]=operation(data[2*pos], data[2*pos+1]);
            pos/=2;
        }
    }//pos in staring vector//There will be problems if we will change + to something else in the beggining of this subprogramm.
    //14.11.25 Don't get it
    void start_segment_tree(vector<int> a){
        int n=a.size();
        N=1;
        while(N<=n){
            N*=2;
        } N*=2;
        data.assign(N, neutral());
        left.resize(N); right.resize(N);
        for(int i=0;i<n;i++) data[i+(N/2)]=a[i];
        for(int i=N/2;i<N;i++){
            left[i]=i;
            right[i]=i+1;
        }
        for(int i=(N/2)-1;i>0;i--){
            data[i]=operation(data[2*i], data[2*i+1]);
            left[i]=left[2*i];
            right[i]=right[2*i+1];
        }
    }//creating the segment tree
};
