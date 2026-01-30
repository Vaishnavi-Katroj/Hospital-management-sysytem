#ifndef PATIENT_H
#define PATIENT_H

typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int priority;
    char doctor[50];
} Patient;

#endif