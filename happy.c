#include <stdio.h>

#define NUM_CLASSES 7
#define NUM_COMPONENTS 4
#define MAX_STUDENTS 10  

void inputMarks(float marks[][NUM_CLASSES][NUM_COMPONENTS], int numStudents, const char *classNames[]);
float calculateOverallAverage(float marks[][NUM_CLASSES][NUM_COMPONENTS], int studentIndex);
void displayResults(float averages[], int numStudents);
void checkResults(float averages[], int numStudents, float marks[][NUM_CLASSES][NUM_COMPONENTS], const char *classNames[]);

int main() {
    int numStudents;
    float studentMarks[MAX_STUDENTS][NUM_CLASSES][NUM_COMPONENTS];
    float averages[MAX_STUDENTS];

    printf("Enter the number of students: ");
    scanf("%d", &numStudents);

    const char *classNames[NUM_CLASSES] = {
        "Analyse 2",
        "Algebre 2",
        "Algorithm and Data Structure 2",
        "Système d'Exploitation",
        "Probability and Statistics",
        "Computer Science",
        "Logic Mathematics"
    };

    inputMarks(studentMarks, numStudents, classNames);

    for (int i = 0; i < numStudents; i++) {
        averages[i] = calculateOverallAverage(studentMarks, i);
    }

    displayResults(averages, numStudents);

    checkResults(averages, numStudents, studentMarks, classNames);

    return 0;
}

void inputMarks(float marks[][NUM_CLASSES][NUM_COMPONENTS], int numStudents, const char *classNames[]) {
    for (int i = 0; i < numStudents; i++) {
        printf("Enter marks for student %d:\n", i + 1);
        for (int j = 0; j < NUM_CLASSES; j++) {
            printf("%s:\n", classNames[j]);
            for (int k = 0; k < NUM_COMPONENTS; k++) {
                do {
                    switch(k) {
                        case 0:
                            printf("   TD: ");
                            break;
                        case 1:
                            printf("   TP: ");
                            break;
                        case 2:
                            printf("   Quiz: ");
                            break;
                        case 3:
                            printf("   Exam: ");
                            break;
                    }

                    if (scanf("%f", &marks[i][j][k]) != 1 || marks[i][j][k] < 0 || marks[i][j][k] > 20) {
                        printf("   Invalid input! Please enter a valid mark between 0 and 20.\n");
                        while (getchar() != '\n');
                    } else {
                        break;
                    }
                } while (1);
            }
        }
    }
}

float calculateOverallAverage(float marks[][NUM_CLASSES][NUM_COMPONENTS], int studentIndex) {
    float sum = 0.0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        for (int j = 0; j < NUM_COMPONENTS; j++) {
            sum += marks[studentIndex][i][j];
        }
    }
    return sum / (NUM_CLASSES * NUM_COMPONENTS);
}

void displayResults(float averages[], int numStudents) {
    printf("\nOverall Averages:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student %d - Average: %.2f\n", i + 1, averages[i]);
    }
}

void checkResults(float averages[], int numStudents, float marks[][NUM_CLASSES][NUM_COMPONENTS], const char *classNames[]) {
    printf("\nResults Summary:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student %d - ", i + 1);
        if (averages[i] >= 10.0) {
            printf("Congratulations on your success!\n");
        } else {
            printf("Remediation Exam is needed. Therapeutic test required for improvement in:\n");
            for (int j = 0; j < NUM_CLASSES; j++) {
                float classAverage = 0.0;
                for (int k = 0; k < NUM_COMPONENTS; k++) {
                    classAverage += marks[i][j][k];
                }
                classAverage /= NUM_COMPONENTS;

                if (classAverage < 10.0) {
                    printf("   - %s\n", classNames[j]);
                }
            }
        }
    }
}
