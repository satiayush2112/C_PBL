#include<stdio.h>

struct Student {
    int id;
    char name[50];
    int room;
    float totalFee;
    float paidFee;
};
void checkAvailability() {
    FILE *fp = fopen("data.txt", "rb");   // use binary mode
    struct Student s;

    int rooms[101] = {0};   // all rooms initially free

    if(fp == NULL) {
        printf("No data available!\n");
        return;
    }

    // 🔹 Read ALL students properly
    while(fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if(s.room >= 1 && s.room <= 100) {
            rooms[s.room] = 1;   // mark occupied
        }
    }

    fclose(fp);

    printf("\n========= ROOM STATUS =========\n");

    // 🔹 Display result
    for(int i = 1; i <= 10; i++) {
        if(rooms[i] == 1)
            printf("Room %d : Occupied\n", i);
        else
            printf("Room %d : Available\n", i);
    }
}