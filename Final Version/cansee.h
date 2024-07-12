class Graph
{
	public:
		virtual void display()=0; 
};
class Forthplace :public Graph
{
	public:
		void display() override{
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                  ¼��ɼ�                 |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
		
	}
};

class Sideplace :public Graph
{
	public:
	void display() override{
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                ��ѯ���˳ɼ�               |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
};
class Secondplace:public Graph{
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|             �ɼ�¼��ɹ�                  |"<<std::endl;
	std::cout<<"\t\t\t|             1.���ɳɼ���                  |"<<std::endl;
	std::cout<<"\t\t\t|             2.��ѯ���˳ɼ�                |"<<std::endl;
	std::cout<<"\t\t\t|             3.���ݷ���                    |"<<std::endl;
	std::cout<<"\t\t\t|             0.�˳�ϵͳ                    |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t��ѡ��:";
}
};
class Thirdplace:public Graph{
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                ���ɳɼ���                 |"<<std::endl;
	std::cout<<"\t\t\t|             1.��ѧ������ɼ���            |"<<std::endl;
	std::cout<<"\t\t\t|             2.���ɼ�����ɼ���            |"<<std::endl;
	std::cout<<"\t\t\t|             0.������һ��                  |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
};
class Firstplace:public Graph {
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|              1.¼��ɼ�                   |"<<std::endl;
	std::cout<<"\t\t\t|              0.�˳�ϵͳ                   |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t׼����n��ʵϰ�ɼ����Ծ�ɼ�����ʽ�����ţ��������༶���ɼ���"<< std::endl;
	std::cout<<"\t\t\t���ڳɼ�����ʽ���ţ��������༶�����ڿ۷֣���Ϊcsv�ļ�"<<std::endl;
	std::cout<<"\t\t\t��ѡ��:\n";
	std::cout<<"\t\t\t"; 
}
};


