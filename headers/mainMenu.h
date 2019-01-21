
#pragma once
#ifndef mainMenu_h
#define mainMenu_h


sf::IntRect cloudeSpiteRec[11];


void sunRays(sf::RenderWindow &window, sf::Texture *sunray_texture, int w, int h, int xL, int xR, int y, int size) //DEMO
{
	func_line left_ray, right_ray;
	line_regression(&left_ray, w, h, xL, y);
	line_regression(&right_ray, w, h, xR, y);

	func_line vertical;
	line_regression(&vertical, xL, y + size, xR, y + size);
	line_meet(&left_ray, &vertical);
	line_meet(&right_ray, &vertical);

	sf::ConvexShape sunRay;
	sunRay.setPointCount(4);
	sunRay.setPoint(0, sf::Vector2f(xL, y));
	sunRay.setPoint(1, sf::Vector2f(xR, y));
	sunRay.setPoint(2, sf::Vector2f(right_ray.x, right_ray.y));
	sunRay.setPoint(3, sf::Vector2f(left_ray.x, left_ray.y));
	if (sunray_texture == NULL)
	{
		sunRay.setFillColor(sf::Color::Transparent);
		sunRay.setOutlineThickness(1);
		sunRay.setOutlineColor(sf::Color::Black);
	}
	else
		sunRay.setTexture(sunray_texture);
	sunRay.setFillColor(sf::Color::Color(248, 204, 103));//reikia kad spalvas is funkcijos gautu
	window.draw(sunRay);

}


void InitRec(sf::ConvexShape *rec, const sf::Texture *cube, sf::IntRect setT, dimension cub, int side, sf::Color color)
{

	rec->setPointCount(4);
	rec->setPoint(0, cub.p0);
	rec->setPoint(1, cub.p1);
	rec->setPoint(2, cub.p2);
	rec->setPoint(3, cub.p3);
	if (cube == NULL)
	{
		switch (side)
		{
		case 0:case 1:case 2:case 3:
		{
			sf::Color darkerColor = color;

			darkerColor.r = color.r - 25;
			darkerColor.g = color.g - 25;
			darkerColor.b = color.b - 25;
			color = darkerColor;
			break;
		}
		case 5:
		{
			sf::Color darkerColor = color;

			darkerColor.r = color.r - 50;
			darkerColor.g = color.g - 50;
			darkerColor.b = color.b - 50;
			color = darkerColor;
			break;
		}
		default:
			break;
		}
		rec->setFillColor(color);
		if (cub.p0.y + 3 >= cub.p2.y && cub.p0.y - 3 <= cub.p2.y)
		{
			rec->setOutlineThickness(0);
			//rec->setOutlineColor(sf::Color::Black);
		}
		else
			if (cub.p0.x + 3 >= cub.p2.x && cub.p0.x - 3 <= cub.p2.x)
			{
				rec->setOutlineThickness(0);
				//rec->setOutlineColor(sf::Color::Black);
			}
			else
			{
				rec->setOutlineThickness(1);
				rec->setOutlineColor(sf::Color::Black);
			}

	}
	else
	{
		rec->setTexture(cube);
		switch (side)
		{
		case 0:
		{
			rec->setFillColor({ 158, 158, 158 });
			break;
		}
		}
		rec->setTextureRect(setT);
	}
}
struct cuboid
{
	dimension bottom;
	dimension top;
};
cuboid getBox(sf::Vector2u Wsize, float x, float y, float z, float w, float h, float l)
{
	dimension bottom = perspective(Wsize.x, Wsize.y, x, y, z, w, l);
	dimension top = perspective(Wsize.x, Wsize.y, x, y, h + z, w, l);
	return { bottom, top };
}



void DrawRec(sf::RenderWindow &window, int wp, int hp, float x, float y, float z, float w, float h, float l, sf::Sprite  * sprite, int Side, bool drawRestSide, sf::Color color)
{
	const sf::Texture *cube = NULL;
	sf::Vector2u textureSize{ 1,1 };
	if (sprite != NULL)
	{
		cube = sprite->getTexture();
		textureSize = cube->getSize();
	}

	dimension bottom = perspective(wp, hp, x, y, z, w, l);
	dimension top = perspective(wp, hp, x, y, h + z, w, l);
	dimension passL;
	passL.p0 = top.p0;
	passL.p1 = top.p3;
	passL.p2 = bottom.p3;
	passL.p3 = bottom.p0;
	dimension passR;
	passR.p0 = top.p1;
	passR.p1 = top.p2;
	passR.p2 = bottom.p2;
	passR.p3 = bottom.p1;
	dimension passF;
	passF.p0 = top.p3;
	passF.p1 = top.p2;
	passF.p2 = bottom.p2;
	passF.p3 = bottom.p3;
	dimension pass;
	pass.p0 = top.p0;
	pass.p1 = top.p3;
	pass.p2 = bottom.p3;
	pass.p3 = bottom.p0;
	dimension passBack;
	passBack.p0 = top.p0;
	passBack.p1 = top.p1;
	passBack.p2 = bottom.p1;
	passBack.p3 = bottom.p0;
	sf::ConvexShape cubeDraw_B;
	sf::ConvexShape cubeDraw_T;
	sf::ConvexShape cubeDraw_L;
	sf::ConvexShape cubeDraw_R;
	sf::ConvexShape cubeDraw_F;
	sf::ConvexShape cubeDraw_Back;


	float wT = textureSize.x / 3;
	float hT = textureSize.y / 2;
	
	sf::IntRect side[6];
	int xT = 1;
	int yT = 1;
	for (int i = 0; i < 6; i++)
	{
		side[i].left = wT*xT;
		side[i].top = hT*yT;
		side[i].width = wT;
		side[i].height = hT;
		xT++;
		if (xT > 3)
		{
			xT = 1;
			yT++;
		}
	}
	if (drawRestSide == true)
	{
		if (Side != 1)
			InitRec(&cubeDraw_B, NULL, side[0], bottom, 0, color);
		if (Side != 2)
			InitRec(&cubeDraw_T, NULL, side[1], top, 1, color);
		if (Side != 3)
			InitRec(&cubeDraw_L, NULL, side[2], pass, 2, color);
		if (Side != 4)
			InitRec(&cubeDraw_R, NULL, side[3], passR, 3, color);
		if (Side != 5)
			InitRec(&cubeDraw_F, NULL, side[4], passF, 4, color);
		if (Side != 6)
			InitRec(&cubeDraw_Back, NULL, side[5], passBack, 5, color);
	}



	if (Side == 0)
	{
		InitRec(&cubeDraw_Back, cube, side[5], passBack, 5, color);
		InitRec(&cubeDraw_B, cube, side[0], bottom, 0, color);
		InitRec(&cubeDraw_T, cube, side[1], top, 1, color);
		InitRec(&cubeDraw_L, cube, side[2], pass, 2, color);
		InitRec(&cubeDraw_R, cube, side[3], passR, 3, color);
		InitRec(&cubeDraw_F, cube, side[4], passF, 4, color);

		window.draw(cubeDraw_Back);
		if (wp / 2 - top.p1.x > 0)
		{
			window.draw(cubeDraw_L);
			window.draw(cubeDraw_B);
			window.draw(cubeDraw_T);
			window.draw(cubeDraw_R);
			window.draw(cubeDraw_F);
		}
		else
			if (wp / 2 - top.p0.x < 0)
			{
				window.draw(cubeDraw_R);
				window.draw(cubeDraw_B);
				window.draw(cubeDraw_T);
				window.draw(cubeDraw_L);
				window.draw(cubeDraw_F);

			}
			else
			{
				window.draw(cubeDraw_L);
				window.draw(cubeDraw_R);
				window.draw(cubeDraw_B);
				window.draw(cubeDraw_T);
				window.draw(cubeDraw_F);
			}
	}
	else
	{
		switch (Side)
		{
		case 1:
		{
			sf::IntRect side;
			if (cube != NULL)
				side = sprite->getTextureRect();
			InitRec(&cubeDraw_B, cube, side, bottom, 0, color);
			window.draw(cubeDraw_Back);
			window.draw(cubeDraw_B);
			if (drawRestSide == true)
			{
				if (wp / 2 - top.p1.x > 0)
				{
					window.draw(cubeDraw_L);
					window.draw(cubeDraw_T);
					window.draw(cubeDraw_R);
					window.draw(cubeDraw_F);



				}
				else
					if (wp / 2 - top.p0.x < 0)
					{
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_T);
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_F);

					}
					else
					{
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_T);
						window.draw(cubeDraw_F);
					}
			}


			break;
		}
		case 2:
		{
			if (drawRestSide == true)
			{

				window.draw(cubeDraw_Back);
				window.draw(cubeDraw_B);
				if (wp / 2 - top.p1.x > 0)
				{
					window.draw(cubeDraw_L);
					window.draw(cubeDraw_R);
					window.draw(cubeDraw_F);
				}
				else
					if (wp / 2 - top.p0.x < 0)
					{
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_F);

					}
					else
					{
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_F);
					}
			}
			sf::IntRect side;
			if (cube != NULL)
				side = sprite->getTextureRect();
			InitRec(&cubeDraw_T, cube, side, top, 1, color);
			window.draw(cubeDraw_T);

			if (drawRestSide == true)
			{

			}




			break;
		}
		case 3:
		{
			sf::IntRect side;
			if (cube != NULL)
				side = sprite->getTextureRect();
			if (drawRestSide == true)
			{
				window.draw(cubeDraw_Back);
				window.draw(cubeDraw_B);
				window.draw(cubeDraw_T);
			}
			InitRec(&cubeDraw_L, cube, side, passL, 2, color);
			window.draw(cubeDraw_L);
			if (drawRestSide == true)
			{
				if (wp / 2 - top.p1.x > 0)
				{
					window.draw(cubeDraw_R);
					window.draw(cubeDraw_F);
				}
				else
					if (wp / 2 - top.p0.x < 0)
					{
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_F);
					}
					else
					{
						window.draw(cubeDraw_F);
					}
			}
			break;
		}
		case 4:
		{


			if (drawRestSide == true) {
				window.draw(cubeDraw_Back);
				window.draw(cubeDraw_B);
				window.draw(cubeDraw_T);
				if (wp / 2 - top.p1.x > 0)
					window.draw(cubeDraw_F);
			}
			sf::IntRect side;
			if (cube != NULL)
				side = sprite->getTextureRect();
			InitRec(&cubeDraw_R, cube, side, passR, 3, color);
			window.draw(cubeDraw_R);

			if (drawRestSide == true)
			{

				if (wp / 2 - top.p0.x < 0)
				{
					window.draw(cubeDraw_L);
					window.draw(cubeDraw_F);

				}
				else
				{
					window.draw(cubeDraw_F);
				}

			}
			break;
		}
		case 5:
		{
			if (drawRestSide == true)
			{
				window.draw(cubeDraw_Back);
				if (wp / 2 - top.p1.x > 0)
				{
					window.draw(cubeDraw_L);
					window.draw(cubeDraw_B);
					window.draw(cubeDraw_T);
					window.draw(cubeDraw_R);



				}
				else
					if (wp / 2 - top.p0.x < 0)
					{
						window.draw(cubeDraw_B);
						window.draw(cubeDraw_T);
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_L);

					}
					else
					{
						window.draw(cubeDraw_L);
						window.draw(cubeDraw_R);
						window.draw(cubeDraw_B);
						window.draw(cubeDraw_T);
					}
			}
			sf::IntRect side;
			if (cube != NULL)
				side = sprite->getTextureRect();
			InitRec(&cubeDraw_F, cube, side, passF, 4, color);
			window.draw(cubeDraw_F);


			break;
		}
		default:
			break;
		}



	}

}

class menu
{
private:
	bool clicked;
	bool active;
	//
	sf::Text name;
	bool hasTexture;
	sf::Sprite look;
	int id;
	//
	particle_spark particle[10];
	//

	int randAnimation;
	dimension buttonD;
	int mCurrentSprite;
	int w1, h1, x1, y1, l1, z1; // for scaling
	sf::Color buttonC;
public:
	int w, h, x, y, z; // for reference

	menu() {};
	void render(sf::RenderWindow &window, int w, int h);
	//void init(int x, int y, sf::IntRect B);
	void update();
	void init(sf::String Name, sf::Font *font, sf::Texture *buttonT, sf::IntRect *partTexture, sf::Color c, dimension textLoc, int buttonID,bool active, int x, int y, int z, int w, int h);
	int handleEvent(sf::Event* e, sf::RenderWindow &window, int unsigned w, int unsigned h);

};



int menu::handleEvent(sf::Event* e, sf::RenderWindow &window, int unsigned wp, int unsigned hp)
{

	if ((e->type == e->MouseMoved || e->type == e->MouseButtonPressed || e->type == e->MouseButtonReleased) && active == true)
	{
		//Get mouse position

		int xM, yM;
		xM = sf::Mouse::getPosition(window).x;
		yM = sf::Mouse::getPosition(window).y;

		sf::Vector2u  windowPoz = { wp, hp };
		//SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		bool inside = true;
		//Mouse is left of the button
		sf::Vector2f bSize;
		if (xM < x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (xM > x + w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (yM < windowPoz.y - z - h)
		{
			inside = false;
		}
		//Mouse below the button
		else if (yM > windowPoz.y - z)
		{
			inside = false;
		}
		//Mouse is outside button

		if (!inside)//&& !clicked)
		{
			clicked = false;
			mCurrentSprite = 0;
		}
		//Mouse is inside button
		else
		{
			if (!clicked && e->type == e->MouseMoved)
			{
				mCurrentSprite = 1;
			}
			if (clicked &&e->type == e->MouseButtonReleased) //&& mCurrentSprite.b == BUTTON_SPRITE_MOUSE_DOWN.b && mCurrentSprite.g == BUTTON_SPRITE_MOUSE_DOWN.g&& mCurrentSprite.r == BUTTON_SPRITE_MOUSE_DOWN.r)
			{
				mCurrentSprite = 2;
				clicked = false;
				return id;
			}
			if (!clicked && e->type == e->MouseButtonPressed)
			{
				clicked = true;
				mCurrentSprite = 3;
			}
		}
	}
	return 0;
}


void menu::update()
{

	if (mCurrentSprite == 3 || active == false)
	{
		y1 = 10;
	}
	else
	{
		y1 = y;
	}

}



void menu::init(sf::String Name, sf::Font *font, sf::Texture *buttonT, sf::IntRect *partTexture, sf::Color c, dimension textLoc, int buttonID, bool active_, int x0, int y0, int z0, int w0, int h0)
{
	active = active_;
	mCurrentSprite = 0;
	id = buttonID;
	x = x1 = x0;
	y = y1 = y0;
	z = z1 = z0;
	w = w1 = w0;
	h = h1 = h0;
	l1 = h0;
	buttonC = c;
	//cout << x << " " << y << " " << 600 -z << " " << w << " " << h << " " << endl;
	clicked = false;
	randAnimation = 0;
	if (buttonT != NULL)
	{
		look.setTexture(*buttonT);
		hasTexture = true;
		if (partTexture != NULL)
			look.setTextureRect(*partTexture);
	}
	else
		hasTexture = false;
	/*
	button.setPosition(x0, y0);
	button.setTexture(buttonT);
	button.setTextureRect(sf::IntRect(0, 0, w0, h0));//nereikia sito
	button.setSize(sf::Vector2f(w0, h0));
	*/


	name.setFont(*font);
	name.setString(Name);
	name.setCharacterSize(24);
	name.setFillColor(sf::Color::White);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	sf::FloatRect textSize = name.getLocalBounds();

	name.setPosition(textLoc.p0.x + w0 / 2 - textSize.width / 2, textLoc.p0.y - h0 / 2 - textSize.height);
	randAnimation = 500 + rand() % 1000;

	//name.setPosition(x, y);



}




void menu::render(sf::RenderWindow &window, int w, int h)
{

	if (hasTexture == true)
		DrawRec(window, w, h, x1, y1, z1, w1, h1, l1, &look, 5, true, buttonC);
	else
		DrawRec(window, w, h, x1, y1, z1, w1, h1, l1, NULL,  0, true, buttonC);


	//window.draw(button);

	window.draw(name);

}
class cloud
{
private:
	int x, y;//random location on ground
	int z; // const cloud up
	int speed; // random small number
	int cloud_sprite_rec_id;
	sf::Vector2u windowSize;
	int w, h; //for reference
	sf::Sprite *cloud_sprite;

	//sf::IntRect *cloud_sprite_rec;


public:
	cloud();
	void init(int w0, int h0, int z0, sf::Sprite *Cloud);
	void update();
	void render(sf::RenderWindow &window, int unsigned wp, int unsigned hp);


};

cloud::cloud()
{
	windowSize = { 0,0 };
}
void cloud::init(int w0, int h0, int z0, sf::Sprite *Cloud)
{
	w = w0;
	h = h0;
	z = z0 + rand() % 100;
	cloud_sprite = Cloud;
	y = rand() % 100000;

	dimension findX;

	if (windowSize.x != 0 && windowSize.y != 0)
	{
		x = 10;
		findX = perspective(windowSize.x, windowSize.y, x, y, z, w, h);
		while (findX.p0.x < windowSize.x)
		{
			x *= 2;
			findX = perspective(windowSize.x, windowSize.y, x, y, z, w, h);

		}

	}
	else
		x = rand() % 10000;
	speed = rand() % 10 + 1;
	cloud_sprite_rec_id = rand() % 11;
}
void cloud::update()
{
	x -= speed;
	dimension check = perspective(windowSize.x, windowSize.y, x, y, z, w, h);

	if (check.p2.x < 0)
		init(w, h, z, cloud_sprite);


}
void cloud::render(sf::RenderWindow &window, int unsigned  wp, int unsigned  hp)
{
	//cloudeSpiteRec[]
	windowSize = { wp,wp };
	cloud_sprite->setTextureRect(cloudeSpiteRec[cloud_sprite_rec_id]);

	DrawRec(window, wp, hp, x, y, 1000, w, h, 1, cloud_sprite, 5, false, sf::Color::Cyan);
}


void renderBackground(sf::RenderWindow &window, int w, int h, cloud *renderCloud, int count)
{
	for (int i = 0; i < count; i++)
	{
		renderCloud[i].update();
		renderCloud[i].render(window, w, h);
	}
}





void main_menu(sf::RenderWindow &window, int w, int h, menu *Menu, int buttonCount)
{



	for (int i = buttonCount - 1; i >= 0; i--)
	{
		Menu[i].update();
		Menu[i].render(window, w, h);
	}
}


#endif // !mainMenu_h
