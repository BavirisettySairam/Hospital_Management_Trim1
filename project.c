#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Hospital {
    char name[50];
    char city[50];
    int beds;
    float price;
    float rating;
    int reviews;
};

struct Doctor {
    char name[50];
    char specialization[50];
    int experience;
};

struct Patient {
    char name[50];
    int age;
    char disease[50];
};

struct Booking {
    char patientName[50];
    char doctorName[50];
};
void writeHospitalToFile(struct Hospital hosp) {
    FILE *file = fopen("hospital_data.txt", "w");
    if (file == NULL) {
        printf("Error opening hospital file!\n");
        return;
    }
    fprintf(file, "%s\n%s\n%d\n%.2f\n%.1f\n%d\n", hosp.name, hosp.city, hosp.beds, hosp.price, hosp.rating, hosp.reviews);
    fclose(file);
    printf("Hospital data saved to file.\n");
}

void readHospitalFromFile(struct Hospital *hosp) {
    FILE *file = fopen("hospital_data.txt", "r");
    if (file == NULL) {
        printf("No hospital data found.\n");
        return;
    }
    fscanf(file, "%[^\n]\n%[^\n]\n%d\n%f\n%f\n%d\n", hosp->name, hosp->city, &hosp->beds, &hosp->price, &hosp->rating, &hosp->reviews);
    fclose(file);
}

void writeDoctorToFile(struct Doctor doc) {
    FILE *file = fopen("doctor_data.txt", "a");
    if (file == NULL) {
        printf("Error opening doctor file!\n");
        return;
    }
    fprintf(file, "%s\n%s\n%d\n", doc.name, doc.specialization, doc.experience);
    fclose(file);
    printf("Doctor data saved to file.\n");
}

void searchDoctorByName(char *name) {
    struct Doctor doc;
    FILE *file = fopen("doctor_data.txt", "r");
    int found = 0;

    if (file == NULL) {
        printf("No doctor data found.\n");
        return;
    }

    while (fscanf(file, "%[^\n]\n%[^\n]\n%d\n", doc.name, doc.specialization, &doc.experience) != EOF) {
        if (strcmp(doc.name, name) == 0) {
            printf("\nDoctor Found:\n");
            printf("Name: %s\nSpecialization: %s\nExperience: %d years\n", doc.name, doc.specialization, doc.experience);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No doctor found with the name '%s'.\n", name);
    }

    fclose(file);
}

void viewAllDoctors() {
    struct Doctor doc;
    FILE *file = fopen("doctor_data.txt", "r");
    if (file == NULL) {
        printf("No doctor data found.\n");
        return;
    }
    printf("\nDoctors Data from File:\n");
    printf("+------------------------------+-----------------------------+--------------------+\n");
    printf("| Name                         | Specialization              | Experience (years) |\n");
    printf("+------------------------------+-----------------------------+--------------------+\n");
    while (fscanf(file, "%[^\n]\n%[^\n]\n%d\n", doc.name, doc.specialization, &doc.experience) != EOF) {
        printf("| %-28s | %-27s | %-18d |\n", doc.name, doc.specialization, doc.experience);
    }
    printf("+------------------------------+-----------------------------+--------------------+\n");
    fclose(file);
}

void writePatientToFile(struct Patient pat) {
    FILE *file = fopen("patient_data.txt", "a");
    if (file == NULL) {
        printf("Error opening patient file!\n");
        return;
    }
    fprintf(file, "%s\n%d\n%s\n", pat.name, pat.age, pat.disease);
    fclose(file);
    printf("Patient data saved to file.\n");
}
void viewAllPatients() {
    struct Patient pat;
    FILE *file = fopen("patient_data.txt", "r");
    if (file == NULL) {
        printf("No patient data found.\n");
        return;
    }
    printf("\nPatients Data from File:\n");
    printf("+------------------------------+-----+-----------------------------+\n");
    printf("| Name                         | Age | Disease                     |\n");
    printf("+------------------------------+-----+-----------------------------+\n");
    while (fscanf(file, "%[^\n]\n%d\n%[^\n]\n", pat.name, &pat.age, pat.disease) != EOF) {
        printf("| %-28s | %-3d | %-27s |\n", pat.name, pat.age, pat.disease);
    }
    printf("+------------------------------+-----+-----------------------------+\n");
    fclose(file);
}

struct Hospital inputHospitalData() {
    struct Hospital hosp;
    printf("Enter Hospital Name: ");
    scanf(" %[^\n]", hosp.name);
    printf("Enter City: ");
    scanf(" %[^\n]", hosp.city);
    printf("Enter Total Beds: ");
    scanf("%d", &hosp.beds);
    printf("Enter Price per Bed: ");
    scanf("%f", &hosp.price);
    printf("Enter Rating (out of 5): ");
    scanf("%f", &hosp.rating);
    printf("Enter Number of Reviews: ");
    scanf("%d", &hosp.reviews);
    return hosp;
}

struct Doctor inputDoctorData() {
    struct Doctor doc;
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", doc.name);
    printf("Enter Specialization: ");
    scanf(" %[^\n]", doc.specialization);
    printf("Enter Years of Experience: ");
    scanf("%d", &doc.experience);
    return doc;
}

struct Patient inputPatientData() {
    struct Patient pat;
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", pat.name);
    printf("Enter Age: ");
    scanf("%d", &pat.age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", pat.disease);
    return pat;
}

void manageHospitals() {
    int sub_choice;
    struct Hospital hospital;
    
    do {
        printf("\nHospital Management Menu:\n");
        printf("1. Add Hospital\n");
        printf("2. View Hospital Details\n");
        printf("3. Return to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &sub_choice);
        
        switch (sub_choice) {
            case 1:
                hospital = inputHospitalData();
                writeHospitalToFile(hospital);
                break;
            case 2:
                readHospitalFromFile(&hospital);
                printf("\nHospital Data:\n");
                printf("+------------------------------+-----------------------------+-------------+-----------+--------+---------+\n");
                printf("| Name                         | City                        | Total Beds | Price/Bed | Rating | Reviews |\n");
                printf("+------------------------------+-----------------------------+-------------+-----------+--------+---------+\n");
                printf("| %-28s | %-27s | %-11d | $%-8.2f | %-6.1f | %-7d |\n",
                       hospital.name, hospital.city, hospital.beds, hospital.price, hospital.rating, hospital.reviews);
                printf("+------------------------------+-----------------------------+-------------+-----------+--------+---------+\n");
                break;
            case 3:
                printf("Returning to Admin Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (sub_choice != 3);
}

void addDoctor() {
    struct Doctor doc = inputDoctorData();
    writeDoctorToFile(doc);
}

void adminMenu() {
    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. View All Doctors\n");
        printf("2. View All Patients\n");
        printf("3. Manage Hospitals\n");
        printf("4. Add Doctor\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllDoctors();
                break;
            case 2:
                viewAllPatients();
                break;
            case 3:
                manageHospitals();
                break;
            case 4:
                addDoctor();
                break;
            case 5:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void doctorMenu() {
    int choice;
    do {
        printf("\nDoctor Menu:\n");
        printf("1. View Patient Bookings\n");
        printf("2. View All Patients\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                
                break;
            case 2:
                viewAllPatients();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void patientMenu() {
    int choice;
    struct Hospital hosp;
    do {
        printf("\nPatient Menu:\n");
        printf("1. Book a Doctor\n");
        printf("2. View Doctors\n");
        printf("3. View Hospital Details\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
               
                break;
            case 2:
                viewAllDoctors();
                break;
            case 3:
                readHospitalFromFile(&hosp);
                printf("\nHospital Details:\n");
                printf("Name: %s\nCity: %s\nBeds: %d\nPrice per Bed: %.2f\nRating: %.1f\nReviews: %d\n", 
                       hosp.name, hosp.city, hosp.beds, hosp.price, hosp.rating, hosp.reviews);
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

int main() {
    int role;
    do {
        printf("\nMain Menu:\n");
        printf("1. Admin\n");
        printf("2. Doctor\n");
        printf("3. Patient\n");
        printf("4. Exit\n");
        printf("Enter your role: ");
        scanf("%d", &role);

        switch (role) {
            case 1:
                adminMenu();
                break;
            case 2:
                doctorMenu();
                break;
            case 3:
                patientMenu();
                break;
            case 4:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid role selected! Please try again.\n");
        }
    } while (role != 4);

    return 0;
}
