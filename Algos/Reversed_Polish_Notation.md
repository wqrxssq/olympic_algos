# Разбор арифмитических выражений + обратная польская нотация

## В чем идея?
Наверное хоть раз вам встречалась задача "Найдите значение арифмитического выражения"(если нет то подумайте как это реализовать), то понимаете насколько это больно.
Использование польской нотации упрощает данную проблему и алгоритм будет выгледеть слежующим образом:
- Из исходной строки сделаем обратную польскую нотацию
- Из польской нотации быстро посчитаем значение выражения

## Что такое обратная польская нотация?
Обратная польская нотация — это форма записи математических выражений, в которой операторы расположены после своих операндов. Отсюда почти сразу понятем алгоритм:
- Поддерживаем стек чисел
- Если встречаем число, то пушим в стек
- Если встречаем оператор, то достаем 2 последних числа, выпираем операцию и результат снова кладем в стек
- Вконце остается один элемент, это и будет результат выражения.

Очевидно, что алгоритм работает за O(n)

Главное преимущество в том, что для обратной польской нотации не нужны скобки

## Задача:
Посчитать значение выражения, если вам дана запись в обратной польской нотации
### Реализация
```cpp
// calc reverse polish notation

// the input is an array of strings in reverse Polish notation
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

## Задача: Разбор арифметического выражения в самом простом случае
Пусть в выражении могут быть скобки, числа, знаки: {+, -, *, /}

Алгоритм заключается в следующем(будем считать, что выражение уже разбито на числа и знаки)
- Заведем 2 стека, один для чисел, другой для знаков, при этом пользуемся правилом, что приоритеты операций строго убывают, считая от вершины стека(если есть скобочки, то внутри скобочек, также упорядочены)
- Если встретили число, то просто запушим его в 1 стек
- Если встретили '(', то запушим во 2 стек
- Если перед нами ')', то выполняем операции до тех пор, пока не встретим обратную скобку
- И наконец если встретили знак операции, то выполняем, пока не будет выполнятся наш инвариант на приоритеты
### Упражнение:
Подумайте почему инвариант именно на строгое убывание, почему нельзя ослабить

Подсказка: рассмотрите выражение: 1+3-4

### Реализация
```cpp
// 2 stacks:
// 1 - numbers
// 2 - signs a1 < a2 < a3 < a4 < ... < an

// if s[i] is a number, add it to the numbers stack
// if s[i] is an operation, then remove all greater or equal ones from the stack and add to the end of it
// if s[i] - (, then add to the 2nd stack
// if s[i] - ), then delete until we meet (
// if the end, then fetch to the end

vector<string> get_expression(string& s) {
    vector<string> exp;
    for (int l = 0, r = 0; l < sz(s); l = r) {
        if (s[l] == ' ') {
            r++;
            continue;
        }
        if (s[l] == '+' || s[l] == '-' || s[l] == '*' || s[l] == '(' || s[l] == ')') {
            exp.push_back(string(1, s[l]));
            r++;
        } else if (isdigit(s[l])) {
            while (r < sz(s) && isdigit(s[r])) {
                r++;
            }
            exp.push_back(s.substr(l, r - l));
        } else {
            cout << "WRONG\n";
            exit(0);
        }
    }
    return exp;
}

int priority_sign(char sign) {
    switch (sign) {
    case '+':
    case '-':
        return 1;
    case '*':
        return 2;
    }
}

bool is_number(string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool is_psp(vector<string>& exp) {
    int cur = 0;
    for (string& s : exp) {
        if (s == "(") {
            cur++;
        } else if (s == ")") {
            cur--;
        }
        if (cur < 0) {
            return false;
        }
    }
    return (cur == 0);
}

void process_operation(stack<char>& signs, stack<int>& numbers) {
    if (numbers.size() < 2) {
        cout << "WRONG\n";
        exit(0);
    }

    int b = numbers.top();
    numbers.pop();
    int a = numbers.top();
    numbers.pop();
    char sign = signs.top();
    signs.pop();

    switch (sign) {
    case '+':
        numbers.push(a + b);
        break;
    case '-':
        numbers.push(a - b);
        break;
    case '*':
        numbers.push(a * b);
        break;
    }
}

int calc(vector<string>& exp) {
    if (!is_psp(exp)) {
        cout << "WRONG\n";
        exit(0);
    }
    stack<int> numbers;
    stack<char> signs;
    for (string& s : exp) {
        if (s == "+" || s == "-" || s == "*") {
            while (!signs.empty() && signs.top() != '(' && priority_sign(signs.top()) >= priority_sign(s[0])) {
                process_operation(signs, numbers);
            }
            signs.push(s[0]);
        } else if (s == "(") {
            signs.push(s[0]);
        } else if (s == ")") {
            while (signs.top() != '(') {
                process_operation(signs, numbers);
            }
            signs.pop();
        } else if (is_number(s)) {
            numbers.push(stoi(s));
        } else {
            cout << "WRONG\n";
            exit(0);
        }
    }
    while(!signs.empty()) {
        process_operation(signs, numbers);
    }
    if (numbers.size() != 1) {
        cout << "WRONG\n";
        exit(0);
    }

    return numbers.top();
}
```
