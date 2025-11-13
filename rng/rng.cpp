using uid = std::uniform_int_distribution<int>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//using uid = std::uniform_real_distribution<double>; для вещественных
uid(0,n)(rng); //границы включительно
