#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ParkingLot.h"
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int main() {
    // ��ʼ��ͣ����������ͣ����������ÿСʱ����
    ParkingLot parkingLot(10, 5.0);

    while (true) {
        cout << "ͣ�����������" << endl;
        cout << "1. ��������" << endl;
        cout << "2. �����뿪" << endl;
        cout << "3. ��ʾͣ������Ϣ" << endl;
        cout << "4. ��ʾ��������" << endl;
        cout << "5. ��������" << endl;
        cout << "6. �޸�ͣ������" << endl;
        cout << "0. �˳�" << endl;
        cout << endl;

        int choice;
        cout << "��ѡ�����: ";
        cin >> choice;

        if (choice == 0) {
            parkingLot.FinalShow();
            break;
        }

        switch (choice) {
        case 1: {
            string CarCode;
            cout << "�����복�ƺ�: ";
            cin >> CarCode;
            parkingLot.CarIn(CarCode);
            break;
        }
        case 2: {
            string CarCode;
            string exit_time_str;  // ���ڽ�������ʱ���ַ���

            cout << "������Ҫ�뿪�ĳ��ƺ��Լ������뿪��ʱ�䣨��ʽ���ƣ�2023-10-25 16:25:31��: ";
            cin >> CarCode;
            cin.ignore();  // ���Իس���
            getline(cin, exit_time_str);  // ��ȡ�������룬�����ո�

            struct tm tm = {};
            int year, month, day, hour, minute, second;

            if (sscanf(exit_time_str.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
                tm.tm_year = year - 1900;  // ��ݴ�1900��ʼ
                tm.tm_mon = month - 1;     // �·ݴ�0��ʼ
                tm.tm_mday = day;
                tm.tm_hour = hour;
                tm.tm_min = minute;
                tm.tm_sec = second;

                time_t exitTime = mktime(&tm);

                //cout << "�뿪ʱ���ʱ�����time_t��: " << exitTime << endl;
                parkingLot.CarOut(CarCode, exitTime);
            }
            else {
                cerr << "����ʱ���ַ�����ʽ����ȷ" << endl;
            }
            break;
        }
        case 3:
            parkingLot.ShowStack();
            break;
        case 4:
            parkingLot.ShowQueue();
            break;
        case 5: {
            string CarCode;
            cout << "������Ҫ���ҵĳ��ƺ�: ";
            cin >> CarCode;
            parkingLot.findCar(CarCode);
            break;
        }
        case 6: {
            double fee;
            cout << "������ÿСʱͣ���ѣ�" << endl;
            cin >> fee;
            parkingLot.ChangeCharge(fee);
        }
        default:
            cout << "��Ч�Ĳ��������������롣" << endl;
        }

    }

    return 0;
}