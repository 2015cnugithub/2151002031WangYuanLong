#include<graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;
enum TYPE {CIRCLE, RECTANGLE, TRIANGLE};
class FigureLink;//超前声明
class Figure
{
	friend class FigureLink;
protected:
	TYPE type;
	int cx,cy;
	static Figure *ptr;//指向将要插入链表的图形绘制对象
	Figure *next;//指向链表中的下一个图形绘制对象
public:
	Figure(int x, int y,TYPE tp)
	{
		cx=x;
		cy=y;
		type = tp;
		next=0;
	}
	virtual void Draw()=0;//图形绘制操作的接口规则
	virtual void Insert()=0;//图形绘制类对象插入链表的借口规则
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

class Circle:public Figure	//圆形类
{
private:
	int radius;//半径
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
	Figure::ptr=new Circle(cx,cy,radius);//先将圆图形保存给一个静态的Figure类型的指针
}

class Rect:public Figure	//矩形
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
	rectangle(cx-width/2,cy-length/2,cx+width/2,cy+length/2);//以cx,cy为中心画矩形
}

void Rect::Insert()
{
	Figure::ptr=new Rect(width,length,cx,cy);
}

class Triangle:public Figure	//三角形
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
		drawpoly(4,points);//画多边形，第一个参数表示几个点，第二个是一系列数组对
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
	
	figureNode->Insert();//各自调用实体图形的Insert，实际上是创建了新的图形结点
	if(head)
	{
		figureNode->ptr->next=head;//若head不为空，则将figureNode->ptr指向head对应的已经插入的节点,永远将最新插入的节点放在链表的最前面
		head=figureNode->ptr;//将head指针指向最新插入的节点，以保证下一次继续插入
	}
	else head=figureNode->ptr;//若是第一次插入节点，直接将head指向待插入的节点
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
					if(kbhit()) choice=getch();//检查此时是否有键盘输入，若有，返回非零值
					if(choice=='P'||choice=='p') break;//若再次按P，继续运动
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
	f=new Triangle(d,d,1,x+1.75*d,y-2.5*d);//创建基本图形三角形
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
				if(v) v->Hide(); //如果选择后当前有一个车存在，需要把车隐藏
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
	还有待完善的问题：
	1、小车的初始化刷新问题
	2、小车行径中的平滑性
	3、小车与卡车的循环切换问题，现在只能切换一次，怎么改进让小车与卡车进行循环切换
*/