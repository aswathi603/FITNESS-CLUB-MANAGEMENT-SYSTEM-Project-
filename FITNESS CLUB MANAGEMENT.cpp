#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Structure to store customer details
struct customer {
    char name[50];
    char mobile[11];
    float bmi;
    char address[100];
    char package[20];
    char join_date[11];
    int train_period;
};

// Function to add customer record to file
void add_record() {
    struct customer c;
    FILE *f;
    f = fopen("customers.dat", "ab+");
    if (f == NULL) {
        printf("Error in opening file!");
        exit(1);
    }
    printf("\nEnter name: ");
    scanf("%s", c.name);
    printf("\nEnter mobile number: ");
    scanf("%s", c.mobile);
    printf("\nEnter BMI: ");
    scanf("%f", &c.bmi);
    printf("\nEnter address: ");
    scanf("%s", c.address);
    printf("\nEnter package details: ");
    scanf("%s", c.package);
    printf("\nEnter joining date (DD/MM/YYYY): ");
    scanf("%s", c.join_date);
    printf("\nEnter training period (in months): ");
    scanf("%d", &c.train_period);
    fwrite(&c, sizeof(c), 1, f);
    printf("\nRecord added successfully!\n");
    fclose(f);
}

// Function to delete customer record from file
void delete_record() {
    char mobile[11];
    int found = 0;
    struct customer c;
    FILE *f, *t;
    f = fopen("customers.dat", "rb");
    if (f == NULL) {
        printf("Error in opening file!");
        exit(1);
    }
    t = fopen("temp.dat", "wb");
    if (t == NULL) {
        printf("Error in opening file!");
        fclose(f);
        exit(1);
    }
    printf("Enter mobile number of customer to be deleted: ");
    scanf("%s", mobile);
    while (fread(&c, sizeof(c), 1, f) == 1) {
        if (strcmp(c.mobile, mobile) != 0)
            fwrite(&c, sizeof(c), 1, t);
        else
            found = 1;
    }
    if (found == 1)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
    fclose(f);
    fclose(t);
    remove("customers.dat");
    rename("temp.dat", "customers.dat");
}

// Function to display all customer records from file
void display_records() {
    struct customer c;
    FILE *f;
    f = fopen("customers.dat", "rb");
    if (f == NULL) {
        printf("Error in opening file!");
        exit(1);
    }
    while (fread(&c, sizeof(c), 1, f) == 1) {
        printf("Name: %s\nMobile Number: %s\nBMI: %f\nAddress: %s\nPackage Details: %s\nJoining Date: %s\nTraining Period: %d months\n\n", c.name, c.mobile, c.bmi, c.address, c.package, c.join_date, c.train_period);
    }
    fclose(f);
}

// Function to search for customer record by mobile number, name, or id
void search_record() {
    char search_query[50];
    int found = 0;
    struct customer c;
    FILE *f;
    f = fopen("customers.dat", "rb");
    if (f == NULL) {
        printf("Error in opening file!");
        exit(1);
   
}
printf("Enter mobile number, name to search: ");
scanf("%s", search_query);
while (fread(&c, sizeof(c), 1, f) == 1) {
    if (strcmp(c.mobile, search_query) == 0 || strcmp(c.name, search_query) == 0) {
        printf("Name: %s\t\nMobile Number: %s\t\nBMI: %f\t\nAddress: %s\t\nPackage Details: %s\t\nJoining Date: %s\t\nTraining Period: %dmonths\n", c.name, c.mobile, c.bmi, c.address, c.package, c.join_date, c.train_period);
        found = 1;
    }
}
if (found == 0)
    printf("Record not found!\n");
fclose(f);
}

// Function to display available slots and let user select one
void select_slot() {
int slots[5] = {0, 0, 0, 0, 0};
int slot, found = 0;
struct customer c;
FILE *f;
f = fopen("customers.dat", "rb");
if (f == NULL) {
printf("Error in opening file!");
exit(1);
}
while (fread(&c, sizeof(c), 1, f) == 1) {
if (c.train_period > 6 && c.train_period <= 12) {
if (strcmp(c.join_date, "01/01/2023") == 0) {
slots[0] = 1;
}
else if (strcmp(c.join_date, "01/02/2023") == 0) {
slots[1] = 1;
}
else if (strcmp(c.join_date, "01/03/2023") == 0) {
slots[2] = 1;
}
else if (strcmp(c.join_date, "01/04/2023") == 0) {
slots[3] = 1;
}
else if (strcmp(c.join_date, "01/05/2023") == 0) {
slots[4] = 1;
}
}
}
printf("Available slots:\n");
for (int i = 0; i < 5; i++) {
if (slots[i] == 0) {
printf("%d. 01/%02d/2023\n", i+1, i+1);
found = 1;
}
}
if (found == 0) {
printf("No slots available!\n");
return;
}
printf("Enter slot number: ");
scanf("%d", &slot);
if (slots[slot-1] == 1) {
printf("Slot already booked!\n");
return;
}
printf("Slot booked successfully!\n");
fclose(f);
}

int main() {
int choice;
while (1) {
printf("Fitness Club Management System\n");
printf("1. Add customer record to file\n2. Delete customer record from file\n3. Display all customer records\n4. Search for customer record\n5. Select slot\n6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
		case 1:
			add_record();
			break;
		case 2:
			delete_record();
			break;
		case 3:
			display_records();
			break;
		case 4:
			search_record();
			break;
		case 5:
			select_slot();
        case 6:
            exit(0);
        default:
            printf("Invalid choice!\n");
    }
}
return 0;
}
