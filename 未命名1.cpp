#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // std::sort
#include <stdexcept>
#include <unordered_map> // std::unordered_map

class Student {
	public:
		std::string name;
		int ID;
		double score1, score2, score3, score4;
		double attendanceScore; // 考勤成绩
		double finalScore; // 最终成绩
		double examScore; //试卷成绩 
		double totalScore;//总成绩 
};

// 函数用于读取CSV文件并返回一个学生向量
std::vector<Student> readStudentsFromCSV(const std::string& filePath, int scoreIndex) {
	std::vector<Student> students;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("无法打开文件: " + filePath);
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
			switch (scoreIndex) {
				case 1:
					students.back().score1 = score;
					break;
				case 2:
					students.back().score2 = score;
					break;
				case 3:
					students.back().score3 = score;
					break;
				case 4:
					students.back().score4 = score;
					break;
				case 5:
					students.back().attendanceScore = score;
					break;//考勤成绩 
				case 6:
					students.back().examScore = score;	
					break; // 试卷成绩 
				default:
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

int main() {
	std::string filePath1 = "实习1.csv";
	std::string filePath2 = "实习2.csv";
	std::string filePath3 = "实习3.csv";
	std::string filePath4 = "实习4.csv";
	std::string filePathAttendance = "考勤.csv";
	std::string filePathexamScore = "试卷成绩.csv";
	try {
		std::vector<Student> students1 = readStudentsFromCSV(filePath1, 1);
		std::vector<Student> students2 = readStudentsFromCSV(filePath2, 2);
		std::vector<Student> students3 = readStudentsFromCSV(filePath3, 3);
		std::vector<Student> students4 = readStudentsFromCSV(filePath4, 4);
		std::vector<Student> studentsAttendance = readStudentsFromCSV(filePathAttendance, 5);
		std::vector<Student> studentsexamScore = readStudentsFromCSV(filePathexamScore, 6);

		// 使用unordered_map根据考号合并成绩
		std::unordered_map<int, Student> studentMap;
		for (const auto& student : students1) {
			studentMap[student.ID] = student;
		}
		for (const auto& student : students2) {
			if (studentMap.find(student.ID) != studentMap.end()) {
				studentMap[student.ID].score2 = student.score2;
			} else {
				studentMap[student.ID] = student;
			}
		}
		for (const auto& student : students3) {
			if (studentMap.find(student.ID) != studentMap.end()) {
				studentMap[student.ID].score3 = student.score3;
			} else {
				studentMap[student.ID] = student;
			}
		}
		for (const auto& student : students4) {
			if (studentMap.find(student.ID) != studentMap.end()) {
				studentMap[student.ID].score4 = student.score4;
			} else {
				studentMap[student.ID] = student;
			}
		}
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
			double averageScore = (student.score1 + student.score2 + student.score3 + student.score4) / 4;
			// 从平均分中减去考勤成绩，得到最终成绩			
			student.finalScore = averageScore - student.attendanceScore;
			if(student.finalScore<0){
				student.finalScore=0;
			}
			student.totalScore =student.finalScore*0.3+student.examScore*0.7;
		}

		// 将map中的学生信息转换回向量
		std::vector<Student> mergedStudents;
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}

		// 按考号排序
		std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);
/*
		// 输出排序后的学生信息
		std::cout<<"姓名   "<<"学号      "<<"成绩1   " <<"成绩2   "<<"成绩3   "<<"成绩4   "<<"考勤扣分   "<<"平时成绩   "<<"试卷成绩      "<<"总成绩"<<std::endl;
		for (const Student& student : mergedStudents) {
			std::cout << student.name << " - " << student.ID << " - "
			          << student.score1 << " - " << student.score2 << " - "
			          << student.score3 << " - " << student.score4 << " - "
			          << student.attendanceScore << " - " << student.finalScore<< " - " << student.examScore <<" - " << student.totalScore<<  std::endl;
		}*/
		
		  // 输出排序后的学生信息到CSV文件
        std::ofstream csvFile("成绩单.csv");
        if (!csvFile.is_open()) {
            std::cerr << "无法打开CSV文件。" << std::endl;
            return 1;
        }

        csvFile << "姓名,考号,成绩1,成绩2,成绩3,成绩4,考勤成绩,试卷成绩,最终成绩" << std::endl;
        for (const Student& student : mergedStudents) {
            csvFile << student.name << "," << student.ID << ","
                    << student.score1 << "," << student.score2 << ","
                    << student.score3 << "," << student.score4 << ","
                    << student.attendanceScore << "," << student.examScore << ","
                    << student.finalScore << std::endl;
        }

        csvFile.close();
        std::cout << "学生成绩已保存到CSV文件中。" << std::endl;
					
	} catch (const std::exception& e) {
		std::cerr << "发生错误: " << e.what() << std::endl;
	}

	return 0;
}



#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
int main()
{
    cout<<"——————————————————————————————————————————————"<<endl;
    cout<<"——————————————————————————————————————————————"<<endl;
    cout<<"|      Final Grade Auto Generation Syste     |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"——————————————————————————————————————————————"<<endl;
    cout<<"——————————————————————————————————————————————"<<endl;
}





