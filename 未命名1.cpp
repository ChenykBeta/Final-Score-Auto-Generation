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
		double attendanceScore; // ���ڳɼ�
		double finalScore; // ���ճɼ�
		double examScore; //�Ծ�ɼ� 
		double totalScore;//�ܳɼ� 
};

// �������ڶ�ȡCSV�ļ�������һ��ѧ������
std::vector<Student> readStudentsFromCSV(const std::string& filePath, int scoreIndex) {
	std::vector<Student> students;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("�޷����ļ�: " + filePath);
	}

	std::string line;
	// ����������
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string IDStr, name, discard;
		double score;
		if (std::getline(iss, IDStr, ',') && std::getline(iss, name, ',') && std::getline(iss, discard, ',') && iss >> score) {
			int ID = std::stoi(IDStr); // �������ַ���ת��Ϊ����
			students.push_back({name, ID, 0, 0, 0, 0, 0, 0,0}); // ��ʼ�����гɼ�Ϊ0
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
					break;//���ڳɼ� 
				case 6:
					students.back().examScore = score;	
					break; // �Ծ�ɼ� 
				default:
					throw std::runtime_error("��Ч�ĳɼ�����");
			}
		} else {
			throw std::runtime_error("�ļ���ʽ����");
		}
	}

	file.close();
	return students;
}

// ����������ıȽϺ���
bool compareByID(const Student& a, const Student& b) {
	return a.ID < b.ID;
}

int main() {
	std::string filePath1 = "ʵϰ1.csv";
	std::string filePath2 = "ʵϰ2.csv";
	std::string filePath3 = "ʵϰ3.csv";
	std::string filePath4 = "ʵϰ4.csv";
	std::string filePathAttendance = "����.csv";
	std::string filePathexamScore = "�Ծ�ɼ�.csv";
	try {
		std::vector<Student> students1 = readStudentsFromCSV(filePath1, 1);
		std::vector<Student> students2 = readStudentsFromCSV(filePath2, 2);
		std::vector<Student> students3 = readStudentsFromCSV(filePath3, 3);
		std::vector<Student> students4 = readStudentsFromCSV(filePath4, 4);
		std::vector<Student> studentsAttendance = readStudentsFromCSV(filePathAttendance, 5);
		std::vector<Student> studentsexamScore = readStudentsFromCSV(filePathexamScore, 6);

		// ʹ��unordered_map���ݿ��źϲ��ɼ�
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
		


		// �������ճɼ�
		for (auto& pair : studentMap) {
			Student& student = pair.second;
			// �����Ĵγɼ���ƽ����
			double averageScore = (student.score1 + student.score2 + student.score3 + student.score4) / 4;
			// ��ƽ�����м�ȥ���ڳɼ����õ����ճɼ�			
			student.finalScore = averageScore - student.attendanceScore;
			if(student.finalScore<0){
				student.finalScore=0;
			}
			student.totalScore =student.finalScore*0.3+student.examScore*0.7;
		}

		// ��map�е�ѧ����Ϣת��������
		std::vector<Student> mergedStudents;
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}

		// ����������
		std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);
/*
		// ���������ѧ����Ϣ
		std::cout<<"����   "<<"ѧ��      "<<"�ɼ�1   " <<"�ɼ�2   "<<"�ɼ�3   "<<"�ɼ�4   "<<"���ڿ۷�   "<<"ƽʱ�ɼ�   "<<"�Ծ�ɼ�      "<<"�ܳɼ�"<<std::endl;
		for (const Student& student : mergedStudents) {
			std::cout << student.name << " - " << student.ID << " - "
			          << student.score1 << " - " << student.score2 << " - "
			          << student.score3 << " - " << student.score4 << " - "
			          << student.attendanceScore << " - " << student.finalScore<< " - " << student.examScore <<" - " << student.totalScore<<  std::endl;
		}*/
		
		  // ���������ѧ����Ϣ��CSV�ļ�
        std::ofstream csvFile("�ɼ���.csv");
        if (!csvFile.is_open()) {
            std::cerr << "�޷���CSV�ļ���" << std::endl;
            return 1;
        }

        csvFile << "����,����,�ɼ�1,�ɼ�2,�ɼ�3,�ɼ�4,���ڳɼ�,�Ծ�ɼ�,���ճɼ�" << std::endl;
        for (const Student& student : mergedStudents) {
            csvFile << student.name << "," << student.ID << ","
                    << student.score1 << "," << student.score2 << ","
                    << student.score3 << "," << student.score4 << ","
                    << student.attendanceScore << "," << student.examScore << ","
                    << student.finalScore << std::endl;
        }

        csvFile.close();
        std::cout << "ѧ���ɼ��ѱ��浽CSV�ļ��С�" << std::endl;
					
	} catch (const std::exception& e) {
		std::cerr << "��������: " << e.what() << std::endl;
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
    cout<<"��������������������������������������������������������������������������������������������"<<endl;
    cout<<"��������������������������������������������������������������������������������������������"<<endl;
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
    cout<<"��������������������������������������������������������������������������������������������"<<endl;
    cout<<"��������������������������������������������������������������������������������������������"<<endl;
}





