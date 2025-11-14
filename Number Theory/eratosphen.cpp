void sieve_eratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            pr.push_back(i);
            if (i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
}
