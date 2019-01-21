#pragma once
#ifndef movement_h
#define movement_h


struct char_sprite
{
	//sf::Rect 

};
sf::IntRect headRec = { 0,0,200,200 };
sf::IntRect bodyRec = { 0,200,150,200 };
sf::IntRect armLeftUrec = { 200,0,250,100 };
sf::IntRect armLeftDrec = { 450,0,250,100 };
sf::IntRect armRightUrec = { 700,0,250,100 };
sf::IntRect armRightDrec = { 950,0,250,100 };

sf::IntRect legLeftUrec = { 200,100,250,100 };
sf::IntRect legLeftDrec = { 450,100,250,100 };
sf::IntRect legRightUrec = { 700,100,250,100 };
sf::IntRect legRightDrec = { 950,100,250,100 };

sf::IntRect swordRec = { 150,200,250,100 };

class segment
{
private:
	sf::Vector2f a, b;
	float len;
	segment *parent;
	float angle;
	int portion;
	sf::Color color;
public:
	segment(float x, float y, float len_, float angle_);
	segment() {};
	segment(segment *seg_, sf::Vector2f relax);
	void setLenght(float len_)
	{
		len = len_;
	}
	void setColor(sf::Color color_)
	{
		color = color_;
	}
	void show(sf::RenderWindow &window)
	{


		sf::Vertex seg[] =
		{
			sf::Vertex(sf::Vector2f(a.x, a.y)),
			sf::Vertex(sf::Vector2f(b.x , b.y))
		};
		seg[0].color = color;
		seg[1].color = color;
		window.draw(seg, 2, sf::Lines);


	}
	void calculateB()
	{
		float dx = len*cos(angle);
		float dy = len*sin(angle);

		b = sf::Vector2f(a.x + dx, a.y + dy);
	}
	void update(int x, int y, segment *seg_, int rules)
	{

		float dx = x - a.x;
		float dy = y - a.y;
		float dc = sqrt(dx*dx + dy*dy);
		portion = 0;
		if (dx > 0 && dy <= 0)//1
		{
			angle = asin(dy / dc);
			portion = 1;
		}
		else
			if (dx >= 0 && dy > 0)//4
			{
				angle = -2 * PI + asin(dy / dc);
				portion = 4;
			}
		if (dx <= 0 && dy < 0)//2
		{
			angle = -PI / 2 + asin(dx / dc);
			portion = 2;
		}
		else
			if (dx < 0 && dy >= 0) // 3
			{
				angle = -PI - asin(dy / dc);
				portion = 3;
			}
		calculateB();

		if (seg_ != NULL)
			switch (rules)
			{
			case -1:

				switch (seg_->portion)
				{
				case 4:
					if (!(seg_->angle > angle && angle > -2 * PI))
					{
						if (!(0 > angle && angle > PI + seg_->angle))
							angle = seg_->angle;
					}
					break;
				case 3:
					if (!(seg_->angle > angle && angle > -2 * PI))
					{
						if (!(0 > angle && angle > PI + seg_->angle))
							angle = seg_->angle;
					}
					break;
				case 2:
					if (!(seg_->angle > angle && angle > -PI + seg_->angle))
					{
						angle = seg_->angle;
					}

					break;
				case 1:
					if (!(seg_->angle > angle && angle > -PI + seg_->angle))
					{
						angle = seg_->angle;
					}

					break;

				default:
					break;
				}
				calculateB();
				break;
			case 1:

				switch (seg_->portion)
				{
				case 4:
					if (!(seg_->angle < angle && angle < 2 * PI + PI / 2 + angle) || (0 > angle && angle > -PI / 2))
					{
						angle = seg_->angle;
					}
					break;
				case 3:
					if (!(seg_->angle < angle))
					{
						angle = seg_->angle;
					}
					break;
				case 2:
					if (!(seg_->angle < angle))
					{
						if ((PI*-3. / 4. > angle > -2. * PI))
						{
							if (!(-2 * PI - (-PI - seg_->angle) > angle > -2 * PI))
								angle = -2 * PI - (-PI - seg_->angle);
						}
						else
							angle = seg_->angle;
					}
					break;
				case 1:

					if (!(seg_->angle < angle))// && angle < 0))
					{
						if ((PI*-3. / 4. > angle > -2. * PI))
						{
							if (!(-2 * PI - (-PI - seg_->angle) > angle > -2 * PI))
								angle = -2 * PI - (-PI - seg_->angle);
						}
						else
							angle = seg_->angle;
					}
					break;

				default:
					break;
				}

				//if (seg_->angle > angle)
			//		angle = seg_->angle;
				calculateB();
				break;
			default:
				break;
			}

	}
	sf::Vector2f getOrigin()
	{
		return a;
	}
	void setOrigin(sf::Vector2f a_)
	{
		a = a_;
	}
	sf::Vector2f getLast()
	{
		return b;
	}
	float getLength()
	{
		return len;
	}
	float getAngle()
	{
		return angle;
	}
	void set(int x, int y)
	{

		a.x = x - len*cos(angle);
		a.y = y - len*sin(angle);
	}
};

segment::segment(segment *seg_, sf::Vector2f relax)
{
	a = seg_->b;
	len = seg_->len;

	angle = seg_->angle;

	//seg_->update(relax.x, relax.y, seg_, 2);
	////sf::Vector2f origin_1 = seg[1].getOrigin();
	//calculateB();

	//seg_->set(relax.x, relax.y);

	//sf::Vector2f origin_2 = seg_->getOrigin();
	//seg_->update(origin_2.x, origin_2.y, seg_, 1);

	//seg_->setOrigin(b);
	calculateB();




}


segment::segment(float x, float y, float len_, float angle_)
{
	a = sf::Vector2f(x, y);
	len = len_;
	angle = angle_;
	calculateB();
}




class segmentMove
{
private:
	float cycle;
	bool hitGround;
	float speed;
	sf::Vector2f lock;
	float r;
public:
	sf::Vector2f moveLeg(bool *move);
	segmentMove() {};
	segmentMove(float speed_, float w, segment *connection)
	{
		cycle = 0;
		hitGround = false;
		speed = speed_;
		lock = connection[1].getLast();
		r = w;
	}
	void update(float speed_, float w, sf::Vector2f lock_)
	{
		cycle = 0;
		speed = speed_;
		lock = lock_;
		r = w;
		hitGround = false;
	}

};


sf::Vector2f segmentMove::moveLeg(bool *move)
{



	float yP = 0;
	if (hitGround == false)
		cycle += speed;

	if (cycle > r * 2) {
		cycle = r * 2;
		hitGround = true;
		*move = false;
		cycle = 0;

	}

	if (hitGround == false)
	{
		yP = sqrt(r*r - (cycle - r)*(cycle - r)) / 5;
	}


	float dx = lock.x + cycle;
	float dy = lock.y - yP;

	return sf::Vector2f(dx, dy);
}

sf::Vector2f kinematic(segment *connection, int count, sf::Vector2f point, int dir)
{

	sf::Vector2f origin_ = point;
	sf::Vector2f startPoint = connection[0].getOrigin();

	for (int i = count - 1; i >= 0; i--)
	{
		if (i - 1 < 0)
			connection[i].update(origin_.x, origin_.y, NULL, 0);
		else
			connection[i].update(origin_.x, origin_.y, &connection[i - 1], dir);

		connection[i].set(origin_.x, origin_.y);
		origin_ = connection[i].getOrigin();
	}
	for (int i = 0; i < count; i++)
	{
		connection[i].setOrigin(startPoint);
		startPoint = connection[i].getLast();

	}
	return connection[count - 1].getLast();

}

struct  character_init
{
	sf::Vector3i charDim;
	sf::Vector2f charLocation;
	sf::Texture *charLook;
	int speed;
	int dir;
	bool block;
	bool debug;

};

class character
{

private:
	bool globalBlock;
	sf::Vector3i charDim;

	dimension charGround;


	dimension charTop;
	dimension farLegLine;
	dimension closeLegLine;
	dimension legBackLen;
	dimension legFrontLen;
	dimension bodyLine;
	dimension shieldRest;
	float legR_len;
	float legL_len;

	cuboid midPoint;
	bool debug;
	sf::Vector2f LegR_check;
	sf::Vector2f LegL_check;
	sf::Vector2f legR_loc;
	sf::Vector2f legL_loc;
	sf::Vector2f attackPoint;
	sf::Vector2f attackDist;
	segment legR[2];
	segment legL[2];

	segment armR[2];
	segment armL[2];

	segment sword;
	int armR_count;
	sf::Vector2f charLocation;
	unsigned int w;
	unsigned int h;
	sf::Sprite charLook;

	sf::RectangleShape hp_indicator;
	sf::RectangleShape hp_indicator_fill;

	int speed;
	void death(sf::RenderWindow &window);
	void rise(sf::RenderWindow &window);
	bool dead;
	int deathCycle;
	bool initBool;
	bool execAnim[2];
public:
	//
	float scale;
	float life;
	bool block;
	bool validAttack;
	cuboid hitBox;
	int dir;
	//
	character(character_init *char_init);
	//character(float x, float y,int w, int h); // + texture 04/05
	void init(character_init *char_init);
	void draw(sf::RenderWindow &window);
	void update(int w, int h);
	int check();
	void control(int direction, bool deffence, sf::Vector2f attackPoint_, std::vector<sf::FloatRect> *boundary);
	sf::FloatRect getRealDim()
	{
		return { charLocation.x,charLocation.y,static_cast<float>(charDim.x),static_cast<float>(charDim.y) };
	}
	sf::Vector2f getAttackPoint()
	{
		return sword.getLast();
	}
	float getLenght()
	{
		return legR_len * 2;
	}
	sf::Vector2f getCenterPoint()
	{
		return midPoint.bottom.p0;
	}
	sf::Vector2f getCenterPointMid()
	{
		return midPoint.top.p0;
	}
};
character::character(character_init *char_init)
{
	init(char_init);
}


void character::init(character_init *char_init)
{
	speed = char_init->speed;
	dir = char_init->dir;
	if (char_init->charLook != NULL)
		charLook.setTexture(*char_init->charLook);
	debug = char_init->debug;
	charDim = char_init->charDim;
	charLocation = char_init->charLocation;// reikia kad perduotu
	globalBlock = char_init->block;

	execAnim[0] = true;
	initBool = false;
	execAnim[1] = false;
	life = 1;
	deathCycle = 0;
	dead = false;
	validAttack = true;
	attackPoint = { charDim.x + 0.f,charDim.y + 0.f };
	armR_count = 2;
	hp_indicator.setSize({ charDim.x + 0.f,charDim.x / 8 + 0.f });
	hp_indicator_fill.setSize({ charDim.x + 0.f,charDim.x / 8 + 0.f });
	hp_indicator.setFillColor(sf::Color::Transparent);
	hp_indicator.setOutlineThickness(2);
	hp_indicator.setOutlineColor(sf::Color::Black);
	hp_indicator_fill.setFillColor(sf::Color::Green);
	hp_indicator_fill.setOutlineThickness(0);

	hp_indicator.setOrigin(0, charDim.x / 8 + 0.f);
	hp_indicator_fill.setOrigin(0, charDim.x / 8 + 0.f);


	legR_loc = { 0,0 };
	legL_loc = { 0,0 };
	legL[0] = segment{ 0,0,1,0 };
	legL[1] = segment{ &legL[0] ,{ 0,0 } };
	legL[0].setColor(sf::Color::Blue);
	legL[1].setColor(sf::Color::Blue);

	legR[0] = segment{ 0,0,1,0 };
	legR[1] = segment{ &legR[0] ,{ 0,0 } };
	legR[0].setColor(sf::Color::Black);
	legR[1].setColor(sf::Color::Black);

	armR[0] = segment{ 0,0,1,0 };
	for (int i = 1; i < armR_count; i++)
		armR[i] = segment{ &armR[i - 1] ,{ 0,0 } };
	//armR[2] = segment{ &armR[1] ,{ 0,0 } };
	for (int i = 0; i < armR_count; i++)
		armR[i].setColor(sf::Color::Black);

	sword = segment{ 0,0,1,0 };
	//armR[1].setColor(sf::Color::Black);
	//armR[2].setColor(sf::Color::Black);

	armL[0] = segment{ 0,0,1,0 };
	armL[1] = segment{ &armL[0] ,{ 0,0 } };
	armL[0].setColor(sf::Color::Blue);
	armL[1].setColor(sf::Color::Blue);
}
void character::update(int wp, int hp)
{
	w = wp;
	h = hp;

	charGround = perspective(w, h, charLocation.x, charLocation.y, 0, charDim.x, charDim.y);
	charTop = perspective(w, h, charLocation.x, charLocation.y, charDim.z, charDim.x, charDim.y);
	legBackLen = perspective(w, h, charLocation.x, charLocation.y + charDim.y, charDim.z / 2, 1, 1);
	legFrontLen = perspective(w, h, charLocation.x, charLocation.y, charDim.z / 2, 1, 1);
	bodyLine = perspective(w, h, charLocation.x + charDim.x / 2, charLocation.y + charDim.y / 2, charDim.z * 7 / 8, 1, 0);
	midPoint = getBox({ w,h }, charLocation.x + charDim.x / 2, charLocation.y + charDim.y / 2, 0, 1, charDim.z / 2, 0);


	hp_indicator.setPosition(charTop.p0.x, charTop.p0.y-20);
	hp_indicator_fill.setPosition(charTop.p0.x, charTop.p0.y-20);

	hp_indicator.setScale((charTop.p1.x - charTop.p0.x) / charDim.x, (charTop.p1.x - charTop.p0.x) / charDim.x);
	hp_indicator_fill.setScale((charTop.p1.x - charTop.p0.x) / charDim.x * life, (charTop.p1.x - charTop.p0.x) / charDim.x);
	if (dir == 1)
	{
		if (block == false)
			shieldRest = perspective(w, h, charLocation.x + charDim.x / 2, charLocation.y + charDim.y / 2, charDim.z / 2, 1, 0);
		else
		{
			shieldRest = perspective(w, h, charLocation.x + charDim.x, charLocation.y + charDim.y * 3 / 4, charDim.z / 2, 1, 0);
		}

		farLegLine = perspective(w, h, charLocation.x, charLocation.y + charDim.y * 3 / 4, 0, charDim.x, 0);
		closeLegLine = perspective(w, h, charLocation.x, charLocation.y + charDim.y * 1 / 4, 0, charDim.x, 0);

		legR_len = (charGround.p3.y - legFrontLen.p0.y) * 2 / 3;
		legL_len = (charGround.p0.y - legBackLen.p0.y) * 2 / 3;
	}
	else if (dir == -1)
	{
		if (block == false)
			shieldRest = perspective(w, h, charLocation.x + charDim.x / 2, charLocation.y + charDim.y / 2, charDim.z / 2, 1, 0);
		else
		{
			shieldRest = perspective(w, h, charLocation.x, charLocation.y + charDim.y * 3 / 4, charDim.z / 2, 1, 0);
		}

		closeLegLine = perspective(w, h, charLocation.x, charLocation.y + charDim.y * 3 / 4, 0, charDim.x, 0);
		farLegLine = perspective(w, h, charLocation.x, charLocation.y + charDim.y * 1 / 4, 0, charDim.x, 0);

		legL_len = (charGround.p3.y - legFrontLen.p0.y) * 2 / 3;
		legR_len = (charGround.p0.y - legBackLen.p0.y) * 2 / 3;
	}
	scale = (charTop.p1.x - charTop.p0.x) / charDim.x;
	legR[0].setOrigin(midPoint.top.p0);
	legR[0].setLenght(legR_len);
	legR[1].setLenght(legR_len);

	legL[0].setOrigin(midPoint.top.p0);
	legL[0].setLenght(legL_len);
	legL[1].setLenght(legL_len);

	armR[0].setOrigin(bodyLine.p0);
	for (int i = 0; i < armR_count; i++)
		armR[i].setLenght(legR_len);

	sword.setOrigin(armR[armR_count - 1].getLast());
	sword.setLenght(legR_len);

	//armR[1].setLenght(legR_len);
	//armR[2].setLenght(legR_len);
	armL[0].setOrigin(bodyLine.p0);
	armL[0].setLenght(legL_len);
	armL[1].setLenght(legL_len);

	hitBox = getBox({ w,h }, charLocation.x, charLocation.y, 0, 80, 120, 80);
}
void character::control(int direction, bool deffence, sf::Vector2f attackPoint_, std::vector<sf::FloatRect> *boundary)
{
	block = deffence;
	for (std::vector<sf::FloatRect>::const_iterator i = boundary->begin(); i != boundary->end(); ++i)
	{
		switch (direction)
		{
		case 1:
		{
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + charDim.x - speed <= i->left && (charLocation.x + speed + charDim.x) >= i->left)
				direction = 0;
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width))
				&& charLocation.y <= i->top - i->height && (charLocation.y + speed) >= i->top - i->height)
				direction = 0;
			dir = 1;
			break;
		}
		case 2:
		{
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width)) 
				&& charLocation.y <= i->top - i->height &&(charLocation.y + speed) >= i->top-i->height )
				direction = 0;
			break;
		}
		case 3:
		{
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + speed >= i->left + i->width && (charLocation.x - speed) <= i->left + i->width)
				direction = 0;
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width))
				&& charLocation.y <= i->top - i->height && (charLocation.y + speed) >= i->top - i->height)
				direction = 0;
			dir = -1;
			break;
		}
		case 4:
		{
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + speed >= i->left+i->width && (charLocation.x - speed) <= i->left + i->width)
				direction = 0;
			dir = -1;
			break;
		}
		case 5:
		{
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + speed >= i->left + i->width && (charLocation.x - speed) <= i->left + i->width)
				direction = 0;
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width))
				&& charLocation.y >= i->top && (charLocation.y - charDim.y - speed <= i->top))
				direction = 0;
			dir = -1;
			break;
		}
		case 6:
		{
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width)) 
				&& charLocation.y>= i->top &&(charLocation.y - charDim.y - speed <= i->top))
				direction = 0;
			break;
		}
		case 7:
		{
			if (((charLocation.x < i->left && charLocation.x + charDim.x > i->left) || (charLocation.x < i->left + i->width && charLocation.x + charDim.x > i->left + i->width) || (i->left < charLocation.x&& charLocation.x < i->left + i->width))
				&& charLocation.y >= i->top && (charLocation.y - charDim.y - speed <= i->top))
				direction = 0;
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + charDim.x - speed <= i->left && (charLocation.x + speed + charDim.x) >= i->left)
				direction = 0;
			dir = 1;
			break;
		}
		case 8:
		{
			if (((charLocation.y < i->top && charLocation.y + charDim.y > i->top) || (charLocation.y < i->top + i->height && charLocation.y + charDim.y > i->top + i->height) || (i->top < charLocation.y&& charLocation.y < i->top + i->height))
				&& charLocation.x + charDim.x - speed <= i->left && (charLocation.x + speed + charDim.x) >= i->left)
				direction = 0;
			dir = 1;
			break;
		}
		default:
			break;
		}

	}




	if (deffence == false)
	{
		switch (direction)
		{
		case 1:
			charLocation.x += speed / sqrt(2);
			charLocation.y += speed / sqrt(2);
			dir = 1;
			break;
		case 2:
			charLocation.y += speed;
			break;
		case 3:
			dir = -1;
			charLocation.x -= speed / sqrt(2);
			charLocation.y += speed / sqrt(2);
			break;
		case 4:
			dir = -1;
			charLocation.x -= speed;
			break;
		case 5:
			dir = -1;
			charLocation.x -= speed / sqrt(2);
			charLocation.y -= speed / sqrt(2);
			break;
		case 6:
			charLocation.y -= speed;
			break;
		case 7:
			dir = 1;
			charLocation.x += speed / sqrt(2);
			charLocation.y -= speed / sqrt(2);
			break;
		case 8:
			dir = 1;
			charLocation.x += speed;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (direction)
		{
		case 1:case 8:case 7:
			dir = 1;
			break;
		case 3:case 4: case 5:
			dir = -1;
			break;
		}
	}
	if (attackPoint.x > attackPoint_.x)
		attackPoint.x -= speed*2;

	if (attackPoint.x < attackPoint_.x)
		attackPoint.x += speed*2;

	if (attackPoint.y > attackPoint_.y)
		attackPoint.y -= speed*2;

	if (attackPoint.y < attackPoint_.y)
		attackPoint.y += speed*2;
	//cout << attackPoint.x << " " << attackPoint.y << endl;
	//attackPoint = attackPoint_;
	//cout << charLocation.x << " " << charLocation.y << endl;

}




int character::check()
{
	kinematic(armR, armR_count, { attackPoint.x,attackPoint.y }, dir*-1);

	kinematic(armL, 2, { shieldRest.p0.x,shieldRest.p0.y }, dir*-1);

	float testa = armR[armR_count - 1].getLast().y - armR[armR_count - 1].getOrigin().y;
	float testb = armR[armR_count - 1].getOrigin().x - armR[armR_count - 1].getLast().x;
	LegR_check = kinematic(legR, 2, legR_loc, dir);
	if (dir == 1)
	{
		kinematic(&sword, 1, { armR[armR_count - 1].getLast().x + testa,armR[armR_count - 1].getLast().y + testb }, 0);


	}
	else
	{
		///if (LegL_check.y > farLegLine.p0.y + 5 || LegL_check.y < farLegLine.p0.y - 5)legL_loc.y = farLegLine.p0.y;
		//if (LegR_check.y > closeLegLine.p0.y + 5 || LegR_check.y < closeLegLine.p0.y - 20)legR_loc.y = closeLegLine.p0.y;
		kinematic(&sword, 1, { armR[armR_count - 1].getLast().x - testa,armR[armR_count - 1].getLast().y - testb }, 0);


	}

		if (LegL_check.y > farLegLine.p0.y + 5 || LegL_check.y < farLegLine.p0.y - 20)legL_loc.y = farLegLine.p0.y;
		if (LegR_check.y > closeLegLine.p0.y + 5 || LegR_check.y < closeLegLine.p0.y - 20)legR_loc.y = closeLegLine.p0.y;
	// reikia tikslensiu skaiciavimu
	
	//__
	if (LegR_check.x + 2 < closeLegLine.p0.x)legR_loc = closeLegLine.p1;//reikia GAP idet
	if (LegR_check.x - 2 > closeLegLine.p1.x)legR_loc.x = closeLegLine.p0.x;



	//__
	LegL_check = kinematic(legL, 2, legL_loc, dir);

	if (LegL_check.x + 2 < farLegLine.p0.x)legL_loc = farLegLine.p1;
	if (LegL_check.x - 2 > farLegLine.p1.x)legL_loc.x = farLegLine.p0.x;



	if (LegR_check.x - 5 < LegL_check.x + 5 && LegR_check.x + 5 > LegL_check.x - 5)
	{
		legR_loc.x = midPoint.bottom.p0.x;
	}
	if (life < 0)
		dead = true;

	if (execAnim[1] == false && dead == true)
	{
		return 1;
	}

	if (execAnim[1] == true && dead == true && deathCycle!=0)
	{
		return 2;
	}
	if (execAnim[1] == true && dead == true && deathCycle == 0)
	{
		return 3;
	}
		return 0;

}
void character::draw(sf::RenderWindow &window)
{




	if (execAnim[0] == false && execAnim[1] == false)
	{
		if (dir == 1)
		{
			//1
			charLook.setRotation(armL[0].getAngle() * 180 / PI);
			charLook.setPosition(armL[0].getOrigin());
			charLook.setTextureRect(armLeftUrec);
			charLook.setScale(armL[0].getLength() / armLeftUrec.width, armL[0].getLength() / armLeftUrec.width);
			charLook.setOrigin(10, armLeftUrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);
			//2
			charLook.setRotation(armL[1].getAngle() * 180 / PI);
			charLook.setPosition(armL[1].getOrigin());
			charLook.setTextureRect(armLeftDrec);
			charLook.setScale(armL[1].getLength() / armLeftDrec.width, armL[1].getLength() / armLeftDrec.width);
			charLook.setOrigin(10, armLeftDrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);

			//3
			charLook.setRotation(legL[0].getAngle() * 180 / PI);
			charLook.setPosition(legL[0].getOrigin());
			charLook.setTextureRect(legLeftUrec);
			charLook.setScale(legL[0].getLength() / legLeftUrec.width, legL[0].getLength() / legLeftUrec.width);
			charLook.setOrigin(10, legLeftUrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);
			//4
			charLook.setRotation(legL[1].getAngle() * 180 / PI);
			charLook.setPosition(legL[1].getOrigin());
			charLook.setTextureRect(legLeftDrec);
			charLook.setScale(legL[1].getLength() / legLeftDrec.width, legL[1].getLength() / legLeftDrec.width);
			charLook.setOrigin(10, legLeftDrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);

			//5
			charLook.setRotation(0);
			charLook.setPosition(midPoint.top.p0);
			charLook.setTextureRect(bodyRec);
			charLook.setScale((midPoint.top.p0.y - bodyLine.p0.y) / bodyRec.width, (midPoint.top.p0.y - bodyLine.p0.y) / bodyRec.width);
			charLook.setOrigin(bodyRec.width / 2, bodyRec.height);
			window.draw(charLook);

			//6
			charLook.setRotation(legR[0].getAngle() * 180 / PI);
			charLook.setPosition(legR[0].getOrigin());
			charLook.setTextureRect(legRightUrec);
			charLook.setScale(legR[0].getLength() / legRightUrec.width, legR[0].getLength() / legRightUrec.width);
			charLook.setOrigin(10, legRightUrec.height / 2);
			window.draw(charLook);
			//7
			charLook.setRotation(legR[1].getAngle() * 180 / PI);
			charLook.setPosition(legR[1].getOrigin());
			charLook.setTextureRect(legRightDrec);
			charLook.setScale(legR[1].getLength() / legRightDrec.width, legR[1].getLength() / legRightDrec.width);
			charLook.setOrigin(10, legRightDrec.height / 2);
			window.draw(charLook);

			//8
			charLook.setRotation(0);
			charLook.setPosition(bodyLine.p0);
			charLook.setTextureRect(headRec);
			//charLook.set
			charLook.setScale((midPoint.top.p0.y - bodyLine.p0.y) / headRec.width, (midPoint.top.p0.y - bodyLine.p0.y) / headRec.width);
			charLook.setOrigin(headRec.width / 2, headRec.height);
			window.draw(charLook);

			//9
			charLook.setRotation(armR[0].getAngle() * 180 / PI);
			charLook.setPosition(armR[0].getOrigin());
			charLook.setTextureRect(armRightUrec);
			charLook.setScale(armR[0].getLength() / armRightUrec.width, armR[0].getLength() / armRightUrec.width);
			charLook.setOrigin(10, armRightUrec.height / 2);
			window.draw(charLook);
			//10
			charLook.setRotation(sword.getAngle() * 180 / PI);
			charLook.setPosition(sword.getOrigin());
			charLook.setTextureRect(swordRec);
			charLook.setScale(sword.getLength() / swordRec.width, sword.getLength() / swordRec.width);
			charLook.setOrigin(10, swordRec.height / 2);
			window.draw(charLook);
			//11
			charLook.setRotation(armR[1].getAngle() * 180 / PI);
			charLook.setPosition(armR[1].getOrigin());
			charLook.setTextureRect(armRightDrec);
			charLook.setScale(armR[1].getLength() / armRightDrec.width, armR[1].getLength() / armRightDrec.width);
			charLook.setOrigin(10, armRightDrec.height / 2);
			window.draw(charLook);


		}
		else
		{
			//1
			charLook.setRotation(armR[0].getAngle() * 180 / PI);
			charLook.setPosition(armR[0].getOrigin());
			charLook.setTextureRect(armRightUrec);
			charLook.setScale(armR[0].getLength() / armRightUrec.width, armR[0].getLength() / armRightUrec.width);
			charLook.setOrigin(10, armRightUrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);
			//2
			charLook.setRotation(sword.getAngle() * 180 / PI);
			charLook.setPosition(sword.getOrigin());
			charLook.setTextureRect(swordRec);
			charLook.setScale(sword.getLength() / swordRec.width, sword.getLength() / swordRec.width);
			charLook.setOrigin(10, swordRec.height / 2);
			window.draw(charLook);

			//3
			charLook.setRotation(armR[1].getAngle() * 180 / PI);
			charLook.setPosition(armR[1].getOrigin());
			charLook.setTextureRect(armRightDrec);
			charLook.setScale(armR[1].getLength() / armRightDrec.width, armR[1].getLength() / armRightDrec.width);
			charLook.setOrigin(10, armRightDrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);
			//4
			charLook.setRotation(legR[0].getAngle() * 180 / PI);
			charLook.setPosition(legR[0].getOrigin());
			charLook.setTextureRect(legRightUrec);
			charLook.setScale(legR[0].getLength() / legRightUrec.width, legR[0].getLength() / legRightUrec.width  * (-1));
			charLook.setOrigin(10, legRightUrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);

			//5
			charLook.setRotation(legR[1].getAngle() * 180 / PI);
			charLook.setPosition(legR[1].getOrigin());
			charLook.setTextureRect(legRightDrec);
			charLook.setScale(legR[1].getLength() / legRightDrec.width, legR[1].getLength() / legRightDrec.width  * (-1));
			charLook.setOrigin(10, legRightDrec.height / 2);
			charLook.setColor(sf::Color::Color(100, 100, 100, 255));
			window.draw(charLook);
			charLook.setColor(sf::Color::White);

			//6


			charLook.setRotation(0);
			charLook.setPosition(midPoint.top.p0);
			charLook.setTextureRect(bodyRec);
			charLook.setScale((midPoint.top.p0.y - bodyLine.p0.y) / bodyRec.width* (-1), (midPoint.top.p0.y - bodyLine.p0.y) / bodyRec.width);
			charLook.setOrigin(bodyRec.width / 2, bodyRec.height);
			window.draw(charLook);
			//7


			charLook.setRotation(legL[0].getAngle() * 180 / PI);
			charLook.setPosition(legL[0].getOrigin());
			charLook.setTextureRect(legLeftUrec);
			charLook.setScale(legL[0].getLength() / legLeftUrec.width, legL[0].getLength() / legLeftUrec.width  * (-1));
			charLook.setOrigin(10, legLeftUrec.height / 2);
			window.draw(charLook);
			//8


			charLook.setRotation(legL[1].getAngle() * 180 / PI);
			charLook.setPosition(legL[1].getOrigin());
			charLook.setTextureRect(legLeftDrec);
			charLook.setScale(legL[1].getLength() / legLeftDrec.width, legL[1].getLength() / legLeftDrec.width  * (-1));
			charLook.setOrigin(10, legLeftDrec.height / 2);
			window.draw(charLook);
			//9


			charLook.setRotation(0);
			charLook.setPosition(bodyLine.p0);
			charLook.setTextureRect(headRec);
			charLook.setScale((midPoint.top.p0.y - bodyLine.p0.y) / headRec.width  * (-1), (midPoint.top.p0.y - bodyLine.p0.y) / headRec.width);
			charLook.setOrigin(headRec.width / 2, headRec.height);
			window.draw(charLook);
			//10



			charLook.setRotation(armL[0].getAngle() * 180 / PI);
			charLook.setPosition(armL[0].getOrigin());
			charLook.setTextureRect(armLeftUrec);
			charLook.setScale(armL[0].getLength() / armLeftUrec.width, armL[0].getLength() / armLeftUrec.width);
			charLook.setOrigin(10, armLeftUrec.height / 2);
			window.draw(charLook);
			//11


			charLook.setRotation(armL[1].getAngle() * 180 / PI);
			charLook.setPosition(armL[1].getOrigin());
			charLook.setTextureRect(armLeftDrec);
			charLook.setScale(armL[1].getLength() / armLeftDrec.width, armL[1].getLength() / armLeftDrec.width);
			charLook.setOrigin(10, armLeftDrec.height / 2);
			window.draw(charLook);
		}


	}

	if (dead == true)
	{
		death(window);
	}
	else
	{
		window.draw(hp_indicator);
		window.draw(hp_indicator_fill);
		DrawRec(window, w, h, charLocation.x, charLocation.y, 0, 80, 0, 80, NULL, 1, false, sf::Color::Transparent);
		if (initBool == false)
			rise(window);

	}



	if (debug == true)
	{
		for (int i = 0; i < 2; i++)
			legR[i].show(window);
		for (int i = 0; i < 2; i++)
			legL[i].show(window);
		for (int i = 0; i < armR_count; i++)
			armR[i].show(window);
		for (int i = 0; i < 2; i++)
			armL[i].show(window);

		sword.show(window);
		DrawRec(window, w, h, charLocation.x + 32.5, charLocation.y + 32.5, 105, 15, 15, 15, NULL, 0, true, sf::Color::Yellow);
		DrawRec(window, w, h, charLocation.x, charLocation.y, 0, 80, 120, 80, NULL, 0, true, sf::Color::Transparent);

		sf::Vertex closeLegLine_[2] =
		{
			closeLegLine.p0,
			closeLegLine.p1
		};
		closeLegLine_[0].color = sf::Color::Red;
		closeLegLine_[1].color = sf::Color::Red;
		sf::Vertex farLegLine_[2] =
		{
			farLegLine.p0,
			farLegLine.p1
		};

		farLegLine_[0].color = sf::Color::Red;
		farLegLine_[1].color = sf::Color::Red;


		window.draw(farLegLine_, 2, sf::Lines);
		window.draw(closeLegLine_, 2, sf::Lines);

		sf::Vertex midpoint_[2] =
		{
			midPoint.bottom.p0,
			midPoint.top.p0
		};
		sf::Vertex attackDist_[2] =
		{
			midPoint.bottom.p0,
			midPoint.top.p0
		};


		midpoint_[0].color = sf::Color::Red;
		midpoint_[1].color = sf::Color::Red;

		window.draw(midpoint_, 2, sf::Lines);

		sf::Vertex bodyLine_[2] =
		{
			bodyLine.p0,


			midPoint.top.p0
		};

		bodyLine_[0].color = sf::Color::Green;
		bodyLine_[1].color = sf::Color::Green;

		window.draw(bodyLine_, 2, sf::Lines);
	}
}

void character::rise(sf::RenderWindow &window)
{

	if (execAnim[0] == false)
	{
		if (deathCycle < 0)
		{
			initBool = true;
			deathCycle = 0;
		}
		else
			deathCycle-=10;

	}
	else
	{


		if (deathCycle > charDim.z*1.5)
		{
			execAnim[0] = false;
			deathCycle = charDim.z*1.5;
		}
		else
			deathCycle+=10;
	}
	DrawRec(window, w, h, charLocation.x, charLocation.y, 0, charDim.x, deathCycle, charDim.y, NULL, 0, true, arenaColor);



}



void character::death(sf::RenderWindow &window)
{

	if (execAnim[1] == false)
	{

		if (deathCycle > charDim.z*1.5)
		{
			execAnim[1] = true;
			deathCycle = charDim.z*1.5;
		}
		else
			deathCycle+=5;
	}
	else
	{
		if (deathCycle <= 0)
		{
			deathCycle =0;
		}
		else
			deathCycle-=5;
	}
	DrawRec(window, w, h, charLocation.x, charLocation.y, 0, charDim.x, deathCycle, charDim.y, NULL, 0, true, arenaColor);



}




#endif // !movement_h
