// test.cpp: implementation of the test class.
//
//////////////////////////////////////////////////////////////////////
#include "iostream"

using namespace std;

bool checked(int y,int m){
	if((y<=0)||(m>12||m<=0))
	{
		return false;
	}else{
		return true;
	}
}

void input(int &y,int &m){
		cout<<"请输入年 月:";
		cin>>y>>m;
        cout<<endl;
		if(!checked(y,m)){
			cout<<"输入有误!"<<endl;
			input(y,m);
		}
}

void control(int &y,int &m,int &d,int &monthmax){
		//判断年份和月份
        if(y%4==0||(y%100==0&&y%400==0))//闰年
        {
            if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
                monthmax=31;
            if(m==2)
                monthmax=29;
            if(m==4||m==6||m==9||m==11)
                monthmax=30;
        }
        if(y%4!=0)//平年
        {
            if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
                monthmax=31;
            if(m==2)
                monthmax=28;
            if(m==4||m==6||m==9||m==11)
                monthmax=30;
        }

        //基姆拉尔森计算公式取得一号周几
        if(m==1||m==2)
        {
            m+=12;    //一月算做上一年的十三月，二月算做上一年的十四月
            y--;
        }
        d=(2+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;//算出这月一号周几
}

void output(int &y,int &m,int &d,int &monthmax){
	 if(d==0)
        {
            d=7;//星期日放在最后
        }
        //输出日历
        {
            {
                //标题模块
                if(m==13)
                {
                    cout<<"   公元 "<<y+1<<" 年 第1月日历"<<endl<<endl;
                }
                if(m==14)
                {
                    cout<<"   公元 "<<y+1<<" 年 第2月日历"<<endl<<endl;
                }
                if(m!=13&&m!=14)
                {
                    cout<<"   公元"<<y<<"年 第"<<m<<"月日历"<<endl<<endl;
                }
            }
			{
				//日历格式
				cout<<" 一  二  三  四  五  六  日  "<<endl<<"==========================="<<endl;
				for(int i=1; i<=d-1; i++)
				{
					cout<<"    ";
				}
				for(int j=1; j<=monthmax; j++)
				{
					if(j<10)
					{
						cout<<"  "<<j<<" ";
					}
					if(j>=10)
					{
						cout<<" "<<j<<" ";
					}
					if((j+d-1)%7==0)
					{
						cout<<endl;
					}
					if(j==monthmax)
					{
						cout<<endl;
					}
				}
			}
            cout<<endl;
		}
}

int main()
{
    int y,m,d,monthmax=0;

    while(1)
    {
        //输入模块调用
		input(y,m);
		//控制模块调用
		control(y,m,d,monthmax);
        //输出模块调用
		output(y,m,d,monthmax);
    }
	return 0;
}
