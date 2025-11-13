#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;

int main() {
    ordered_set s;

    // Вставка элементов
    s.insert(10);
    s.insert(5);
    s.insert(20);
    s.insert(15);

    // Найти k-й наименьший элемент (0-based)
    cout << *s.find_by_order(0) << endl; // 5
    cout << *s.find_by_order(2) << endl; // 15

    // Сколько элементов меньше чем X
    cout << s.order_of_key(12) << endl; // 2 (5, 10 < 12)
    cout << s.order_of_key(15) << endl; // 2 (5, 10 < 15)

    return 0;
}
