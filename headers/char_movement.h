#pragma once
#ifndef char_movement_h


//___________TEST
struct animationLoc
{
	int Start;
	int end;
};
animationLoc animCharLoc[8];

int testRate, testCount;


//___________TEST
void spriteCheetInit(sf::Sprite *sprite, sf::IntRect *store,int w, int h)
{
	
	animCharLoc[0] = { 45, 50 };
	animCharLoc[1] = { 51, 56 };
	animCharLoc[2] = { 9, 14 };
	animCharLoc[3] = { 15, 20 };
	animCharLoc[4] = { 21, 26 };
	animCharLoc[5] = { 27, 32 };
	animCharLoc[6] = { 33, 38 };
	animCharLoc[7] = { 39, 44 };


	testRate = 0;
	testCount = 0;
	int w0 = 0;
	int h0 = 0;

	for (int i = 0; i < 8; i++)
	{
		store[i].left = w0;
		store[i].top = h0;
		store[i].width = w;
		store[i].height = h;
		w0 += w;
		sf::IntRect check = sprite->getTextureRect();
		if (w0 >= check.width)
		{
			w0 = 0;
			h0 += h;
		}

	}
	for (int i = 8; i < 56; i++)
	{
		store[i].left = w0;
		store[i].top = h0;
		store[i].width = w;
		store[i].height = h;
		w0 += w;
		sf::IntRect check = sprite->getTextureRect();
		if (w0 >= check.width)
		{
			w0 = 0;
			h0 += h;
		}

	}




}

/*
void animate(sf::RenderWindow &win,sf::Sprite *sprite, sf::IntRect *animation, int dir,bool anim, int x, int y, float scale)
{
	int k;
	if (charMove.x != 0 && charMove.y != 0)
		k = (charMove.x + charMove.y) / 2;
	else
		k = charMove.x + charMove.y;

	switch (k)
	{
	case 1:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 2:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 3:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 4:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 5:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 6:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 7:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[k].Start > testCount || animCharLoc[k].end < testCount)
				testCount = animCharLoc[k].Start;

			testRate = 0;
		}
		break;
	case 8:
		testRate++;
		if (testRate > 10)
		{
			testCount++;
			if (animCharLoc[0].Start > testCount || animCharLoc[0].end < testCount)
				testCount = animCharLoc[0].Start;

			testRate = 0;
		}
		break;
	case 0:
		testRate = 0;
		testCount = dir;
		break;
	default:
		testRate = 0;
		testCount = dir;
		break;
	}





	sprite->setPosition(x, y);
	sprite->setTextureRect(animation[testCount]);
	sprite->setScale(scale, scale);
	win.draw(*sprite);
}


*/





#endif // !char_movement_h
