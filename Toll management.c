#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define SIZE 3

struct vehicle {
    char vehicle_no[20];
    char vehicle_type[20];
    char origin[20];
    char destination[20];
    char journey_typ[20];
    float price;
};

struct vehicle vh[SIZE];

void enqueue();
void dequeue();
void show_ticket(struct vehicle fr);
void gotoxy(int x, int y);

int rear = -1;
int front = -1;

int main() {
    gotoxy(10, 4);
    printf("<---- Expressway Toll Management System ---->");
    gotoxy(19, 6);
    printf("Press any key to continue...");
    getch();
    system("cls");

    int ch;
    while (1) {
        printf("\n\nWhat do you want to work on?\n");
        printf("\n1. Add a car to the waiting line\n2. Print ticket for the next car\n3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                exit(1);
            default:
                gotoxy(15, 10);
                printf("Enter valid choice! \n");
        }
        getch();
        system("cls");
    }
}

void enqueue() {
    system("cls");
    if (rear == SIZE - 1) {
        gotoxy(15, 6);
        printf("Toll Waiting Place is Full!\n");
        gotoxy(15, 8);
        printf("Press any key to continue...");
    } else {
        if (front == -1)
            front = 0;

        rear++;
        printf("\nEnter the vehicle number: ");
        scanf("%s", vh[rear].vehicle_no);
        system("cls");
        gotoxy(15, 6);
        printf("Vehicle Number [%s] is added to the toll waiting place", vh[rear].vehicle_no);
        gotoxy(15, 8);
        printf("Press any key to continue...");
    }
}

void dequeue() {
    int ch;
    float price = 200;
    system("cls");

    while (1) {
        if (front == -1 || front > rear) {
            gotoxy(15, 6);
            printf("There is no car present \n");
            gotoxy(15, 8);
            printf("Press any key to continue...");
            break;
        } else {
            printf("\nWhat is type of the vehicle?");
            printf("\n1.Car\n2.Bus\n3.Truck\n\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);

            if (ch == 1)
                strcpy(vh[front].vehicle_type, "Car");
            else if (ch == 2) {
                strcpy(vh[front].vehicle_type, "Bus");
                price *= 1.5;
            } else if (ch == 3) {
                strcpy(vh[front].vehicle_type, "Truck");
                price *= 2;
            } else {
                printf("Enter valid choice");
                break;
            }

            printf("\nEnter destination: ");
            printf("\n1.Mumbai\n2.Surat\n3.Bharuch\n\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);

            if (ch == 1)
                strcpy(vh[front].destination, "Mumbai");
            else if (ch == 2) {
                strcpy(vh[front].destination, "Surat");
                price *= 0.75;
            } else if (ch == 3) {
                strcpy(vh[front].destination, "Bharuch");
                price *= 0.5;
            } else {
                printf("Enter valid choice ");
                break;
            }

            printf("\nEnter journey type: ");
            printf("\n1.Single journey\n2.Return journey\n\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);

            if (ch == 1)
                strcpy(vh[front].journey_typ, "Single journey");
            else if (ch == 2) {
                strcpy(vh[front].journey_typ, "Return journey");
                price *= 1.8;
            } else {
                printf("Enter valid choice");
                break;
            }

            vh[front].price = price;
            system("cls");

            show_ticket(vh[front]);

            gotoxy(55, 5);
            printf("Do you want to print this ticket?");
            gotoxy(55, 6);
            printf("1.Yes");
            gotoxy(55, 7);
            printf("2.No");
            gotoxy(55, 9);
            printf("Enter your choice: ");
            gotoxy(75, 9);
            scanf("%d", &ch);
            system("cls");

            if (ch == 1) {
                FILE *fp = fopen("ticket.txt", "w");
                if (fp == NULL) {
                    gotoxy(10, 5);
                    printf("Error while printing the ticket");
                } else {
                    fwrite(&vh[front], sizeof(vh[front]), 1, fp);
                    fclose(fp);
                    gotoxy(10, 5);
                    printf("Ticket printed successfully!");
                    gotoxy(10, 7);
                    printf("Press any key to continue...!");
                }
            } else if (ch == 2) {
                gotoxy(10, 5);
                printf("Ticket is cancelled!");
                printf("Press any key to continue...!");
            }

            front++;
            break;
        }
    }
}

void show_ticket(struct vehicle fr) {
    time_t t;
    time(&t);
    strcpy(fr.origin, "Ahemdabad");

    gotoxy(10, 4);
    printf("AHEMDABAD EXPRESS WAYS INDUSTRIAL AND");
    gotoxy(17, 6);
    printf("DEVELOPMENT AUTHORITY");
    gotoxy(10, 7);
    printf("--------------------------");
    gotoxy(15, 8);
    printf("From %s to %s", fr.origin, fr.destination);

    gotoxy(10, 10);
    printf("Ticket No");
    gotoxy(22, 10);
    printf(": %d", rand());

    gotoxy(10, 12);
    printf("Date and Time");
    gotoxy(22, 12);
    printf(": %s", ctime(&t));

    gotoxy(10, 14);
    printf("Vehicle No");
    gotoxy(22, 14);
    printf(": %s", fr.vehicle_no);

    gotoxy(10, 16);
    printf("Type of Vehicle");
    gotoxy(22, 16);
    printf(": %s", fr.vehicle_type);

    gotoxy(10, 18);
    printf("Type of Journey");
    gotoxy(22, 18);
    printf(": %s", fr.journey_typ);

    gotoxy(10, 20);
    printf("Fees");
    gotoxy(22, 20);
    printf(": Rs. %.2f", fr.price);
    gotoxy(10, 21);
    printf("-------------------");

    gotoxy(17, 24);
    printf("Speed Limit 100 KMH");
    gotoxy(13, 25);
    printf("For Emergency Call 1800-123-3127");
    gotoxy(19, 27);
    printf("Safe Journey!");
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

