#include"Student.h" 

int main() {
	zh.display();
	int t;
	std::cin>>t;
	if(t==1) {
		system("cls");
		Intership_score();
	} else if(t==0) {
		exit(0);     //�˳�����
	}
	while(true) {
		pro.display();
		std::cin>>t;
		if(t==1) {
			while(true) {

				pm.display();
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
		} 
		else if(t==2) 
		{
			Check();
		} 
		else if(t==3)
		{
			drawHistogram();
			std::cout<<"\t\t\t�Ƿ����"<<std::endl;
	        std::cout<<"\t\t\t";
        	std::string k;
        	std::cin>>k;
	        if(k!="��") {
	    	break;
        	}
		}
		else if(t==0) {
			break;
		}
	}
	
	return 0;
}

