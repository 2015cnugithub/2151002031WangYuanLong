#include<graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;
enum TYPE {CIRCLE, RECTANGLE, TRIANGLE};
class FigureLink;//��ǰ����
class Figure
{
	friend class FigureLink;
protected:
	TYPE type;
	int cx,cy;
	static Figure *ptr;//ָ��Ҫ���������ͼ�λ��ƶ���
	Figure *next;//ָ�������е���һ��ͼ�λ��ƶ���
public:
	Figure(int x, int y,TYPE tp)
	{
		cx=x;
		cy=y;
		type = tp;
		next=0;
	}
	virtual void Draw()=0;//ͼ�λ��Ʋ����Ľӿڹ���
	virtual void Insert()=0;//ͼ�λ���������������Ľ�ڹ���
	void Hide();
	void Move();
};

Figure *Figure::ptr=0;

void Figure::Hide()
{
	unsigned int sc=getcolor();
	setcolor(BLACK);
	Draw();
	setcolor(sc);
}

void Figure::Move()
{
	Hide();
	cx+=1;
	Draw();
}

class Circle:public Figure	//Բ����
{
private:
	int radius;//�뾶
public:
	Circle(int x, int y, int r):Figure(x,y,CIRCLE)
	{
		radius=r;
	}
	void Draw();
	void Insert();
};

void Circle::Draw()
{
	circle(cx,cy,radius);
}

void Circle::Insert()
{
	Figure::ptr=new Circle(cx,cy,radius);//�Ƚ�Բͼ�α����һ����̬��Figure���͵�ָ��
}

class Rect:public Figure	//����
{
private:
	int width;
	int length;
public:
	Rect(int w, int l, int x, int y):Figure(x,y,RECTANGLE)
	{
		width=w;
		length=l;
	}
	void Draw();
	void Insert();
};

void Rect::Draw()
{
	rectangle(cx-width/2,cy-length/2,cx+width/2,cy+length/2);//��cx,cyΪ���Ļ�����
}

void Rect::Insert()
{
	Figure::ptr=new Rect(width,length,cx,cy);
}

class Triangle:public Figure	//������
{
private:
	int RightAngleFlag;
	int bottomSide;
	int height;
public:
	Triangle(int b,int h,int flag,int x,int y):Figure(x,y,TRIANGLE)
	{
		bottomSide=b;
		height=h;
		RightAngleFlag=flag;
	}
	void Draw();
	void Insert();
};

void Triangle::Draw()
{
	if(RightAngleFlag==1)
	{
		int points[8]={cx-bottomSide/2,cy+height/2,cx+bottomSide/2,cy+height/2,
				cx+bottomSide/2,cy-height/2,cx-bottomSide/2,cy+height/2};
		drawpoly(4,points);//������Σ���һ��������ʾ�����㣬�ڶ�����һϵ�������
	}
	else
	{
		int points[8]={cx-bottomSide/2,cy+height/2,cx+bottomSide/2,cy+height/2,
				cx-bottomSide/2,cy-height/2,cx-bottomSide/2,cy+height/2};
		drawpoly(4,points);
	}
}

void Triangle::Insert()
{
	Figure::ptr=new Triangle(bottomSide,height,RightAngleFlag,cx,cy);
}

class FigureLink
{
protected:
	Figure *head;
public:
	FigureLink(){head=0;}
	~FigureLink(){Empty();}
	void Empty();
	void Insert(Figure *figureNode);
	void Draw();
	void Hide();
	void Move();
};

void FigureLink::Empty()
{
	Figure *current;
	Figure *next;
	current=head;
	while(current)
	{
		next=current->next;
		delete current;
		current=next;
	}
}

void FigureLink::Insert(Figure *figureNode)
{
	
	figureNode->Insert();//���Ե���ʵ��ͼ�ε�Insert��ʵ�����Ǵ������µ�ͼ�ν��
	if(head)
	{
		figureNode->ptr->next=head;//��head��Ϊ�գ���figureNode->ptrָ��head��Ӧ���Ѿ�����Ľڵ�,��Զ�����²���Ľڵ�����������ǰ��
		head=figureNode->ptr;//��headָ��ָ�����²���Ľڵ㣬�Ա�֤��һ�μ�������
	}
	else head=figureNode->ptr;//���ǵ�һ�β���ڵ㣬ֱ�ӽ�headָ�������Ľڵ�
}

void FigureLink::Draw()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->Draw();
		current=current->next;
	}
}

void FigureLink::Hide()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->Hide();
		current=current->next;
	}
}

void FigureLink::Move()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->Move();
		current=current->next;
	}
}

class Vehicle
{
protected:
	FigureLink contents;
	int WheelSize;
	int x;
	int y;
public:
	void Draw();
	void Hide();
	void Move();
};

void Vehicle::Draw()
{
	contents.Draw();
}

void Vehicle::Hide()
{
	contents.Hide();
}

void Vehicle::Move()
{
	int i=0;
	int seconds=100;
	int speed=7;
	int choice;
	while(i<800)
	{
		contents.Move();
		Sleep(seconds/speed);
		if(kbhit())
		{
			choice=getch();
			if(choice=='+'||choice=='=') seconds-=7;
			else if(choice=='-'||choice=='_') seconds+=7;
			else if(choice=='E'||choice=='e') return;
			else if(choice=='P'||choice=='p')
			{
				while(1)
				{
					choice=0;
					if(kbhit()) choice=getch();//����ʱ�Ƿ��м������룬���У����ط���ֵ
					if(choice=='P'||choice=='p') break;//���ٴΰ�P�������˶�
				}
			}
		}
		i++;
	}
	
}

class Car:public Vehicle
{
public:
	Car(int d, int xstart, int ystart);
};

Car::Car(int d,int xstart,int ystart)
{
	WheelSize=d;
	x=xstart;
	y=ystart;
	Figure *f;
	f=new Triangle(d,d,1,x+1.75*d,y-2.5*d);//��������ͼ��������
	contents.Insert(f);
	f=new Rect(3.5*d,d,x+4*d,y-2.5*d);
	contents.Insert(f);
	f=new Triangle(d,d,2,x+6.25*d,y-2.5*d);
	contents.Insert(f);
	f=new Rect(8*d,d,x+4*d,y-1.5*d);
	contents.Insert(f);
	f=new Circle(x+1.75*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+6.25*d,y-0.5*d,0.5*d);
	contents.Insert(f);
}

class Truck:public Vehicle
{
public:
	Truck(int d, int xstart, int ystart);
};

Truck::Truck(int d,int xstart,int ystart)
{
	WheelSize=d;
	x=xstart;
	y=ystart;
	Figure *f;
	f=new Rect(9*d,4*d,x+4.5*d,y-3*d);
	contents.Insert(f);
	f=new Rect(2*d,3*d,x+2+10*d,y-2.5*d);
	contents.Insert(f);
	f=new Circle(x+d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+2.25*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+6.75*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+8*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+10*d,y-0.5*d,0.5*d);
	contents.Insert(f);
}

class Menu{
public:
	Menu(){
		Vehicle *v=0;
		Car car(10,30,500);
		Truck truck(10,30,500);
		int choice=0;

		initgraph(800,600);
		outtextxy(15,10,"1  Car  2  Truck  3  Exit");
		rectangle(20,30,780,570);
		outtextxy(25,35,"First, press a number(1,2,3), then press 'S,P,E,+,-' to control it");
		outtextxy(25,50,"Press <S> key to start moving");
		outtextxy(25,65,"Press <P> key to pause/continue moving");
		outtextxy(25,80,"Press <E> key to end moving");
		outtextxy(25,95,"Press <+> key to speed up");
		outtextxy(25,110,"Press <-> key to speed down");
		line(20,502,780,502);

		while(choice!='3')
		{	
			choice=getch();
			if(choice=='1')
			{
				if(v) v->Hide(); //���ѡ���ǰ��һ�������ڣ���Ҫ�ѳ�����
				v=&car;
				v->Draw();
				
			}
			else if(choice=='2')
			{
				if(v) v->Hide();
				v=&truck;
				v->Draw();
			}
			 if(choice=='S'||choice=='s')
			{
				if(v) v->Move();
			}

		}
			closegraph();
	}
	
};

int main()
{
	Menu m;
	return 0;
}

/*
	���д����Ƶ����⣺
	1��С���ĳ�ʼ��ˢ������
	2��С���о��е�ƽ����
	3��С���뿨����ѭ���л����⣬����ֻ���л�һ�Σ���ô�Ľ���С���뿨������ѭ���л�
*/