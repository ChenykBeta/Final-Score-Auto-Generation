#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // std::sort
#include <stdexcept>
#include <unordered_map> // std::unordered_map
#include<iomanip>
#include"cansee.h"
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
int n = 1;

switchUltra ultra;
switchAir air;
switchZH zh;
switchPro pro;
switchProMax pm;


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

std::unordered_map<int, Student> studentMap;
int Intership_score() {
	// 使用unordered_map根据考号合并成绩
	ultra.display();
	try {
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
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}
			std::cout<<"转换成功"<<std::endl;
		
			
	} catch (const std::exception& e) {
		std::cerr << "发生错误: " << e.what() << std::endl;
	}
	n--;
	return n;
}


void IDTranscript() {
	// 按考号排序
	std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);
	// 输出排序后的学生信息到CSV文件
	std::string name;
	std::cout<<"\t\t\t请命名成绩单（不带后缀）"<<std::endl<<"\t\t\t";
	std::cin>> name;
	name=name+".csv"; 
	std::ofstream csvFile(name);
	if (!csvFile.is_open()) {
		std::cerr << "无法打开CSV文件。" << std::endl;
		return ;
	}
	csvFile << "姓名,考号,";
	for(int i=1; i<=n; i++) {
		csvFile << "实习成绩"<<i<<",";
	}
	csvFile <<"考勤扣分,试卷成绩,平时成绩,最终成绩" << std::endl;
	for (const Student& student : mergedStudents) {
		csvFile << student.name << "," << student.ID << ",";
		for(int i=1; i<=n; i++) {
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
void  ScoreTranscript() {
	// 按成绩排序
	std::sort(mergedStudents.begin(), mergedStudents.end(), totalScore);
	// 输出成绩排序后的学生信息到CSV文件
	std::string name;
	std::cout<<"\t\t\t请命名成绩单(不带后缀)"<<std::endl<<"\t\t\t";
	std::cin>> name;
	name=name+".csv";
	std::ofstream csvFile(name);
	if (!csvFile.is_open()) {
		std::cerr << "无法打开CSV文件。" << std::endl;
		return ;
	}
	csvFile << "姓名,考号,";
	for(int i=1; i<=n; i++) {
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
	std::cout<<"\033c";
	air.display();
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
			for (int j = 1; j <= n; j++) {
				std::cout <<std::endl<<"\t\t\t实习成绩" << j << ":" << student.score[j];
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
void drawHistogram() {
	std::cout<<"\033c";
    std::vector<double> totalScores;
    for (const auto& student : mergedStudents) {
        totalScores.push_back(student.totalScore);
    }

    int intervals[5] = {0}; // 5 intervals for 0-19, 20-39, 40-59, 60-79, 80-100
    for (const auto& score : totalScores) {
        int index = static_cast<int>(score / 20);
        if (index >= 5) index = 4;
        intervals[index]++;
    }

    int totalStudents = totalScores.size();
    double percentages[5] = {0};
    for (int i = 0; i < 5; ++i) {
        percentages[i] = static_cast<double>(intervals[i]) / totalStudents * 100;
    }

    // Find the maximum percentage for scaling the y-axis
    double maxPercentage = *std::max_element(std::begin(percentages), std::end(percentages));
  
   
    // Output the histogram vertically with x and y axes
    std::cout << "\t\t\t\t\t\t成绩分布直方图：" << std::endl;

    // Print y-axis labels and histogram
    for (int i = 20; i >= 0; --i) {
        double currentPercentage = i * 5;
        std::cout << std::setw(4) << currentPercentage << "% | ";
        for (int j = 0; j < 5; ++j) {
            if (percentages[j] >= currentPercentage) {
                std::cout << "****  ";
            } else {
                std::cout << "      ";
            }
        }
        std::cout << std::endl;
    }

    // Print x-axis
    std::cout << "      +";
    for (int i = 0; i < 5; ++i) {
        std::cout << "------";
    }
    std::cout << std::endl;

    // Print x-axis labels
    std::cout << "     0 ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << std::setw(5) << i * 20 << " ";
    }
   
  // Calculate and output max, min, and average score
  std::cout<<std::endl;
    std::cout<<std::endl;
     std::cout<<std::endl;
      std::cout<<std::endl;
    double maxScore = *std::max_element(totalScores.begin(), totalScores.end());
    double minScore = *std::min_element(totalScores.begin(), totalScores.end());
    double averageScore = std::accumulate(totalScores.begin(), totalScores.end(), 0.0) / totalStudents;
    
   std::cout<<"\t------------------------"<<std::endl;
   std::cout<<"\t|  最高分:|"<<"  "<<maxScore<<"        |"<<std::endl;
   std::cout<<"\t|  最低分:|"<<"  "<<minScore<<"         |"<<std::endl;
   std::cout<<"\t|  平均分:|"<<"  "<<std::setprecision(2) << averageScore<<"        |"<<std::endl;
   std::cout<<"\t------------------------"<<std::endl;
   
  
}
