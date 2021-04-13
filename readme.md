## Идея решения

Парсер на Python конвертирует картинку в двумерный массив из 0 и 1.

В другом файле, уже на C++, считывается полученный массив.

Для поиска пересечений используется сканлайн: 
он проходит слева направо и инкрементирует счётчик, если видит пересечение двух отрезков.

Для этого необходимо сконвертировать полученный массив в граф.
Чтобы это сделать, надо найти вершины и рёбра между ними.

Для нахождения вершин смотрим на крайние точки сверху, снизу, слева, справа.
Когда видим точку, "удаляем" её и продолжаем в том же направлении.
Если видим на пути прямую вместо точки (для этого проверяем толщину), то прибавляем 2 к вершинам.
Таким способом найдём все вершины графа. 

Для нахождения рёбер рассмотрим все пары чёрных точек. 
Если между вершинами есть ребро, то пара точек из них будет соединена отрезком.
Так мы сможем определить все рёбра в графе.

После нахождения рёбер применяем сканлайн, и получаем ответ (также нужно в конце вычесть число вершин).

## Запуск

Запустить parser.py
