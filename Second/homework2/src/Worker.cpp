/*
 * Worker.cpp
 *
 *  Created on: 2015-10-15
 *      Author: Wang
 */

//#include "Worker.h"
#include "iostream"
using namespace std;

class Worker {
public:
	char *name;
	int age;
	char *sex;
	int mode;
	double pay_per_hour;
	int weekHours;
	double weekSalary;
public:
	Worker();
Worker(char* name,int age,char* sex,int mode,double pay_per_hour,int weekHours,double weekSalay);
Worker(Worker& worker);//拷贝构造
	virtual ~Worker();
	virtual void Name();
	virtual double compute_pay(double hours)=0;
	friend  ostream &operator<<(ostream &out,const Worker &worker);  //有缘重载符声明放在头文件里面就会报错，为什么？

};

Worker::Worker() {
	// TODO Auto-generated constructor stub
}
Worker::Worker(char *name,int age,char *sex,int mode,double pay_per_hour,int weekHours=0,double weekSalary=0){
	this->name=name;
	this->age=age;
	this->sex=sex;
	this->mode=mode;
	this->pay_per_hour=pay_per_hour;
	this->weekHours=weekHours;
	this->weekSalary=weekSalary;
}

Worker::~Worker() {
	// TODO Auto-generated destructor stub
}


ostream &operator << (ostream &out,const Worker &worker){
	out<<worker.name<<'\t'<<worker.age<<'\t'<<worker.sex<<'\t'<<worker.mode<<'\t'<<
			worker.pay_per_hour<<'\t'<<worker.weekHours<<'\t'<<worker.weekSalary<<endl;
	return out;
}

void Worker::Name(){
	cout<<this->name<<"\t";
}

class HourlyWorker:public Worker{
public:

	HourlyWorker(char *name,int age,char *sex,int mode,double pay_per_hour,int weekHours=0,double weekSalary=0):Worker(name,age,sex,mode,pay_per_hour,weekHours,weekSalary){

	}
	double compute_pay(double hours){
		this->weekHours=hours;
		if(hours<40&&hours>0){
			this->weekSalary=this->pay_per_hour*hours;
		}else if(hours>=40){
			this->weekSalary=this->pay_per_hour*40+1.5*this->pay_per_hour*(hours-40);
		}
		return this->weekSalary;
	}
};
//
class SalariedWorker:public Worker{
public:
	SalariedWorker(char *name,int age,char *sex,int mode,double pay_per_hour,int weekHours=0,double weekSalary=0):Worker(name,age,sex,mode,pay_per_hour,weekHours,weekSalary){

		}
	double compute_pay(double hours){
		this->weekHours=hours;
		if(hours>35){
			this->weekSalary=hours*40;
		}else if(hours<35){
			this->weekSalary=this->pay_per_hour*hours+0.5*this->pay_per_hour*(35-hours);
		}
		return this->weekSalary;
	}

};
//自定义菜单类
class Menu{
public:Menu(){
	int options = -1;
		char *name=NULL;
		int age=0;
		char *sex=NULL;
		int mode = 0;
		int pay_per_hour=0;
		while(1){
			cout << endl<<"----------------操作菜单----------------"<<endl;
			cout << "1、录入信息"<<"\t2、查看信息"<<"\t3、退出"<<endl;
			cin >> options;
			Worker *workers[2];
			if(options==1){
			 for(int i=0;i<2;i++)
			 {
			  char *name=new char;
			  char *sex = new char;
			  cout<<"姓名：";cin>>name;
			  cout<<"年龄：";cin>>age;
			  cout<<"性别(男，女)：";cin>>sex;
			  cout<<"发薪模式(0:计时，1:级）：";cin>>mode;
			  if(mode==0){
				 while(1){
					 cout<<"计薪等级(10,20,40)：";cin>>pay_per_hour;
					 if(pay_per_hour==10||pay_per_hour==20||pay_per_hour==40){
						 break;
					 }else {
						 cout <<"输入不合法，请重新输入";
					 }

				 }

			  }else if(mode==1){
				 while(1){
					 cout<<"计薪等级(30,50)：";cin>>pay_per_hour;
					 if(pay_per_hour==30||pay_per_hour==50){
						 break;
					 }else{
						 cout<<"输入不合法，请重新输入";
					 }
				 }
			 }else{
				 cout<<"类型输入不合法"<<endl;
			 }
			  if(mode==0){
				  workers[i]=new HourlyWorker(name,age,sex,mode,pay_per_hour);
			  }
			  if(mode==1){
				  workers[i]=new SalariedWorker(name,age,sex,mode,pay_per_hour);
			  }

			 }
			}else if(options==2){
				int choose;
				int weekhours;
				while(1){

					cout<<"请输入要查询工人的编号：(1--5),返回上级：0:"<<endl;
					for(int j=0;j<2;j++){
						cout<<j+1<<"、";(*workers[j]).Name();cout<<'\t';
					}
					cout<<endl;
					cin>>choose;
					if(choose==0) break;
					if(choose>5||choose<1){
						cout<<"输入不合法，请重新输入：";continue;
					}
					cout<<"姓名：\t"<<"年龄：\t"<<"性别：\t"<<"类别：\t"<<"时薪：\t"<<"时长：\t"<<"周新"<<endl;
					cout<<(*workers[choose-1]);//输出某个工人信息

						cout<<"输入这名工人的周工作时长(0返回上级)：";cin>>weekhours;
						double h=(*workers[choose-1]).weekHours;
						if(weekhours!=0){
							h=weekhours;
						}else break;

						(*workers[choose-1]).compute_pay(weekhours);
				}
			}else if(options==3){
				cout<<"已退出系统！";
				exit(0);
			}
		}
}
};

int main(){
	Menu m;
	return 0;
}


