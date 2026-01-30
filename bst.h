#ifndef BST_H
#define BST_H

#include "patient.h"
#include "queue.h"  // needed for Queue*

typedef struct BSTNode {
    Patient data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// ---------------- BST CORE FUNCTIONS ----------------
BSTNode* insertBST(BSTNode* root, Patient p);
BSTNode* deleteBST(BSTNode* root, int id);
BSTNode* findMax(BSTNode* root);
BSTNode* searchBST(BSTNode* root, int id);
void inorderBST(BSTNode* root);

// ---------------- CSV FUNCTIONS ----------------
void saveToCSV(BSTNode* root, Queue* normalQueue, const char* filename);
BSTNode* loadFromCSV(Queue* normalQueue, const char* filename);

// ---------------- DOCTOR & TREATMENT ----------------
void assignDoctor(BSTNode* root, Queue* normalQueue);
BSTNode* treatPatient(BSTNode** root, Queue* normalQueue);

#endif