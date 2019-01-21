#pragma once
#ifndef Diagonal_method_h
#define Diagonal_method_h

int a = 40;



struct func_line
{
	float a, b;
	float x, y;
	bool hor;
};
struct dimension
{
	//float x0, y0, x1, y1, x2, y2, x3, y3;
	sf::Vector2f p0, p1, p2, p3;
};


void line_regression(func_line *line, float x0, float y0, float x1, float y1)
{
	if (x0 - x1 == 0)
	{
		line->hor = false;
		line->a = x0;
		line->b = 0;
	}
	else
	{
		line->a = (y0 - y1) / (x0 - x1);
		line->b = y0 - line->a * x0;
		line->hor = true;
	}
}

void line_meet(func_line *line0, func_line *line1)
{
	if (line0->hor == false)
	{
		float x = line0->a;
		float y = line1->a * x + line1->b;
		line0->x = x;
		line1->x = x;
		line0->y = y;
		line1->y = y;

	}
	else
		if (line1->hor == false)
		{
			float x = line1->a;
			float y = line0->a * x + line0->b;
			line0->x = x;
			line1->x = x;
			line0->y = y;
			line1->y = y;
		}
		else
		{
			float x = (line1->b - line0->b) / (line0->a - line1->a);
			float y = line1->a * x + line1->b;
			line0->x = x;
			line1->x = x;
			line0->y = y;
			line1->y = y;
		}
}


dimension perspective(int w, int h, int x, int y, int z, int sizeW, int sizeH) // reikia Z
{
	x -= w / 2;
	y = w - y;
	//float alfa =asin( x / sqrt(x*x+y*y));
	//float x0 = (h/2*sin(alfa)) / (sin(PI / 2 - alfa)); // del pelytes

	float x0 = x;
	float d = -1/4 * w;


	func_line lineDiagonal;
	line_regression(&lineDiagonal, d, h / 2, w, h);

	func_line projection_left_Side;
	line_regression(&projection_left_Side, w / 2, h / 2, x0 + w / 2, h);


	func_line projection_right_Side;
	line_regression(&projection_right_Side, w / 2, h / 2, x0 + w / 2 + sizeW, h);




	/*
	func_line projection_front_Side;
	line_regression(&projection_front_Side, 0, y + h / 2, w, y + h / 2);
	//*/
	func_line projection_front;
	line_regression(&projection_front, y, h, w / 2, h / 2);
	line_meet(&projection_front, &lineDiagonal);
	func_line projection_front_Side;
	line_regression(&projection_front_Side, 0, projection_front.y, w, projection_front.y);







	line_meet(&projection_front_Side, &lineDiagonal);

	func_line projection;

	line_regression(&projection, w / 2, h / 2, projection_front_Side.x, projection_front_Side.y);
	func_line bottom;
	line_regression(&bottom, 0, h, w, h);

	line_meet(&bottom, &projection);
	func_line projection_2;
	line_regression(&projection_2, w / 2, h / 2, projection.x - sizeH, projection.y);
	line_meet(&projection_2, &lineDiagonal);



	func_line projection_back_Side;
	line_regression(&projection_back_Side, 0, projection_2.y, w, projection_2.y);




	line_meet(&projection_left_Side, &projection_back_Side);
	sf::Vector2f p0;
	sf::Vector2f p1;
	sf::Vector2f p2;
	sf::Vector2f p3;

	p0.x = projection_left_Side.x;
	p0.y = projection_left_Side.y;
	line_meet(&projection_back_Side, &projection_right_Side);
	p1.x = projection_back_Side.x;
	p1.y = projection_back_Side.y;
	line_meet(&projection_right_Side, &projection_front_Side);
	p2.x = projection_right_Side.x;
	p2.y = projection_right_Side.y;
	line_meet(&projection_left_Side, &projection_front_Side);
	p3.x = projection_front_Side.x;
	p3.y = projection_front_Side.y;





	if (z != 0)
	{
		func_line projection_z;
		func_line projection_z0;
		func_line projection_h;
		func_line projection_w;
		func_line projection_h_obj;
		line_regression(&projection_z, 0, h - z, w / 2, h / 2);
		line_regression(&projection_z0, 0, h, w / 2, h / 2);


		//___
		line_regression(&projection_h_obj, p3.x, p3.y, p3.x, p3.y + 10);

		line_meet(&projection_z0, &projection_front_Side);
		line_regression(&projection_h, projection_z0.x, projection_z0.y, projection_z0.x, projection_z0.y + 10);

		line_meet(&projection_h, &projection_z);
		line_regression(&projection_w, projection_h.x, projection_h.y, projection_h.x + 10, projection_h.y);

		line_meet(&projection_w, &projection_h_obj);

		p3.x = projection_w.x;
		p3.y = projection_w.y;

		line_regression(&projection_h_obj, p2.x, p2.y, p2.x, p2.y + 10);
		line_meet(&projection_w, &projection_h_obj);
		p2.x = projection_w.x;
		p2.y = projection_w.y;

		line_regression(&projection_h_obj, p0.x, p0.y, p0.x, p0.y + 10);

		line_meet(&projection_z0, &projection_back_Side);
		line_regression(&projection_h, projection_z0.x, projection_z0.y, projection_z0.x, projection_z0.y + 10);

		line_meet(&projection_h, &projection_z);
		line_regression(&projection_w, projection_h.x, projection_h.y, projection_h.x + 10, projection_h.y);
		line_meet(&projection_w, &projection_h_obj);
		p0.x = projection_w.x;
		p0.y = projection_w.y;

		line_regression(&projection_h_obj, p1.x, p1.y, p1.x, p1.y + 10);
		line_meet(&projection_w, &projection_h_obj);
		p1.x = projection_w.x;
		p1.y = projection_w.y;
		//___
	}








	dimension perspective = { p0,p1,p2,p3 };
	return perspective;
}
void perspective2D()
{



}














#endif