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


int main() {

	std::cout<<"            ��ӭ������ĩ�ɼ��Զ�����ϵͳ           "<<std::endl;
	std::cout<<"\n"<<"\n"<<"\n"<<std::endl;

	std::cout<<"׼����n��ʵϰ�ɼ����Ծ�ɼ�����ʽ�����ţ��������༶���ɼ���"<< std::endl;
	std::cout<<"���ڳɼ�����ʽ���ţ��������༶�����ڿ۷֣���Ϊcsv�ļ�"<<std::endl;

	int n=1;
	std::string Address;
	std::string input=" ";
	try {

		// ʹ��unordered_map���ݿ��źϲ��ɼ�
		std::unordered_map<int, Student> studentMap;
		while(input!="��") {
			std::cout<<"�������"<<n<<"��ʵϰ�ɼ����ĵ�ַ"<<std::endl;
			std::cin>>Address;
			std::vector<Student> students1 = readStudentsFromCSV(Address, n);
			for (const auto& student : students1) {
				if (studentMap.find(student.ID) != studentMap.end()) {
					studentMap[student.ID].score[n] = student.score[n];
				} else {
					studentMap[student.ID] = student;
				}
			}
			std::cout<<"�Ƿ��������"<<std::endl;
			std::cin>>input;
			n++;
		}


		std::string KAddress,SAddress;
		std::cout<<"�����뿼�ڳɼ����ĵ�ַ"<<std::endl;
		std::cin>>KAddress;
		std::vector<Student> studentsAttendance = readStudentsFromCSV(KAddress,30);
		std::cout<<"�������Ծ�ɼ�����ַ"<<std::endl;
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
		std::vector<Student> mergedStudents;
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}


		// ����������
		std::sort(mergedStudents.begin(), mergedStudents.end(), compareByID);

		// ���������ѧ����Ϣ��CSV�ļ�
		std::ofstream csvFile("ѧ������ɼ���.csv");
		if (!csvFile.is_open()) {
			std::cerr << "�޷���CSV�ļ���" << std::endl;
			return 1;
		}
		csvFile << "����,����,";
		for(int i=1; i<n; i++) {
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
		std::cout << "ѧ������ɼ����ѱ��浽CSV�ļ��С�" << std::endl;



		// ���ɼ�����
		std::sort(mergedStudents.begin(), mergedStudents.end(), totalScore);
		// ����ɼ�������ѧ����Ϣ��CSV�ļ�
		std::ofstream scsvFile("�ɼ�����ɼ���.csv");
		if (!scsvFile.is_open()) {
			std::cerr << "�޷���CSV�ļ���" << std::endl;
			return 1;
		}
		scsvFile << "����,����,";
		for(int i=1; i<n; i++) {
			scsvFile << "ʵϰ�ɼ�"<<i<<",";
		}
		scsvFile <<"���ڿ۷�,�Ծ�ɼ�,ƽʱ�ɼ�,���ճɼ�" << std::endl;
		for (const Student& student : mergedStudents) {
			scsvFile << student.name << "," << student.ID << ",";
			for(int i=1; i<n; i++) {
				scsvFile <<student.score[i] << ",";
			}
			scsvFile<< student.attendanceScore << "," << student.examScore << "," <<std::fixed <<std::setprecision(1)
			        << student.finalScore <<","<< std::fixed << std::setprecision(1) <<student.totalScore<< std::endl;
		}
		scsvFile.close();
		std::cout << "�ɼ�����ɼ����ѱ��浽CSV�ļ��С�" << std::endl;


	} catch (const std::exception& e) {
		std::cerr << "��������: " << e.what() << std::endl;
	}


	catch (const std::exception& e) {
		std::cerr << "��������: " << e.what() << std::endl;
	}

	return 0;
}
