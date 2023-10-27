#include "ParkingLot.h"

ParkingLot::ParkingLot(int Capacity, double charge_per_hour):capacity(Capacity),charge_per_hour(charge_per_hour){

}

void ParkingLot::CarIn(string CarCode) {

    Car car(CarCode);
    car.InTime = time(0);

    if (InStack.size() < capacity) {//如果停车场停的下
        InStack.push(car);
        cout << "车辆 " << car.CarCode << " 进入停车场。" << endl;
    }
    else {//停车场停不下，停在便道上
        OutQueue.push(car);
        cout << "车辆 " << car.CarCode << " 在便道上等候。" << endl;
    }
}

void ParkingLot::CarOut(string CarCode, time_t exitTime){
    Car carToExit;
    bool found = false;
    stack<Car> tempStack;
    
    while (!InStack.empty()) {// 从停车场查找车辆
        Car car = InStack.top();
        InStack.pop();
        if (car.CarCode == CarCode) {
            found = true;
            carToExit = car;
            carToExit.OutTime = exitTime;  // 设置离开时间
        }
        else {
            tempStack.push(car); // 将非匹配的车重新入栈
        }
    }

    while (!tempStack.empty()) {// 重新放回停车场
        InStack.push(tempStack.top());
        tempStack.pop();
    }

    if (found) {
        // 计算费用并记录
        double duration = difftime(carToExit.OutTime, carToExit.InTime);
        carToExit.charge = (duration / 3600) * charge_per_hour;
        money.push_back(carToExit);
        cout << "车辆 " << carToExit.CarCode << " 离开停车场。" << endl;
        cout << "停留时间：" << fixed << setprecision(2) << duration / 3600 << "小时，费用：" << fixed << setprecision(2) << carToExit.charge << "元" << endl;

        if (!OutQueue.empty()) {// 如果便道上有等待的车辆，将其放入停车场
            Car car = OutQueue.front();
            OutQueue.pop();
            CarIn(car.CarCode);//这里会重新得到一个本地时间
        }
    }
    else {
        cout << "未找到车辆 " << CarCode << "。" << endl;
    }

}

void ParkingLot::ShowStack() {// 显示停车场信息
    cout << "停车场信息：" << endl;
    stack<Car> tempStack = InStack;//临时的stack，用了就丢

    while (!tempStack.empty()) {
        Car car = tempStack.top();
        tempStack.pop();
        cout << "车牌号：" << car.CarCode << "，进入时间：" << ctime(&car.InTime);
    }
}

void ParkingLot::ShowQueue() {// 显示便道上的情况
    cout << "便道上的车辆：" << endl;
    queue<Car> tempQueue = OutQueue;//临时的Queue，用了就丢

    while (!tempQueue.empty()) {
        Car car = tempQueue.front();
        tempQueue.pop();
        cout << "车牌号：" << car.CarCode << "，进入时间：" << ctime(&car.InTime);
    }
}

void ParkingLot::findCar(string licensePlate){
    stack<Car> tempStack = InStack;
    queue<Car> tempQueue = OutQueue;
    bool found = false;

    while (!tempStack.empty()) {//先在停车场里找
        Car car = tempStack.top();
        tempStack.pop();
        if (car.CarCode == licensePlate) {
            found = true;
            cout << "车辆 " << car.CarCode << " 在停车场内。" << endl;
            break;
        }
    }

    while (!tempQueue.empty() && !found) {//如果停车场里没找到，则在便道上找
        Car car = tempQueue.front();
        tempQueue.pop();
        if (car.CarCode == licensePlate) {
            found = true;
            cout << "车辆 " << car.CarCode << " 在便道上。" << endl;
            break;
        }
    }

    if (!found) {//停车场和便道都没找到车
        cout << "未找到车辆 " << licensePlate << "。" << endl;
    }
}

void ParkingLot::ChangeCharge(double newRate){
    this->charge_per_hour = newRate;
    cout << "缴费标准已修改为 " << charge_per_hour << " 元/小时。" << endl;
}

void ParkingLot::FinalShow(){
    if (money.empty()) {
        cout << "暂无收费记录。" << endl;
    }
    else {
        cout << "停车收费明细表：" << endl;
        cout << "=====================================================================================================" << endl;
        cout << left << setw(15) << "车牌号" << setw(25) << "进入时间" << setw(25) << "离开时间" << setw(15) << "停留时间" << right << setw(10) << "费用" << endl;
        cout << "=====================================================================================================" << endl;

        double totalCost = 0; // 总停车费用

        for (auto it : money) {
            char entryTimeStr[26];
            char exitTimeStr[26];

            // 使用strftime将时间格式化为固定宽度的字符串
            strftime(entryTimeStr, sizeof(entryTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&it.InTime));
            strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&it.OutTime));

            cout << left << setw(15) << it.CarCode << setw(25) << entryTimeStr << setw(25) << exitTimeStr << setw(15) << fixed << setprecision(2) << difftime(it.OutTime, it.InTime) / 3600 << right << setw(10) << fixed << setprecision(2) << it.charge << endl;
            totalCost += it.charge;
        }

        cout << "总停车费用为：" << totalCost << endl;
    }
}
