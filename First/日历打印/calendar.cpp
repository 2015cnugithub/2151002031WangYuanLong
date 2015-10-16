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
		cout<<"�������� ��:";
		cin>>y>>m;
        cout<<endl;
		if(!checked(y,m)){
			cout<<"��������!"<<endl;
			input(y,m);
		}
}

void control(int &y,int &m,int &d,int &monthmax){
		//�ж���ݺ��·�
        if(y%4==0||(y%100==0&&y%400==0))//����
        {
            if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
                monthmax=31;
            if(m==2)
                monthmax=29;
            if(m==4||m==6||m==9||m==11)
                monthmax=30;
        }
        if(y%4!=0)//ƽ��
        {
            if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
                monthmax=31;
            if(m==2)
                monthmax=28;
            if(m==4||m==6||m==9||m==11)
                monthmax=30;
        }

        //��ķ����ɭ���㹫ʽȡ��һ���ܼ�
        if(m==1||m==2)
        {
            m+=12;    //һ��������һ���ʮ���£�����������һ���ʮ����
            y--;
        }
        d=(2+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;//�������һ���ܼ�
}

void output(int &y,int &m,int &d,int &monthmax){
	 if(d==0)
        {
            d=7;//�����շ������
        }
        //�������
        {
            {
                //����ģ��
                if(m==13)
                {
                    cout<<"   ��Ԫ "<<y+1<<" �� ��1������"<<endl<<endl;
                }
                if(m==14)
                {
                    cout<<"   ��Ԫ "<<y+1<<" �� ��2������"<<endl<<endl;
                }
                if(m!=13&&m!=14)
                {
                    cout<<"   ��Ԫ"<<y<<"�� ��"<<m<<"������"<<endl<<endl;
                }
            }
			{
				//������ʽ
				cout<<" һ  ��  ��  ��  ��  ��  ��  "<<endl<<"==========================="<<endl;
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
        //����ģ�����
		input(y,m);
		//����ģ�����
		control(y,m,d,monthmax);
        //���ģ�����
		output(y,m,d,monthmax);
    }
	return 0;
}
