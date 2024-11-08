
```cpp
// calc reverse polish notation
int calc(const vector<string>& expression) {
    stack<int> cur;
    for (const string& exp : expression) {
        if (ispunct(exp[0])) {  // symbol is {+, -, *}
            assert(cur.size() >= 2);

            int b = cur.top();
            cur.pop();
            int a = cur.top();
            cur.pop();

            switch (exp[0]) {
            case '+': cur.push(a + b); break;
            case '-': cur.push(a - b); break;
            case '*': cur.push(a * b); break;
            default: break;
            }
        } else {  // number
            cur.push(stoi(exp));
        }
    }
    assert(cur.size() == 1);
    return cur.top();
}
```