class Graph
{
	public:
		virtual void display()=0; 
};
class switchUltra :public Graph
{
	public:
		void display() override{
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                  录入成绩                 |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
		
	}
};

class switchAir :public Graph
{
	public:
	void display() override{
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                查询个人成绩               |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
};
class switchPro:public Graph{
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|             成绩录入成功                  |"<<std::endl;
	std::cout<<"\t\t\t|             1.生成成绩单                  |"<<std::endl;
	std::cout<<"\t\t\t|             2.查询个人成绩                |"<<std::endl;
	std::cout<<"\t\t\t|             3.数据分析                    |"<<std::endl;
	std::cout<<"\t\t\t|             0.退出系统                    |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t请选择:";
}
};
class switchProMax:public Graph{
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                生成成绩单                 |"<<std::endl;
	std::cout<<"\t\t\t|             1.按学号排序成绩单            |"<<std::endl;
	std::cout<<"\t\t\t|             2.按成绩排序成绩单            |"<<std::endl;
	std::cout<<"\t\t\t|             0.返回上一级                  |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
};
class switchZH:public Graph {
	public:
	void display() override{
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|              1.录入成绩                   |"<<std::endl;
	std::cout<<"\t\t\t|              0.退出系统                   |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t准备好n次实习成绩和试卷成绩（格式：考号，姓名，班级，成绩）"<< std::endl;
	std::cout<<"\t\t\t考勤成绩（格式考号，姓名，班级，考勤扣分）均为csv文件"<<std::endl;
	std::cout<<"\t\t\t请选择:";
}
};


