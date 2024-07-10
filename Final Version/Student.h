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
		double attendanceScore; // ���ڳɼ�
		double finalScore; // ���ճɼ�
		double examScore; //�Ծ�ɼ�
		double totalScore;//�ܳɼ�
};
// ȫ�ֱ���
std::vector<Student> mergedStudents;
int n = 1;

switchUltra ultra;
switchAir air;
switchZH zh;
switchPro pro;
switchProMax pm;


// �������ڶ�ȡCSV�ļ�������һ��ѧ������
std::vector<Student> readStudentsFromCSV(const std::string& filePath, int scoreIndex) {
	std::vector<Student> students;
	std::ifstream file(filePath);
	while (!file.is_open()) {
		std::cerr << "\t\t\t�޷����ļ�: " << filePath << "\n\t\t\t�����������ļ�·����������'�˳�'�Խ�������" << std::endl;
		std::cout << "\t\t\t�������ļ�·��: \n";
		std::cout<<"\t\t\t";
		std::string newPath;
		std::cin >> newPath;
		if (newPath == "�˳�") {
			std::cerr << "�������˳���" << std::endl;
			exit(1); // ���߷���һ��������������ȡ������������
		}
		file.open(newPath);
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
			if(scoreIndex==30) {
				students.back().attendanceScore = score;
			} else if(scoreIndex==31) {
				students.back().examScore = score;
			} else if(scoreIndex<30) {
				students.back().score[scoreIndex] = score;
			} else {
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
// �����ճɼ�����ıȽϺ���
bool totalScore(const Student& a, const Student& b) {
	return a.totalScore > b.totalScore;
}

std::unordered_map<int, Student> studentMap;
int Intership_score() {
	// ʹ��unordered_map���ݿ��źϲ��ɼ�
	ultra.display();
	try {
		std::string Address;
		std::string input=" ";
		while(input!="��") {
			std::cout<<"\t\t\t�������"<<n<<"��ʵϰ�ɼ����ĵ�ַ"<<std::endl;
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
			std::cout<<"\t\t\t�Ƿ��������"<<std::endl;
			std::cout<<"\t\t\t";
			std::cin>>input;
			n++;
		}


		std::string KAddress,SAddress;
		std::cout<<"\t\t\t�����뿼�ڳɼ����ĵ�ַ"<<std::endl;
		std::cout<<"\t\t\t";
		std::cin>>KAddress;
		std::vector<Student> studentsAttendance = readStudentsFromCSV(KAddress,30);
		std::cout<<"\t\t\t�������Ծ�ɼ�����ַ"<<std::endl;
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

		// �������ճɼ�
		for (auto& pair : studentMap) {
			Student& student = pair.second;
			// �����Ĵγɼ���ƽ����
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

		// ��map�е�ѧ����Ϣת��������
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}
			std::cout<<"ת���ɹ�"<<std::endl;
		
			
	} catch (const std::exception& e) {
		std::cerr << "��������: " << e.what() << std::endl;
	}
	n--;
	return n;
}


void IDTranscript() {
	// ����������
	std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);
	// ���������ѧ����Ϣ��CSV�ļ�
	std::string name;
	std::cout<<"\t\t\t�������ɼ�����������׺��"<<std::endl<<"\t\t\t";
	std::cin>> name;
	name=name+".csv"; 
	std::ofstream csvFile(name);
	if (!csvFile.is_open()) {
		std::cerr << "�޷���CSV�ļ���" << std::endl;
		return ;
	}
	csvFile << "����,����,";
	for(int i=1; i<=n; i++) {
		csvFile << "ʵϰ�ɼ�"<<i<<",";
	}
	csvFile <<"���ڿ۷�,�Ծ�ɼ�,ƽʱ�ɼ�,���ճɼ�" << std::endl;
	for (const Student& student : mergedStudents) {
		csvFile << student.name << "," << student.ID << ",";
		for(int i=1; i<=n; i++) {
			csvFile <<student.score[i] << ",";
		}
		csvFile<< student.attendanceScore << "," << student.examScore << "," <<std::fixed <<std::setprecision(1)
		       << student.finalScore <<","<< std::fixed << std::setprecision(1) <<student.totalScore<< std::endl;
	}
	csvFile.close();
	std::cout << "\t\t\tѧ������ɼ����ѱ��浽CSV�ļ��С�" << std::endl;
	std::cout<<"\t\t\t�Ƿ����"<<std::endl;
	std::cout<<"\t\t\t";
	std::string k;
	std::cin>>k;
	if(k!="��") {
		exit(0);
	}
}
void  ScoreTranscript() {
	// ���ɼ�����
	std::sort(mergedStudents.begin(), mergedStudents.end(), totalScore);
	// ����ɼ�������ѧ����Ϣ��CSV�ļ�
	std::string name;
	std::cout<<"\t\t\t�������ɼ���(������׺)"<<std::endl<<"\t\t\t";
	std::cin>> name;
	name=name+".csv";
	std::ofstream csvFile(name);
	if (!csvFile.is_open()) {
		std::cerr << "�޷���CSV�ļ���" << std::endl;
		return ;
	}
	csvFile << "����,����,";
	for(int i=1; i<=n; i++) {
		csvFile << "ʵϰ�ɼ�"<<i<<",";
	}
	csvFile <<"���ڿ۷�,�Ծ�ɼ�,ƽʱ�ɼ�,���ճɼ�" << std::endl;
	for (const Student& student : mergedStudents) {
		csvFile << student.name << "," << student.ID << ",";
		for(int i=1; i<n; i++) {
			csvFile <<student.score[i] << ",";
		}
		csvFile<< student.attendanceScore << "," << student.examScore << "," <<std::fixed <<std::setprecision(1)
		        << student.finalScore <<","<< std::fixed << std::setprecision(1) <<student.totalScore<< std::endl;
	}
	csvFile.close();
	std::cout << "\t\t\t�ɼ�����ɼ����ѱ��浽CSV�ļ��С�" << std::endl;
	std::cout<<"\t\t\t�Ƿ����"<<std::endl;
	std::cout<<"\t\t\t";
	std::string k;
	std::cin>>k;
	if(k!="��") {
		exit(0);
	}
}
void Check() {
	std::cout<<"\033c";
	air.display();
	std::string queryInput;
	while (true) {
		std::cout << "\t\t\t������Ҫ��ѯ�Ŀ��ţ�����'�˳�'�Խ�����ѯ����\n\t\t\t";
		std::cin >> queryInput;
		if (queryInput == "�˳�") {
			break;
		}
		int queryID = std::stoi(queryInput);
		auto it = studentMap.find(queryID);
		if (it != studentMap.end()) {
			const Student& student = it->second;
			std::cout << "\t\t\t���ţ�" << student.ID <<std::endl<<"\t\t\t������" << student.name;
			for (int j = 1; j <= n; j++) {
				std::cout <<std::endl<<"\t\t\tʵϰ�ɼ�" << j << ":" << student.score[j];
			}
			std::cout <<std::endl<<"\t\t\t���ڿ۷֣�" << student.attendanceScore
			          <<std::endl<<"\t\t\t�Ծ�ɼ���" << student.examScore
			          <<std::endl<<"\t\t\tƽʱ�ɼ���" << student.finalScore
			          <<std::endl<<"\t\t\t���ճɼ���" << student.totalScore << std::endl;
		} else {
			std::cout << "\t\t\tδ�ҵ�����Ϊ " << queryID << " ��ѧ����" << std::endl;
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
    std::cout << "\t\t\t\t\t\t�ɼ��ֲ�ֱ��ͼ��" << std::endl;

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
   std::cout<<"\t|  ��߷�:|"<<"  "<<maxScore<<"        |"<<std::endl;
   std::cout<<"\t|  ��ͷ�:|"<<"  "<<minScore<<"         |"<<std::endl;
   std::cout<<"\t|  ƽ����:|"<<"  "<<std::setprecision(2) << averageScore<<"        |"<<std::endl;
   std::cout<<"\t------------------------"<<std::endl;
   
  
}
