const double PI = 3.1415926535;
const unsigned int w = 800;
const unsigned int h = 600;
const unsigned int arenaSize = 800;
//#include <iostream>
using namespace std;
#include <string>
#include <SFML/Graphics.hpp>
#include <math.h>

sf::Color buttonColor = { 255, 66, 229, 255 };
sf::Color arenaColor = {200,200,200,255};
#include "../headers/particle_effect.h"
#include "../headers/diagonal_method.h"
//#include "../headers/starfield.h"
#include "../headers/mainMenu.h"
#include "../headers/movement.h"
#include "../headers/intro.h"

/*
void loadConfig()
{
	std::ifstream fin("data/config.txt");
	std::string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		std::istringstream strin(line.substr(line.find("=") + 1));
		if (line.find("width") != -1)
		{
			strin >> Width;
		}
		else if (line.find("height") != -1)
		{
			strin >> Height;
		}
		else if (line.find("background color") != -1)
		{
			strin >> data.background.r;
			strin >> data.background.g;
			strin >> data.background.b;
			strin >> data.background.a;
		}
		else if (line.find("edge color") != -1)
		{
			strin >> data.edge.r;
			strin >> data.edge.g;
			strin >> data.edge.b;
			strin >> data.edge.a;
		}
		else if (line.find("map color") != -1)
		{
			strin >> data.map.r;
			strin >> data.map.g;
			strin >> data.map.b;
			strin >> data.map.a;
		}
		else if (line.find("grid color") != -1)
		{
			strin >> data.grid.r;
			strin >> data.grid.g;
			strin >> data.grid.b;
			strin >> data.grid.a;
		}

		else if (line.find("textures dir") != -1)
		{
			strin >> data.textureDir;

		}
		else if (line.find("node texture") != -1)
		{
			strin >> data.nodeTexture;
		}
		else if (line.find("font dir") != -1)
		{
			strin >> data.fontDir;
		}
		else if (line.find("text font") != -1)
		{
			strin >> data.textFontSize;
			strin >> data.textFont;
		}
		else if (line.find("tree font") != -1)
		{
			strin >> data.treeFontSize;
			strin >> data.treeFont;
		}
		else if (line.find("button font color") != -1)
		{
			int r, g, b, a;
			strin >> r;
			strin >> g;
			strin >> b;
			strin >> a;
			data.buttonFontColor = make_color(r, g, b, a);
		}
		else if (line.find("tree color") != -1)
		{
			int r, g, b, a;
			strin >> r;
			strin >> g;
			strin >> b;
			strin >> a;
			data.treeFontColor = make_color(r, g, b, a);
		}
		else if (line.find("text color") != -1)
		{
			int r, g, b, a;
			strin >> r;
			strin >> g;
			strin >> b;
			strin >> a;
			textColor = make_color(r, g, b, a);
		}
		else if (line.find("Cursor") != -1)
		{


			strin >> data.cursorSpriteSize.x;
			strin >> data.cursorSpriteSize.y;
			strin >> data.cursorSpriteLocation.x;
			strin >> data.cursorSpriteLocation.y;
			strin >> data.cursorSprite;
			int c = 0;
			for (int i = 0; i < data.cursorSpriteLocation.y; i++)
				for (int k = 0; k < data.cursorSpriteLocation.x; k++)
				{
					cursorSprite[c] = { k*data.cursorSpriteSize.x, i*data.cursorSpriteSize.y, data.cursorSpriteSize.x, data.cursorSpriteSize.y };
					c++;
				}

		}

	}
	fin.close();
}
*/


particle_spark particle[100];// (floor(map.x), floor(map.y)));

class combat_logic
{
private:
	character *mainD;
	character *enemy;
	sf::FloatRect bounds;
	int enemyCount;
public:
	bool bloodGenerate;
	void init(character *mainD, character *enemy, sf::FloatRect bounds, int enemyCount);
	void update(character *mainD, character *enemy);
	void check();
}game_core_logic;

void combat_logic::init(character *mainD_, character *enemy_, sf::FloatRect bounds_, int enemyCount_)
{
	mainD = mainD_;
	enemy = enemy_;
	bounds = bounds_;
	enemyCount = enemyCount_;
}
void combat_logic::update(character *mainD_, character *enemy_)
{
	mainD = mainD_;
	enemy = enemy_;
}

void combat_logic::check()
{

	cuboid mainHitBox = mainD->hitBox;
	sf::Vector2f mainCenter = mainD->getCenterPoint();
	float maxDist = mainD->getLenght();
	sf::Vector2f attackPointM = mainD->getAttackPoint();
	for (int i = 0; i < enemyCount; i++)
	{

		if (mainD->dir == 1)
		{
			sf::Vector2f enemyMid = enemy[i].getCenterPoint();
			if (mainHitBox.bottom.p2.x < enemyMid.x
				&&mainHitBox.bottom.p1.x< enemyMid.x
				&&mainHitBox.bottom.p2.y> enemyMid.y
				&&mainHitBox.bottom.p1.y < enemyMid.y
				&&enemyMid.x - mainCenter.x < maxDist
				&& mainD->block == false)
			{
				if (mainD->validAttack == true)
				{
					if (attackPointM.x > enemy[i].getCenterPoint().x)
					{
						enemy[i].life -= 0.1;
						mainD->validAttack = false;
						bloodGenerate = true;


					}
				}
				else
				{
					if (attackPointM.x < enemy[i].getCenterPoint().x)
						mainD->validAttack = true;
				}
			}
		}
		else
		{
			sf::Vector2f enemyMid = enemy[i].getCenterPoint();
			if (mainHitBox.bottom.p3.x > enemyMid.x
				&&mainHitBox.bottom.p0.x > enemyMid.x
				&&mainHitBox.bottom.p3.y > enemyMid.y
				&&mainHitBox.bottom.p0.y < enemyMid.y
				&&enemyMid.x - mainCenter.x < maxDist
				&& mainD->block == false)
			{
				if (mainD->validAttack == true)
				{
					if (attackPointM.x < enemy[i].getCenterPoint().x)
					{
						enemy[i].life -= 0.1;
						mainD->validAttack = false;
						bloodGenerate = true;
					}
				}
				else
				{
					if (attackPointM.x > enemy[i].getCenterPoint().x)
						mainD->validAttack = true;
				}
			}

		}


		if (enemy[i].dir == 1)
		{
			sf::Vector2f attackPointE = enemy[i].getAttackPoint();
			if (enemy[i].hitBox.bottom.p2.x < mainCenter.x
				&&enemy[i].hitBox.bottom.p1.x< mainCenter.x
				&&enemy[i].hitBox.bottom.p2.y> mainCenter.y
				&&enemy[i].hitBox.bottom.p1.y < mainCenter.y
				&&mainCenter.x - enemy[i].getCenterPoint().x < enemy[i].getLenght()
				&& enemy[i].block == false)
			{
				if (enemy[i].validAttack == true)
				{
					if (attackPointE.x > mainCenter.x)
					{
						mainD->life -= 0.01;
						enemy[i].validAttack = false;
					}
				}
				else
				{
					if (attackPointE.x < mainD->hitBox.bottom.p0.x)
						enemy[i].validAttack = true;
				}
			}
		}
		else
		{
			sf::Vector2f attackPointE = enemy[i].getAttackPoint();
			if (enemy[i].hitBox.bottom.p3.x > mainCenter.x
				&&enemy[i].hitBox.bottom.p0.x > mainCenter.x
				&&enemy[i].hitBox.bottom.p3.y > mainCenter.y
				&&enemy[i].hitBox.bottom.p0.y < mainCenter.y
				&&mainCenter.x - enemy[i].getCenterPoint().x < enemy[i].getLenght()
				&& enemy[i].block == false)
			{
				if (enemy[i].validAttack == true)
				{
					if (attackPointE.x < mainCenter.x)
					{
						mainD->life -= 0.01;
						enemy[i].validAttack = false;
					}
				}
				else
				{
					if (attackPointE.x > mainD->hitBox.bottom.p2.x)
						enemy[i].validAttack = true;
				}
			}

		}



	}



}
struct enemyControl
{
	int dir;
	sf::Vector2f attackPoint;
	bool block;
}enemyContr[2];

void AI(character *zomby, enemyControl *zombyControl, character *toKill)
{
	sf::Vector2f mainCenter = toKill->getCenterPoint();
	//movement control
	if (zomby->getCenterPoint().x > toKill->getCenterPoint().x)
	{
		if (zomby->hitBox.bottom.p3.y > mainCenter.y
			&&zomby->hitBox.bottom.p0.y < mainCenter.y
			&&mainCenter.x - zomby->getCenterPoint().x <zomby->getLenght()
			&& zomby->block == false)
			zombyControl->dir = 4;
		else
		if (zomby->hitBox.bottom.p3.y < mainCenter.y
			&& zomby->block == false)
			zombyControl->dir = 5;
		else
		if (zomby->hitBox.bottom.p0.y > mainCenter.y
			&& zomby->block == false)
			zombyControl->dir = 3;
	}else
	if (zomby->getCenterPoint().x < toKill->getCenterPoint().x)
	{
		if (zomby->hitBox.bottom.p2.y> mainCenter.y
			&&zomby->hitBox.bottom.p1.y < mainCenter.y
			&&mainCenter.x - zomby->getCenterPoint().x < zomby->getLenght()
			&& zomby->block == false)
			zombyControl->dir = 8;
		else
		if (zomby->hitBox.bottom.p2.y< mainCenter.y
			&& zomby->block == false)
			zombyControl->dir = 7;
		else
		if (zomby->hitBox.bottom.p1.y > mainCenter.y
			&& zomby->block == false)
			zombyControl->dir = 1;
	}else
		zombyControl->dir = 0;

	//attack control
	if (zomby->validAttack == true)
	{
		zombyControl->attackPoint = toKill->getCenterPointMid();
	}else
	{
		if (zomby->dir == 1)
			zombyControl->attackPoint = { 0,0 };
		else
			zombyControl->attackPoint = zomby->hitBox.top.p2;
	}



}



int main()
{
	enemyContr[0].dir = 0;
	enemyContr[0].attackPoint = { 0,0 };
	enemyContr[0].block = false;
	srand(time(NULL));
	sf::Vector3f battleGround[10][9];
	float battleGroundSpeed[10][9];
	int battleGroundH[10][9];
	sf::IntRect textureCrop[10][9];





	std::vector<sf::FloatRect> boundary;
	boundary.reserve(10);
	{
		boundary.push_back({0,100,0,700});//left bound
		boundary.push_back({ 0,800,800,0 });// upper bound
		boundary.push_back({ 800,100,0,700 });// right bound
		boundary.push_back({ 0,10,800,0 });// lower bound
	}




	

	//epic :DTESTTESTTEST
	//int time = sf::ran

	sf::RenderWindow window(sf::VideoMode(w, h), "Bramble Jam", sf::Style::Close);
	sf::CircleShape shape(100.f);
	sf::ConvexShape tile;
	shape.setFillColor(sf::Color::Green);
	sf::Vector2i position = sf::Mouse::getPosition();
	//*


	sf::IntRect Binit;
	//effect_g.x1, effect_g.y1

	Binit.height = 0;
	Binit.width = 0;
	Binit.top = 0;
	Binit.left = 0;


	//visas texturas ir media kad krautu per funkcija
	sf::Texture texture;
	if (!texture.loadFromFile("media/background_2.jpg"))
	{
		// error...
	}
	sf::Texture textureLogo;
	if (!textureLogo.loadFromFile("media/sfml_logo.png"))
	{
		// error...
	}
	sf::Sprite battleGroundAnim;
	battleGroundAnim.setTexture(texture);





	{
		int xT = 0;
		int yT = 0;
		int incramentX = texture.getSize().x / 8;
		int incramentY = texture.getSize().y / 8;
		

		for (int y = 7; y >= 0; y--)
		{
			for (int x = 1; x < 9; x++)
			{
				textureCrop[x][y] = { xT,yT,incramentX ,incramentY };
				xT += incramentX;
			}
			xT = 0;
			yT += incramentY;
		}
		for (int y = 8; y >=0; y--)
		{
			for (int x = -1; x < 9; x++)
			{
				
				battleGround[x + 1][y].x = static_cast<float>(x)*(arenaSize / 8);
				battleGround[x + 1][y].y = y*(arenaSize / 8) + 100;
				battleGround[x + 1][y].z = -1000;
				battleGroundSpeed[x + 1][y] = rand() % 15 + 5;

				if(y==8 || x== -1 || x == 8)battleGroundH[x + 1][y] = -250 +rand() % 50;
				else
					battleGroundH[x + 1][y] = -300;
			}
		}
	}







	sf::Texture menu_bg_image;
	if (!menu_bg_image.loadFromFile("media/scenary_menu_bg.png"))
	{
		// error...
	}
	sf::Texture enemy_0;
	if (!enemy_0.loadFromFile("media/enemy_0.jpg"))
	{
		// error...
	}
	sf::Texture bg_sky;
	if (!bg_sky.loadFromFile("media/sky_test.jpg"))
	{
		// error...
	}
	sf::Texture cloud_sprite_sheet;
	if (!cloud_sprite_sheet.loadFromFile("media/scenary_Clouds_sprite_sheet.png"))
	{
		// error...
	}

	sf::Texture sunray_texture;
	if (!sunray_texture.loadFromFile("media/sunray.png"))
	{
		// error...
	}
	if (!sf::Shader::isAvailable())
	{
		// shaders are not available...
	}

	sf::Texture sprite_test;
	if (!sprite_test.loadFromFile("media/old_lady_char.png"))
	{
		// error...
		//cout << "media/sprite_test.png nera tokio failo" << endl;
	}
	sf::Image blood_1;
	if (!blood_1.loadFromFile("media/Blood_2.png"))
	{
		// error...
	}
	sf::Texture effectOverLay;

	effectOverLay.create(w * 10, h * 10);

	character_init mainGuy, enemyGuy[2];
	sprite_test.setSmooth(true);
	enemy_0.setSmooth(true);



	mainGuy = { {80,80,120},{ 100,350 },&sprite_test,10, 1, true,false };
	enemyGuy[0] = { { 80,80,120 },{ 500, 350 },&enemy_0,0, 1, true,false };
	//enemyGuy[1] = { { 80,80,120 },{ 500, 200 },NULL,5, 1, true,true };

	character ourHero(&mainGuy);
	character enemy[1] = { (&enemyGuy[0]) };
	sf::FloatRect test;
	test.height = 0;


	game_core_logic.init(&ourHero, enemy, test, 1);

	sf::Sprite bgSky;
	sf::Sprite menu_bg;
	sf::Sprite cloud_sprite;
	cloud_sprite.setTexture(cloud_sprite_sheet);
	menu_bg.setTexture(menu_bg_image);

	bgSky.setTexture(bg_sky);
	bgSky.setScale(0.5, 0.5);
	bgSky.setPosition(0, -400);


	bool Anim = false;
	sf::Vector2i charMove;
	dimension charLocationReal;

	for (int i = 0; i < 100; i++)
	{
		particle[i].init(w / 2, h / 2, Binit);
	}
	//Star star[1000];
	//for (int i = 0; i < 1000; i++)
	//{
	//	star[i].init(w, h);
	//}

	cloud Cloud[25];
	for (int i = 0; i < 25; i++)
	{
		Cloud[i].init(w, h, 1000, &cloud_sprite);
	}


	{
		sf::Vector2u textureSize{ 1,1 };
		textureSize = cloud_sprite_sheet.getSize();
		float wT = textureSize.x / 3;
		float hT = textureSize.y / 4;
		int xT = 1;
		int yT = 1;
		for (int i = 0; i < 5; i++)
		{
			cloudeSpiteRec[i].left = wT*xT;
			cloudeSpiteRec[i].top = hT*yT;
			cloudeSpiteRec[i].width = wT;
			cloudeSpiteRec[i].height = hT;
			xT++;
			if (xT > 3)
			{
				xT = 1;
				yT++;
			}
		}

	}



	sf::ConvexShape box_1;
	box_1.setPointCount(4);
	box_1.setPoint(0, sf::Vector2f(0, 0));
	box_1.setPoint(1, sf::Vector2f(0, 100));
	box_1.setPoint(2, sf::Vector2f(100, 100));
	box_1.setPoint(3, sf::Vector2f(100, 0));
	box_1.setOrigin(50, 50);
	box_1.setPosition(w / 2, h / 2);
	box_1.setFillColor(sf::Color::Magenta);

	//*/
	sf::RectangleShape rec;
	tile.setPointCount(4);
	//rec.setS
	double angle = sin(30 * PI / 180) / sin(60 * PI / 180);
	float b = 500;
	int y0 = b / 2 * angle;
	tile.setPoint(0, sf::Vector2f(0, 0));
	tile.setPoint(1, sf::Vector2f(b / 2, -y0));
	tile.setPoint(2, sf::Vector2f(b, 0));
	tile.setPoint(3, sf::Vector2f(b / 2, y0));
	window.setFramerateLimit(60);


	int MenuSelected = 0;
	bool MenuRender = true;
	sf::Font font;
	if (!font.loadFromFile("fonts/SVBasicManual.ttf"))
	{
		//cout << "nera font" << endl;
	}
	sf::Text fps_show;
	fps_show.setFont(font);
	fps_show.setCharacterSize(12);
	fps_show.setFillColor(sf::Color::White);
	sf::FloatRect fps_text_origin = fps_show.getGlobalBounds();
	fps_show.setOrigin(fps_text_origin.width, fps_text_origin.height);
	sf::Texture buttonT;
	if (!buttonT.loadFromFile("media/dirt_test.jpg"))
	{
		//cout << "nera media/dirt_test.jpg texture" << endl;
	}
	menu MainMenu[5];
	menu charSeleect[6];
	sf::String MenuString[5];
	MenuString[0] = "New Game";
	MenuString[1] = "Continue";
	MenuString[2] = "Options";
	MenuString[3] = "Credits";
	MenuString[4] = "Exit";
	bool activeMenu[5] = {true,false,false, true, true};



	int k = 0;
	for (int i = 4, k = 1; i >= 0; i--, k++)
	{
		dimension textLoc = perspective(w, h, w / 2 - 3. / 16 * w, 0, 1. / 8 * h*k, 1, 1);
		//MainMenu[i].init(MenuString[i], &font, &buttonT,i+1, w / 2 - 3. / 16 * w, 1. / 8 * h * 2 + i * (1. / 8 * h), 3. / 8 * w, 1. / 8 * h - 1. / 8 * h *0.2);
		MainMenu[i].init(MenuString[i], &font, NULL, NULL, buttonColor, textLoc, i + 1, activeMenu[i], w / 2 - 3. / 16 * w, 0, 1. / 8 * h*k, 3. / 8 * w, 1. / 8 * h - 1. / 8 * h *0.2);
	}


	//___
	float boxSize = w / 5;
	sf::Vector2f boxlocation = { 0,0 };
	sf::RectangleShape selectBox[6];
	k = 0;
	for (int i = 0; i < 2; i++)
	{
		boxlocation.y += boxSize / 2;
		for (int l = 0; l < 3; l++)
		{
			boxlocation.x += boxSize / 2;

			dimension textLoc = perspective(w, h, w / 2 - 3. / 16 * w, 0, 1. / 8 * h*k, 1, 1);

			if (k == 3)
				charSeleect[k].init("", &font, &sprite_test, &headRec, buttonColor, textLoc, k + 1,true, boxlocation.x, 0, 1. / 8 * h + boxlocation.y, boxSize, boxSize);
			else
				charSeleect[k].init("", &font, NULL, NULL, buttonColor, textLoc, k + 1,false, boxlocation.x, 0, 1. / 8 * h + boxlocation.y, boxSize, boxSize);
			k++;
			boxlocation.x += boxSize;
		}
		boxlocation.x = 0;
		boxlocation.y += boxSize;
	}
	//___
	sf::Clock clock;

	// create a clock to track the elapsed time
	k = 0;
	bool hitGround = false;
	bool hitmove = true;
	init_boot(window, &font);
	while (window.isOpen())
	{
		window.clear();

		position = sf::Mouse::getPosition(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (MenuRender == true)
				for (int i = 0; i < 5; i++)
				{
					int check = MainMenu[i].handleEvent(&event, window, w, h);
					if (check != 0)
					{

						MenuSelected = check;
					}
				}
			if (MenuSelected == 1)
			{
				for (int i = 0; i < 6; i++)
				{
					int check = charSeleect[i].handleEvent(&event, window, w, h);
					if (check != 0)
					{
						if (check == 4)
							MenuSelected = 8;
						//test = check;
					}
				}
			}



			if (event.type == sf::Event::Closed || MenuSelected == 5)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				MenuSelected = 11;


		}
		switch (MenuSelected)
		{

		case 1:
		{
			MenuRender = false;


			window.draw(menu_bg);
			renderBackground(window, w, h, Cloud, 25);
			main_menu(window, w, h, charSeleect, 6);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				MenuSelected = 0;

			break;
		}
		case 2:
		{

			//__________
			if (event.type == event.MouseButtonPressed)
			{
				for (int i = 0; i < 100; i++)
				{
					particle[i].init(w / 2, h / 2, Binit);
				}

			}
			MenuRender = false;
			tile.setPosition(w / 2 - b / 2, h / 2);
			//window.draw(bgSky);
			window.draw(menu_bg);
			renderBackground(window, w, h, Cloud, 25);
			tile.setFillColor(sf::Color::Cyan);
			//window.draw(tile);
			tile.setPosition(w / 2, h / 2);

			//starField(window, star, 1000, 0, 0, w, h, 1);
			dimension tileD = perspective(w, h, 10, 50, 0, arenaSize, arenaSize);
			dimension tileD_deph = perspective(w, h, 10, 50, -50, arenaSize, arenaSize);
			float scale = tileD.p2.x - tileD.p3.x;
			float CharScale = scale;
			sf::ConvexShape tile;
			sf::ConvexShape tile_deph;
			tile.setPointCount(4);
			tile.setPoint(0, tileD.p0);
			tile.setPoint(1, tileD.p1);
			tile.setPoint(2, tileD.p2);
			tile.setPoint(3, tileD.p3);
			tile.setTexture(&texture);
			sf::ConvexShape tile_effectOverLay;
			tile_effectOverLay.setPointCount(4);
			tile_effectOverLay.setPoint(0, tileD.p0);
			tile_effectOverLay.setPoint(1, tileD.p1);
			tile_effectOverLay.setPoint(2, tileD.p2);
			tile_effectOverLay.setPoint(3, tileD.p3);
			tile_effectOverLay.setTexture(&effectOverLay);



			tile_deph.setPointCount(4);
			tile_deph.setPoint(0, tileD_deph.p0);
			tile_deph.setPoint(1, tileD_deph.p1);
			tile_deph.setPoint(2, tileD_deph.p2);
			tile_deph.setPoint(3, tileD_deph.p3);
			tile_deph.setFillColor(sf::Color::Green);
			//tile.setFillColor(sf::Color::);

			dimension effect = perspective(w, h, position.x, position.y, 0, 1, 1);
			dimension effect_g = perspective(w, h, 10, 50, 0, w - 20, position.y);

			scale = (effect_g.p1.x - effect_g.p0.x) / scale;

			sf::ConvexShape test;
			test.setPointCount(4);
			test.setPoint(0, effect_g.p0);
			test.setPoint(1, effect_g.p1);
			test.setPoint(2, effect_g.p2);
			test.setPoint(3, effect_g.p3);
			test.setFillColor(sf::Color::Transparent);
			test.setOutlineColor(sf::Color::White);
			sf::IntRect boundary;
			//effect_g.x1, effect_g.y1
			boundary.height = effect_g.p1.y;
			boundary.width = effect_g.p1.x;
			boundary.top = 0;
			boundary.left = effect_g.p0.x;
			if (boundary.height > tileD.p2.y)
			{
				boundary.height = h;
				test.setPoint(2, effect_g.p1);
				test.setPoint(3, effect_g.p0);
			}
			if (boundary.height < tileD.p1.y)
			{
				boundary.height = h;
				test.setPoint(2, effect_g.p1);
				test.setPoint(3, effect_g.p0);
			}

			if (event.type == event.MouseButtonPressed)
			{
				for (int i = 0; i < 100; i++)
				{
					particle[i].init(position.x, position.y, boundary);
				}
			}


			sparcle_generator(window, particle, effect.p0.x, effect.p0.y, 100, true, boundary, 0, scale);
			window.draw(tile_deph);
			window.draw(tile);
			window.draw(test);
			window.draw(tile_effectOverLay);


			sparcle_generator(window, particle, effect.p0.x, effect.p0.y, 100, true, boundary, 1, scale);

			//reikia daryti texutre AR rect[5] kad visas puses nudazytu
			DrawRec(window, w, h, position.x, position.y, 0, 100, 100, 100, NULL, 1, true, sf::Color::Cyan);
			DrawRec(window, w, h, 0,0, 150, 500, 20, 100, &bgSky, 0, true, sf::Color::Cyan);
			DrawRec(window, w, h, position.x, position.y, 450, 50, 200, 100, NULL, 0, true, sf::Color::Cyan);
			DrawRec(window, w, h, position.x, position.y, 300, 600, 50, 100, NULL, 0, true, sf::Color::Cyan);

			if (event.type == event.MouseButtonPressed)
			{
				unsigned int testx = position.x;
				unsigned int testy = position.y;
				effectOverLay.update(blood_1, testx, testy);
			}
			break;
		}


		case 0:
		{
			//sunRays(window, &sunray_texture, 400, 240, MainMenu[0].x, MainMenu[0].x + MainMenu[0].w, h- MainMenu[0].z- MainMenu[0].h, -50);
			//sunRays(window, &sunray_texture,400, 200, MainMenu[0].z, MainMenu[0].z + MainMenu[0].w, MainMenu[0].y, -50);


			MenuRender = true;

			window.draw(menu_bg);

			renderBackground(window, w, h, Cloud, 25);
			main_menu(window, w, h, MainMenu, 5);

			sf::Text game_name;
			game_name.setFont(font);
			game_name.setString("Bramble Jam");
			game_name.setCharacterSize(54);
			game_name.setFillColor(sf::Color::Magenta);
			game_name.setOutlineColor(sf::Color::Color(20, 20, 20, 255));
			game_name.setOutlineThickness(1);
			game_name.setOrigin(game_name.getGlobalBounds().width / 2,0 );
			game_name.setPosition(w/2, MainMenu[0].h);
			window.draw(game_name);



		}
		break;
		case 9:
		{
			MenuRender = false;
			window.draw(menu_bg);
			renderBackground(window, w, h, Cloud, 25);



			bool exit = true;
			for (int y = 8; y >= 0; y--)
			{
				for (int x = 9; x >= 5; x--)
				{
					if (battleGround[x][y].z < battleGroundH[x][y])
					{
						exit = false;
						battleGround[x][y].z += battleGroundSpeed[x][y];
					}
					else
						battleGround[x][y].z = battleGroundH[x][y];

					battleGroundAnim.setTextureRect(textureCrop[x][y]);
					DrawRec(window, w, h, battleGround[x][y].x, battleGround[x][y].y, battleGround[x][y].z, 100, 300, 100, &battleGroundAnim, 2, true, arenaColor);
				}
			}
			for (int y = 8; y >= 0; y--)
			{
				for (int x = 0; x < 5; x++)
				{
					if (battleGround[x][y].z < battleGroundH[x][y])
					{
						exit = false;
						battleGround[x][y].z += battleGroundSpeed[x][y];
					}
					else
						battleGround[x][y].z = battleGroundH[x][y];
					battleGroundAnim.setTextureRect(textureCrop[x][y]);
					DrawRec(window, w, h, battleGround[x][y].x, battleGround[x][y].y, battleGround[x][y].z, 100, 300, 100, &battleGroundAnim, 2, true, arenaColor);
				}
			}
			if (exit == true)
				MenuSelected = 10;


		}
			
			break;
		case 4:
		{
			MenuRender = false;
			sf::RectangleShape logo;
			sf::Text name;
			logo.setSize({ textureLogo.getSize().x + 0.f, textureLogo.getSize().y + 0.f });
			logo.setTexture(&textureLogo);
			logo.setOrigin({ logo.getSize().x / 2, logo.getSize().y / 2 });
			name.setFont(font);
			name.setString("Powered by");
			name.setCharacterSize(24);
			name.setFillColor(sf::Color::White);
			name.setOutlineColor(sf::Color::Black);
			name.setOutlineThickness(1);
			name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
			name.setPosition(window.getSize().x /2, window.getSize().y *2/5);
			logo.setPosition(name.getPosition().x, name.getPosition().y + logo.getSize().y*0.1);
			logo.setScale(0.1, 0.1);

			window.draw(name);
			window.draw(logo);
			name.setString("Developed by");
			name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
			name.setPosition(logo.getPosition().x, logo.getPosition().y+logo.getSize().y*0.1);
			window.draw(name);

			name.setString("\tSimutis PI16B\nDragonometrijos Komanda");
			name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
			name.move(0, name.getGlobalBounds().height);
			window.draw(name);



			break;
		}
		case 8:

			mainGuy = { { 80,80,120 },{ 100,350 },&sprite_test,6, 1, true,false };
			enemyGuy[0] = { { 80,80,120 },{ 500, 350 },&enemy_0,3, 1, true,false };
			ourHero.init(&mainGuy);
			enemy[0].init(&enemyGuy[0]);
			for (int y = 8; y >= 0; y--)
			{
				for (int x = -1; x < 9; x++)
				{

					battleGround[x + 1][y].x = static_cast<float>(x)*(arenaSize / 8);
					battleGround[x + 1][y].y = y*(arenaSize / 8) + 100;
					battleGround[x + 1][y].z = -1000;
					battleGroundSpeed[x + 1][y] = rand() % 15 + 5;

					if (y == 8 || x == -1 || x == 8)battleGroundH[x + 1][y] = -250 + rand() % 50;
					else
						battleGroundH[x + 1][y] = -300;
				}
			}
			MenuSelected = 9;
			break;
		case 10:
		{





			//setup
			MenuRender = false;
			tile.setPosition(w / 2 - b / 2, h / 2);
			window.draw(menu_bg);
			renderBackground(window, w, h, Cloud, 25);
			tile.setFillColor(sf::Color::Cyan);
			//window.draw(tile);
			tile.setPosition(w / 2, h / 2);

			//starField(window, star, 1000, 0, 0, w, h, 1);

			dimension tileD = perspective(w, h, 0, 100, 0, arenaSize, arenaSize);
			dimension tileD_deph = perspective(w, h, 0, 100, -100, arenaSize, arenaSize);

			sf::ConvexShape tile;
			sf::ConvexShape tile_deph;
			tile.setPointCount(4);
			tile.setPoint(0, tileD.p0);
			tile.setPoint(1, tileD.p1);
			tile.setPoint(2, tileD.p2);
			tile.setPoint(3, tileD.p3);

			tile_deph.setPointCount(4);
			tile_deph.setPoint(0, tileD_deph.p3);
			tile_deph.setPoint(1, tileD_deph.p2);
			tile_deph.setPoint(2, tileD.p2);
			tile_deph.setPoint(3, tileD.p3);
			tile_deph.setFillColor(arenaColor);
			tile.setTexture(&texture);

			//setup
			for (int y = 8; y >= 0; y--)
			{
				for (int x = 9; x >= 5; x--)
				{
					if (x == 9 || y == 8)
						DrawRec(window, w, h, battleGround[x][y].x, battleGround[x][y].y, battleGround[x][y].z, 100, 300, 100, NULL, 0, false, arenaColor);
				}
			}
			for (int y = 8; y >= 0; y--)
			{
				for (int x = 0; x < 5; x++)
				{
					if (x == 0 || y == 8)
						DrawRec(window, w, h, battleGround[x][y].x, battleGround[x][y].y, battleGround[x][y].z, 100, 300, 100, NULL, 0, false, arenaColor);
				}
			}

			window.draw(tile_deph);
			window.draw(tile);

			bool block = false;
			bool yMove = false;
			bool xMove = false;
			int dir;
			sf::Vector2i charLocation{ 0,0 };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				charLocation.x = 4;
				xMove = true;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				charLocation.x = 8;
				xMove = true;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				charLocation.y = 2;
				yMove = true;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				charLocation.y = 6;
				yMove = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				block = true;
			}

			if (yMove == true && xMove == true)
			{
				if (charLocation.y == 2 && charLocation.x == 8)
					dir = 1;
				else
					dir = (charLocation.x + charLocation.y) / 2;
			}
			else
				dir = charLocation.x + charLocation.y;


			//global check = check if dudes is dead, if hit is registred, or failed(like blocekd) if powerUp is pickedup, out of bounds all that shit

			ourHero.update(w, h);
			int ourHeroDead = ourHero.check();




			

			enemy[0].update(w, h);
			int enemyDead = enemy[0].check();
			AI(&enemy[0], &enemyContr[0], &ourHero);




			boundary.push_back(enemy[0].getRealDim());
			ourHero.control(dir, block, { position.x + 0.f, position.y + 0.f }, &boundary);
			boundary.pop_back();

			



			if (enemyDead == 0)
			{
				boundary.push_back(ourHero.getRealDim());
				enemy[0].control(enemyContr[0].dir, enemyContr[0].block, enemyContr[0].attackPoint, &boundary);
				boundary.pop_back();
			}



			if (enemy[0].getCenterPoint().y < ourHero.getCenterPoint().y)

			{


				if (enemyDead != 3)
				{
					enemy[0].draw(window);
				}
				else
				{
					enemyGuy[0].charLocation = { 500, 350 };

					enemy[0].init(&enemyGuy[0]);
				}
				if (ourHeroDead != 3)
					ourHero.draw(window);
				else
					MenuSelected = 12;
			}
			else
			{

				if (ourHeroDead != 3)
					ourHero.draw(window);
				else
					MenuSelected = 12;
				if (enemyDead != 3)
				{
					enemy[0].draw(window);
				}
				else
				{
					enemyGuy[0].charLocation = { 500, 350 };

					enemy[0].init(&enemyGuy[0]);
				}
			}
			//enemy[1].control(0, false, { position.x + 0.f, position.y + 0.f });
			//enemy[1].update(w, h);
			//enemy[1].check();
			//enemy[1].draw(window);
			game_core_logic.update(&ourHero, enemy);
			game_core_logic.check();




			float scale;
			//sf::IntRect bound = { static_cast<int>(tileD_deph.p3.x),0,static_cast<int>(tileD_deph.p2.x),static_cast<int>(ourHero.getCenterPoint().y) };

			sf::IntRect bound;
			bound.height = static_cast<int>(ourHero.getCenterPoint().y);
			bound.width = static_cast<int>(tileD_deph.p2.x);
			bound.top = 0;
			bound.left = static_cast<int>(tileD_deph.p3.x);
			if (game_core_logic.bloodGenerate == true)
			{
				scale = ourHero.scale;
				for (int i = 0; i < 100; i++)
				{
					particle[i].init(ourHero.getAttackPoint().x, ourHero.getAttackPoint().y, bound);
				}
				game_core_logic.bloodGenerate = false;
			}
			sparcle_generator(window, particle, ourHero.getAttackPoint().x, ourHero.getAttackPoint().y, 100, false, bound, 1, scale);
			break;
		}


			case 12:
			{
				MenuRender = false;
				sf::Text name;
				name.setFont(font);
				name.setString("GAME OVER");
				name.setCharacterSize(24);
				name.setFillColor(sf::Color::White);
				name.setOutlineColor(sf::Color::Black);
				name.setOutlineThickness(1);
				name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
				name.setPosition(window.getSize().x / 2, window.getSize().y * 2 / 5);

				window.draw(name);



				break;
			}
		default:
			MenuRender = true;
			window.draw(menu_bg);
			renderBackground(window, w, h, Cloud, 25);
			main_menu(window, w, h, MainMenu, 5); //windowPoz.y - z - h
			break;
		}

		sf::Time elapsed1 = clock.getElapsedTime();
		clock.restart();
		std::string fps_text = std::to_string(elapsed1.asMilliseconds());
		//cout << fps_text << endl;
		fps_show.setString(fps_text);
		fps_show.setPosition(w, h);
		window.draw(fps_show);
		window.display();


	}

	return 0;
}