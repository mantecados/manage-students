#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct representing a student with a name, array of grades and grade count
typedef struct {
  char* name;
  float* grades;
  int gradeCount;
} Student;

/*
 * Allocates memory for students and prompts the user to enter names and valid grades
 * Params:
 *   - studentCount: number of students to register
 *   - gradeCount: number of grades per student
 * Returns:
 *   - Pointer to dynamically allocated array of Student structs
 */

Student* addStudents(int studentCount, int gradeCount) {
  Student* students = malloc(sizeof(Student) * studentCount);

  for (int i = 0; i < studentCount; i++) {
    // Flush input buffer before reading name
    while (getchar() != '\n');

    // Allocate memory for name and grades
    students[i].name = malloc(100);
    students[i].grades = malloc(sizeof(float) * gradeCount);
    students[i].gradeCount = gradeCount;

    // Prompt for student's name
    printf("Student %d\n",i+1);
    printf("------------\n");

    char buffer[100];
    printf("Name: ");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")] = '\0'; // Remove trailing newline
    strcpy(students[i].name,buffer);
    printf("\n");

    // Prompt for grades with input validation
    for (int j = 0; j < gradeCount; j++) {
      float grade;
      int valid = 0;

      // Loop until user provides a valid grade between 0 and 10
      while (!valid) {
        printf("Grade %d (0-10): ",j + 1);

        //Check if input is a float and withing the allowed range
        if (scanf("%f",&grade) == 1 && grade >= 0 && grade <= 10) {
          students[i].grades[j] = grade;
          valid = 1;
        } else {
          printf("Invalid grade. Number must be between 1 and 10\n\n");

          // Clear invalid input from buffer
          while (getchar() != '\n');
        }
      }
    }
    system("cls"); // Clear screen after each student
  }

  return students;
}

/*
 * printStudents:
 * Displays all registered students and their grades with averages
 * Params:
 *    - students: pointer to the array of students
 *    - studentCount: number of students
 *    - gradeCount: number of grades per student
 */ 
void printStudents(Student* students, int studentCount, int gradeCount) {

  for (int i = 0; i < studentCount; i++) {
    printf("%s (Student %d) \n",students[i].name,i+1);
    printf("-------------------\n");

    // Print individual grades
    for (int j = 0; j < students[i].gradeCount; j++) {
      printf("Grade %d = %.2f\n", j+1, students[i].grades[j]);
    }

    // Calculate and print average
    float sum = 0;
    for (int j = 0; j < students[i].gradeCount; j++) {
    sum += students[i].grades[j];
    }
    float avg = sum / students[i].gradeCount;
    printf("\nAverage = %.2f\n\n", avg);
  }

  system("pause");
  system("cls");
}
/* 
 * freeStudents:
 * Frees all dynamically allocated memory for students
 * Params:
 *    - students: pointer to array of students
 *    - studentCount: number of students
 *    - gradeCount: unused, but kept for compatibility
 */
void freeStudents(Student* students, int studentCount, int gradeCount) {
  for (int i = 0; i < studentCount; i++) {
    free(students[i].name);
    free(students[i].grades);
  }
}

// ============================================
// MAIN FUNCTION: Entry point of the program
// ============================================
int main() {

  Student* students = NULL;
  int studentCount = 0;
  int gradeCount = 0;

  while (1) {
    int option;

    // Menu
    printf("Register students\n");
    printf("-----------------\n");
    printf("1. Add students\n");
    printf("2. See students\n");
    printf("3. Exit\n\n");

    printf("Option: ");
    scanf("%d",&option);
    system("cls");

    switch (option) {
      case 1:
        // Free memory before adding new students
        if (students != NULL) {
          freeStudents(students,studentCount, gradeCount);
        }
      
        // Get student and grade counts
        printf("Number of students: ");
        scanf("%d",&studentCount);
        if (studentCount > 9) {
          printf("Te vas a tirar hasta mañana miarma\n\n");
        }
    
        printf("Number of grades per student: ");
        scanf("%d",&gradeCount);
        if (gradeCount > 9) {
          printf("Tu ta loco\n");
        }
        printf("\n");
        system("pause");
        system("cls");
        
        // Add students
        students = addStudents(studentCount, gradeCount);
      break;
      
      case 2:
        //  Print registered students or warning if none
        if (students != NULL) {
          printStudents(students,studentCount,gradeCount);
        } else {
        printf("No students registered yet.\n\n");
        system("pause");
        system("cls");
        }
      break;

      case 3:
        // Free memory on exit
        if (students != NULL) {
         freeStudents(students, studentCount, gradeCount);
        }
        return 0;
      break;

      default:
      // Handle invalid option
       system("cls");
       printf("Invalid option");
       system("pause");
      break;
    }
  }
  return 0;
}