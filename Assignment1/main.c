#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

void KFactorAlgorithm();

void KFactorAlgorithmPaper();

void KFactorAlgorithmArrivalZero();

void KFactorAlgorithmProcessSize();

void KFactorAlgorithmProcessSizeTest();

int inputChecker(char input[20], char mode);

int main() {
    while(1){
        char userInput[20];
        int flag = 0, flag2 = 0;
        int select, choice;

        printf("=======================================");
        printf("\nMuhammad Nurhakim Bin Mohd Razalee");
        printf("\n2001019");
        printf("\nPaper Assigned: 2");
        printf("\n=======================================");
        printf("\nAlgorithms: ");
        printf("\n1) K-Factor Algorithm (Manual Burst Times & Arrival Times)");
        printf("\n2) K-Factor Algorithm (Paper given Burst Times (RNG) & Arrival Times, T=0)");
        printf("\n3) K-Factor Algorithm (Manual Burst Times with 0 Arrival Times)");
        printf("\n4) K-Factor Algorithm (Manual Process Size with Random Burst Times & Arrival Times = 0)");
        printf("\n\nSelect Algorithm: ");
        fgets(userInput, 16, stdin);
        flag = inputChecker(userInput, 3);
        while (flag == 1) {
            flag = 0;
            printf("\n=======================================");
            printf("\n\t  INVALID INPUT!");
            printf("\n=======================================");
            printf("\nPlease only Input 1,2,3 or 4 without any spaces.\n");
            printf("\nAlgorithms: ");
            printf("\n1) K-Factor Algorithm (Manual Burst Times & Arrival Times)");
            printf("\n2) K-Factor Algorithm (Paper given Burst Times (RNG) & Arrival Times = 0)");
            printf("\n3) K-Factor Algorithm (Manual Burst Times with 0 Arrival Times)");
            printf("\n4) K-Factor Algorithm (Manual Process Size with Random Burst Times & Arrival Times = 0)");
            printf("\n\nSelect Algorithm: ");
            fgets(userInput, 16, stdin);
            flag = inputChecker(userInput, 3);
        }
        select = atoi(userInput);
        if (select == 1) {
            KFactorAlgorithm();
        } else if (select == 2) {
            KFactorAlgorithmPaper();
        } else if (select == 3) {
            KFactorAlgorithmArrivalZero();
        } else if (select == 4) {
            KFactorAlgorithmProcessSize();              //Process number capped at 10000
//        KFactorAlgorithmProcessSizeTest();        //Attempted to use malloc but results were inaccurate after 12000 processes due to lack of hardware power.
        }
        printf("\nDo you wish to try another algorithm?");
        printf("\n1) Yes\t 2) No");
        printf("\nChoice:");
        fgets(userInput, 16, stdin);
        flag2 = inputChecker(userInput, 5);
        while (flag2 == 1){
            flag2 = 0;
            printf("\n=======================================");
            printf("\n\t  INVALID INPUT!");
            printf("\n=======================================");
            printf("\nPlease only Input 1 or 2 without any spaces.\n");
            printf("\nDo you wish to try another algorithm?");
            printf("\n1) Yes\t 2) No");
            printf("\nChoice:");
            fgets(userInput, 16, stdin);
            flag2 = inputChecker(userInput, 5);
        }

        choice = atoi(userInput);
        if(choice == 1){
            continue;
        } else if(choice == 2){
            printf("\nSystem will now exit.");
            exit(0);
        }
    }

}

void KFactorAlgorithm() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0;
    int P[10001], A[10001], i, j, n, total = 0, pos, temp;


    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\n\t\tK-FACTOR ALGORITHM - Manual Inputs");
    printf("\n================================================================\n");
    printf("\nEnter number of processes (Max 10000 Processes):");
    fgets(input, 16, stdin);
    passed = inputChecker(input, 1);        //flag to activate error handling



    while (passed == 1) {                          //If flag is activated
        passed = 0;
        printf("\nInvalid input! Please enter an Integer without any spaces.\n");
        printf("\nEnter number of processes (Max 10000 Processes):");
        fgets(input, 16, stdin);
        passed = inputChecker(input, 1);
    }

    n = atoi(input);                                //convert string to integer


    printf("\n%d Process(es)", n);


    for (i = 0; i < n; i++) {
        int burstPassed = 0, arrivalPassed = 0;
        printf("\nProcess No (%d):", i + 1);
        printf("\nEnter Burst Time:");
        fgets(input, 16, stdin);
        burstPassed = inputChecker(input, 4);           //flag for error handling (for burst times)
        while (burstPassed == 1) {
            burstPassed = 0;
            printf("\nInvalid input! Please enter an Integer without any spaces. (Burst Times cannot be 0)\n");
            printf("\nProcess No (%d):", i + 1);
            printf("\nEnter Burst Time:");
            fgets(input, 16, stdin);
            burstPassed = inputChecker(input, 4);
        }
        P[i] = atoi(input);                                     //convert string to integer

        printf("Enter arrival Time:");


        fgets(input, 16, stdin);
        arrivalPassed = inputChecker(input, 2);         //flag for error handling (for arrival times)
        while (arrivalPassed == 1) {
            arrivalPassed = 0;
            printf("\n\nInvalid input! Please enter an Integer without any spaces.\n");
            printf("\nProcess No (%d):", i + 1);
            printf("\nBurst Time: %d", P[i]);
            printf("\nEnter Arrival Time:");
            fgets(input, 16, stdin);
            arrivalPassed = inputChecker(input, 2);
        }
        A[i] = atoi(input);                                     //convert string to integer

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
    printf("\n\nSorted Based on SJF Arrival Time (Ready Queue): \n");
    //sorting of burst times for ready queue
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] <
                A[pos]) {                     //compares all of the contents in the array if it has the smallest arrival time. Sorts accordingly (aka places into ready queue).
                pos = j;
            } else if (A[j] == A[pos]) {              //if arrival time is the same, compares burst time.
                if (P[j] < P[pos]) {
                    pos = j;
                }
            }
        }

        temp = P[i];                                //Use a holder to keep the value
        P[i] = P[pos];                              //Assign new burst time to the current position
        P[pos] = temp;                              //The taken burst time is replaced


        temp = A[i];                                //Use a holder to keep the value of Arrival Time
        A[i] = A[pos];                              //Assign new arrival time to the current position
        A[pos] = temp;

        temp = ProcessNo[i];                        //Same concept with the above but now for process number labelling
        ProcessNo[i] = ProcessNo[pos];
        ProcessNo2[i] = ProcessNo2[pos];
        ProcessNo[pos] = temp;
        ProcessNo2[pos] = temp;
        printf("Process %d: %d\n", ProcessNo[i], P[i]);
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy Array of process to another Array
    }


    printf("\nSorted Based on K = 2: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                temp = P[i];                        //Same concept as above using holder to store values temporarily
                P[i] = P[i + 1];
                P[i + 1] = temp;

                temp = ProcessNo[i];                //Same concept
                ProcessNo[i] = ProcessNo[i + 1];
                ProcessNo[i + 1] = temp;

                timePassed += P[i];                 //add the time passed
            } else {
                timePassed += P[i];
            }
        } else {
            timePassed += P[i];
        }


        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
    }

    wt[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt[i] += P[j];                                //Assigns waiting time based on the Process burst time

        total += wt[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                              //finding turnaround time
        total += tat[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo[i], P[i], wt[i], tat[i]);
    }

    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;

    printf("\n\nSorted Based on K alternative: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                temp = P2[i];                        //Same concept as above using holder to store values temporarily
                P2[i] = P2[i + 1];
                P2[i + 1] = temp;

                temp = ProcessNo2[i];                //Same concept
                ProcessNo2[i] = ProcessNo2[i + 1];
                ProcessNo2[i + 1] = temp;

                timePassed += P2[i];                 //add the time passed
            } else {
                timePassed += P2[i];
            }
        } else {
            timePassed += P2[i];
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }

        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo2[i], P2[i]);
    }

    wt2[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt2[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt2[i] += P2[j];                                //Assigns waiting time based on the Process burst time

        total += wt2[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt2 = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                              //finding turnaround time
        total += tat2[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo2[i], P2[i], wt2[i], tat2[i]);
    }

    avg_tat2 = (float) total / n;
    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K = 2) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt2);
    printf("\nAverage Turnaround Time = %f\n", avg_tat2);

}

void KFactorAlgorithmPaper() {

    //initialise k = 2
    int k = 2, passed = 0;
    int P[20], A[20], i, j, n, total = 0, pos, temp;

    //For K = 2;
    int ProcessNo[20], wt[20], tat[20], timePassed = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int P2[20], ProcessNo2[20], checker = 0, wt2[20], tat2[20];
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\n\tK-FACTOR ALGORITHM FOLLOWING PAPER OUTPUT");
    printf("\n================================================================\n");
    n = 10;                                //following paper process number
    printf("\n%d Process(es)", n);
    for (i = 0; i < n; i++) {
        P[i] = (rand() % 100) + 1;                  //Assign random burst times
        A[i] = 0;                                   //Standardise arrival time according to paper

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
    printf("\n\nSorted Based on SJF Arrival Time (Ready Queue): \n");
    //sorting of burst times for ready queue
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] <
                A[pos]) {                     //compares all of the contents in the array if it has the smallest arrival time. Sorts accordingly (aka places into ready queue).
                pos = j;
            } else if (A[j] == A[pos]) {              //if arrival time is the same, compares burst time.
                if (P[j] < P[pos]) {
                    pos = j;
                }
            }
        }

        temp = P[i];                                //Use a holder to keep the value
        P[i] = P[pos];                              //Assign new burst time to the current position
        P[pos] = temp;                              //The taken burst time is replaced


        temp = A[i];                                //Use a holder to keep the value of Arrival Time
        A[i] = A[pos];                              //Assign new arrival time to the current position
        A[pos] = temp;

        temp = ProcessNo[i];                        //Same concept with the above but now for process number labelling
        ProcessNo[i] = ProcessNo[pos];
        ProcessNo2[i] = ProcessNo2[pos];
        ProcessNo[pos] = temp;
        ProcessNo2[pos] = temp;
        printf("Process %d: %d\n", ProcessNo[i], P[i]);
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy Array of process to another Array
    }
    printf("\nSorted Based on K = 2: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                temp = P[i];                        //Same concept as above using holder to store values temporarily
                P[i] = P[i + 1];
                P[i + 1] = temp;

                temp = ProcessNo[i];                //Same concept
                ProcessNo[i] = ProcessNo[i + 1];
                ProcessNo[i + 1] = temp;

                timePassed += P[i];                 //add the time passed
            } else {
                timePassed += P[i];
            }
        } else {
            timePassed += P[i];
        }


        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
    }

    wt[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt[i] += P[j];                                //Assigns waiting time based on the Process burst time

        total += wt[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                              //finding turnaround time
        total += tat[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo[i], P[i], wt[i], tat[i]);
    }

    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;

    printf("\n\nSorted Based on K alternative: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                temp = P2[i];                        //Same concept as above using holder to store values temporarily
                P2[i] = P2[i + 1];
                P2[i + 1] = temp;

                temp = ProcessNo2[i];                //Same concept
                ProcessNo2[i] = ProcessNo2[i + 1];
                ProcessNo2[i + 1] = temp;

                timePassed += P2[i];                 //add the time passed
            } else {
                timePassed += P2[i];
            }
        } else {
            timePassed += P2[i];
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }

        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo2[i], P2[i]);
    }

    wt2[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt2[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt2[i] += P2[j];                                //Assigns waiting time based on the Process burst time

        total += wt2[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt2 = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                              //finding turnaround time
        total += tat2[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo2[i], P2[i], wt2[i], tat2[i]);
    }

    avg_tat2 = (float) total / n;
    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K = 2) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt2);
    printf("\nAverage Turnaround Time = %f\n", avg_tat2);

}

void KFactorAlgorithmArrivalZero() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0;
    int P[10001], A[10001], i, j, n, total = 0, pos, temp;

    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\n\tK-FACTOR ALGORITHM - Arrival Time = Zero");
    printf("\n================================================================\n");
    printf("\nEnter number of processes (Max 10000 Processes):");
    fgets(input, 16, stdin);
    passed = inputChecker(input, 1);        //flag to activate error handling



    while (passed == 1) {                          //If flag is activated
        passed = 0;
        printf("\nInvalid input! Please enter an Integer without any spaces.\n");
        printf("\nEnter number of processes (Max 10000 Processes):");
        fgets(input, 16, stdin);
        passed = inputChecker(input, 1);
    }

    n = atoi(input);                                //convert string to integer


    printf("\n%d Process(es)", n);


    for (i = 0; i < n; i++) {
        int burstPassed = 0, arrivalPassed = 0;
        printf("\nProcess No (%d):", i + 1);
        printf("\nEnter Burst Time:");
        fgets(input, 16, stdin);
        burstPassed = inputChecker(input, 4);           //flag for error handling (for burst times)
        while (burstPassed == 1) {
            burstPassed = 0;
            printf("\nInvalid input! Please enter an Integer without any spaces. (Burst Times cannot be 0)\n");
            printf("\nProcess No (%d):", i + 1);
            printf("\nEnter Burst Time:");
            fgets(input, 16, stdin);
            burstPassed = inputChecker(input, 4);
        }
        P[i] = atoi(input);                                     //convert string to integer
        A[i] = 0;                                               //Arrival Time = 0

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
    printf("\n\nSorted Based on SJF Arrival Time (Ready Queue): \n");
    //sorting of burst times for ready queue
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] <
                A[pos]) {                     //compares all of the contents in the array if it has the smallest arrival time. Sorts accordingly (aka places into ready queue).
                pos = j;
            } else if (A[j] == A[pos]) {              //if arrival time is the same, compares burst time.
                if (P[j] < P[pos]) {
                    pos = j;
                }
            }
        }

        temp = P[i];                                //Use a holder to keep the value
        P[i] = P[pos];                              //Assign new burst time to the current position
        P[pos] = temp;                              //The taken burst time is replaced


        temp = A[i];                                //Use a holder to keep the value of Arrival Time
        A[i] = A[pos];                              //Assign new arrival time to the current position
        A[pos] = temp;

        temp = ProcessNo[i];                        //Same concept with the above but now for process number labelling
        ProcessNo[i] = ProcessNo[pos];
        ProcessNo2[i] = ProcessNo2[pos];
        ProcessNo[pos] = temp;
        ProcessNo2[pos] = temp;
        printf("Process %d: %d\n", ProcessNo[i], P[i]);
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy Array of process to another Array
    }


    printf("\nSorted Based on K = 2: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                temp = P[i];                        //Same concept as above using holder to store values temporarily
                P[i] = P[i + 1];
                P[i + 1] = temp;

                temp = ProcessNo[i];                //Same concept
                ProcessNo[i] = ProcessNo[i + 1];
                ProcessNo[i + 1] = temp;

                timePassed += P[i];                 //add the time passed
            } else {
                timePassed += P[i];
            }
        } else {
            timePassed += P[i];
        }


        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
    }

    wt[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt[i] += P[j];                                //Assigns waiting time based on the Process burst time

        total += wt[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                              //finding turnaround time
        total += tat[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo[i], P[i], wt[i], tat[i]);
    }

    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;

    printf("\n\nSorted Based on K alternative: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                temp = P2[i];                        //Same concept as above using holder to store values temporarily
                P2[i] = P2[i + 1];
                P2[i + 1] = temp;

                temp = ProcessNo2[i];                //Same concept
                ProcessNo2[i] = ProcessNo2[i + 1];
                ProcessNo2[i + 1] = temp;

                timePassed += P2[i];                 //add the time passed
            } else {
                timePassed += P2[i];
            }
        } else {
            timePassed += P2[i];
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }

        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo2[i], P2[i]);
    }

    wt2[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt2[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt2[i] += P2[j];                                //Assigns waiting time based on the Process burst time

        total += wt2[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt2 = (float) total / n;
    total = 0;                                            //clears total time

    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                              //finding turnaround time
        total += tat2[i];                                  //Adds turnaround time to the total Turnaround time.
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo2[i], P2[i], wt2[i], tat2[i]);
    }

    avg_tat2 = (float) total / n;
    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K = 2) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt2);
    printf("\nAverage Turnaround Time = %f\n", avg_tat2);

}

void KFactorAlgorithmProcessSize() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0;
    int P[10001], A[10001], i, j, n, total = 0, pos, temp;

    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\nK-FACTOR ALGORITHM - Manual Process Size, RNG Bursts and AT = 0");
    printf("\n================================================================\n");
    printf("\nEnter number of processes (Max 10000 Processes):");
    fgets(input, 16, stdin);
    passed = inputChecker(input, 1);        //flag to activate error handling



    while (passed == 1) {                          //If flag is activated
        passed = 0;
        printf("\nInvalid input! Please enter an Integer without any spaces.\n");
        printf("\nEnter number of processes (Max 10000 Processes):");
        fgets(input, 16, stdin);
        passed = inputChecker(input, 1);
    }

    n = atoi(input);                                //convert string to integer


    printf("\n%d Process(es)", n);

    for (i = 0; i < n; i++) {
        P[i] = (rand() % 100) + 1;                  //Assign random burst times
        A[i] = 0;                                    //convert string to integer

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
    //sorting of burst times for ready queue
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] <
                A[pos]) {                     //compares all of the contents in the array if it has the smallest arrival time. Sorts accordingly (aka places into ready queue).
                pos = j;
            } else if (A[j] == A[pos]) {              //if arrival time is the same, compares burst time.
                if (P[j] < P[pos]) {
                    pos = j;
                }
            }
        }

        temp = P[i];                                //Use a holder to keep the value
        P[i] = P[pos];                              //Assign new burst time to the current position
        P[pos] = temp;                              //The taken burst time is replaced


        temp = A[i];                                //Use a holder to keep the value of Arrival Time
        A[i] = A[pos];                              //Assign new arrival time to the current position
        A[pos] = temp;

        temp = ProcessNo[i];                        //Same concept with the above but now for process number labelling
        ProcessNo[i] = ProcessNo[pos];
        ProcessNo2[i] = ProcessNo2[pos];
        ProcessNo[pos] = temp;
        ProcessNo2[pos] = temp;
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy Array of process to another Array
    }


    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                temp = P[i];                        //Same concept as above using holder to store values temporarily
                P[i] = P[i + 1];
                P[i + 1] = temp;

                temp = ProcessNo[i];                //Same concept
                ProcessNo[i] = ProcessNo[i + 1];
                ProcessNo[i + 1] = temp;

                timePassed += P[i];                 //add the time passed
            } else {
                timePassed += P[i];
            }
        } else {
            timePassed += P[i];
        }


    }

    wt[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt[i] += P[j];                                //Assigns waiting time based on the Process burst time

        total += wt[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt = (float) total / n;
    total = 0;                                            //clears total time

    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                              //finding turnaround time
        total += tat[i];                                  //Adds turnaround time to the total Turnaround time.
    }

    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;

    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                temp = P2[i];                        //Same concept as above using holder to store values temporarily
                P2[i] = P2[i + 1];
                P2[i + 1] = temp;

                temp = ProcessNo2[i];                //Same concept
                ProcessNo2[i] = ProcessNo2[i + 1];
                ProcessNo2[i + 1] = temp;

                timePassed += P2[i];                 //add the time passed
            } else {
                timePassed += P2[i];
            }
        } else {
            timePassed += P2[i];
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }

    }

    wt2[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt2[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt2[i] += P2[j];                                //Assigns waiting time based on the Process burst time

        total += wt2[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt2 = (float) total / n;
    total = 0;                                            //clears total time

    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                              //finding turnaround time
        total += tat2[i];                                  //Adds turnaround time to the total Turnaround time.
    }

    avg_tat2 = (float) total / n;
    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K = 2) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt2);
    printf("\nAverage Turnaround Time = %f\n", avg_tat2);

}

void KFactorAlgorithmProcessSizeTest() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0;
    int *P, *A, i, j, n, total = 0, pos, temp;

    //For K = 2;
    int *ProcessNo, *wt, *tat, timePassed = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int *P2, *ProcessNo2, checker = 0, *wt2, *tat2;
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\nK-FACTOR ALGORITHM - Manual Process Size, RNG Bursts and AT = 0");
    printf("\n================================================================\n");
    printf("\nEnter number of processes (Max 20000 Processes):");
    fgets(input, 16, stdin);
    passed = inputChecker(input, 1);        //flag to activate error handling



    while (passed == 1) {                          //If flag is activated
        passed = 0;
        printf("\nInvalid input! Please enter an Integer without any spaces.\n");
        printf("\nEnter number of processes (Max 20000 Processes):");
        fgets(input, 16, stdin);
        passed = inputChecker(input, 1);
    }

    n = atoi(input);                                //convert string to integer
    P = (int *) malloc(n * sizeof(int));
    if (P == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    A = (int *) malloc(n * sizeof(int));
    if (A == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    ProcessNo = (int *) malloc(n * sizeof(int));
    if (ProcessNo == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    wt = (int *) malloc(n * sizeof(int));
    if (wt == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    wt2 = (int *) malloc(n * sizeof(int));
    if (wt2 == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    ProcessNo2 = (int *) malloc(n * sizeof(int));
    if (ProcessNo2 == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    tat = (int *) malloc(n * sizeof(int));
    if (tat == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    tat2 = (int *) malloc(n * sizeof(int));
    if (tat2 == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }
    P2 = (int *) malloc(n * sizeof(int));
    if (P2 == NULL) {
        printf("\nError! memory not allocated.");
        exit(0);
    }


    printf("\n%d Process(es)", n);

    for (i = 0; i < n; i++) {
        P[i] = (rand() % 100) + 1;                  //Assign random burst times
        A[i] = 0;                                    //convert string to integer

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
//    printf("\n\nSorted Based on SJF Arrival Time (Ready Queue): \n");
    //sorting of burst times for ready queue
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (A[j] <
                A[pos]) {                     //compares all of the contents in the array if it has the smallest arrival time. Sorts accordingly (aka places into ready queue).
                pos = j;
            } else if (A[j] == A[pos]) {              //if arrival time is the same, compares burst time.
                if (P[j] < P[pos]) {
                    pos = j;
                }
            }
        }

        temp = P[i];                                //Use a holder to keep the value
        P[i] = P[pos];                              //Assign new burst time to the current position
        P[pos] = temp;                              //The taken burst time is replaced


        temp = A[i];                                //Use a holder to keep the value of Arrival Time
        A[i] = A[pos];                              //Assign new arrival time to the current position
        A[pos] = temp;

        temp = ProcessNo[i];                        //Same concept with the above but now for process number labelling
        ProcessNo[i] = ProcessNo[pos];
        ProcessNo2[i] = ProcessNo2[pos];
        ProcessNo[pos] = temp;
        ProcessNo2[pos] = temp;
//        printf("Process %d: %d\n",ProcessNo[i], P[i]);
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy Array of process to another Array
    }


//    printf("\nSorted Based on K = 2: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                temp = P[i];                        //Same concept as above using holder to store values temporarily
                P[i] = P[i + 1];
                P[i + 1] = temp;

                temp = ProcessNo[i];                //Same concept
                ProcessNo[i] = ProcessNo[i + 1];
                ProcessNo[i + 1] = temp;

                timePassed += P[i];                 //add the time passed
            } else {
                timePassed += P[i];
            }
        } else {
            timePassed += P[i];
        }


//        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
    }

    wt[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt[i] += P[j];                                //Assigns waiting time based on the Process burst time

        total += wt[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt = (float) total / n;
    total = 0;                                            //clears total time

//    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                              //finding turnaround time
        total += tat[i];                                  //Adds turnaround time to the total Turnaround time.
//        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",ProcessNo[i],P[i],wt[i],tat[i]);
    }

    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;

//    printf("\n\nSorted Based on K alternative: ");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        }
        if (i != n - 1) {                               //if it is not the last process, perform sort
            if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                temp = P2[i];                        //Same concept as above using holder to store values temporarily
                P2[i] = P2[i + 1];
                P2[i + 1] = temp;

                temp = ProcessNo2[i];                //Same concept
                ProcessNo2[i] = ProcessNo2[i + 1];
                ProcessNo2[i + 1] = temp;

                timePassed += P2[i];                 //add the time passed
            } else {
                timePassed += P2[i];
            }
        } else {
            timePassed += P2[i];
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }

//        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo2[i], P2[i]);
    }

    wt2[0] = 0;                                            //first waiting time is 0 since it is the first process.

    for (i = 1; i < n; i++) {
        wt2[i] = 0;                                        //clears all the waiting times first.
        for (j = 0; j < i; j++)
            wt2[i] += P2[j];                                //Assigns waiting time based on the Process burst time

        total += wt2[i];                                   //total time passed + waiting time to calculate total time after every process is done.
    }

    avg_wt2 = (float) total / n;
    total = 0;                                            //clears total time

//    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                            //finding turnaround time
        total += tat2[i];                                  //Adds turnaround time to the total Turnaround time.
//        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",ProcessNo2[i],P2[i],wt2[i],tat2[i]);
    }

    avg_tat2 = (float) total / n;
    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K = 2) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %f", avg_wt2);
    printf("\nAverage Turnaround Time = %f\n", avg_tat2);

    free(P);
    free(P2);
    free(A);
    free(ProcessNo2);
    free(ProcessNo);
    free(wt);
    free(wt2);
    free(tat);
    free(tat2);
}

int inputChecker(char input[20], char mode) {
    int i, n;
    int passed = 0;
    for (i = 0; i < strlen(input); i++) {    //Input error Handling
        if (input[0] == '\n') {               //If user just enters without any input \n = newline
            passed = 1;                       //trigger flag to do while loop.
            break;
        }
        if (isalnum(input[i]) == 0) {         //Check if it is alpha numeric.
            if (input[i] != '\n') {           //If it is a new line ignore as fgets uses it.
                passed = 1;
                break;
            }
        }

        if (isalpha(input[i]) !=
            0) {         //Check if it is a letter. Breaks if it is (due to character having ASCII integer values, this is required)
            passed = 1;
            break;
        }

    }
    n = atoi(input);                        //To check if user inputs something like 0000010
    if (mode == 3) {
        if (n < 1 || n > 4) {
            passed = 1;
        }
    } else if (mode == 1) {
        if (n == 0 && mode == 1) {                             //if it adds up to 0 anyways, activate error handling.
            passed = 1;
        }

        if (n < 1 || n > 10000) {
            passed = 1;
        }
    } else if (mode == 2) {
        if (n < 0) {
            passed = 1;
        }
    } else if (mode == 4) {
        if (n < 1) {
            passed = 1;
        }
    } else if (mode == 5){
        if (n < 1 || n > 2){
            passed = 1;
        }
    }
    if (passed == 0) {
        return 0;
    } else {
        return 1;
    }
    return 0;
}
