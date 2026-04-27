#include<stdio.h>

// 🔴 Function Prototypes (VERY IMPORTANT)
int login();

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void clearFile();
void updateFee();
void deleteStudent();
void checkAvailability();
void feeReport();
void showMenu() {
    printf("\n===== HOSTEL MANAGEMENT SYSTEM =====\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. Room Availability\n");
    printf("6. Fee Report\n");
    printf("7. Clear All Records\n");
    printf("8. Update Fee Payment\n");
    printf("0. Exit\n");
    printf("m. Show Menu Again\n");
}

int main() {
    char choice;
    if(!login()) return 0;
    showMenu();

    do {
    printf("\nEnter your choice: ");
    scanf(" %c", &choice);

        switch(choice) {
            case '0':printf("Exiting...\n");break;
            case '1': addStudent(); break;
            case '2': viewStudents(); break;
            case '3': updateStudent(); break;
            case '4': deleteStudent(); break;
            case '5': checkAvailability(); break;
            case '6': feeReport(); break;
            case '7': clearFile(); break;
            case '8': updateFee(); break;
            case 'm':
            case 'M':
                  showMenu();
                  break;
        }

    } while(choice != '0');

    return 0;
}