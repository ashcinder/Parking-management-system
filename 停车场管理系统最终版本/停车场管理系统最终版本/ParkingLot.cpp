#include "ParkingLot.h"

ParkingLot::ParkingLot(int Capacity, double charge_per_hour):capacity(Capacity),charge_per_hour(charge_per_hour){

}

void ParkingLot::CarIn(string CarCode) {

    Car car(CarCode);
    car.InTime = time(0);

    if (InStack.size() < capacity) {//���ͣ����ͣ����
        InStack.push(car);
        cout << "���� " << car.CarCode << " ����ͣ������" << endl;
    }
    else {//ͣ����ͣ���£�ͣ�ڱ����
        OutQueue.push(car);
        cout << "���� " << car.CarCode << " �ڱ���ϵȺ�" << endl;
    }
}

void ParkingLot::CarOut(string CarCode, time_t exitTime){
    Car carToExit;
    bool found = false;
    stack<Car> tempStack;
    
    while (!InStack.empty()) {// ��ͣ�������ҳ���
        Car car = InStack.top();
        InStack.pop();
        if (car.CarCode == CarCode) {
            found = true;
            carToExit = car;
            carToExit.OutTime = exitTime;  // �����뿪ʱ��
        }
        else {
            tempStack.push(car); // ����ƥ��ĳ�������ջ
        }
    }

    while (!tempStack.empty()) {// ���·Ż�ͣ����
        InStack.push(tempStack.top());
        tempStack.pop();
    }

    if (found) {
        // ������ò���¼
        double duration = difftime(carToExit.OutTime, carToExit.InTime);
        carToExit.charge = (duration / 3600) * charge_per_hour;
        money.push_back(carToExit);
        cout << "���� " << carToExit.CarCode << " �뿪ͣ������" << endl;
        cout << "ͣ��ʱ�䣺" << fixed << setprecision(2) << duration / 3600 << "Сʱ�����ã�" << fixed << setprecision(2) << carToExit.charge << "Ԫ" << endl;

        if (!OutQueue.empty()) {// ���������еȴ��ĳ������������ͣ����
            Car car = OutQueue.front();
            OutQueue.pop();
            CarIn(car.CarCode);//��������µõ�һ������ʱ��
        }
    }
    else {
        cout << "δ�ҵ����� " << CarCode << "��" << endl;
    }

}

void ParkingLot::ShowStack() {// ��ʾͣ������Ϣ
    cout << "ͣ������Ϣ��" << endl;
    stack<Car> tempStack = InStack;//��ʱ��stack�����˾Ͷ�

    while (!tempStack.empty()) {
        Car car = tempStack.top();
        tempStack.pop();
        cout << "���ƺţ�" << car.CarCode << "������ʱ�䣺" << ctime(&car.InTime);
    }
}

void ParkingLot::ShowQueue() {// ��ʾ����ϵ����
    cout << "����ϵĳ�����" << endl;
    queue<Car> tempQueue = OutQueue;//��ʱ��Queue�����˾Ͷ�

    while (!tempQueue.empty()) {
        Car car = tempQueue.front();
        tempQueue.pop();
        cout << "���ƺţ�" << car.CarCode << "������ʱ�䣺" << ctime(&car.InTime);
    }
}

void ParkingLot::findCar(string licensePlate){
    stack<Car> tempStack = InStack;
    queue<Car> tempQueue = OutQueue;
    bool found = false;

    while (!tempStack.empty()) {//����ͣ��������
        Car car = tempStack.top();
        tempStack.pop();
        if (car.CarCode == licensePlate) {
            found = true;
            cout << "���� " << car.CarCode << " ��ͣ�����ڡ�" << endl;
            break;
        }
    }

    while (!tempQueue.empty() && !found) {//���ͣ������û�ҵ������ڱ������
        Car car = tempQueue.front();
        tempQueue.pop();
        if (car.CarCode == licensePlate) {
            found = true;
            cout << "���� " << car.CarCode << " �ڱ���ϡ�" << endl;
            break;
        }
    }

    if (!found) {//ͣ�����ͱ����û�ҵ���
        cout << "δ�ҵ����� " << licensePlate << "��" << endl;
    }
}

void ParkingLot::ChangeCharge(double newRate){
    this->charge_per_hour = newRate;
    cout << "�ɷѱ�׼���޸�Ϊ " << charge_per_hour << " Ԫ/Сʱ��" << endl;
}

void ParkingLot::FinalShow(){
    if (money.empty()) {
        cout << "�����շѼ�¼��" << endl;
    }
    else {
        cout << "ͣ���շ���ϸ��" << endl;
        cout << "=====================================================================================================" << endl;
        cout << left << setw(15) << "���ƺ�" << setw(25) << "����ʱ��" << setw(25) << "�뿪ʱ��" << setw(15) << "ͣ��ʱ��" << right << setw(10) << "����" << endl;
        cout << "=====================================================================================================" << endl;

        double totalCost = 0; // ��ͣ������

        for (auto it : money) {
            char entryTimeStr[26];
            char exitTimeStr[26];

            // ʹ��strftime��ʱ���ʽ��Ϊ�̶���ȵ��ַ���
            strftime(entryTimeStr, sizeof(entryTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&it.InTime));
            strftime(exitTimeStr, sizeof(exitTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&it.OutTime));

            cout << left << setw(15) << it.CarCode << setw(25) << entryTimeStr << setw(25) << exitTimeStr << setw(15) << fixed << setprecision(2) << difftime(it.OutTime, it.InTime) / 3600 << right << setw(10) << fixed << setprecision(2) << it.charge << endl;
            totalCost += it.charge;
        }

        cout << "��ͣ������Ϊ��" << totalCost << endl;
    }
}
