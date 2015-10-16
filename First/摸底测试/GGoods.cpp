#include<iostream>
using namespace std;
//商品类定义
class CGoods{
protected:
	long no;
	char *p_name;
	double price;
	static int count;
public:
	//无参构造函数
	CGoods();
	//有参构造函数
	CGoods(long no,char *q_name,double price);
	//拷贝构造函数
	CGoods(CGoods &goods);
	//析构函数
	virtual ~CGoods();
	void printNo();
	void printName();
	void printPrice();
	void print();
	int getCount();
	int getNo();
	friend char* getName(CGoods& goods);
	bool operator < (CGoods& goods);
	bool operator >= (CGoods& goods);
	virtual void usedFor();//虚函数，子类可重写此函数实现多态，注意虚函数与纯虚函数的区别
};
//商品类实现
CGoods::CGoods(){}
CGoods::CGoods(long no,char *q_name,double price){
			this->no = no;
			this->p_name = q_name;
			this->price = price;
		}
	//拷贝构造函数
CGoods::CGoods(CGoods &goods){
		this->no = goods.no;
		this->p_name = goods.p_name;
		this->price = goods.price;
		this->count = goods.count;
	}
CGoods::~CGoods(){}
void CGoods::printNo(){
		cout << "商品号："<<this->no<<endl;
	}
void CGoods:: printName(){
		cout << "商品名："<<this->p_name<<endl;
	}
void CGoods:: printPrice(){
		cout << "商品价格："<< this->price<<endl;
	}
void CGoods:: print(){
		cout << "商品号："<<this->no << "\t商品名："<< this->p_name <<"\t商品价格:"<<showpoint<<this->price<<endl;
	}
int CGoods::getCount(){
		return this->count;
	}
int CGoods::getNo(){
	return this->no;
}
char* getName(CGoods& goods){
		return goods.p_name;
	}
bool CGoods::operator < (CGoods& goods){
	if(this->price<goods.price){
		return true;
	}else{
		return false;
	}
}
bool CGoods::operator >= (CGoods& goods){
	if(this->price<goods.price){
		return false;
	}else{
		return true;
	}
}
 void CGoods::usedFor(){
	cout << "商品号：" <<this->no<<"\t商品名："<<
			this->p_name<<"\t商品价格："<<this->price<<"\t\t商品总数："<<this->count<<endl;
}
int CGoods::count=10;

//衣服类定义
class CClothes:public CGoods{
	char *p_brand;
public:
	CClothes();
	CClothes(CGoods& goods,char *p_brand);
	virtual ~CClothes();
	void usedFor();
};
//衣服类实现
CClothes::CClothes(){}
CClothes::CClothes(CGoods& goods,char *p_brand):CGoods(goods),p_brand(p_brand){}
CClothes::~CClothes(){}
void CClothes::usedFor(){//重写自己的usedFor函数，实现多态
	cout<<"品牌:"<<this->p_brand<<"\t";
	CGoods::usedFor();
}

//实物类定义
class CFood:public CGoods{
	char *p_brand;
public:
	CFood();
	CFood(CGoods& goods,char *p_brand);
	~CFood();
	void usedFor();
};
//实物类实现
CFood::CFood(){}
CFood::CFood(CGoods& goods,char *p_brand):CGoods(goods),p_brand(p_brand){}
CFood::~CFood(){}
void CFood::usedFor(){
	cout<<"品牌:"<<this->p_brand<<"\t";
	CGoods::usedFor();
}


//测试类
int main(){
	CGoods goods1(1,"牛奶",5.20),goods2(2,"面包",6.00);
	goods1.print();
	//动态联编方式，父类接收子类对象，运行时才确定调用哪个对象的方法
	CGoods *clothes = new CClothes(goods1,"衣服");
	clothes->usedFor();
	delete clothes;
	CGoods *food = new CFood(goods2,"面包");
	food->usedFor();
	delete food;
	//传统调用方式
	CClothes clothes1(goods1,"衣服");
	clothes1.usedFor();
	CFood food1(goods2,"食物");
	food1.usedFor();
	cout<<"友元函数得到了商品号为："<<goods1.getNo()<<" 的商品名字是："<<getName(goods1)<<endl;
	if(goods1<goods2){
		cout<<"运算符<重载：goods1<goods2"<<endl;
	}
	if(goods2>=goods1){
		cout << "运算符>=重载：goods2>=goods1"<<endl;
	}
	return 0;
}
