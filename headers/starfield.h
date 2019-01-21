#pragma once
#ifndef starfield_h
#define starfield_h


class Star
{
public:
	void init(int W, int H);
	void update(int w, int h, int W0, int H0, float speed);
	void render(sf::RenderWindow &gRenderer);
	Star();
private:
	float x, y, z;
	int h, w;
	float scale;

};
void Star::init(int W, int H)
{
	x = rand() % W;
	y = rand() % H;
	z = rand() % H;
	scale = 0.01;
}
Star::Star()
{
	x = (rand() + 1) % (w * 2);
	y = (rand() + 1) % (h * 2);
	z = (rand() + 1) % (w * 2);
	scale = 0.01;
}
void Star::update(int W, int H, int W0, int H0, float speed)
{
	w = W;
	h = H;
	z -= 10 * speed;

	if (z < 1)
	{
		z = 1;
	}
	scale += 0.01*speed;
	if (scale > 1.5)scale = 1.5;
	if (x <= 0 || x>W0 || y <= 0 || y> H0)
		init(W0, H0);
}
void Star::render(sf::RenderWindow &gRenderer)
{
	int x_tail = x;
	int y_tail = y;
	float zx = (x / z);
	float zy = (y / z);

	if (x <w - 5 && y < h + 5)
	{
		x -= zx;// *(w - x) / w;
		y -= zy;// *(h - y) / h;
	}
	else
		if (x < w - 5 && y > h + 5)
		{
			x -= zx;// *(w - x) / w;
			y += zy;// *(y - h) / h;
		}
		else
			if (x > w + 5 && y > h - 5)
			{
				x += zx;// *(x - w) / w;
				y += zy;// *(y - h) / h;
			}
			else
				if (x > w + 5 && y < h - 5)
				{
					x += zx;// *(x - w) / w;
					y -= zy;// *(h - y) / h;
				}
				else
					if (x >= w - 5 && x <= w + 5 && y < h)
					{
						y -= zy;
					}
					else
						if (x < w  && y <= h + 5 && y >= h - 5)
						{
							x -= zx;
						}
						else
							if (x >= w - 5 && x <= w + 5 && y > h)
							{
								y += zy;
							}
							else
								if (x > w  && y <= h + 5 && y >= h - 5)
								{
									x += zx;
								}

	//SDL_RenderDrawLine(gRenderer, x, y, x_tail, y_tail);

	//sf::RectangleShape line(sf::Vector2f(150, 5));
	///line.rotate(45);


	sf::CircleShape shape(5 * scale);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);
	gRenderer.draw(shape);
}


void starField(sf::RenderWindow &gRenderer, Star *star, int StarCount, int x, int y, int W, int H, float speed)
{
	//std::cout << << speed << std::endl;
	for (int i = 0; i < StarCount; i++)
	{

		star[i].update(x, y, W, H, speed);
		star[i].render(gRenderer);
	}
}
#endif