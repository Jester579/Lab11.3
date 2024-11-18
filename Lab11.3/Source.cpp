//C:\Users\User\source\repos\Lab11.3\train.txt
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum TrainType { REGULAR, COMFORT, EXPRESS };
string trainTypeStr[] = { "���������", "ϳ��������� ��������", "��������� �������" };

void AddTrain(const string& filename) {
    ofstream file(filename, ios::app); 
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    string destination, departureTime;
    int type;

    cin.ignore();
    cout << "����� ������ �����������: ";
    getline(cin, destination);

    cout << "��� ���������� (0 - ���������, 1 - ϳ��������� ��������, 2 - ��������� �������): ";
    cin >> type;
    while (type < 0 || type > 2) {
        cout << "������������ ���! �������� ������: ";
        cin >> type;
    }

    cout << "��� ����������� (��:��): ";
    cin >> departureTime;

    file << destination << ";" << type << ";" << departureTime << "\n";

    file.close();
    cout << "����� ������ ������." << endl;
}

void PrintTrains(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!" << endl;
        return;
    }

    string line;
    cout << "===================================================================" << endl;
    cout << "| ����� �����������      | ���                     | ���          |" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    while (getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.rfind(';');
        string destination = line.substr(0, pos1);
        int type = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        string departureTime = line.substr(pos2 + 1);

        cout << "| " << setw(20) << left << destination
            << "| " << setw(24) << left << trainTypeStr[type]
            << "| " << setw(10) << right << departureTime << " |" << endl;
    }
    cout << "===================================================================" << endl;
    file.close();
}

void TrainsAfterTime(const string& filename) {
    string inputTime;
    cout << "������ ��� (��:��): ";
    cin >> inputTime;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.rfind(';');
        string destination = line.substr(0, pos1);
        int type = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        string departureTime = line.substr(pos2 + 1);

        if (departureTime > inputTime) {
            cout << "����� �����������: " << destination
                << ", ���: " << trainTypeStr[type]
                << ", ��� �����������: " << departureTime << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "���� �����, �� �������� ���� " << inputTime << "." << endl;
    }

    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "������ ����� ���������� ����� (� �����������): ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl << "����:" << endl;
        cout << " [1] - ������ �����" << endl;
        cout << " [2] - ������� �� ������" << endl;
        cout << " [3] - ����� ���� ��������� ����" << endl;
        cout << " [0] - �����" << endl;
        cout << "������� ��: ";
        cin >> menuItem;
        switch (menuItem) {
        case 1:
            AddTrain(filename);
            break;
        case 2:
            PrintTrains(filename);
            break;
        case 3:
            TrainsAfterTime(filename);
            break;
        case 0:
            cout << "���������� ������ ��������." << endl;
            break;
        default:
            cout << "������������ ����! ��������� �� ���." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
