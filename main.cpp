#include "MyStruct.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
using namespace std;

void processFile(MyStruct& data, const string& filename) {
    ifstream fin(filename);
    string cmd;
    while (fin >> cmd) {
        if (cmd == "read") {
            int idx; fin >> idx;
            data.read(idx);
        } else if (cmd == "write") {
            int idx, val; fin >> idx >> val;
            data.write(idx, val);
        } else if (cmd == "string") {
            string s = data;
        }
    }
}

int main() {
    MyStruct data;

    vector<string> files1 = {"fileA1.txt", "fileA2.txt", "fileA3.txt"};
    vector<string> files2 = {"fileB1.txt", "fileB2.txt", "fileB3.txt"};
    vector<string> files3 = {"fileC1.txt", "fileC2.txt", "fileC3.txt"};

    auto t1 = chrono::high_resolution_clock::now();
    processFile(data, files1[0]);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "1 thread: "
         << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << " µs\n";

    auto t3 = chrono::high_resolution_clock::now();
    thread th1(processFile, ref(data), files2[0]);
    thread th2(processFile, ref(data), files2[1]);
    th1.join(); th2.join();
    auto t4 = chrono::high_resolution_clock::now();
    cout << "2 threads: "
         << chrono::duration_cast<chrono::microseconds>(t4 - t3).count()
         << " µs\n";

    auto t5 = chrono::high_resolution_clock::now();
    thread th3(processFile, ref(data), files3[0]);
    thread th4(processFile, ref(data), files3[1]);
    thread th5(processFile, ref(data), files3[2]);
    th3.join(); th4.join(); th5.join();
    auto t6 = chrono::high_resolution_clock::now();
    cout << "3 threads: "
         << chrono::duration_cast<chrono::microseconds>(t6 - t5).count()
         << " µs\n";

    cout << "Final values: " << string(data) << endl;
}
