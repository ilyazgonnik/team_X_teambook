const int sieve_C = 1e7+5;
vector<int> pr(0);//простые числа до C (не вкл)
vector<int> lp(sieve_C);//минимальный простой делитель 

void linear_sieve(){
    for (int i = 2; i < sieve_C; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && (pr[j]*i<sieve_C); ++j) {
            lp[pr[j] * i] = pr[j];
        }
    }
}
