int gcd (int x, int y){
    if(x<y){
        swap(x, y);
    }
    if(y==0){
        return x;
    }
    else{
        x=x%y;
        swap(x, y);
        return gcd(x, y);
    }
}

int multi_gcd_help(int n, vector<int> &a, int step){
    if(step==n){
        return a[0];
    }
    else{
        for(int i=0;i<n;i=i+2*step){
            int x=gcd(a[i], a[i+step]);
            a[i]=x;
        }
        step=step*2;
        return multi_gcd_help(n, a, step);
    }
}

int multi_gcd(int n, vector<int> a){
    int k=1;
    while(k<n){
        k=k*2;
    }
    n=k;
    a.resize(k);
    return multi_gcd_help(n, a, 1);
}
