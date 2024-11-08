# Разбор арифмитических выражений + обратная польская нотация

## - В чем идея?
Наверное хоть раз вам встречалась задача "Найдите значение арифмитического выражения"(если нет то подумайте как это реализовать), то понимаете насколько это больно.
Использование польской нотации упрощает данную проблему и алгоритм будет выгледеть слежующим образом:
- Из исходной строки сделаем обратную польскую нотацию
- Из польской нотации быстро посчитаем значение выражения

## Что такое обратная польская нотация?
Обратная польская нотация — это форма записи математических выражений, в которой операторы расположены после своих операндов. Отсюда почти сразу понятем алгоритм TODO: записать

## Реализация
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