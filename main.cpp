#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct P {
    int id;
    char name[50];
    int age;
    int emg;
    struct P *nxt;
} P;

P *head = NULL;
int q[100], f = -1, r = -1;
int st[100], t = -1;
P *table[10];

int hash(int id) {
    return id % 10;
}

void enq(int id) {
    if (r == 99) return;
    if (f == -1) f = 0;
    q[++r] = id;
}

int deq() {
    if (f == -1 || f > r) return -1;
    return q[f++];
}

void push(int id) {
    if (t == 99) return;
    st[++t] = id;
}

int pop() {
    if (t == -1) return -1;
    return st[t--];
}

P* newP(int id, char name[], int age, int emg) {
    P *p = (P*)malloc(sizeof(P));
    p->id = id;
    strcpy(p->name, name);
    p->age = age;
    p->emg = emg;
    p->nxt = NULL;
    return p;
}

void addP(int id, char name[], int age, int emg) {
    P *p = newP(id, name, age, emg);

    if (head == NULL) head = p;
    else {
        P *tmp = head;
        while (tmp->nxt) tmp = tmp->nxt;
        tmp->nxt = p;
    }

    if (emg == 1) push(id);
    else enq(id);

    int i = hash(id);
    p->nxt = table[i];
    table[i] = p;
}

P* findP(int id) {
    int i = hash(id);
    P *c = table[i];
    while (c) {
        if (c->id == id) return c;
        c = c->nxt;
    }
    return NULL;
}

void outP(int id) {
    P *prev = NULL, *c = head;
    while (c) {
        if (c->id == id) {
            if (prev) prev->nxt = c->nxt;
            else head = c->nxt;
            free(c);
            printf("Patient with ID %d has been successfully discharged from the hospital.\n", id);
            return;
        }
        prev = c;
        c = c->nxt;
    }
    printf("No patient found with the entered ID %d.\n", id);
}

void treat() {
    int id = -1;
    if (t != -1) id = pop();
    else if (f != -1 && f <= r) id = deq();

    if (id == -1) {
        printf("There are currently no patients waiting for treatment.\n");
        return;
    }
    P *p = findP(id);
    if (p) printf("Now treating patient: %s (ID: %d, Age: %d, Emergency: %d)\n", p->name, p->id, p->age, p->emg);
}

void show() {
    P *c = head;
    printf("\nList of all current patients in the hospital:\n");
    printf("ID\tName\tAge\tEmergency(1=Yes/0=No)\n");
    while (c) {
        printf("%d\t%s\t%d\t%d\n", c->id, c->name, c->age, c->emg);
        c = c->nxt;
    }
}

int main() {
    int ch, id, age, emg;
    char name[50];

    while (1) {
        printf("\n=== Hospital Patient Management System ===\n");
        printf("Please choose an option from the menu below:\n");
        printf("1. Add a new patient\n");
        printf("2. Treat the next patient in line\n");
        printf("3. Search for a patient by ID\n");
        printf("4. Discharge a patient by ID\n");
        printf("5. Display all patients\n");
        printf("6. Exit the program\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Enter patient details in the following format:\n");
            printf("ID (number) Name (single word) Age (number) Emergency status (1 for yes, 0 for no):\n");
            scanf("%d %s %d %d", &id, name, &age, &emg);
            addP(id, name, age, emg);
            printf("Patient %s with ID %d has been added successfully.\n", name, id);
        } else if (ch == 2) {
            treat();
        } else if (ch == 3) {
            printf("Enter the patient ID you want to search for: ");
            scanf("%d", &id);
            P *p = findP(id);
            if (p) printf("Patient found: %s (ID: %d, Age: %d, Emergency: %d)\n", p->name, p->id, p->age, p->emg);
            else printf("No patient found with ID %d.\n", id);
        } else if (ch == 4) {
            printf("Enter the patient ID you want to discharge: ");
            scanf("%d", &id);
            outP(id);
        } else if (ch == 5) {
            show();
        } else if (ch == 6) {
            printf("Exiting the system. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}
