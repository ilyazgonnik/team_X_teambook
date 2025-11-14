//changing value, result on segment
struct segment_tree{
    int N;
    vector<int> data;
    vector<int> left;
    vector<int> right;
};

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

bool in(segment_tree &st, int v, int l, int r){
    if(st.left[v]>=l && st.right[v]<=r){
        return true;
    }
    else{
        return false;
    }
}//Is the cone of v in [l, r)

bool intersect(segment_tree &st, int v, int l, int r){
    if(st.left[v]>=r || st.right[v]<=l){
        return false;
    }
    else{
        return true;
    }
}//Is the cone of v intersect with [l, r)

void res_on_segment_help(segment_tree &st, int l, int r, int start, int &ans){
    if(start<st.N && l<r){
        if(in(st, start, l, r)){
            ans=operation(ans, st.data[start]);
        }
        else{
            if(intersect(st, start, l , r)){
                start*=2;
                int m=st.right[start];
                res_on_segment_help(st, l, min(m, r), start, ans);
                res_on_segment_help(st, max(l, m), r, start+1, ans);
            }
        }
    }
}

int res_on_segment(segment_tree &st, int l, int r){
    l+=(st.N/2);
    r+=(st.N/2);
    int ans=neutral();  
    res_on_segment_help(st, l, r, 1, ans);
    return ans;
}//[l, r) in the starting vector 

void changing_number(segment_tree &st, int pos, int new_value){
    pos+=(st.N/2);
    st.data[pos]=new_value; pos/=2;
    while(pos!=0){
        st.data[pos]=operation(st.data[2*pos], st.data[2*pos+1]);
        pos/=2;
    }
}//pos in staring vector//There will be problems if we will change + to something else in the beggining of this subprogramm.
//14.11.25 Don't get it

void start_segment_tree( segment_tree &st, vector<int> a){
    int n=a.size();
    int N=1;
    while(N<=n){
        N*=2;
    } N*=2; st.N=N;
    st.data.assign(N, neutral());
    st.left.resize(N); st.right.resize(N);
    for(int i=0;i<n;i++){
        st.data[i+(N/2)]=a[i];
    }
    for(int i=N/2;i<N;i++){
        st.left[i]=i;
        st.right[i]=i+1;
    }
    for(int i=(N/2)-1;i>0;i--){
        st.data[i]=operation(st.data[2*i], st.data[2*i+1]);
        st.left[i]=st.left[2*i];
        st.right[i]=st.right[2*i+1];
    }
}//creating the segment tree 
