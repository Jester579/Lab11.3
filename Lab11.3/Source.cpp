//C:\Users\User\source\repos\Lab11.3\train.txt
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum TrainType { REGULAR, COMFORT, EXPRESS };
string trainTypeStr[] = { "Звичайний", "Підвищеного комфорту", "Швидкісний експрес" };

void AddTrain(const string& filename) {
    ofstream file(filename, ios::app); 
    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    string destination, departureTime;
    int type;

    cin.ignore();
    cout << "Назва пункту призначення: ";
    getline(cin, destination);

    cout << "Тип електрички (0 - Звичайний, 1 - Підвищеного комфорту, 2 - Швидкісний експрес): ";
    cin >> type;
    while (type < 0 || type > 2) {
        cout << "Неправильний тип! Повторіть спробу: ";
        cin >> type;
    }

    cout << "Час відправлення (ГГ:ХХ): ";
    cin >> departureTime;

    file << destination << ";" << type << ";" << departureTime << "\n";

    file.close();
    cout << "Запис успішно додано." << endl;
}

void PrintTrains(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    string line;
    cout << "===================================================================" << endl;
    cout << "| Пункт призначення      | Тип                     | Час          |" << endl;
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
    cout << "Введіть час (ГГ:ХХ): ";
    cin >> inputTime;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
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
            cout << "Пункт призначення: " << destination
                << ", Тип: " << trainTypeStr[type]
                << ", Час відправлення: " << departureTime << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Немає поїздів, що відходять після " << inputTime << "." << endl;
    }

    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "Введіть назву текстового файлу (з розширенням): ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl << "Меню:" << endl;
        cout << " [1] - Додати запис" << endl;
        cout << " [2] - Вивести всі записи" << endl;
        cout << " [3] - Поїзди після вказаного часу" << endl;
        cout << " [0] - Вихід" << endl;
        cout << "Виберіть дію: ";
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
            cout << "Завершення роботи програми." << endl;
            break;
        default:
            cout << "Неправильний вибір! Спробуйте ще раз." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
