#include<iostream>

int n;

void print(int x,char a,char b){
	std::cout<<"Move disk "<<x<<": "<<a<<"---------->"<<b<<std::endl;
}
//�ݹ� 
void solve(int x,char a,char b,char c){              //�ݹ鴦����ʾ����x�����Ӵ�a���ƶ���c�� 
	if(x==1){
		print(1,a,c);
	}
	else{
		solve(x-1,a,c,b);         //����ǰ�������������������ȷŵ�B���� 
		print(x,a,c);
		solve(x-1,b,a,c);         //Ȼ�󽫵�ǰ���������֮ǰ�������ַŵ�C���ϣ���ʱA��������ʱ���õ����� 
	} 
}

int main(){
	std::cout<<"Please input the num of disk:";
	std::cin>>n;
	std::cout<<"Solve problem:"<<std::endl;
	solve(n,'A','B','C');
	return 0;
}