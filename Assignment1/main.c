#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

void KFactorAlgorithm();
void KFactorAlgorithmPaper();
void KFactorAlgorithmArrivalZero();
void KFactorAlgorithmProcessSize();
void KFactorAlgorithmProcessSizeDynamic();
void KFactorRandomAll();
void KFactorRandomBurst();
int inputChecker(char input[20], char mode);

int main() {

    while (1) {
        srand(1);                     // To ensure random values are same each time we run the program.
        char userInput[20];
        int flag = 0, flag2 = 0;            // Flag to ensure correct input
        int select, choice;                 // Variables to store input (after error checking).

        printf("=======================================");
        printf("\nMuhammad Nurhakim Bin Mohd Razalee");
        printf("\n2001019");
        printf("\nPaper Assigned: 2");
        printf("\n=======================================");
        printf("\nAlgorithms: ");
        printf("\n1) K-Factor Algorithm (Manual Burst Times & Arrival Times with idle time consideration)");
        printf("\n2) K-Factor Algorithm (Paper given Burst Times (RNG) & Arrival Times, T=0)");
        printf("\n3) K-Factor Algorithm (Manual Burst Times with 0 Arrival Times)");
        printf("\n4) K-Factor Algorithm (Manual Process Size with Random Burst Times & Arrival Times = 0)");
        printf("\n5) K-Factor Algorithm (Same as [4] But memory is dynamically allocated. HARDWARE RELIANT)");
        printf("\n6) K-Factor Algorithm Random 1 (5 Seeds RNG Burst & RNG Arrival (For Group Test))");
        printf("\n7) K-Factor Algorithm Random 2 (5 Seeds RNG Burst & Arrival = 0 (For Group Test))");
        printf("\n\nSelect Algorithm: ");
        fgets(userInput, 16, stdin);        // get user input
        flag = inputChecker(userInput, 3);          // Run the inputChecker function.
        while (flag == 1) {
            flag = 0;
            printf("\n=======================================");
            printf("\n\t  INVALID INPUT!");
            printf("\n=======================================");
            printf("\nPlease only Input 1,2,3 or 4 without any spaces.\n");
            printf("\nAlgorithms: ");
            printf("\n1) K-Factor Algorithm (Manual Burst Times & Arrival Times with idle time consideration)");
            printf("\n2) K-Factor Algorithm (Paper given Burst Times (RNG) & Arrival Times = 0)");
            printf("\n3) K-Factor Algorithm (Manual Burst Times with 0 Arrival Times)");
            printf("\n4) K-Factor Algorithm (Manual Process Size with Random Burst Times & Arrival Times = 0)");
            printf("\n5) K-Factor Algorithm (Same as [4] But memory is dynamically allocated. HARDWARE RELIANT)");
            printf("\n6) K-Factor Algorithm Random 1 (5 Seeds RNG Burst & RNG Arrival (For Group Test))");
            printf("\n7) K-Factor Algorithm Random 2 (5 Seeds RNG Burst & Arrival = 0 (For Group Test))");
            printf("\n\nSelect Algorithm: ");
            fgets(userInput, 16, stdin);        //get user input
            flag = inputChecker(userInput, 3);          // Run input checker function
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
        } else if (select == 5) {
            KFactorAlgorithmProcessSizeDynamic();        //Attempted to use malloc but results were inaccurate after 12000 processes due to lack of hardware power.
        }else if (select == 6) {
            KFactorRandomAll();        //For group testing
        } else if (select == 7){
            KFactorRandomBurst();
        }
        printf("\nDo you wish to try another algorithm?");
        printf("\n1) Yes\t 2) No");
        printf("\nChoice:");
        fgets(userInput, 16, stdin);
        flag2 = inputChecker(userInput, 5);
        while (flag2 == 1) {
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
        if (choice == 1) {
            continue;
        } else if (choice == 2) {
            printf("\nSystem will now exit.");
            exit(0);
        }
    }

}

/// K-Factor Algorithm [With Manual burst times and arrival times & idle time scenarios]
void KFactorAlgorithm() {
    //initialise k = 2
    char input[20];
    int k = 2, passed = 0, flagger = 0;
    int P[10001], A[10001], A2[10001], extraTime[10001], i, j, n, total = 0, pos, temp;
    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0, readyQueueTime = 0;
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
    //Sort based on arrival time
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

    //Sort burst times of processes other than process that arrived first
    for (i = 0; i < n; i++) {
        if (i == 0) {
//            printf("Process %d: %d (Already Executing)\n", ProcessNo[i], P[i]);
            readyQueueTime += P[i];
            continue;
        } else {
            pos = i;

            for (j = i + 1; j < n; j++) {
                if (readyQueueTime >=
                    A[pos]) {                                 //check if process had already arrived while a process is executing
                    if (readyQueueTime >= A[j]) {             //check if any other process have also arrived
                        if (P[pos] >
                            P[j]) {                           // If there are other processes being ready, compare burst times for SJF
                            pos = j;
                        }
                    }
                } else {                                      //if process has not arrived
                    flagger = 1;

                    if (readyQueueTime >=
                        A[j]) {                               // Check if any other processes in the array arrive faster. If it does, it takes precedence
                        pos = j;
                    } else {                                  // If no other process arrive faster find out how long this process need to arrive and executes
                        extraTime[pos] = A[pos] - readyQueueTime;  //It will need this much extra time
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
            extraTime[i] = extraTime[pos];
            ProcessNo[pos] = temp;
            ProcessNo2[pos] = temp;
            if (flagger == 1) {                         // If process has not arrived
                readyQueueTime += P[i] + extraTime[i];
            } else {
                readyQueueTime += P[i];
            }
//            printf("Process %d: %d\n", ProcessNo[i], P[i]);
        }
    }

    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy of array
        A2[i] = A[i];
    }
    printf("\n----------------------------------------------");
    printf("\n|         Sorted Based on K = 2:             |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A[i] &&
                    timePassed >= A[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                        temp = P[i];                        //Same concept as above using holder to store values temporarily
                        P[i] = P[i + 1];
                        P[i + 1] = temp;

                        temp = ProcessNo[i];                //Same concept
                        ProcessNo[i] = ProcessNo[i + 1];
                        ProcessNo[i + 1] = temp;

                        temp = A[i];                                //Use a holder to keep the value of Arrival Time
                        A[i] = A[i+1];                              //Assign new arrival time to the current position
                        A[i+1] = temp;

                        timePassed += P[i];                 //add the time passed
                    } else {
                        timePassed += P[i];
                    }
                } else if (timePassed >= A[i]) {     //if only the first process is ready then execute.
                    timePassed += P[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A[i] - timePassed) + P[i];
                }
            } else {                                //if it is the last process
                timePassed += P[i];
            }
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo[i], 5,P[i]);
    }
    printf("\n----------------------------------------------");

    printf("\n\nGANTT CHART:");
    int ongoing = 0, idleTime[2000];
    int executedProcess = 0;
    int allIdle = 0;

    for(i = 0; i < n; i++){
        // Clears all waiting time first.
        wt[i] = 0;
        // Clears all idleTime first.
        idleTime[i] = 0;
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P[i] + A[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime[i] += (ongoing - P[i]);              // Get the idle time before the first process
            allIdle += idleTime[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime[i], idleTime[i]);
            printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);

        } else if (i==0 && A[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        } else {
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A[i]) {      // If the current time is before the process arrives, wt = 0;
                wt[i] = 0;
            } else if ((allIdle + executedProcess) > A[i]) {    // If the current time is more or equal to the arrival time
                wt[i] = (allIdle + executedProcess) - A[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt[i];
        // Total waiting time used to find average
    }
    avg_wt = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo[i],5, P[i],5, wt[i],5, tat[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;
    printf("\n\n----------------------------------------------");
    printf("\n| Sorted Based on K increases alternatively: |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A2[i] &&
                    timePassed >= A2[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                        temp = P2[i];                        //Same concept as above using holder to store values temporarily
                        P2[i] = P2[i + 1];
                        P2[i + 1] = temp;

                        temp = ProcessNo2[i];                //Same concept
                        ProcessNo2[i] = ProcessNo2[i + 1];
                        ProcessNo2[i + 1] = temp;

                        temp = A2[i];                                //Use a holder to keep the value of Arrival Time
                        A2[i] = A2[i+1];                              //Assign new arrival time to the current position
                        A2[i+1] = temp;

                        timePassed += P2[i];                 //add the time passed
                    } else {
                        timePassed += P2[i];
                    }
                } else if (timePassed >= A2[i]) {     //if only the first process is ready then execute.
                    timePassed += P2[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A2[i] - timePassed) + P2[i];
                }
            } else {                                //if it is the last process
                timePassed += P2[i];
            }
        }
        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo2[i], 5,P2[i]);
    }
    printf("\n----------------------------------------------");
    printf("\n\nGANTT CHART:");
    //clear variables
    int idleTime2[2000];
    ongoing = 0;
    executedProcess = 0;
    allIdle = 0;

    for(i = 0; i < n; i++){
        wt2[i] = 0;                                        // Clears all waiting time first.
        idleTime2[i] = 0;                                     // Clears all idle time first.
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P2[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A2[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P2[i] + A2[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime2[i] += (ongoing - P2[i]);              // Get the idle time before the first process
            allIdle += idleTime2[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime2[i], idleTime2[i]);
            printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);

        } else if (i==0 && A2[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P2[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        } else {
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt2[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A2[i]) {      // If the current time is before the process arrives, wt = 0;
                wt2[i] = 0;
            } else if ((allIdle + executedProcess) > A2[i]) {    // If the current time is more or equal to the arrival time
//                    printf("\n Hit. AllIdle : %d, Executed Processes: %d, Total %d", allidle, executedProcess, idleTime[i], allidle + executedProcess);
                wt2[i] = (allIdle + executedProcess) - A2[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt2[i];
        // Total waiting time used to find average
    }
    avg_wt2 = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat2[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo2[i],5, P2[i],5, wt2[i],5, tat2[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat2 = (float) total / n;

    printf("\n\n=========================================================");
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

/// K-Factor Algorithm [With Paper burst times and arrival times]
void KFactorAlgorithmPaper() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0, flagger = 0;
    int P[10001], A[10001], A2[10001], extraTime[10001], i, j, n = 10, total = 0, pos, temp;


    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0, readyQueueTime = 0;
    float avg_wt, avg_tat;

    //For K increases alternatively:
    int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
    float avg_wt2, avg_tat2;


    printf("\n================================================================");
    printf("\n   K-FACTOR ALGORITHM - Paper Test Case (RNG burst , AT=1)");
    printf("\n================================================================\n");
    for (i = 0; i < n; i++) {
        P[i] = (rand() % 100) + 1;                  //Assign random burst times
        A[i] = 0;                                   //Standardise arrival time according to paper

        ProcessNo[i] = i + 1;
        ProcessNo2[i] = i + 1;
    }
    //Sort based on arrival time
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

    //Sort burst times of processes other than process that arrived first
    for (i = 0; i < n; i++) {
        if (i == 0) {
//            printf("Process %d: %d (Already Executing)\n", ProcessNo[i], P[i]);
            readyQueueTime += P[i];
            continue;
        } else {
            pos = i;

            for (j = i + 1; j < n; j++) {
                if (readyQueueTime >=
                    A[pos]) {                                 //check if process had already arrived while a process is executing
                    if (readyQueueTime >= A[j]) {             //check if any other process have also arrived
                        if (P[pos] >
                            P[j]) {                           // If there are other processes being ready, compare burst times for SJF
                            pos = j;
                        }
                    }
                } else {                                      //if process has not arrived
                    flagger = 1;

                    if (readyQueueTime >=
                        A[j]) {                               // Check if any other processes in the array arrive faster. If it does, it takes precedence
                        pos = j;
                    } else {                                  // If no other process arrive faster find out how long this process need to arrive and executes
                        extraTime[pos] = A[pos] - readyQueueTime;  //It will need this much extra time
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
            extraTime[i] = extraTime[pos];
            ProcessNo[pos] = temp;
            ProcessNo2[pos] = temp;
            if (flagger == 1) {                         // If process has not arrived
                readyQueueTime += P[i] + extraTime[i];
            } else {
                readyQueueTime += P[i];
            }
//            printf("Process %d: %d\n", ProcessNo[i], P[i]);
        }
    }
    for (i = 0; i < n; i++) {
        P2[i] = P[i];                               //Copy of array
        A2[i] = A[i];
    }
    printf("\n----------------------------------------------");
    printf("\n|         Sorted Based on K = 2:             |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A[i] &&
                    timePassed >= A[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                        temp = P[i];                        //Same concept as above using holder to store values temporarily
                        P[i] = P[i + 1];
                        P[i + 1] = temp;

                        temp = ProcessNo[i];                //Same concept
                        ProcessNo[i] = ProcessNo[i + 1];
                        ProcessNo[i + 1] = temp;

                        temp = A[i];                                //Use a holder to keep the value of Arrival Time
                        A[i] = A[i+1];                              //Assign new arrival time to the current position
                        A[i+1] = temp;

                        timePassed += P[i];                 //add the time passed
                    } else {
                        timePassed += P[i];
                    }
                } else if (timePassed >= A[i]) {     //if only the first process is ready then execute.
                    timePassed += P[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A[i] - timePassed) + P[i];
                }
            } else {                                //if it is the last process
                timePassed += P[i];
            }
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo[i], 5,P[i]);
    }
    printf("\n----------------------------------------------");

    printf("\n\nGANTT CHART:");
    int ongoing = 0, idleTime[2000];
    int executedProcess = 0;
    int allIdle = 0;

    for(i = 0; i < n; i++){
        // Clears all waiting time first.
        wt[i] = 0;
        // Clears all idleTime first.
        idleTime[i] = 0;
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P[i] + A[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime[i] += (ongoing - P[i]);              // Get the idle time before the first process
            allIdle += idleTime[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime[i], idleTime[i]);
            printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);

        } else if (i==0 && A[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        } else {
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A[i]) {      // If the current time is before the process arrives, wt = 0;
                wt[i] = 0;
            } else if ((allIdle + executedProcess) > A[i]) {    // If the current time is more or equal to the arrival time
                wt[i] = (allIdle + executedProcess) - A[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt[i];
        // Total waiting time used to find average
    }
    avg_wt = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo[i],5, P[i],5, wt[i],5, tat[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;
    printf("\n\n----------------------------------------------");
    printf("\n| Sorted Based on K increases alternatively: |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A2[i] &&
                    timePassed >= A2[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                        temp = P2[i];                        //Same concept as above using holder to store values temporarily
                        P2[i] = P2[i + 1];
                        P2[i + 1] = temp;

                        temp = ProcessNo2[i];                //Same concept
                        ProcessNo2[i] = ProcessNo2[i + 1];
                        ProcessNo2[i + 1] = temp;

                        temp = A2[i];                                //Use a holder to keep the value of Arrival Time
                        A2[i] = A2[i+1];                              //Assign new arrival time to the current position
                        A2[i+1] = temp;

                        timePassed += P2[i];                 //add the time passed
                    } else {
                        timePassed += P2[i];
                    }
                } else if (timePassed >= A2[i]) {     //if only the first process is ready then execute.
                    timePassed += P2[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A2[i] - timePassed) + P2[i];
                }
            } else {                                //if it is the last process
                timePassed += P2[i];
            }
        }

        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo2[i], 5,P2[i]);
    }
    printf("\n----------------------------------------------");
    printf("\n\nGANTT CHART:");
    //clear variables
    int idleTime2[2000];
    ongoing = 0;
    executedProcess = 0;
    allIdle = 0;

    for(i = 0; i < n; i++){
        wt2[i] = 0;                                        // Clears all waiting time first.
        idleTime2[i] = 0;                                     // Clears all idle time first.
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P2[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A2[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P2[i] + A2[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime2[i] += (ongoing - P2[i]);              // Get the idle time before the first process
            allIdle += idleTime2[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime2[i], idleTime2[i]);
            printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);

        } else if (i==0 && A2[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P2[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        } else {
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt2[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A2[i]) {      // If the current time is before the process arrives, wt = 0;
                wt2[i] = 0;
            } else if ((allIdle + executedProcess) > A2[i]) {    // If the current time is more or equal to the arrival time
//                    printf("\n Hit. AllIdle : %d, Executed Processes: %d, Total %d", allidle, executedProcess, idleTime[i], allidle + executedProcess);
                wt2[i] = (allIdle + executedProcess) - A2[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt2[i];
        // Total waiting time used to find average
    }
    avg_wt2 = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat2[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo2[i],5, P2[i],5, wt2[i],5, tat2[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat2 = (float) total / n;

    printf("\n\n=========================================================");
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

/// K-Factor Algorithm [With Manual burst times and arrival times are set to 0]
void KFactorAlgorithmArrivalZero() {

    //initialise k = 2
    char input[20];
    int k = 2, passed = 0, flagger = 0;
    int P[10001], A[10001], A2[10001], extraTime[10001], i, j, n, total = 0, pos, temp;


    //For K = 2;
    int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0, readyQueueTime = 0;
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
        int burstPassed = 0;
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
    //Sort based on arrival time
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
        P2[i] = P[i];                               //Copy of array
        A2[i] = A[i];
    }
    printf("\n----------------------------------------------");
    printf("\n|         Sorted Based on K = 2:             |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                //if it is the first process, dont need to sort anymore.
            timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A[i] &&
                    timePassed >= A[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                        temp = P[i];                        //Same concept as above using holder to store values temporarily
                        P[i] = P[i + 1];
                        P[i + 1] = temp;

                        temp = ProcessNo[i];                //Same concept
                        ProcessNo[i] = ProcessNo[i + 1];
                        ProcessNo[i + 1] = temp;

                        temp = A[i];                                //Use a holder to keep the value of Arrival Time
                        A[i] = A[i+1];                              //Assign new arrival time to the current position
                        A[i+1] = temp;

                        timePassed += P[i];                 //add the time passed
                    } else {
                        timePassed += P[i];
                    }
                } else if (timePassed >= A[i]) {     //if only the first process is ready then execute.
                    timePassed += P[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A[i] - timePassed) + P[i];
                }
            } else {                                //if it is the last process
                timePassed += P[i];
            }
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo[i], 5,P[i]);
    }
    printf("\n----------------------------------------------");

    printf("\n\nGANTT CHART:");
    int ongoing = 0, idleTime[2000];
    int executedProcess = 0;
    int allIdle = 0;

    for(i = 0; i < n; i++){
        // Clears all waiting time first.
        wt[i] = 0;
        // Clears all idleTime first.
        idleTime[i] = 0;
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P[i] + A[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime[i] += (ongoing - P[i]);              // Get the idle time before the first process
            allIdle += idleTime[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime[i], idleTime[i]);
            printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);

        } else if (i==0 && A[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        } else {
            if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime[i], ongoing);
                ongoing += P[i];
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo[i], P[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A[i]) {      // If the current time is before the process arrives, wt = 0;
                wt[i] = 0;
            } else if ((allIdle + executedProcess) > A[i]) {    // If the current time is more or equal to the arrival time
                wt[i] = (allIdle + executedProcess) - A[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt[i];
        // Total waiting time used to find average
    }
    avg_wt = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat[i] = P[i] + wt[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo[i],5, P[i],5, wt[i],5, tat[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat = (float) total / n;

    //clear common variables
    timePassed = 0;
    total = 0;
    printf("\n\n----------------------------------------------");
    printf("\n| Sorted Based on K increases alternatively: |");
    printf("\n----------------------------------------------");
    for (i = 0; i < n; i++) {
        if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
            timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if (timePassed >= A2[i] &&
                    timePassed >= A2[i + 1]) { //checks if first and second process in the ready queue
                    if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                        temp = P2[i];                        //Same concept as above using holder to store values temporarily
                        P2[i] = P2[i + 1];
                        P2[i + 1] = temp;

                        temp = ProcessNo2[i];                //Same concept
                        ProcessNo2[i] = ProcessNo2[i + 1];
                        ProcessNo2[i + 1] = temp;

                        temp = A2[i];                                //Use a holder to keep the value of Arrival Time
                        A2[i] = A2[i+1];                              //Assign new arrival time to the current position
                        A2[i+1] = temp;

                        timePassed += P2[i];                 //add the time passed
                    } else {
                        timePassed += P2[i];
                    }
                } else if (timePassed >= A2[i]) {     //if only the first process is ready then execute.
                    timePassed += P2[i];
                } else {                            //if none has arrived, take the remaining time and add it
                    timePassed = (A2[i] - timePassed) + P2[i];
                }
            } else {                                //if it is the last process
                timePassed += P2[i];
            }
        }

        //----Alternative adding to K----
        if (checker == 0) {                          //check if K has already been incremented previously
            checker = checker + 1;                   //If it hasn't the next loop will increment it

        } else if (checker == 1) {                   //Flag to increment is set
            checker = checker - 1;                  //Change the flag back
            k++;                                    //increment K
        }
        printf("\n| Process No: %*d  |\t Burst Time: %*d   |", 5,ProcessNo2[i], 5,P2[i]);
    }
    printf("\n----------------------------------------------");
    printf("\n\nGANTT CHART:");
    //clear variables
    int idleTime2[2000];
    ongoing = 0;
    executedProcess = 0;
    allIdle = 0;

    for(i = 0; i < n; i++){
        wt2[i] = 0;                                        // Clears all waiting time first.
        idleTime2[i] = 0;                                     // Clears all idle time first.
    }
    for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
        executedProcess += P2[i-1];                        // Saves the total process time that has been executed
        if (i == 0 && A2[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
            ongoing += (P2[i] + A2[i]);                     // Set the current ongoing time to Process burst + the arrival time
            idleTime2[i] += (ongoing - P2[i]);              // Get the idle time before the first process
            allIdle += idleTime2[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
            printf("\n|0| Idle: %d |%d| ", idleTime2[i], idleTime2[i]);
            printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);

        } else if (i==0 && A2[i] == 0) {                   // If it is the first process and the arrival time is 0,
            ongoing += P2[i];                              // The current time is now the time of the process burst
            printf("\n|0| P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
        } else if (i == n-1) {                                          // If it is not the first process,
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];               // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        } else {
            if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                ongoing += idleTime2[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                printf("Idle: %d |%d| ", idleTime2[i], ongoing);
                ongoing += P2[i];
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            } else if (A[i] <=ongoing){               // If there is no idle time
                ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                printf("P%d: %d |%d| ", ProcessNo2[i], P2[i], ongoing);
            }
        }

        if(i == 0){                                 // If it is the first process, the wt is 0.
            wt2[i] = 0;
        } else {                                    // if it is not the first process
            if ((allIdle + executedProcess) <= A2[i]) {      // If the current time is before the process arrives, wt = 0;
                wt2[i] = 0;
            } else if ((allIdle + executedProcess) > A2[i]) {    // If the current time is more or equal to the arrival time
//                    printf("\n Hit. AllIdle : %d, Executed Processes: %d, Total %d", allidle, executedProcess, idleTime[i], allidle + executedProcess);
                wt2[i] = (allIdle + executedProcess) - A2[i];     // The waiting time will be the current time - the arrival time.
            }
        }
        total += wt2[i];
        // Total waiting time used to find average
    }
    avg_wt2 = (float) total / n;
    total = 0;
    printf("\n\n--------------------------------------------------------------------------");
    printf("\n|Process\t  |Burst Time  \t    |Waiting Time\t|Turnaround Time |");
    printf("\n--------------------------------------------------------------------------");
    for (i = 0; i < n; i++) {
        tat2[i] = P2[i] + wt2[i];                                                              // Finding turnaround time following formula Burst time + waiting time
        total += tat2[i];                                                                    //Adds turnaround time to the total Turnaround time.
        printf("\n|P%d\t\t  |%*d\t    |%*d\t\t|%*d           |", ProcessNo2[i],5, P2[i],5, wt2[i],5, tat2[i]);
    }
    printf("\n--------------------------------------------------------------------------");
    avg_tat2 = (float) total / n;

    printf("\n\n=========================================================");
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

/// K-Factor Algorithm [With RNG burst times and arrival times are set to 0]
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
        } else {
            if (i != n - 1) {                               //if it is not the last process, perform sort
                if ((k * P[i]) > (timePassed + P[i + 1])) {    //following paper algorithm
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
        } else {
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
    printf("\n\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    printf("\n=========================================================");
    printf("\n K-Factor Algorithm (K Increases Alternatively) :");
    printf("\n=========================================================");
    printf("\n\nAverage Waiting Time = %.2f", avg_wt2);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat2);

}

/// K-Factor Algorithm [With RNG burst times and arrival times are set to 0 BUT MEMORY IS DYNAMICALLY ALLOCATED]
/// (To prevent hardware limitations )
void KFactorAlgorithmProcessSizeDynamic() {

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
    printf("\n\nWARNING: MEMORY IS DYNAMICALLY ALLOCATED. TO PREVENT ANY CRASHES,");
    printf("\nDO NOT INPUT LARGE NUMBER OF PROCESSES");
    printf("\n================================================================\n");
    printf("\nEnter number of processes:");
    fgets(input, 16, stdin);
    passed = inputChecker(input, 4);        //flag to activate error handling



    while (passed == 1) {                          //If flag is activated
        passed = 0;
        printf("\nInvalid input! Please enter an Integer without any spaces.\n");
        printf("\nEnter number of processes:");
        fgets(input, 16, stdin);
        passed = inputChecker(input, 4);
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
        } else {
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
        } else {
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

/// K-Factor Algorithm [With RNG burst times and rng arrival times for Group Testing]
void KFactorRandomAll() {
    // For group testing
    int seed = 1;
    printf("\n================================================================");
    printf("\nK-FACTOR ALGORITHM - Group Testing 2 BURST RNG & ARRIVAL = 0");
    printf("\n================================================================\n");
    while (seed != 6){
        //initialise k = 2
        char input[20];
        int k = 2, passed = 0, flagger = 0;
        int P[10001], A[10001], A2[10001], extraTime[10001], i, j, n=50, total =0 , pos = 0, temp = 0;


        //For K = 2;
        int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0, readyQueueTime = 0;
        float avg_wt= 0, avg_tat = 0;

        //For K increases alternatively:
        int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
        float avg_wt2 = 0, avg_tat2 = 0;

        srand(seed);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\t\t50 Processes with Seed: %d", seed);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n Burst Times List:");


        for (i = 0; i < n; i++) {

            P[i] = (rand() % 100) + 1;                     // Assign Burst Times Range: 1 to 100
            if(i == n-1){
                printf(" %d.", P[i]);
            } else {
                printf(" %d,", P[i]);
            }

            ProcessNo[i] = i + 1;
            ProcessNo2[i] = i + 1;
        }

        printf("\n\n Arrival Times List:");
        for (i = 0; i < n; i++) {
            A[i] = (rand() % 10);                     // Assign Burst Times Range: 1 to 100
            if(i == n-1){
                printf(" %d.", A[i]);
            } else {
                printf(" %d,", A[i]);
            }
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
//        printf("Process %d: %d\n", ProcessNo[i], P[i]);
        }

        //Sort burst times of processes other than process that arrived first
        for (i = 0; i < n; i++) {
            if (i == 0) {
//            printf("Process %d: %d (Already Executing)\n", ProcessNo[i], P[i]);
                readyQueueTime += P[i];
                continue;
            } else {
                pos = i;

                for (j = i + 1; j < n; j++) {
                    if (readyQueueTime >=
                        A[pos]) {                                 //check if process had already arrived while a process is executing
                        if (readyQueueTime >= A[j]) {             //check if any other process have also arrived
                            if (P[pos] >
                                P[j]) {                           // If there are other processes being ready, compare burst times for SJF
                                pos = j;
                            }
                        }
                    } else {                                      //if process has not arrived
                        flagger = 1;

                        if (readyQueueTime >=
                            A[j]) {                               // Check if any other processes in the array arrive faster. If it does, it takes precedence
                            pos = j;
                        } else {                                  // If no other process arrive faster find out how long this process need to arrive and executes
                            extraTime[pos] = A[pos] - readyQueueTime;  //It will need this much extra time
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
                extraTime[i] = extraTime[pos];
                ProcessNo[pos] = temp;
                ProcessNo2[pos] = temp;
                if (flagger == 1) {                         // If process has not arrived
                    readyQueueTime += P[i] + extraTime[i];
                } else {
                    readyQueueTime += P[i];
                }
//            printf("Process %d: %d\n", ProcessNo[i], P[i]);
            }
        }

        for (i = 0; i < n; i++) {
            P2[i] = P[i];                               //Copy of array
            A2[i] = A[i];
        }

        for (i = 0; i < n; i++) {
            if (i == 0) {                                //if it is the first process, dont need to sort anymore.
                timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
            } else {
                if (i != n - 1) {                               //if it is not the last process, perform sort
                    if (timePassed >= A[i] &&
                        timePassed >= A[i + 1]) { //checks if first and second process in the ready queue
                        if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                            temp = P[i];                        //Same concept as above using holder to store values temporarily
                            P[i] = P[i + 1];
                            P[i + 1] = temp;

                            temp = ProcessNo[i];                //Same concept
                            ProcessNo[i] = ProcessNo[i + 1];
                            ProcessNo[i + 1] = temp;

                            temp = A[i];                                //Use a holder to keep the value of Arrival Time
                            A[i] = A[i+1];                              //Assign new arrival time to the current position
                            A[i+1] = temp;

                            timePassed += P[i];                 //add the time passed
                        } else {
                            timePassed += P[i];
                        }
                    } else if (timePassed >= A[i]) {     //if only the first process is ready then execute.
                        timePassed += P[i];
                    } else {                            //if none has arrived, take the remaining time and add it
                        timePassed = (A[i] - timePassed) + P[i];
                    }
                } else {                                //if it is the last process
                    timePassed += P[i];
                }
            }
//        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
        }
        printf("\n");
        int ongoing = 0, idleTime[2000];
        int executedProcess = 0;
        int allIdle = 0;

        for(i = 0; i < n; i++){
            wt[i] = 0;                                        // Clears all waiting time first.
            idleTime[i] = 0;                                  // Clears all idleTime first.
        }
        for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
            executedProcess += P[i-1];                        // Saves the total process time that has been executed
            if (i == 0 && A[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
                ongoing += (P[i] + A[i]);                     // Set the current ongoing time to Process burst + the arrival time
                idleTime[i] += (ongoing - P[i]);              // Get the idle time before the first process
                allIdle += idleTime[i];                       // Adds it to the allIdle variable which stores all the idle times combined.

            } else if (i==0 && A[i] == 0) {                   // If it is the first process and the arrival time is 0,
                ongoing += P[i];                              // The current time is now the time of the process burst
            } else {                                          // If it is not the first process,
                if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                    idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                    allIdle += idleTime[i];               // Adds the idle time to the All idle variable
                    ongoing += idleTime[i] + P[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                } else if (A[i] <=ongoing){               // If there is no idle time
                    ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
                }
            }

            if(i == 0){                                 // If it is the first process, the wt is 0.
                wt[i] = 0;
            } else {                                    // if it is not the first process
                if ((allIdle + executedProcess) <= A[i]) {      // If the current time is before the process arrives, wt = 0;
                    wt[i] = 0;
                } else if ((allIdle + executedProcess) > A[i]) {    // If the current time is more or equal to the arrival time
                    wt[i] = (allIdle + executedProcess) - A[i];     // The waiting time will be the current time - the arrival time.
                }
            }
            total += wt[i];
            // Total waiting time used to find average
        }
        avg_wt = (float) total / n;
        total = 0;                                                                              // Clears total time
        for (i = 0; i < n; i++) {
            tat[i] = P[i] + wt[i];                                                              // Finding turnaround time following formula Burst time + waiting time
            total += tat[i];                                                                    //Adds turnaround time to the total Turnaround time.
        }
        avg_tat = (float) total / n;

        //clear common variables
        timePassed = 0;
        total = 0;

//    printf("\n\nSorted Based on K increases alternatively: ");
        for (i = 0; i < n; i++) {
            if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
                timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
            } else {
                if (i != n - 1) {                               //if it is not the last process, perform sort
                    if (timePassed >= A2[i] &&
                        timePassed >= A2[i + 1]) { //checks if first and second process in the ready queue
                        if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                            temp = P2[i];                        //Same concept as above using holder to store values temporarily
                            P2[i] = P2[i + 1];
                            P2[i + 1] = temp;

                            temp = ProcessNo2[i];                //Same concept
                            ProcessNo2[i] = ProcessNo2[i + 1];
                            ProcessNo2[i + 1] = temp;

                            temp = A2[i];                                //Use a holder to keep the value of Arrival Time
                            A2[i] = A2[i+1];                              //Assign new arrival time to the current position
                            A2[i+1] = temp;

                            timePassed += P2[i];                 //add the time passed
                        } else {
                            timePassed += P2[i];
                        }
                    } else if (timePassed >= A2[i]) {     //if only the first process is ready then execute.
                        timePassed += P2[i];
                    } else {                            //if none has arrived, take the remaining time and add it
                        timePassed = (A2[i] - timePassed) + P2[i];
                    }
                } else {                                //if it is the last process
                    timePassed += P2[i];
                }
            }

            //----Alternative adding to K----
            if (checker == 0) {                          //check if K has already been incremented previously
                checker = checker + 1;                   //If it hasn't the next loop will increment it

            } else if (checker == 1) {                   //Flag to increment is set
                checker = checker - 1;                  //Change the flag back
                k++;                                    //increment K
            }
        }
        printf("\n");

        //clear variables
        int idleTime2[2000];
        ongoing = 0;
        executedProcess = 0;
        allIdle = 0;

        for(i = 0; i < n; i++){
            wt2[i] = 0;                                        // Clears all waiting time first.
            idleTime2[i] = 0;                                     // Clears all idle time first.
        }
        for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
            executedProcess += P2[i-1];                        // Saves the total process time that has been executed
            if (i == 0 && A2[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
                ongoing += (P2[i] + A2[i]);                     // Set the current ongoing time to Process burst + the arrival time
                idleTime2[i] += (ongoing - P2[i]);              // Get the idle time before the first process
                allIdle += idleTime2[i];                       // Adds it to the allIdle variable which stores all the idle times combined.

            } else if (i==0 && A2[i] == 0) {                   // If it is the first process and the arrival time is 0,
                ongoing += P2[i];                              // The current time is now the time of the process burst
            } else {                                          // If it is not the first process,
                if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                    idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                    allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
                    ongoing += idleTime2[i] + P2[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
                } else if (A2[i] <=ongoing){               // If there is no idle time
                    ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
                }
            }

            if(i == 0){                                 // If it is the first process, the wt is 0.
                wt2[i] = 0;
            } else {                                    // if it is not the first process
                if ((allIdle + executedProcess) <= A2[i]) {      // If the current time is before the process arrives, wt = 0;
                    wt2[i] = 0;
                } else if ((allIdle + executedProcess) > A2[i]) {    // If the current time is more or equal to the arrival time
                    wt2[i] = (allIdle + executedProcess) - A2[i];     // The waiting time will be the current time - the arrival time.
                }
            }
            total += wt2[i];
            // Total waiting time used to find average
        }
        avg_wt2 = (float) total / n;
        total = 0;                                                                              // Clears total time
        for (i = 0; i < n; i++) {
            tat2[i] = P2[i] + wt2[i];                                                              // Finding turnaround time following formula Burst time + waiting time
            total += tat2[i];                                                                    //Adds turnaround time to the total Turnaround time.
        }
        avg_tat2 = (float) total / n;

        printf("=========================================================");
        printf("\n K-Factor Algorithm (K = 2) :");
        printf("\n=========================================================");
        printf("\n\nAverage Waiting Time = %.2f", avg_wt);
        printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

        printf("\n=========================================================");
        printf("\n K-Factor Algorithm (K Increases Alternatively) :");
        printf("\n=========================================================");
        printf("\n\nAverage Waiting Time = %.2f", avg_wt2);
        printf("\nAverage Turnaround Time = %.2f\n\n\n\n", avg_tat2);

        seed++;
    }
}

/// K-Factor Algorithm [With RNG burst times and 0 arrival times for Group Testing]
void KFactorRandomBurst() {
    // For group testing
    int seed = 1;
    printf("\n================================================================");
    printf("\nK-FACTOR ALGORITHM - Group Testing 2 BURST RNG & ARRIVAL = 0");
    printf("\n================================================================\n");
    while (seed != 6){
        //initialise k = 2
        char input[20];
        int k = 2, passed = 0, flagger = 0;
        int P[10001], A[10001], A2[10001], extraTime[10001], i, j, n=50, total =0 , pos = 0, temp = 0;


        //For K = 2;
        int ProcessNo[10001], wt[10001], tat[10001], timePassed = 0, readyQueueTime = 0;
        float avg_wt= 0, avg_tat = 0;

        //For K increases alternatively:
        int P2[10001], ProcessNo2[10001], checker = 0, wt2[10001], tat2[10001];
        float avg_wt2 = 0, avg_tat2 = 0;

        srand(seed);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\t\t50 Processes with Seed: %d", seed);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n Process List:");


        for (i = 0; i < n; i++) {

            P[i] = (rand() % 100) + 1;                     // Assign Burst Times Range: 1 to 100
            A[i] = 0;                                     // Assign Arrival Times to be 0;
            if(i == n-1){
                printf(" %d.", P[i]);
            } else {
                printf(" %d,", P[i]);
            }

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

        //Sort burst times of processes other than process that arrived first
        for (i = 0; i < n; i++) {
            if (i == 0) {
//            printf("Process %d: %d (Already Executing)\n", ProcessNo[i], P[i]);
                readyQueueTime += P[i];
                continue;
            } else {
                pos = i;

                for (j = i + 1; j < n; j++) {
                    if (readyQueueTime >=
                        A[pos]) {                                 //check if process had already arrived while a process is executing
                        if (readyQueueTime >= A[j]) {             //check if any other process have also arrived
                            if (P[pos] >
                                P[j]) {                           // If there are other processes being ready, compare burst times for SJF
                                pos = j;
                            }
                        }
                    } else {                                      //if process has not arrived
                        flagger = 1;

                        if (readyQueueTime >=
                            A[j]) {                               // Check if any other processes in the array arrive faster. If it does, it takes precedence
                            pos = j;
                        } else {                                  // If no other process arrive faster find out how long this process need to arrive and executes
                            extraTime[pos] = A[pos] - readyQueueTime;  //It will need this much extra time
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
                extraTime[i] = extraTime[pos];
                ProcessNo[pos] = temp;
                ProcessNo2[pos] = temp;
                if (flagger == 1) {                         // If process has not arrived
                    readyQueueTime += P[i] + extraTime[i];
                } else {
                    readyQueueTime += P[i];
                }
//            printf("Process %d: %d\n", ProcessNo[i], P[i]);
            }
        }

        for (i = 0; i < n; i++) {
            P2[i] = P[i];                               //Copy of array
            A2[i] = A[i];
        }

//    printf("\nSorted Based on K = 2: ");
        for (i = 0; i < n; i++) {
            if (i == 0) {                                //if it is the first process, dont need to sort anymore.
                timePassed += P[i];                      // Allocate the CPU to the first process in the ready queue.
            } else {
                if (i != n - 1) {                               //if it is not the last process, perform sort
                    if (timePassed >= A[i] &&
                        timePassed >= A[i + 1]) { //checks if first and second process in the ready queue
                        if (k * P[i] > timePassed + P[i + 1]) {    //following paper algorithm
                            temp = P[i];                        //Same concept as above using holder to store values temporarily
                            P[i] = P[i + 1];
                            P[i + 1] = temp;

                            temp = ProcessNo[i];                //Same concept
                            ProcessNo[i] = ProcessNo[i + 1];
                            ProcessNo[i + 1] = temp;

                            temp = A[i];                                //Use a holder to keep the value of Arrival Time
                            A[i] = A[i+1];                              //Assign new arrival time to the current position
                            A[i+1] = temp;

                            timePassed += P[i];                 //add the time passed
                        } else {
                            timePassed += P[i];
                        }
                    } else if (timePassed >= A[i]) {     //if only the first process is ready then execute.
                        timePassed += P[i];
                    } else {                            //if none has arrived, take the remaining time and add it
                        timePassed = (A[i] - timePassed) + P[i];
                    }
                } else {                                //if it is the last process
                    timePassed += P[i];
                }
            }
//        printf("\nProcess No: %d\t\t  %d\t\t", ProcessNo[i], P[i]);
        }
        printf("\n");
        int ongoing = 0, idleTime[2000];
        int executedProcess = 0;
        int allIdle = 0;

        for(i = 0; i < n; i++){
            wt[i] = 0;                                        // Clears all waiting time first.
            idleTime[i] = 0;                                  // Clears all idleTime first.
        }
        for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
            executedProcess += P[i-1];                        // Saves the total process time that has been executed
            if (i == 0 && A[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
                ongoing += (P[i] + A[i]);                     // Set the current ongoing time to Process burst + the arrival time
                idleTime[i] += (ongoing - P[i]);              // Get the idle time before the first process
                allIdle += idleTime[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
//            printf("\nIt became idle for %d second(s)", idleTime[i]);                   // Displays the idle information
//            printf("\nProcess %d ends execution at : %d", ProcessNo[i], ongoing);       // Displays when each process finishes executing

            } else if (i==0 && A[i] == 0) {                   // If it is the first process and the arrival time is 0,
                ongoing += P[i];                              // The current time is now the time of the process burst
//            printf("\nProcess %d ends execution at : %d", ProcessNo[i], ongoing);       // Displays when each process finishes executing
            } else {                                          // If it is not the first process,
                if(A[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                    idleTime[i] += A[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                    allIdle += idleTime[i];               // Adds the idle time to the All idle variable
//                printf("\nIt became idle for %d second(s)", idleTime[i]);                // Displays the idle information
                    ongoing += idleTime[i] + P[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
//                printf("\nProcess %d ends execution at : %d", ProcessNo[i], ongoing);       // Displays when each process finishes executing
                } else if (A[i] <=ongoing){               // If there is no idle time
                    ongoing += P[i];                      // The time this process ends its execution will be the current time + process burst
//                printf("\nProcess %d ends execution at : %d", ProcessNo[i], ongoing);       // Displays when each process finishes executing
                }
            }

            if(i == 0){                                 // If it is the first process, the wt is 0.
                wt[i] = 0;
            } else {                                    // if it is not the first process
                if ((allIdle + executedProcess) <= A[i]) {      // If the current time is before the process arrives, wt = 0;
                    wt[i] = 0;
                } else if ((allIdle + executedProcess) > A[i]) {    // If the current time is more or equal to the arrival time
//                    printf("\n Hit. AllIdle : %d, Executed Processes: %d, Total %d", allidle, executedProcess, idleTime[i], allidle + executedProcess);
                    wt[i] = (allIdle + executedProcess) - A[i];     // The waiting time will be the current time - the arrival time.
                }
            }
            total += wt[i];
            // Total waiting time used to find average
        }
        avg_wt = (float) total / n;
        total = 0;                                                                              // Clears total time
//    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
        for (i = 0; i < n; i++) {
            tat[i] = P[i] + wt[i];                                                              // Finding turnaround time following formula Burst time + waiting time
            total += tat[i];                                                                    //Adds turnaround time to the total Turnaround time.
//        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo[i], P[i], wt[i], tat[i]);
        }
        avg_tat = (float) total / n;

        //clear common variables
        timePassed = 0;
        total = 0;

//    printf("\n\nSorted Based on K increases alternatively: ");
        for (i = 0; i < n; i++) {
            if (i == 0) {                                 //if it is the first process, dont need to sort anymore.
                timePassed += P2[i];                      // Allocate the CPU to the first process in the ready queue.
            } else {
                if (i != n - 1) {                               //if it is not the last process, perform sort
                    if (timePassed >= A2[i] &&
                        timePassed >= A2[i + 1]) { //checks if first and second process in the ready queue
                        if (k * P2[i] > timePassed + P2[i + 1]) {    //following paper algorithm
                            temp = P2[i];                        //Same concept as above using holder to store values temporarily
                            P2[i] = P2[i + 1];
                            P2[i + 1] = temp;

                            temp = ProcessNo2[i];                //Same concept
                            ProcessNo2[i] = ProcessNo2[i + 1];
                            ProcessNo2[i + 1] = temp;

                            temp = A2[i];                                //Use a holder to keep the value of Arrival Time
                            A2[i] = A2[i+1];                              //Assign new arrival time to the current position
                            A2[i+1] = temp;

                            timePassed += P2[i];                 //add the time passed
                        } else {
                            timePassed += P2[i];
                        }
                    } else if (timePassed >= A2[i]) {     //if only the first process is ready then execute.
                        timePassed += P2[i];
                    } else {                            //if none has arrived, take the remaining time and add it
                        timePassed = (A2[i] - timePassed) + P2[i];
                    }
                } else {                                //if it is the last process
                    timePassed += P2[i];
                }
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
        printf("\n");

        //clear variables
        int idleTime2[2000];
        ongoing = 0;
        executedProcess = 0;
        allIdle = 0;

        for(i = 0; i < n; i++){
            wt2[i] = 0;                                        // Clears all waiting time first.
            idleTime2[i] = 0;                                     // Clears all idle time first.
        }
        for (i = 0; i < n; i++) {                             // go through all the processes in the ready queue
            executedProcess += P2[i-1];                        // Saves the total process time that has been executed
            if (i == 0 && A2[i] > 0) {                         // If it is the first process AND the arrival time is more than 0 (meaning idle time)
                ongoing += (P2[i] + A2[i]);                     // Set the current ongoing time to Process burst + the arrival time
                idleTime2[i] += (ongoing - P2[i]);              // Get the idle time before the first process
                allIdle += idleTime2[i];                       // Adds it to the allIdle variable which stores all the idle times combined.
//            printf("\nIt became idle for %d second(s)", idleTime2[i]);                   // Displays the idle information
//            printf("\nProcess %d ends execution at : %d", ProcessNo2[i], ongoing);       // Displays when each process finishes executing

            } else if (i==0 && A2[i] == 0) {                   // If it is the first process and the arrival time is 0,
                ongoing += P2[i];                              // The current time is now the time of the process burst
//            printf("\nProcess %d ends execution at : %d", ProcessNo2[i], ongoing);       // Displays when each process finishes executing
            } else {                                          // If it is not the first process,
                if(A2[i] > ongoing){                       // If the arrival time is more than the time last process finishes executing,
                    idleTime2[i] += A2[i] - ongoing;        // Get the idle time which is the arrival - the ongoing
                    allIdle += idleTime2[i];               // Adds the idle time to the All idle variable
//                printf("\nIt became idle for %d second(s)", idleTime2[i]);                // Displays the idle information
                    ongoing += idleTime2[i] + P2[i];        // The time this process will finish executing will be the current time + idle time + the process burst time
//                printf("\nProcess %d ends execution at : %d", ProcessNo2[i], ongoing);       // Displays when each process finishes executing
                } else if (A2[i] <=ongoing){               // If there is no idle time
                    ongoing += P2[i];                      // The time this process ends its execution will be the current time + process burst
//                printf("\nProcess %d ends execution at : %d", ProcessNo2[i], ongoing);       // Displays when each process finishes executing
                }
            }

            if(i == 0){                                 // If it is the first process, the wt is 0.
                wt2[i] = 0;
            } else {                                    // if it is not the first process
                if ((allIdle + executedProcess) <= A2[i]) {      // If the current time is before the process arrives, wt = 0;
                    wt2[i] = 0;
                } else if ((allIdle + executedProcess) > A2[i]) {    // If the current time is more or equal to the arrival time
//                    printf("\n Hit. AllIdle : %d, Executed Processes: %d, Total %d", allidle, executedProcess, idleTime[i], allidle + executedProcess);
                    wt2[i] = (allIdle + executedProcess) - A2[i];     // The waiting time will be the current time - the arrival time.
                }
            }
            total += wt2[i];
            // Total waiting time used to find average
        }
        avg_wt2 = (float) total / n;
        total = 0;                                                                              // Clears total time
//    printf("\n\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
        for (i = 0; i < n; i++) {
            tat2[i] = P2[i] + wt2[i];                                                              // Finding turnaround time following formula Burst time + waiting time
            total += tat2[i];                                                                    //Adds turnaround time to the total Turnaround time.
//        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d", ProcessNo2[i], P2[i], wt2[i], tat2[i]);
        }
        avg_tat2 = (float) total / n;

        printf("=========================================================");
        printf("\n K-Factor Algorithm (K = 2) :");
        printf("\n=========================================================");
        printf("\n\nAverage Waiting Time = %.2f", avg_wt);
        printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

        printf("\n=========================================================");
        printf("\n K-Factor Algorithm (K Increases Alternatively) :");
        printf("\n=========================================================");
        printf("\n\nAverage Waiting Time = %.2f", avg_wt2);
        printf("\nAverage Turnaround Time = %.2f\n\n\n\n", avg_tat2);

        seed++;
    }
}

/// Input sanitization function used for all inputs.
int inputChecker(char input[20], char mode) {
    int i, n;
    int passed = 0;
    for (i = 0; i < strlen(input); i++) {    //Input error Handling
        if (input[0] == '\n') {               //If user just enters without any input \n = newline
            passed = 1;                       //trigger flag to do while loop.
            break;
        }
        if (isalnum(input[i]) == 0) {         //Check if it is alpha numeric.
            if (input[i] != '\n') {           //If it is a new line ignore as "fgets" uses it.
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
    if (mode == 3) {                                           // Mode 3 (Menu Selection)
        if (n < 1 || n > 7) {                                  // Only allows 1, 2 ,3 ,4, 5, 6, 7
            passed = 1;
        }
    } else if (mode == 1) {                                    // Mode 1 (No of Process Selection)
        if (n == 0 && mode == 1) {                             //if it adds up to 0 anyways, activate error handling.
            passed = 1;
        }

        if (n < 1 || n > 10000) {                               //IF it is not in the specified range
            passed = 1;
        }
    } else if (mode == 2) {                                     // Mode 2 (Arrival Times) cannot be negative.
        if (n < 0) {
            passed = 1;
        }
    } else if (mode == 4) {                                     // Mode 4 (Burst Times) burst times cannot be lesser than 1.
        if (n < 1) {
            passed = 1;
        }
    } else if (mode == 5) {                                      // Mode 5 (Redo algo Selection) Only 1 (try another algo) or 2 (exit)
        if (n < 1 || n > 2) {
            passed = 1;
        }
    }
    if (passed == 0) {
        return 0;
    } else {
        return 1;
    }

}
