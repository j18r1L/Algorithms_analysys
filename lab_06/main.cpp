#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace chrono;
mutex mtx;
mutex mtx2;

struct queue
{
    int data[10];
    int rear, front;
};

void init(struct queue *que);
void insert(struct queue *que, int x);
void print(struct queue *que);
int remove(struct queue *que);
int empty(struct queue *que);
void first(struct queue *que1, struct queue *que2);
void second(struct queue *que2, struct queue *que3);
void third(struct queue *que3);

int main()
{
    struct queue *que1;
    que1 = (queue*)malloc(sizeof(queue));
    init(que1);
    
    struct queue *que2;
    que2 = (queue*)malloc(sizeof(queue));
    init(que2);
    
    struct queue *que3;
    que3 = (queue*)malloc(sizeof(queue));
    init(que3);
    
    for (int i = 0; i < 5; i++)
        insert(que1, i);
    
    
    print(que1);
    
    thread th1(first, que1, que2);
    thread th2(second, que2, que3);
    thread th3(third, que3);
    
    
    th1.join();
    th2.join();
    th3.join();
    return 0;
    
}

void first(struct queue *que1, struct queue *que2)
{
    ofstream out("text.txt", std::ios::app);
    int i = 0;
    int temp;
    //auto time;
    cout << "FIRST START WORKING" << endl;
    while (empty(que1) == 1)
    {
        
        temp = remove(que1) * 2;
        auto cache_time = chrono::system_clock::now();
        cout  << "obrabotan  1 konveerom: " << temp << " id: " << i << endl;
        out << chrono::system_clock::to_time_t(cache_time) << " " << "obrabotan 1 konveerom" << temp << "id: " << i << endl;
        mtx.lock();
        insert(que2, temp);
        mtx.unlock();
        
        cout << "zanesli v 2   ochered: " << temp << " id: " << i << endl;
        cache_time = chrono::system_clock::now();
        out << chrono::system_clock::to_time_t(cache_time) << " "<< "zanesli v 2   ochered: " << temp << " id: " << i << endl;
        this_thread::sleep_for(chrono::seconds(5));
        i++;
    }
    out.close();
    cout << "FIRST STOP WORKING" << endl;
}

void second(struct queue *que2, struct queue *que3)
{
    int i = 0;
    int temp;
    ofstream out("text.txt", std::ios::app);
    this_thread::sleep_for(chrono::seconds(3));
    cout << "SECOND START WORKING" << endl;
    while (empty(que2) == 1)
    {
        mtx.lock();
        temp = remove(que2);
        mtx.unlock();
        temp = temp * temp;
        cout << "obrabotan  2 konveerom: " << temp << " id: " << i << endl;
        auto cache_time = chrono::system_clock::now();
        out << chrono::system_clock::to_time_t(cache_time) << " "<< "obrabotan  2 konveerom: " << temp << " id: " << i << endl;
        mtx2.lock();
        insert(que3, temp);
        mtx2.unlock();
        
        cout << "zanesli v  3   ochered: " << temp << " id: " << i << endl;
        cache_time = chrono::system_clock::now();
        out << chrono::system_clock::to_time_t(cache_time) << " "<< "zanesli v  3   ochered: " << temp << " id: " << i << endl;
        this_thread::sleep_for(chrono::seconds(5));
        i++;
    }
    out.close();
    cout << "SECOND STOP WORKING" << endl;
}

void third(struct queue *que3)
{
    int i = 0;
    int temp;
    this_thread::sleep_for(chrono::seconds(4));
    ofstream out("text.txt", std::ios::app);
    cout << "THIRD START WORKING" << endl;
    while (empty(que3) == 1)
    {
        mtx2.lock();
        temp = remove(que3);
        mtx2.unlock();
        temp += 10;
        cout << "obrabotan  3 konveerom: " << temp << " id: " << i << endl;
        auto cache_time = chrono::system_clock::now();
        out << chrono::system_clock::to_time_t(cache_time) << " obrabotan  3 konveerom: " << temp << " id: " << i << endl;
        cout << "zanesli    v      file: " << temp << " id: " << i << endl;
        cache_time = chrono::system_clock::now();
        out << chrono::system_clock::to_time_t(cache_time) << " zanesli    v      file: " << temp << " id: " << i << endl;
        this_thread::sleep_for(chrono::seconds(5));
        i++;
    }
    out.close();
    cout << "THIRD STOP WORKING" << endl;
}

void init(struct queue *que)
{
    que->front = 1;
    que->rear = 0;
}

void insert(struct queue *que, int x)
{
    if(que->rear < 10 - 1)
    {
        que->rear++;
        que->data[que->rear] = x;
    }
    else
        cout << "ochered pysta" << endl;
}

void print(struct queue *que)
{
    if (empty(que) == 1)
    {
        for (int h = que->front; h <= que->rear; h++)
        {
            cout << que->data[h] << " ";
        }
    }
    else
        cout << "ochered pysta";
    cout << endl;
}

int remove(struct queue *que)
{
    int temp = 0;
    if (empty(que) == 1)
    {
        temp = que->data[que->front];
        for (int h = que->front; h < que->rear; h++)
        {
            que->data[h] = que->data[h + 1];
        }
        que->rear--;
    }
    else
        cout << "ochered pysta" << endl;
    
    return temp;
}

int empty(struct queue *que)
{
    int emp = 0;
    if (que->rear >= que->front)
        emp = 1;
    else
        emp = 0;
    return emp;
}
