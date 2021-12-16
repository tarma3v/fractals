#include <SFML/Graphics.hpp>
#include <utility>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

typedef long double ld;

const int xsize = 900, ysize = 900;
const int amount_of_iterations = 1000;
const long double EPS = 1e-7;
const int color_const = 0;

// !!!
const ld cx = 0.3, cy = 0.46;

// 0.3 0.5
// -0.0085, 0.71;
// 0.3 0.46
// -0.800043099666580, 0.164138006668392

class ComplexNumber {
public:
	// ComplexNumber() : x(0), y(0) {}
	ComplexNumber(ld x_set = 0, ld y_set = 0) : x(x_set), y(y_set) {}
	ComplexNumber(ComplexNumber&& other) {
		x = std::exchange(other.x, 0);
		y = std::exchange(other.y, 0);
	}
	ComplexNumber(const ComplexNumber& a) : x(a.x), y(a.y) {}

	friend ComplexNumber operator* (ComplexNumber a, ComplexNumber b) {
		ComplexNumber result;
		result.x = a.x * b.x - a.y * b.y;
		result.y = a.y * b.x + a.x * b.y;
		return result;
	}
	friend ComplexNumber operator+ (ComplexNumber a, ComplexNumber b) {
		ComplexNumber c(a.x + b.x, a.y + b.y);
		return c;
	}
	ComplexNumber& operator=(ComplexNumber rvalue) {
		(*this).x = rvalue.GetX();
		(*this).y = rvalue.GetY();
		return *this;
	}
	long double GetX() { return x; };
	long double GetY() { return y; };
	std::pair <int, int> GetXY() { return { x, y }; };
	long double len2() {
		return (x * x + y * y);
	}
private:
	ld x, y;
};

int draw(ComplexNumber z) {
	ComplexNumber C(cx, cy);
	for (int i = 0; i < amount_of_iterations; ++i) {
		z = C + z * z;
		if (z.len2() >= -EPS + 4) {
			return (i + color_const) % 256;
		}
	}
	// std::cout << std::fixed << std::setprecision(7);
	// std::cout << C.len2() << std::endl;
	return -1;
}

ComplexNumber prepare(int i, int j, ld xfrom, ld yfrom, ld xto, ld yto) {
	ld xx, yy;
	xx = xfrom + (xto - xfrom) * i * 1.0 / xsize;
	yy = yfrom + (yto - yfrom) * j * 1.0 / ysize;
	ComplexNumber c(xx, yy);
	// std::cout << c.GetX() << ' ' << c.GetY() << '\n';
	return c;
}

Image screen;
Sprite sprite;
Texture texture;
int k = 0;
string name;

// нужно для сохранения картинок
string from_int_to_string(int x) {
	if (x == 0)
		return "0";


	string ans;
	bool t = x < 0;
	if (t)
		x *= -1;
	while (x > 0) {
		ans += (char)(x % 10 + '0');
		x /= 10;
	}
	if (t)
		ans += '-';
	reverse(ans.begin(), ans.end());
	return ans;
}

void ScreenOnSprite(ld xfrom, ld yfrom, ld xto, ld yto)
{


	for (int i = 0; i < xsize; ++i)
		for (int j = 0; j < ysize; ++j)
			screen.setPixel(i, j, Color(0, 0,(Uint8)draw(prepare(i, j, xfrom, yfrom, xto, yto)) ));
	texture.loadFromImage(screen);
	sprite.setTexture(texture);

	screen.saveToFile(name + from_int_to_string(k) + ".png");
	k++;
}




int main()
{
	cout << "enter name of file: ";
	cin >> name;
	RenderWindow window(VideoMode(xsize, ysize), "SFMLworks");
	window.setFramerateLimit(30);

	RectangleShape cell(Vector2f(1, 1));
	RectangleShape WindowSave(Vector2f(xsize, ysize));
	ComplexNumber nul(0, 0);
	int color;
	ld xto = 2.0, yto = 2.0, xfrom = -2.0, yfrom = -2.0;
	bool changed = true;

	
	screen.create(xsize, ysize);
	ScreenOnSprite(xfrom, yfrom, xto, yto);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		if (Mouse::isButtonPressed(Mouse::Left)) {
			sf::Vector2i c1 = Mouse::getPosition(window);
			changed = true;
			while (Mouse::isButtonPressed(Mouse::Left)) {
				if (sf::Event::MouseMoved) {
					//drawfractal again

					window.draw(sprite);

					cell.setFillColor(Color::White);
					sf::Vector2i c_cur = Mouse::getPosition(window);
					int xmin = std::min(c1.x, c_cur.x);
					int ymin = std::min(c1.y, c_cur.y);
					std::cout << c1.x << ' ' << c1.y << ' ' << c_cur.x << ' ' << c_cur.y << ' ' << xmin << ' ' << ymin << '\n';
					for (int i = xmin; i < c1.x + c_cur.x - xmin; ++i) {
						cell.setPosition(i, c1.y);
						window.draw(cell);
						cell.setPosition(i, c_cur.y);
						window.draw(cell);
					}
					for (int j = ymin; j < c1.y + c_cur.y - ymin; ++j) {
						cell.setPosition(c1.x, j);
						window.draw(cell);
						cell.setPosition(c_cur.x, j);
						window.draw(cell);
					}
					window.display();
				}
			}
			sf::Vector2i c2 = Mouse::getPosition(window);
			std::cout << c1.x << ' ' << c1.y << ' ' << c2.x << ' ' << c2.y << '\n';
			ld xf, yf, xt, yt;

			xf = (c1.x * xto + (xsize * 1LL - c1.x) * xfrom) * 1.0 / xsize;
			yf = (c1.y * yto + (ysize * 1LL - c1.y) * yfrom) * 1.0 / ysize;

			xt = (c2.x * xto + (xsize * 1LL - c2.x) * xfrom) * 1.0 / xsize;
			yt = (c2.y * yto + (ysize * 1LL - c2.y) * yfrom) * 1.0 / ysize;

			xfrom = xf;
			yfrom = yf;
			xto = xt;
			yto = yt;

			if (xto < xfrom) {
				std::swap(xto, xfrom);
			}
			if (yto < yfrom) {
				std::swap(yto, yfrom);
			}
			std::cout << xfrom << ' ' << yfrom << ' ' << xto << ' ' << yto << '\n';
			ScreenOnSprite(xfrom, yfrom, xto, yto);
		}
		window.draw(sprite);

		window.display();
	}
	return 0;
}
