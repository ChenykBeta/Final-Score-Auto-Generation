#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // std::sort
#include <stdexcept>
#include <unordered_map> // std::unordered_map
#include<iomanip>
class Student {
	public:
		std::string name;
		int ID;
		double score[30];
		double attendanceScore; // 考勤成绩
		double finalScore; // 最终成绩
		double examScore; //试卷成绩
		double totalScore;//总成绩
};
// 全局变量
std::vector<Student> mergedStudents;
void Graph_data(const std::vector<Student> &mergedStudents) {
    
    std::map<int, int> graph;

    
    for (const auto& student : mergedStudents) {
        int range = static_cast<int>(student.totalScore / 10) * 10;
        graph[range]++;
    }

    int maxFrequency = std::max_element(graph.begin(), graph.end(),
                                        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                                            return a.second < b.second;
                                        })->second;

    
    for (const auto& entry : graph) {
        std::cout << entry.first << "-" << entry.first + 9 << ": ";
        int barWidth = static_cast<int>((static_cast<double>(entry.second) / maxFrequency) * 50); // 50为最大宽度
        for (int i = 0; i < barWidth; ++i) {
            std::cout << "*";
        }
        std::cout << " (" << entry.second << ")" << std::endl;
    }
}
int n = 1;

void switchZH() {
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|             1.录入成绩                    |"<<std::endl;
	std::cout<<"\t\t\t|             0.退出系统                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t准备好n次实习成绩和试卷成绩（格式：考号，姓名，班级，成绩）"<< std::endl;
	std::cout<<"\t\t\t考勤成绩（格式考号，姓名，班级，考勤扣分）均为csv文件"<<std::endl;
	std::cout<<"\t\t\t请选择:";
}
// 函数用于读取CSV文件并返回一个学生向量
std::vector<Student> readStudentsFromCSV(const std::string& filePath, int scoreIndex) {
	std::vector<Student> students;
	std::ifstream file(filePath);
	while (!file.is_open()) {
		std::cerr << "\t\t\t无法打开文件: " << filePath << "\n\t\t\t请重新输入文件路径，或输入'退出'以结束程序。" << std::endl;
		std::cout << "\t\t\t请输入文件路径: \n";
		std::cout<<"\t\t\t";
		std::string newPath;
		std::cin >> newPath;
		if (newPath == "退出") {
			std::cerr << "程序已退出。" << std::endl;
			exit(1); // 或者返回一个空向量，具体取决于您的需求
		}
		file.open(newPath);
	}
	std::string line;
	// 跳过标题行
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string IDStr, name, discard;
		double score;
		if (std::getline(iss, IDStr, ',') && std::getline(iss, name, ',') && std::getline(iss, discard, ',') && iss >> score) {
			int ID = std::stoi(IDStr); // 将考号字符串转换为整数
			students.push_back({name, ID, 0, 0, 0, 0, 0, 0,0}); // 初始化所有成绩为0
			if(scoreIndex==30) {
				students.back().attendanceScore = score;
			} else if(scoreIndex==31) {
				students.back().examScore = score;
			} else if(scoreIndex<30) {
				students.back().score[scoreIndex] = score;
			} else {
				throw std::runtime_error("无效的成绩索引");
			}
		} else {
			throw std::runtime_error("文件格式错误");
		}
	}

	file.close();
	return students;
}
// 按考号排序的比较函数
bool compareByID(const Student& a, const Student& b) {
	return a.ID < b.ID;
}
// 按最终成绩排序的比较函数
bool totalScore(const Student& a, const Student& b) {
	return a.totalScore > b.totalScore;
}
void switchUltra() {
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|               录入成绩                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
void switchAir() {
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|               查询个人成绩                |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
std::unordered_map<int, Student> studentMap;
void Intership_score() {
	// 使用unordered_map根据考号合并成绩
	switchUltra();
	try {
		int n=1;
		std::string Address;
		std::string input=" ";
		while(input!="否") {
			std::cout<<"\t\t\t请输入第"<<n<<"次实习成绩单的地址"<<std::endl;
			std::cout<<"\t\t\t";
			std::cin>>Address;
			std::vector<Student> students1 = readStudentsFromCSV(Address, n);
			for (const auto& student : students1) {
				if (studentMap.find(student.ID) != studentMap.end()) {
					studentMap[student.ID].score[n] = student.score[n];
				} else {
					studentMap[student.ID] = student;
				}
			}
			std::cout<<"\t\t\t是否继续输入"<<std::endl;
			std::cout<<"\t\t\t";
			std::cin>>input;
			n++;
		}


		std::string KAddress,SAddress;
		std::cout<<"\t\t\t请输入考勤成绩单的地址"<<std::endl;
		std::cout<<"\t\t\t";
		std::cin>>KAddress;
		std::vector<Student> studentsAttendance = readStudentsFromCSV(KAddress,30);
		std::cout<<"\t\t\t请输入试卷成绩单地址"<<std::endl;
		std::cout<<"\t\t\t";
		std::cin>>SAddress;
		std::vector<Student> studentsexamScore = readStudentsFromCSV(SAddress,31);
		for (const auto& student : studentsAttendance) {
			if (studentMap.find(student.ID) != studentMap.end()) {
				studentMap[student.ID].attendanceScore = student.attendanceScore;
			} else {
				studentMap[student.ID] = student;
			}
		}
		for (const auto& student : studentsexamScore) {
			if (studentMap.find(student.ID) != studentMap.end()) {
				studentMap[student.ID].examScore = student.examScore;
			} else {
				studentMap[student.ID] = student;
			}
		}

		// 计算最终成绩
		for (auto& pair : studentMap) {
			Student& student = pair.second;
			// 计算四次成绩的平均分
			double averageScore=0.0;
			for(int i=1; i<n; i++) {
				averageScore +=student.score[i];
			}

			student.finalScore = (averageScore/(n-1)) - student.attendanceScore;
			if(student.finalScore<0) {
				student.finalScore=0;
			}
			student.totalScore =student.finalScore*0.3+student.examScore*0.7;
		}

		// 将map中的学生信息转换回向量
		std::vector<Student> mergedStudents;
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}
	} catch (const std::exception& e) {
		std::cerr << "发生错误: " << e.what() << std::endl;
	}
}
void switchPro() {
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|             成绩录入成功                  |"<<std::endl;
	std::cout<<"\t\t\t|             1.生成成绩单                  |"<<std::endl;
	std::cout<<"\t\t\t|             2.查询个人成绩                |"<<std::endl;
	std::cout<<"\t\t\t|             0.退出系统                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t请选择:";
}
void switchProMax() {
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           欢迎来到期末成绩生成系统        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|              生成成绩单                   |"<<std::endl;
	std::cout<<"\t\t\t|             1.按学号排序成绩单            |"<<std::endl;
	std::cout<<"\t\t\t|             2.按成绩排序成绩单            |"<<std::endl;
	std::cout<<"\t\t\t|             0.返回上一级                  |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
int IDTranscript() {
	// 按考号排序
	std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);
	// 输出排序后的学生信息到CSV文件
	std::ofstream csvFile("学号排序成绩单.csv");
	if (!csvFile.is_open()) {
		std::cerr << "无法打开CSV文件。" << std::endl;
		return 1;
	}
	csvFile << "姓名,考号,";
	for(int i=1; i<n; i++) {
		csvFile << "实习成绩"<<i<<",";
	}
	csvFile <<"考勤扣分,试卷成绩,平时成绩,最终成绩" << std::endl;
	for (const Student& student : mergedStudents) {
		csvFile << student.name << "," << student.ID << ",";
		for(int i=1; i<n; i++) {
			csvFile <<student.score[i] << ",";
		}
		csvFile<< student.attendanceScore << "," << student.examScore << "," <<std::fixed <<std::setprecision(1)
		       << student.finalScore <<","<< std::fixed << std::setprecision(1) <<student.totalScore<< std::endl;
	}
	csvFile.close();
	std::cout << "\t\t\t学号排序成绩单已保存到CSV文件中。" << std::endl;
	std::cout<<"\t\t\t是否继续"<<std::endl;
	std::cout<<"\t\t\t";
	std::string k;
	std::cin>>k;
	if(k!="是") {
		exit(0);
	}
}
int  ScoreTranscript() {
	// 按成绩排序
	std::sort(mergedStudents.begin(), mergedStudents.end(), totalScore);
	// 输出成绩排序后的学生信息到CSV文件
	std::ofstream scsvFile("成绩排序成绩单.csv");
	if (!scsvFile.is_open()) {
		std::cerr << "无法打开CSV文件。" << std::endl;
		return 1;
	}
	scsvFile << "姓名,考号,";
	for(int i=1; i<n; i++) {
		scsvFile << "实习成绩"<<i<<",";
	}
	scsvFile <<"考勤扣分,试卷成绩,平时成绩,最终成绩" << std::endl;
	for (const Student& student : mergedStudents) {
		scsvFile << student.name << "," << student.ID << ",";
		for(int i=1; i<n; i++) {
			scsvFile <<student.score[i] << ",";
		}
		scsvFile<< student.attendanceScore << "," << student.examScore << "," <<std::fixed <<std::setprecision(1)
		        << student.finalScore <<","<< std::fixed << std::setprecision(1) <<student.totalScore<< std::endl;
	}
	scsvFile.close();
	std::cout << "\t\t\t成绩排序成绩单已保存到CSV文件中。" << std::endl;
	std::cout<<"\t\t\t是否继续"<<std::endl;
	std::cout<<"\t\t\t";
	std::string k;
	std::cin>>k;
	if(k!="是") {
		exit(0);
	}
}
void Check() {
	system("cls");
	// 考号查询功能
	switchAir();
	std::string queryInput;
	while (true) {
		std::cout << "\t\t\t请输入要查询的考号（输入'退出'以结束查询）：\n\t\t\t";
		std::cin >> queryInput;
		if (queryInput == "退出") {
			break;
		}
		int queryID = std::stoi(queryInput);
		auto it = studentMap.find(queryID);
		if (it != studentMap.end()) {
			const Student& student = it->second;
			std::cout << "\t\t\t考号：" << student.ID <<std::endl<<"\t\t\t姓名：" << student.name;
			for (int j = 1; j < n; j++) {
				std::cout <<std::endl<<"\t\t\t实习成绩" << j << ":" << student.score[j]<<std::endl;
			}
			std::cout <<std::endl<<"\t\t\t考勤扣分：" << student.attendanceScore
			          <<std::endl<<"\t\t\t试卷成绩：" << student.examScore
			          <<std::endl<<"\t\t\t平时成绩：" << student.finalScore
			          <<std::endl<<"\t\t\t最终成绩：" << student.totalScore << std::endl;
		} else {
			std::cout << "\t\t\t未找到考号为 " << queryID << " 的学生。" << std::endl;
		}
	}
}

