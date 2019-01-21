#pragma once
#ifndef particle_effect_h
#define particle_effect_h

const double G = 9.8;


class particle_spark
{
private:
	double v; //velocity main (random)
	double x, y; //particle location in global render screen (random)
	double angle; // 0-180 in degres (random)
	double a, b; // calculated velocity of x and y
	sf::Color color; // in yellow and orange spectr (random)
	// function to calculate angle to bounce off and set velocity and angle

	// in wich time period kill the spark
	bool dead;
	int life;
	int life_spawn;
	//
	int size; // small (random)
	double time;
	// to render in front TRUE
	sf::IntRect Bmain;
public:
	float scale;
	sf::Vector2i starpoint;
	bool Brender;
	particle_spark() {}
	void render(sf::RenderWindow &window, int level);
	// x,y-relative to spark
	void init(int x, int y, sf::IntRect B);
	void update(int x0, int y0, bool always, sf::IntRect B, float c);

};
void particle_spark::init(int x0, int y0, sf::IntRect B)
{
	dead = false;
	Brender = true;
	size = rand() & 3;
	int b = 150;
	color.r = b;
	color.g = rand() % b;
	color.b = 0;
	life = 0;
	//color = { 244,66 + rand() % 178,66, 0xFF };
	x = 0;
	y = 0;
	starpoint.x = x0;
	starpoint.y = y0;
	angle = (rand() % 359 + 1) * PI / 180;
	v = rand() % 10 - 5;
	a = v * cos(angle);
	b = v * sin(angle) - 0.5f*G;
	life_spawn = round(rand() % 40 + v);
	Bmain = B;

}
void particle_spark::update(int x0, int y0, bool always, sf::IntRect B, float c)
{
	if (dead == false)
	{
		scale = c;
		life++;
		if (v > 0)
			x += 0.05;
		else
			x -= 0.05;

		y = a*x + b*x*x;

		if (starpoint.y - y * 10 >= Bmain.height &&starpoint.x <= Bmain.width && starpoint.x >= Bmain.left) // basicly bounce off
		{
			//size--;
			if (v >= 0)
			{
				angle = PI / 16 * 5;

			}
			else
				if (v < 0)
				{
					angle = PI / 16 * 3;

				}
			a = v * cos(angle);

			b = v * sin(angle) - 0.5*G;
			starpoint.y = Bmain.height - 1;
			starpoint.x -= x * 10;
			x = 0;
			y = 0;
		}


		if (life > life_spawn && always == true)init(x0, y0, B);
		if (life > life_spawn && always == false) dead = true;



		if (Brender == false)Brender = true;
		if (starpoint.x > Bmain.width || starpoint.x < Bmain.left)
			Brender = false;

	}
}
void particle_spark::render(sf::RenderWindow &window, int level)
{
	if (dead == false)
		switch (level)
		{
		case 0:
			if (Brender == false)
			{
				sf::CircleShape shape(size*scale);



				shape.setPosition(starpoint.x - x * 10, starpoint.y - y * 10);
				shape.setFillColor(color);
				window.draw(shape);
			}
			break;
		case 1:
			if (Brender == true)
			{
				sf::CircleShape shape(size*scale);
				shape.setPosition(starpoint.x - x * 10, starpoint.y - y * 10);
				shape.setFillColor(color);
				window.draw(shape);
			}
			break;
		}




}
void sparcle_generator(sf::RenderWindow &win, particle_spark *spark, int x, int y, int count, bool always, sf::IntRect B, int level, float scale)
{
	for (int i = 0; i < count; i++)
	{

		spark[i].update(x, y, always, B, scale);
		spark[i].render(win, level);



	}
}


#endif