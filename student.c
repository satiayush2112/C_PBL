#include<stdio.h>
#include<stdlib.h>

struct Student {
    int id;
    char name[50];
    int room;
    float totalFee;
    float paidFee;
};
// ================= ADD STUDENT =================
void addStudent() {
   FILE *fp = fopen("data.txt","ab");
    struct Student s;

    if(fp == NULL) {
        printf("File error!\n");
        return;
    }
printf("ID: ");
scanf("%d",&s.id);

// clear buffer
int ch;
while((ch = getchar()) != '\n' && ch != EOF);

printf("Name: ");
scanf(" %[^\n]", s.name);

printf("Room: ");
scanf("%d",&s.room);

printf("Total Fee: ");
scanf("%f",&s.totalFee);

printf("Paid Fee: ");
scanf("%f",&s.paidFee);

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// ================= VIEW STUDENTS =================
void viewStudents() {
    FILE *fp = fopen("data.txt","rb");
    struct Student s;
    int choice, id, found = 0;

    if(fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\n1. View All Students\n");
    printf("2. Search by ID\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        // 🔹 Show all students

        printf("\n================ STUDENT RECORDS ================\n");
        printf("%-5s %-15s %-8s %-10s %-10s %-10s\n",
               "ID","Name","Room","Total","Paid","Remaining");
        printf("--------------------------------------------------------------\n");

        while(fread(&s,sizeof(s),1,fp)) {
            float remaining = s.totalFee - s.paidFee;

            printf("%-5d %-15s %-8d %-10.2f %-10.2f %-10.2f\n",
                   s.id, s.name, s.room,
                   s.totalFee, s.paidFee, remaining);
        }
    }
    else if(choice == 2) {
        // 🔹 Search by ID

        printf("Enter ID: ");
        scanf("%d", &id);

        while(fread(&s,sizeof(s),1,fp)) {
            if(s.id == id) {
                printf("\n================ STUDENT RECORD ================\n");
                printf("%-5s %-15s %-8s %-10s %-10s %-10s\n",
                       "ID","Name","Room","Total","Paid","Remaining");
                printf("--------------------------------------------------------------\n");

                float remaining = s.totalFee - s.paidFee;

                printf("%-5d %-15s %-8d %-10.2f %-10.2f %-10.2f\n",
                       s.id, s.name, s.room,
                       s.totalFee, s.paidFee, remaining);

                found = 1;
                break;
            }
        }

        if(!found)
            printf("Student not found!\n");
    }
    else {
        printf("Invalid choice!\n");
    }

    fclose(fp);
}
// ================= UPDATE FEE =================
void updateFee() {
    FILE *fp = fopen("data.txt","rb+");
    struct Student s;
    int id, found = 0;
    float amount;

    if(fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter ID to update fee: ");
    scanf("%d", &id);

    while(fread(&s,sizeof(s),1,fp)) {
        if(s.id == id) {
            printf("Enter amount to add: ");
            scanf("%f", &amount);

            s.paidFee += amount;

            if(s.paidFee > s.totalFee)
                s.paidFee = s.totalFee;

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s,sizeof(s),1,fp);

            printf("Fee updated successfully!\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Student not found!\n");
}

// ================= FEE REPORT =================
void feeReport() {
    FILE *fp = fopen("data.txt","rb");
    struct Student s;

    if(fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\n--- Pending Fees ---\n");

    while(fread(&s,sizeof(s),1,fp)) {
        float remaining = s.totalFee - s.paidFee;

        if(remaining > 0) {
            printf("%s -> Remaining: %.2f\n", s.name, remaining);
        }
    }

    fclose(fp);
}

// ================= UPDATE STUDENT =================
void updateStudent() {
    FILE *fp = fopen("data.txt", "rb+");
    struct Student s;
    int id, found = 0;

    if(fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("Enter new Name: ");
            scanf("%s", s.name);

            printf("Enter new Room: ");
            scanf("%d", &s.room);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("Updated Successfully!\n");
    else
        printf("Record Not Found!\n");
}

// ================= DELETE STUDENT =================
void deleteStudent() {
    FILE *fp = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Student s;
    int id, found = 0;

    if(fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");

    if(found)
        printf("Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
}

// ================= CLEAR FILE =================
void clearFile() {
    FILE *fp = fopen("data.txt", "w");
    fclose(fp);
    printf("All records cleared successfully!\n");
}