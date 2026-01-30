#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// ---------------- BST CORE FUNCTIONS ----------------

BSTNode* createBSTNode(Patient p) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->data = p;
    node->left = node->right = NULL;
    return node;
}

BSTNode* insertBST(BSTNode* root, Patient p) {
    if (!root) return createBSTNode(p);
    if (p.priority < root->data.priority)
        root->left = insertBST(root->left, p);
    else
        root->right = insertBST(root->right, p);
    return root;
}

BSTNode* findMax(BSTNode* root) {
    while (root && root->right) root = root->right;
    return root;
}

BSTNode* deleteBST(BSTNode* root, int id) {
    if (!root) return NULL;

    if (root->data.id == id) {
        if (!root->left && !root->right) { free(root); return NULL; }
        if (!root->left) { BSTNode* temp = root->right; free(root); return temp; }
        if (!root->right) { BSTNode* temp = root->left; free(root); return temp; }

        BSTNode* temp = findMax(root->left);
        root->data = temp->data;
        root->left = deleteBST(root->left, temp->data.id);
        return root;
    }

    root->left = deleteBST(root->left, id);
    root->right = deleteBST(root->right, id);
    return root;
}

BSTNode* searchBST(BSTNode* root, int id) {
    if (!root) return NULL;
    if (root->data.id == id) return root;
    BSTNode* leftSearch = searchBST(root->left, id);
    if (leftSearch) return leftSearch;
    return searchBST(root->right, id);
}

void inorderBST(BSTNode* root) {
    if (!root) return;
    inorderBST(root->right);
    printf("ID:%d | Name:%s | Age:%d | Disease:%s | Priority:%d | Doctor:%s\n",
           root->data.id, root->data.name, root->data.age,
           root->data.disease, root->data.priority, root->data.doctor);
    inorderBST(root->left);
}

// ---------------- CSV FUNCTIONS ----------------

void saveBSTtoCSVHelper(BSTNode* root, FILE* fp) {
    if (!root) return;
    saveBSTtoCSVHelper(root->left, fp);
    fprintf(fp, "%d,%s,%d,%s,%d,%s\n",
            root->data.id, root->data.name, root->data.age,
            root->data.disease, root->data.priority, root->data.doctor);
    saveBSTtoCSVHelper(root->right, fp);
}

void saveToCSV(BSTNode* root, Queue* normalQueue, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) { printf("Error opening file for writing.\n"); return; }

    // Save emergency BST
    saveBSTtoCSVHelper(root, fp);

    // Save normal queue
    QueueNode* temp = normalQueue->front;
    while (temp) {
        Patient p = temp->data;
        fprintf(fp, "%d,%s,%d,%s,%d,%s\n", p.id, p.name, p.age, p.disease, p.priority, p.doctor);
        temp = temp->next;
    }

    fclose(fp);
    printf("Patient data saved to %s successfully.\n", filename);
}

BSTNode* loadFromCSV(Queue* normalQueue, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("No existing data found. Starting fresh.\n"); return NULL; }

    BSTNode* root = NULL;
    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        Patient temp;
        char doctor[50];
        sscanf(line, "%d,%49[^,],%d,%49[^,],%d,%49[^\n]",
               &temp.id, temp.name, &temp.age, temp.disease, &temp.priority, doctor);
        strcpy(temp.doctor, doctor);

        if (temp.priority == 1)
            root = insertBST(root, temp);
        else
            enqueue(normalQueue, temp);
    }
    fclose(fp);
    printf("Patient data loaded from %s successfully.\n", filename);
    return root;
}

// DOCTOR & TREATMENT 

void assignDoctor(BSTNode* root, Queue* normalQueue) {
    int id;
    char doctorName[50];
    printf("Enter patient ID to assign doctor: ");
    scanf("%d", &id);

    BSTNode* patient = searchBST(root, id);
    if (!patient) {
        // Check normal queue
        QueueNode* temp = normalQueue->front;
        while (temp) {
            if (temp->data.id == id) {
                printf("Enter doctor name: ");
                scanf(" %[^\n]", doctorName);
                strcpy(temp->data.doctor, doctorName);
                printf("Doctor %s assigned to normal patient ID %d.\n", doctorName, id);
                return;
            }
            temp = temp->next;
        }
        printf("Patient not found!\n");
        return;
    }

    printf("Enter doctor name: ");
    scanf(" %[^\n]", doctorName);
    strcpy(patient->data.doctor, doctorName);
    printf("Doctor %s assigned to emergency patient ID %d.\n", doctorName, id);
}

BSTNode* treatPatient(BSTNode** root, Queue* normalQueue) {
    int id;
    printf("Enter patient ID to treat: ");
    scanf("%d", &id);

    BSTNode* patient = searchBST(*root, id);
    if (patient) {
        printf("Treating emergency patient: ID=%d, Name=%s\n", patient->data.id, patient->data.name);
        *root = deleteBST(*root, id);
        return *root;
    }

    // Check normal queue
    QueueNode* temp = normalQueue->front;
    QueueNode* prev = NULL;
    while (temp) {
        if (temp->data.id == id) {
            printf("Treating normal patient: ID=%d, Name=%s\n", temp->data.id, temp->data.name);
            if (prev) prev->next = temp->next;
            else normalQueue->front = temp->next;
            if (temp == normalQueue->rear) normalQueue->rear = prev;
            free(temp);
            return *root;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Patient not found!\n");
    return *root;
}