int32_t main()
{
    int max_test=10;
    for(int test=0;test<max_test;test++){
        int n;
        cin>>n;
        segment_tree st;
        vector<int> a(n);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        start_segment_tree(st, a);
        int m;
        cin>>m;
        for(int i=0;i<m;i++){
            string s;
            cin>>s;
            if(s=="in"){
                int l;
                int r;
                cin>>l;l--;
                cin>>r;
                int value;
                cin>>value;
                changing_segment(st, l, r, value);
            }
            else{
                int l;
                cin>>l;l--;
                cout<<res_number(st, l)<<endl;
            }
        }
    }
    return 0;
}
//для проверки(но, увы, не самой содержательной) 908-B
