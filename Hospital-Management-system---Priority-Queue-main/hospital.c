/*
PATIENT APPOINTMENT SCHEDULER USING PRIORITY QUEUE
---------------------------------------------------
MINI PROJECT - DATA STRUCTURES (C LANGUAGE)
Based on Sustainable Development Goal 3:
"Good Health and Well-being"
---------------------------------------------------
This project simulates an efficient patient scheduling
system for hospitals using a priority queue (min-heap).
It prioritizes patients based on medical urgency and
helps optimize healthcare response time.


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 25

// Date structure
typedef struct {
char month[3];
char day[3];
char year[5];
} Date;

// Patient structure
typedef struct {
Date birth;
char name[MAX_STRING];
int ssn;
char gender;
int priority; // 1 = critical, 2 = high, 3 = medium, 4 = low
char task[MAX_STRING];
} Patient;

// Priority Queue structure
typedef struct {
Patient* heap;
int size;
int capacity;
} PriorityQ;

// Function declarations
PriorityQ createPQ(int capacity);
int isEmpty(PriorityQ* pq);
void newPatient(PriorityQ* pq, Patient p);
Patient processPatient(PriorityQ* pq);
void updatePatient(PriorityQ* pq, int index, int newPriority);
void swap(Patient* a, Patient* b);
void upHeap(PriorityQ* pq, int index);
void downHeap(PriorityQ* pq, int index);

// Main function
int main(void) {
printf("Hospital Management System (Automatic Demo Mode)\n");
printf("------------------------------------------------\n");

// Create priority queue
PriorityQ pq = createPQ(5);

// Simulated dataset (auto patients instead of input)
Patient samplePatients[] = {
    {{"05", "12", "1985"}, "John", 12345, 'M', 1, "Emergency Surgery"},
    {{"10", "08", "1992"}, "Sarah", 54321, 'F', 3, "Check-up"},
    {{"07", "03", "2000"}, "David", 67890, 'M', 2, "X-ray"},
    {{"09", "15", "1978"}, "Emily", 11122, 'F', 4, "Consultation"},
    {{"11", "21", "1989"}, "Michael", 33344, 'M', 1, "ICU Admission"}
};

int totalPatients = 5;

// Insert patients automatically
for (int i = 0; i < totalPatients; i++) {
    newPatient(&pq, samplePatients[i]);
}

// Process patients by priority
printf("\nProcessing patients in order of priority:\n");
while (!isEmpty(&pq)) {
    Patient p = processPatient(&pq);
    printf("Processing patient: %-8s | Priority: %d | Task: %s\n", 
           p.name, p.priority, p.task);
}

free(pq.heap);
return 0;


}

// Create a priority queue
PriorityQ createPQ(int capacity) {
PriorityQ pq;
pq.size = 0;
pq.capacity = capacity;
pq.heap = (Patient*)malloc((capacity + 1) * sizeof(Patient));
return pq;
}

// Check if the priority queue is empty
int isEmpty(PriorityQ* pq) {
return pq->size == 0;
}

// Insert a new patient into the priority queue
void newPatient(PriorityQ* pq, Patient p) {
if (pq->size >= pq->capacity) {
pq->capacity = 2;
pq->heap = (Patient*)realloc(pq->heap, (pq->capacity + 1) * sizeof(Patient));
if (pq->heap == NULL) {
printf("Memory allocation failed\n");
exit(1);
}
}
pq->heap[++pq->size] = p;
upHeap(pq, pq->size);
}

// Remove and return the patient with highest priority
Patient processPatient(PriorityQ* pq) {
if (isEmpty(pq)) {
printf("No patients left to process.\n");
exit(1);
}
Patient top = pq->heap[1];
pq->heap[1] = pq->heap[pq->size--];
downHeap(pq, 1);
return top;
}

// Update a patient's priority
void updatePatient(PriorityQ* pq, int index, int newPriority) {
if (index < 1 || index > pq->size) {
printf("Invalid index\n");
return;
}
int oldPriority = pq->heap[index].priority;
pq->heap[index].priority = newPriority;
if (newPriority < oldPriority)
upHeap(pq, index);
else
downHeap(pq, index);
}

// Swap two patients
void swap(Patient* a, Patient* b) {
Patient temp = *a;
*a = *b;
*b = temp;
}

// Maintain min-heap property (up)
void upHeap(PriorityQ* pq, int index) {
while (index > 1) {
int parent = index / 2;
if (pq->heap[index].priority >= pq->heap[parent].priority) break;
swap(&pq->heap[index], &pq->heap[parent]);
index = parent;
}
}

// Maintain min-heap property (down)
void downHeap(PriorityQ* pq, int index) {
while (2 * index <= pq->size) {
int left = 2 * index;
int right = left + 1;
int smallest = left;

    if (right <= pq->size && pq->heap[right].priority < pq->heap[left].priority)
        smallest = right;

    if (pq->heap[index].priority <= pq->heap[smallest].priority) break;
    swap(&pq->heap[index], &pq->heap[smallest]);
    index = smallest;
}


}
