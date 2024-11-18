# Топ $k$

## Решение

### Идеи

Пусть элементы разбросаны равномерно, зацикливаний нет, тогда как за проход найти $k$ наибольших?

Пусть мы прошлись по последовательности, и $max\\_el = M$

Известно, что если элементы разбросаны равномерно и их $N$, то они встречаются в среднем каждые $\sim \frac{M}{N},$ то есть при $N = 10^8 \sim 21$, тогда идея следующая, пройтись по массиву, взяв все элементы $$a_n \geq M - \frac{M}{N} * k - \epsilon ,$$ и если их будет $k \leq 10^{5} \leq cnt \leq 10^{6}$, то сохраним в массив, дальше отсортируем массив, и возьмем $k$ наибольших!

### Плохие случаи

Проблема возникает в 2 случаях:

- Не набралось $k$ элементов
- Набралось $> 10^6$ элементов

В обоих случаях, можно заметить, что такое возможно если $a_n$ не распределены равномерно, то есть существует цикл, который повторяется очень много раз:

Найдем этот цикл(?)(в том числе длину), распишем элементы в нем, для каждого знаем сколько раз он повторится, значит можем восстановить ответ!