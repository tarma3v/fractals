Русский / Russian:
<big>Фракталы Жюлиа</big>

<big>Тармаев Александр, 2021</big>

<big>Что это за проект?</big>  
Данный проект рисует множество Жюлиа, используя для этого метод 
итераций. Интересуемую область можно приближать, зона рисуется по
двум точкам: координатам, где была нажата и отпущена ЛКМ. Все 
изображения сохраняются в папке, где расположен проект. Получаются
красивые картинки, можно изучать различные фракталы.

<big>Как пользоваться программой?</big>  
Потребуется подключить библиотеки SFML к вашему проекту. 
Туториал с подключением к VS можно найти здесь: https://www.youtube.com/watch?v=w339OWGlSo0&list=WL&index=1&t=38s
После запуска необходимо ввести имя, после все файлы будут
сохранены в файл {имя}{сколько приближений было сделано}, 
например, если ввести имя "frac", то первое изображение
сохранится как frac0.png, картинка после первого зума
сохранится в frac1.png и так далее.

<big>Как устроен подсчёт</big>  
Написан `class ComplexNumber`, в котором есть операторы `+`, 
`*`, `=`, а также конструкторы по двум вещественным числам:
Real и Im. Изначально задано комплексное число C, им определяется
фрактал. В зависимости от координат окна меняем пробегаемые z 
значения, высчитываем amount_of_iterations раз число z 
по формуле`z = z * z + C`, если модуль z стал больше 2, 
то возвращаем номер итерации. Чем больше номер, 
тем ярче пиксель. (Изначально границы окна от -2 до 2).

English:
<big>Julia Fractals</big>

<big>Tarmaev Alexander, 2021</big>

<big>What is this project?</big>
This project draws Julia sets using the iteration method. The area of interest can be zoomed in; the zone is drawn between two points: the coordinates where the left mouse button was pressed and released. All images are saved in the folder where the project is located, resulting in beautiful pictures that can be used to study various fractals.

<big>How to use the program?</big>
You will need to connect the SFML libraries to your project. A tutorial on how to connect it to Visual Studio can be found here: https://www.youtube.com/watch?v=w339OWGlSo0&list=WL&index=1&t=38s. After launching, you need to enter a name; all files will be saved in a file named {name}{number of zooms made}. For example, if you enter the name "frac," the first image will be saved as frac0.png, the image after the first zoom will be saved as frac1.png, and so on.

<big>How is the calculation done?</big>
A class called ComplexNumber is written, which includes operators +, *, =, as well as constructors for two real numbers: Real and Im. Initially, a complex number C is defined, which determines the fractal. Depending on the window coordinates, the values of z are changed, and the amount_of_iterations times z is calculated using the formula z = z * z + C. If the modulus of z becomes greater than 2, the iteration number is returned. The higher the number, the brighter the pixel. (Initially, the window boundaries are from -2 to 2).
