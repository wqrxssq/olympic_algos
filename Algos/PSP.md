# Правильные скобочные последовательности aka ПСП

## Что такое ПСП

## Задача: Проверка на правильность
Пусть дано 

### Реализация
```cpp
void is_psp() {
    string s;
    cin >> s;
    stack<char> q;
    for (char c : s) {
        if (c == '[' || c == '{' || c == '(') { // is opening bracket
            q.push(c);
        } else { // is closing bracket
            if (q.empty() || abs(c - q.top()) > 2) {
                cout << "no\n";
                return;
            } else {
                q.pop();
            }
        }
    }
    if (q.empty()) {
        cout << "yes\n";
    } else {
        cout << "no\n";
    }
}
```