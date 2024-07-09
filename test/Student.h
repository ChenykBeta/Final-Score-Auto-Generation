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
// ȫ�ֱ���
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
        int barWidth = static_cast<int>((static_cast<double>(entry.second) / maxFrequency) * 50); // 50Ϊ�����
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
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|             1.¼��ɼ�                    |"<<std::endl;
	std::cout<<"\t\t\t|             0.�˳�ϵͳ                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t׼����n��ʵϰ�ɼ����Ծ�ɼ�����ʽ�����ţ��������༶���ɼ���"<< std::endl;
	std::cout<<"\t\t\t���ڳɼ�����ʽ���ţ��������༶�����ڿ۷֣���Ϊcsv�ļ�"<<std::endl;
	std::cout<<"\t\t\t��ѡ��:";
}
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
void switchUltra() {
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|               ¼��ɼ�                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
void switchAir() {
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|               ��ѯ���˳ɼ�                |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
std::unordered_map<int, Student> studentMap;
void Intership_score() {
	// ʹ��unordered_map���ݿ��źϲ��ɼ�
	switchUltra();
	try {
		int n=1;
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
		std::vector<Student> mergedStudents;
		for (const auto& pair : studentMap) {
			mergedStudents.push_back(pair.second);
		}
	} catch (const std::exception& e) {
		std::cerr << "��������: " << e.what() << std::endl;
	}
}
void switchPro() {
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|             �ɼ�¼��ɹ�                  |"<<std::endl;
	std::cout<<"\t\t\t|             1.���ɳɼ���                  |"<<std::endl;
	std::cout<<"\t\t\t|             2.��ѯ���˳ɼ�                |"<<std::endl;
	std::cout<<"\t\t\t|             0.�˳�ϵͳ                    |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t��ѡ��:";
}
void switchProMax() {
	std::cout<<"\033c";
	std::cout<<"\n"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
	std::cout<<"\t\t\t|           ��ӭ������ĩ�ɼ�����ϵͳ        |"<<std::endl;
	std::cout<<"\t\t\t|===========================================|"<<std::endl;
	std::cout<<"\t\t\t|              ���ɳɼ���                   |"<<std::endl;
	std::cout<<"\t\t\t|             1.��ѧ������ɼ���            |"<<std::endl;
	std::cout<<"\t\t\t|             2.���ɼ�����ɼ���            |"<<std::endl;
	std::cout<<"\t\t\t|             0.������һ��                  |"<<std::endl;
	std::cout<<"\t\t\t|                                           |"<<std::endl;
	std::cout<<"\t\t\t============================================="<<std::endl;
}
int IDTranscript() {
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
	std::cout << "\t\t\tѧ������ɼ����ѱ��浽CSV�ļ��С�" << std::endl;
	std::cout<<"\t\t\t�Ƿ����"<<std::endl;
	std::cout<<"\t\t\t";
	std::string k;
	std::cin>>k;
	if(k!="��") {
		exit(0);
	}
}
int  ScoreTranscript() {
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
	system("cls");
	// ���Ų�ѯ����
	switchAir();
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
			for (int j = 1; j < n; j++) {
				std::cout <<std::endl<<"\t\t\tʵϰ�ɼ�" << j << ":" << student.score[j]<<std::endl;
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

