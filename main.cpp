#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
struct SELEM {
    string time;
    string plate;
    string data;
    SELEM* next;
};

typedef SELEM ELEM, * PELEM, * LLIST;

void Print(const LLIST& l) {
    for (LLIST temp = l; temp; temp = temp->next) {
        cout << temp->plate << endl;
    }
}
 
LLIST llInit() {
    return NULL;
}



LLIST llInsertTail(LLIST l, const string& data, const string& time = "", const string& plate = "") {
    PELEM e = new ELEM;
    e->data = data;
    e->time = time;
    e->plate = plate;
    e->next = NULL;

    if (!l) return e;

    PELEM p = l;
    while (p->next) {
        p = p->next;
    }
    p->next = e;
    return l;
}

int Find(LLIST l, const string& plate) {
    int i = 1;
    for (; l; l = l->next, ++i) {
        if (l->plate == plate) {
            return i;
        }
    }
    return -1;
}

LLIST llDelete(LLIST l, PELEM a) {
    if (!a) return l;

    if (l == a) {
        LLIST temp = l->next;
        delete l;
        return temp;
    }

    PELEM current = l;
    while (current->next && current->next != a) {
        current = current->next;
    }

    if (current->next == a) {
        current->next = a->next;
        delete a;
    }

    return l;
}

PELEM llSeek(LLIST l, int i) {
    for (; i > 0 && l; --i) {
        l = l->next;
    }
    return l;
}

int out(LLIST& l, const string& time, const string& plate) {
    int pos = Find(l, plate);
    if (pos == -1) {
        return -1;
    }
    PELEM n = llSeek(l, pos - 1);
    l = llDelete(l, n);
    return 0;
}

LLIST llDeleteAll(LLIST l) {
    PELEM p;
    while (l) {
        p = l->next;
        delete l;
        l = p;
    }
    return NULL;
}

int In(LLIST& l, const string& time, const string& plate) {
    int n = Find(l, plate);
    if (n != -1) {
        return 0;
    }
    l = llInsertTail(l,"", time, plate);
    return 1;
}

int Check(PELEM l) {
    int dem = 0;
    for (int i = 0; i < 4 && i < l->plate.size(); i++) {
        if (l->plate[i] == 'x') {
            dem++;
        }
    }
    return (dem == 4) ? 1 : 0;
}

int cnt_moto(LLIST l) {
    int count = 0;
    while (l) {
        if (Check(l) == 0) {
            count++;
        }
        l = l->next;
    }
    return count;
}
int Bill(LLIST l, const string& time, const string& plate) {
    int S = 0;
    if (Find(l, plate) == -1) {
        return -1;
    }
    else {
        if (Check(l)) {
            if (l->time.compare("06:00:00") == 1 && l->time.compare("18:00:00") == -1) {
                if (time.compare("06:00:00") == 1 && time.compare("18:00:00") == -1) {
                    S = 1;
                }
                else if (time.compare("18:00:00") == 1) {
                    S = 2;
                }
            }
            else if ((l->time.compare("06:00:00") == -1 || l->time.compare("18:00:00") == 1)) {
                if (time.compare("06:00:00") == 1 && time.compare("18:00:00") == -1) {
                    S = 3;
                }
                else if (time.compare("18:00:00") == 1) {
                    S = 5;
                }

            }
        }
        else {
            if (l->time.compare("06:00:00") == 1 && l->time.compare("18:00:00") == -1) {
                if (time.compare("06:00:00") == 1 && time.compare("18:00:00") == -1) {
                    S = 3;
                }
                else if (time.compare("18:00:00") == 1) {
                    S = 5;
                }
            }
            else if ((l->time.compare("06:00:00") == -1 || l->time.compare("18:00:00") == 1)) {
                if (time.compare("06:00:00") == 1 && time.compare("18:00:00") == -1) {
                    S = 8;
                }
                else if (time.compare("18:00:00") == 1) {
                    S = 13;
                }
            }
        }
    }
    return S;
}


int main() {
    LLIST L1 = llInit();
    LLIST L2 = llInit();

    while (true) {
        string a, b;
        cin >> a;
        if (a == "*") {
            break;
        }
        cin >> b;
        L1 = llInsertTail(L1,"", a, b);
    }

    while (true) {
        string a;
        cin >> a;
        if (a == "***") {
            break;
        }

        if (a == "find") {
            string plate;
            cin >> plate;
            L2 = llInsertTail(L2, a, "", plate);
        }
        else if (a == "in" || a == "out" || a == "bill") {
            string c, b;
            cin >> c >> b;
            L2 = llInsertTail(L2, a, c, b);
        }
        else {
            L2 = llInsertTail(L2, a);
        }
    }

    LLIST command = L2;
    while (command) {
        if (command->data == "list") {
            Print(L1);
        }
        else if (command->data == "find") {
            cout << Find(L1, command->plate) << endl;
        }
        else if (command->data == "in") {
            cout << In(L1, command->time, command->plate) << endl;
        }
        else if (command->data == "out") {
            cout << out(L1, command->time, command->plate) << endl;
        }
        else if (command->data == "cnt-moto") {
            cout << cnt_moto(L1) << endl;
        }
        else if (command->data == "bill") {
            cout << Bill(L1, command->time, command->plate) << endl;
        }
        command = command->next;
    }

    L1 = llDeleteAll(L1);
    L2 = llDeleteAll(L2);

    getch();
    return 0;
}
