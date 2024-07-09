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


int main() {

	std::cout<<"            欢迎来到期末成绩自动生产系统           "<<std::endl;
	std::cout<<"\n"<<"\n"<<"\n"<<std::endl;

	std::cout<<"准备好n次实习成绩和试卷成绩（格式：考号，姓名，班级，成绩）"<< std::endl;
	std::cout<<"考勤成绩（格式考号，姓名，班级，考勤扣分）均为csv文件"<<std::endl;

	int n=1;
	std::string Address;
	std::string input=" ";
	try {

		// 使用unordered_map根据考号合并成绩
		std::unordered_map<int, Student> studentMap;
		while(input!="否") {
			std::cout<<"请输入第"<<n<<"次实习成绩单的地址"<<std::endl;
			std::cin>>Address;
			std::vector<Student> students1 = readStudentsFromCSV(Address, n);
			for (const auto& student : students1) {
				if (studentMap.find(student.ID) != studentMap.end()) {
					studentMap[student.ID].score[n] = student.score[n];
				} else {
					studentMap[student.ID] = student;
				}
			}
			std::cout<<"是否继续输入"<<std::endl;
			std::cin>>input;
			n++;
		}


		std::string KAddress,SAddress;
		std::cout<<"请输入考勤成绩单的地址"<<std::endl;
		std::cin>>KAddress;
		std::vector<Student> studentsAttendance = readStudentsFromCSV(KAddress,30);
		std::cout<<"请输入试卷成绩单地址"<<std::endl;
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
		std::cout << "学号排序成绩单已保存到CSV文件中。" << std::endl;



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
		std::cout << "成绩排序成绩单已保存到CSV文件中。" << std::endl;


	} catch (const std::exception& e) {
		std::cerr << "发生错误: " << e.what() << std::endl;
	}


	catch (const std::exception& e) {
		std::cerr << "发生错误: " << e.what() << std::endl;
	}

	return 0;
}
