//поддерживается такое условие - сумма на путях до вершин=листьев равна РЕАЛЬНОМУ значению листа

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
    .return (now_left*now_right)%mod;//умножение по модулю
}

int neutral(){
    .return 0;//+
    .return inf;//min
    .return -inf;//max
    .return 0;//gcd
    .return 1;//умножение (?по модулю?)
}

bool in(segment_tree &st, int v, int l, int r){
    if(st.left[v]>=l && st.right[v]<=r){
        return true;
    }
    else{
        return false;
    }
}//лежит ли конус v в промежутке [l, r)

bool intersect(segment_tree &st, int v, int l, int r){
    if(st.left[v]>=r || st.right[v]<=l){
        return false;
    }
    else{
        return true;
    }
}//пересекается ли конус v с промежутком [l, r)

int res_number(segment_tree &st, int pos){
    pos+=(st.N/2);
    int start=1;
    int ans=neutral();  
    while(start!=pos){
        ans=operation(ans, st.data[start]);
        start*=2;
        if(!intersect(st, start, pos, pos+1)){
            start++;
        }
    }
    return operation(ans, st.data[start]);
}//pos в изначальном массиве

void changing_segment_help(segment_tree &st, int start, int l, int r, int num){
    if(start<st.N && l<r){
        if(in(st, start, l, r)){
            st.data[start]=operation(st.data[start], num);
        }
        else{
            if(intersect(st, start, l , r)){
                start*=2;
                int m=st.right[start];
                changing_segment_help(st, start,  l, min(m, r), num);
                changing_segment_help(st, start+1,  max(l, m), r, num);
            }
        }
    }
}

void changing_segment(segment_tree &st, int l, int r, int num){
    l+=(st.N/2);
    r+=(st.N/2);
    changing_segment_help(st, 1, l, r, num);
}//[l, r) в изначальном массиве

//скопировал  И ЗРЯ! ВЕДЬ НАДО ЗАПОЛНЯТЬ data НЕЙТРАЛЬНЫМИ ЭЛЕМЕНТАМИ ПО УМОЛЧАНИЮ
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
        st.left[i]=st.left[2*i];
        st.right[i]=st.right[2*i+1];
    }
}//создание дерева отрезков по массиву a для некой операции (возможно, надо менять изчальные данные для листов -19.10.25 я убрал) 
