#include"Student.h"
#include<iostream> 
int main() {
	switchZH();
	int t;
	std::cin>>t;
	if(t==1) {
		system("cls");
		Intership_score();
	} else if(t==0) {
		exit(0);     //�˳�����
	}
	while(true) {
		switchPro();
		std::cin>>t;
		if(t==1) {
			while(true) {

				switchProMax();
				std::cout<<"\t\t\t��ѡ��:";
				int z;
				std::cin>>z;
				if(z==1) {
					IDTranscript();
				} else if(z==2) {
					ScoreTranscript();
				} else if(z==0) {
					break;//������һҳ
				}
			}
		} else if(t==2) {
			Check();
		} else if(t==0) {
			break;
		}
	}
	return 0;
}

