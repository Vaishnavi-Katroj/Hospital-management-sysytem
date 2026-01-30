#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

// Global variables
BSTNode* emergencyRoot = NULL;
Queue normalQueue;

// ---------------- Core Functions ----------------

void addPatient() {
    Patient p;
    printf("Enter ID: "); scanf("%d", &p.id);
    printf("Enter Name: "); scanf(" %[^\n]", p.name);
    printf("Enter Age: "); scanf("%d", &p.age);
    printf("Enter Disease: "); scanf(" %[^\n]", p.disease);
    printf("Enter Priority (1-5): "); scanf("%d", &p.priority);
    strcpy(p.doctor, ""); // Initially no doctor

    if (p.priority == 1) {
        emergencyRoot = insertBST(emergencyRoot, p);
        printf("Patient added to Emergency.\n");
    } else {
        enqueue(&normalQueue, p);
        printf("Patient added to Normal Queue.\n");
    }
}

void dischargePatient() {
    int id; 
    printf("Enter Patient ID to discharge: "); scanf("%d", &id);

    BSTNode* pNode = searchBST(emergencyRoot, id);
    if (pNode) {
        printf("Discharging Emergency Patient: %s\n", pNode->data.name);
        emergencyRoot = deleteBST(emergencyRoot, id);
        return;
    }

    QueueNode* temp = normalQueue.front;
    QueueNode* prev = NULL;
    while (temp) {
        if (temp->data.id == id) break;
        prev = temp;
        temp = temp->next;
    }

    if (temp) {
        if (prev) prev->next = temp->next;
        else normalQueue.front = temp->next;
        if (temp == normalQueue.rear) normalQueue.rear = prev;
        printf("Discharging Normal Patient: %s\n", temp->data.name);
        free(temp);
        return;
    }

    printf("Patient not found.\n");
}

void updatePatientStatus() {
    int id, newPriority;
    printf("Enter Patient ID: "); scanf("%d", &id);
    printf("Enter new Priority (1-5): "); scanf("%d", &newPriority);

    BSTNode* pNode = searchBST(emergencyRoot, id);
    if (pNode) {
        pNode->data.priority = newPriority;
        if (newPriority != 1) {
            Patient p = pNode->data;
            emergencyRoot = deleteBST(emergencyRoot, id);
            enqueue(&normalQueue, p);
            printf("Moved Emergency Patient to Normal Queue.\n");
        } else printf("Emergency priority updated.\n");
        return;
    }

    QueueNode* temp = normalQueue.front;
    QueueNode* prev = NULL;
    while (temp) {
        if (temp->data.id == id) break;
        prev = temp;
        temp = temp->next;
    }

    if (temp) {
        temp->data.priority = newPriority;
        if (newPriority == 1) {
            Patient p = temp->data;
            if (prev) prev->next = temp->next;
            else normalQueue.front = temp->next;
            if (temp == normalQueue.rear) normalQueue.rear = prev;
            free(temp);
            emergencyRoot = insertBST(emergencyRoot, p);
            printf("Moved Normal Patient to Emergency.\n");
        } else printf("Normal priority updated.\n");
        return;
    }

    printf("Patient not found.\n");
}

void generateReport() {
    printf("\n--- Emergency Patients ---\n");
    if (emergencyRoot) inorderBST(emergencyRoot);
    else printf("No emergency patients.\n");

    printf("\n--- Normal Patients ---\n");
    if (isQueueEmpty(&normalQueue)) printf("No normal patients.\n");
    else {
        QueueNode* temp = normalQueue.front;
        while (temp) {
            Patient p = temp->data;
            printf("ID:%d | Name:%s | Age:%d | Disease:%s | Priority:%d | Doctor:%s\n",
                   p.id, p.name, p.age, p.disease, p.priority, p.doctor);
            temp = temp->next;
        }
    }
}