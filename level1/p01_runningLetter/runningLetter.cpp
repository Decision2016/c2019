#include<cstdio>
#include<iostream>
#include<windows.h>
#include<cstdlib>


#define W 80       //�������п�� 
#define SLEEP_TIME 50     //��������ʱ�� 

char s[] = "test";

int main(){
	int len = strlen(s);
	while(1){
		for(int i = 0;i<W - len;i++){
			system("cls");
			for(int j = 1;j<=i;j++) std::cout<<" ";
			std::cout<<s;
			Sleep(SLEEP_TIME);
		}
		for(int i = W - len;i>=0;i--){
			system("cls");
			for(int j = 1;j<=i;j++) std::cout<<" ";
			std::cout<<s;
			Sleep(SLEEP_TIME);
		}
	}
	return 0;
}

