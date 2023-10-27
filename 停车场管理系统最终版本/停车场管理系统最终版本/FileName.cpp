#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ParkingLot.h"
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int main() {
    // 初始化停车场，设置停车场容量和每小时费用
    ParkingLot parkingLot(10, 5.0);

    while (true) {
        cout << "停车场管理程序" << endl;
        cout << "1. 车辆到达" << endl;
        cout << "2. 车辆离开" << endl;
        cout << "3. 显示停车场信息" << endl;
        cout << "4. 显示便道上情况" << endl;
        cout << "5. 查找汽车" << endl;
        cout << "6. 修改停车费用" << endl;
        cout << "0. 退出" << endl;
        cout << endl;

        int choice;
        cout << "请选择操作: ";
        cin >> choice;

        if (choice == 0) {
            parkingLot.FinalShow();
            break;
        }

        switch (choice) {
        case 1: {
            string CarCode;
            cout << "请输入车牌号: ";
            cin >> CarCode;
            parkingLot.CarIn(CarCode);
            break;
        }
        case 2: {
            string CarCode;
            string exit_time_str;  // 用于接收日期时间字符串

            cout << "请输入要离开的车牌号以及车辆离开的时间（格式类似：2023-10-25 16:25:31）: ";
            cin >> CarCode;
            cin.ignore();  // 忽略回车符
            getline(cin, exit_time_str);  // 获取整行输入，包括空格

            struct tm tm = {};
            int year, month, day, hour, minute, second;

            if (sscanf(exit_time_str.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
                tm.tm_year = year - 1900;  // 年份从1900开始
                tm.tm_mon = month - 1;     // 月份从0开始
                tm.tm_mday = day;
                tm.tm_hour = hour;
                tm.tm_min = minute;
                tm.tm_sec = second;

                time_t exitTime = mktime(&tm);

                //cout << "离开时间的时间戳（time_t）: " << exitTime << endl;
                parkingLot.CarOut(CarCode, exitTime);
            }
            else {
                cerr << "日期时间字符串格式不正确" << endl;
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
            cout << "请输入要查找的车牌号: ";
            cin >> CarCode;
            parkingLot.findCar(CarCode);
            break;
        }
        case 6: {
            double fee;
            cout << "请输入每小时停车费：" << endl;
            cin >> fee;
            parkingLot.ChangeCharge(fee);
        }
        default:
            cout << "无效的操作，请重新输入。" << endl;
        }

    }

    return 0;
}