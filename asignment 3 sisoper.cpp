#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>

using namespace std;

// Generate 1000 random requests in the range [0, 4999]
vector<int> requests() {
    vector<int> req(1000);
    for (int i = 0; i < 1000;i++) {
        req[i] = rand() % 5000;
    }
    return req;
}

int fcfs(const vector<int>& req, int head) {
    int movement = 0;
    int current = head;
    for (int i=0;i<req.size();i++) {
        movement += abs(current - req[i]);
        current = req[i];
    }
    return movement;
}

int scan(vector<int> req, int head, bool mRight) {
    int movement = 0;
    vector<int> left, right;
    for (int i=0;i<req.size();i++){
        if (req[i]< head)
            left.push_back(req[i]);
        else
            right.push_back(req[i]);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int current = head;
    if (mRight) {
        for (int i=0;i<right.size();i++) {
            movement += abs(current - right[i]);
            current = right[i];
        }
        if (!left.empty()) {
            movement += abs(current - (5000 - 1));
            current = 5000 - 1;

            for (int i = left.size() - 1; i >= 0; i--) {
                movement += abs(current - left[i]);
                current = left[i];
            }
        }
    } else {
        for (int i = left.size() - 1; i >= 0; i--) {
            movement += abs(current - left[i]);
            current = left[i];
        }

        if (!right.empty()) {
            movement += abs(current - 0);
            current = 0;
            for (int i=0;i<right.size();i++) {
                movement += abs(current - right[i]);
                current = right[i];
            }
        }
    }

    return movement;
}

int cscan(vector<int> req, int head, bool mRight) {
    int movement = 0;
    vector<int> left, right;
    for (int i=0;i<req.size();i++){
        if (req[i]< head)
            left.push_back(req[i]);
        else
            right.push_back(req[i]);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int current = head;
    if (mRight) {
        for (int i=0;i<right.size();i++) {
            movement += abs(current - right[i]);
            current = right[i];
        }
        if (!left.empty()) {
            movement += abs(current - (5000 - 1));
            current = 0;
            movement += (5000 - 1);
        }
        for (int i=0;i<left.size();i++) {
            movement += abs(current - left[i]);
            current = left[i];
        }
    } 
    else {
        for (int i = left.size() - 1; i >= 0; --i) {
            movement += abs(current - left[i]);
            current = left[i];
        }
        if (!right.empty()) {
            movement += current;
            current = 5000 - 1;
            movement += (5000 - 1); 
            for (int i = right.size() - 1; i >= 0; --i) {
                movement += abs(current - right[i]);
                current = right[i];
            }
        }
    }

    return movement;
}


int main() {
    int head;
    string dir;
    bool mRight = false;
    cout << "Ingresa la posición inicial del cabezal del disco (0 - " << 4999 << "): ";
    cin >> head;
    cout << "Ingresa la direccion inicial de movimiento (derecha o izquierda)";
    cin >> dir;
    if (dir == "derecha")
        mRight = true;
    vector<int> req = requests();
    
    for (int i = 0; i < 1000;i++) {
        if (i == 999)
            cout << req[i] << endl;
        else:
            cout << req[i] << ", ";
    }

    int total_fcfs = fcfs(requests, head);
    int total_scan = scan(requests, head, move_right);
    int total_cscan = cscan(requests, head, move_right);

    cout << "\nResultados\n";
    cout << "Posición incial del cabezal: " << head << "\n";
    cout << "Movimiento hacia: " << (mRight ? "Derecha" : "Izquierda") << "\n\n";
    cout << "Movimiento de FCFS " << total_fcfs << " cilindros\n";
    cout << "Movimiento de SCAN " << total_scan << " cilindros\n";
    cout << "Movimiento de C-SCAN " << total_cscan << " cilindros\n";
    cout << "-----------------------------------------\n";

    return 0;
}
