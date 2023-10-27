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
	time_t OutTime;//����ʱ��
	string CarCode;//���ƺ�
	double charge;//�շ�

    Car(string CarCode) :CarCode(CarCode) {

    }

    Car() {

    }
};

class ParkingLot {
private:
    int capacity;           // ͣ��������
    stack<Car> InStack;     // ģ��ͣ������ʹ��ջ
    queue<Car> OutQueue;    // ģ������ʹ�ö���
    vector<Car> money;      // ���ü�¼
    double charge_per_hour; // ÿСʱ����
public:

    ParkingLot(int n, double rate);//���캯����ģ��ÿСʱ�շ����

    void CarIn(string CarCode);//��������ͣ����

    void CarOut(string CarCode, time_t exitTime);//�����뿪ͣ����

    void ShowStack();//չʾͣ����������

    void ShowQueue();//չʾ���������

    void findCar(string licensePlate);//�ҳ�

    void ChangeCharge(double newRate);//�޸��շѱ�׼

    void FinalShow();//���յ�չʾ
};