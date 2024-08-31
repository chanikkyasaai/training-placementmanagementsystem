#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function declarations
void registerJob();
void registerCandidate();
void viewJobs();
void viewCandidates();
void applyJob();
void updateJob();
void deleteJob();
void updateCandidate();


//structure definitions
struct job {
    char title[50];
    char description[200];
    char category[20];
    int vacancies;
};

struct candidate {
    char name[50];
    char email[50];
    char category[20];
    char qualification[50];
};

int main() {
    int choice;
    while (1) {
        printf("\n\nTraining and Placement Management System\n");
        printf("1. Register a Job\n");
        printf("2. Register a Candidate\n");
        printf("3. View Jobs\n");
        printf("4. View Candidates\n");
        printf("5. Apply for a Job\n");
        printf("6. Update a Job\n");
        printf("7. Delete a Job\n");
        printf("8. Update Candidate Details\n");
        printf("9. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            registerJob();
            break;
        case 2:
            registerCandidate();
            break;
        case 3:
            viewJobs();
            break;
        case 4:
            viewCandidates();
            break;
        case 5:
            applyJob();
            break;
        case 6:
            updateJob();
            break;
        case 7:
            deleteJob();
            break;
        case 8:
            updateCandidate();
            break;
        case 9:
            printf("\nExiting the program...");
            exit(0);
            break;
        default:
            printf("\nInvalid choice! Please choose a valid option.");
        }
    }
    return 0;
}

void registerJob() {
    struct job j;
    printf("\n\nEnter the details of the job:\n");
    printf("Title: ");
    scanf(" %[^\n]", j.title);
    printf("Description: ");
    scanf(" %[^\n]", j.description);
    printf("Category: ");
    scanf(" %[^\n]", j.category);
    printf("Vacancies: ");
    scanf("%d", &j.vacancies);

    FILE* fptr;
    fptr = fopen("jobs.txt", "a");
    fprintf(fptr, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
    fclose(fptr);

    printf("\nJob registered successfully!");
}

void registerCandidate() {
    struct candidate c;
    printf("\n\nEnter your details:\n");
    printf("Name: ");
    scanf(" %[^\n]", c.name);
    printf("Email: ");
    scanf(" %[^\n]", c.email);
    printf("Category: ");
    scanf(" %[^\n]", c.category);
    printf("Qualification: ");
    scanf(" %[^\n]", c.qualification);

    FILE* fptr;
    fptr = fopen("candidates.txt", "a");
    fprintf(fptr, "%s %s %s %s\n", c.name, c.email, c.category, c.qualification);
    fclose(fptr);

    printf("\nCandidate registered successfully!");
}

void viewJobs() {
    FILE* fptr;
    char ch;

    printf("\n\nList of Jobs:\n");
    printf("Title\tDescription\tCategory\tVacancies\n");

    fptr = fopen("jobs.txt", "r");
    if (fptr == NULL) {
        printf("No jobs available!");
        return;
    }

    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }
    fclose(fptr);
}

void viewCandidates() {
    FILE* fptr;
    struct candidate c;

    printf("\n\nList of Candidates:\n");
    printf("Name\tEmail\tCategory\tQualification\n");

    fptr = fopen("candidates.txt", "r");
    if (fptr == NULL) {
        printf("No Candidates available!");
        return;
    }

    while (fscanf(fptr, " %[^\n]", c.name) != EOF) {
        printf("%s\n", c.name);
    }
    fclose(fptr);
}

void applyJob() {
    char jobTitle[50];
    char candidateEmail[50];
    printf("\n\nEnter the job title you want to apply for: ");
    scanf(" %[^\n]", jobTitle);
    printf("Enter your email: ");
    scanf(" %[^\n]", candidateEmail);

    FILE* jobFptr;
    jobFptr = fopen("jobs.txt", "r");
    if (jobFptr == NULL) {
        printf("\nError: Unable to open the jobs file!");
        return;
    }

    FILE* tempFptr;
    tempFptr = fopen("temp.txt", "w");
    if (tempFptr == NULL) {
        printf("\nError: Unable to open a temporary file!");
        fclose(jobFptr);
        return;
    }

    int flag = 0;
    struct job j;
    while (fscanf(jobFptr, "%s %s %s %d", j.title, j.description, j.category, &j.vacancies) != EOF) {
        if (strcmp(j.title, jobTitle) == 0) {
            flag = 1;
            if (j.vacancies == 0) {
                printf("\nSorry, there are no vacancies left for this job.");
                fclose(jobFptr);
                fclose(tempFptr);
                remove("temp.txt");
                return;
            }
            j.vacancies--;
            fprintf(tempFptr, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
            printf("\nYou have successfully applied for the job!");
        }
        else {
            fprintf(tempFptr, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
        }
    }

    if (flag == 0) {
        printf("\nJob title not found!");
    }

    fclose(jobFptr);
    fclose(tempFptr);
    remove("jobs.txt");
    rename("temp.txt", "jobs.txt");
}

void updateJob() {
    char jobTitle[50];
    printf("\n\nEnter the title of the job you want to update:");
        scanf(" %[^\n]", jobTitle);

    FILE* jobFptr;
    jobFptr = fopen("jobs.txt", "r");
    if (jobFptr == NULL) {
        printf("\nError: Unable to open the jobs file!");
        return;
    }

    FILE* tempFptr;
    tempFptr = fopen("temp.txt", "w");
    if (tempFptr == NULL) {
        printf("\nError: Unable to open a temporary file!");
        fclose(jobFptr);
        return;
    }

    int flag = 0;
    struct job j;
    while (fscanf(jobFptr, "%s %s %s %d", j.title, j.description, j.category, &j.vacancies) != EOF) {
        if (strcmp(j.title, jobTitle) == 0) {
            flag = 1;
            printf("\nEnter the updated details of the job:\n");
            printf("Title: ");
            scanf(" %[^\n]", j.title);
            printf("Description: ");
            scanf(" %[^\n]", j.description);
            printf("Category: ");
            scanf(" %[^\n]", j.category);
            printf("Vacancies: ");
            scanf("%d", &j.vacancies);
            fprintf(tempFptr, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
            printf("\nJob details updated successfully!");
        }
        else {
            fprintf(tempFptr, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
        }
    }

    if (flag == 0) {
        printf("\nJob title not found!");
    }

    fclose(jobFptr);
    fclose(tempFptr);
    remove("jobs.txt");
    rename("temp.txt", "jobs.txt");
}

void deleteJob() {
    char title[50];
    printf("\n\nEnter the title of the job to be deleted: ");
    scanf(" %[^\n]", title);

    FILE* fptr1;
    fptr1 = fopen("jobs.txt", "r");
    if (fptr1 == NULL) {
        printf("\nError: Unable to open the jobs file!");
        return;
    }

    FILE* fptr2;
    fptr2 = fopen("temp.txt", "w");
    if (fptr2 == NULL) {
        printf("\nError: Unable to open a temporary file!");
        fclose(fptr1);
        return;
    }

    int flag = 0;
    struct job j;

    while (fscanf(fptr1, "%s %s %s %d", j.title, j.description, j.category, &j.vacancies) != EOF) {
        if (strcmp(j.title, title) == 0) {
            flag = 1;
            printf("\nThe job has been deleted successfully!");
            continue;
        }
        fprintf(fptr2, "%s %s %s %d\n", j.title, j.description, j.category, j.vacancies);
    }

    if (flag == 0) {
        printf("\nError: Job not found!");
    }

    fclose(fptr1);
    fclose(fptr2);

    remove("jobs.txt");
    rename("temp.txt", "jobs.txt");
}

void updateCandidate() {
    char email[50];
    struct candidate c;

    printf("\n\nEnter the email of the candidate to be updated: ");
    scanf(" %[^\n]", email);

    FILE* fptr;
    FILE* fptr1;
    fptr = fopen("candidates.txt", "r");
    fptr1 = fopen("temp.txt", "w");

    int found = 0;
    while (fscanf(fptr, "%s %s %s %s", c.name, c.email, c.category, c.qualification) != EOF) {
        if (strcmp(c.email, email) == 0) {
            found = 1;
            printf("\n\nEnter the updated details:\n");
            printf("Name: ");
            scanf(" %[^\n]", c.name);
            printf("Email: ");
            scanf(" %[^\n]", c.email);
            printf("Category: ");
            scanf(" %[^\n]", c.category);
            printf("Qualification: ");
            scanf(" %[^\n]", c.qualification);

            fprintf(fptr1, "%s %s %s %s\n", c.name, c.email, c.category, c.qualification);

            printf("\nCandidate details updated successfully!");
        }
        else {
            fprintf(fptr1, "%s %s %s %s\n", c.name, c.email, c.category, c.qualification);
        }
    }
    fclose(fptr);
    fclose(fptr1);

    if (!found) {
        printf("\nCandidate with email '%s' not found!", email);
    }
}
