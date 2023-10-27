#define _CRT_SECURE_NO_WARNINGS

#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

struct Car {
	time_t InTime;
	time_t OutTime;//进出时间
	string CarCode;//车牌号
	double charge;//收费

    Car(string CarCode) :CarCode(CarCode) {

    }

    Car() {

    }
};

class ParkingLot {
private:
    int capacity;           // 停车场容量
    stack<Car> InStack;     // 模拟停车场，使用栈
    queue<Car> OutQueue;    // 模拟便道，使用队列
    vector<Car> money;      // 费用记录
    double charge_per_hour; // 每小时费用
public:

    ParkingLot(int n, double rate);//构造函数，模拟每小时收费情况

    void CarIn(string CarCode);//车辆进入停车场

    void CarOut(string CarCode, time_t exitTime);//车辆离开停车场

    void ShowStack();//展示停车场的数据

    void ShowQueue();//展示便道的数据

    void findCar(string licensePlate);//找车

    void ChangeCharge(double newRate);//修改收费标准

    void FinalShow();//最终的展示
};