#include <stdio.h>
#include <stdlib.h>
#include "hospital.h"
#include "bst.h" // for assignDoctor and treatPatient functions

int main() {
    int choice;

    // Initialize queue
    initQueue(&normalQueue);

    // Load data from CSV (both BST & Queue)
    emergencyRoot = loadFromCSV(&normalQueue, "patients.csv");

    while (1) {
        printf("\n--- Hospital Management ---\n");
        printf("1. Add Patient\n2. Discharge Patient\n3. Update Patient Status\n4. Generate Report\n");
        printf("5. Assign Doctor\n6. Treat Patient\n7. Exit\n");
        printf("Enter choice: "); scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: dischargePatient(); break;
            case 3: updatePatientStatus(); break;
            case 4: generateReport(); break;
            case 5: assignDoctor(emergencyRoot, &normalQueue); break;
            case 6: emergencyRoot = treatPatient(&emergencyRoot, &normalQueue); break;
            case 7:
                saveToCSV(emergencyRoot, &normalQueue, "patients.csv");
                printf("Exiting... Data saved.\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}