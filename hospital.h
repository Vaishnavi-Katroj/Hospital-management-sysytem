#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "queue.h"
#include "bst.h"

// Global variables
extern BSTNode* emergencyRoot;
extern Queue normalQueue;

// Function declarations
void addPatient();
void dischargePatient();
void updatePatientStatus();
void generateReport();

#endif