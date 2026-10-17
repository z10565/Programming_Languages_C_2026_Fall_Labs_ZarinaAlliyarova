// week5_task4_struct_binary_io.c   (BONUS)
// Name: Zarina  Surname: Alliyarova Student ID: 251ADB103
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

int save_student_binary(const Student* s, const char* filename);
int load_student_binary(const char* filename, Student* out);
long file_size(const char* filename);

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;
  Student loaded = {0};
  const char* bin_file = "student.bin";
  const char* txt_file = "student.txt";

  printf("Saving student in binary format...\n");
  if (save_student_binary(&s1, bin_file) != 0) {
    fprintf(stderr, "Failed to save binary student.\n");
    return EXIT_FAILURE;
  }

  FILE* fp = fopen(txt_file, "w");
  if (fp == NULL) {
    perror(txt_file);
    return EXIT_FAILURE;
  }
  int write_ok = fprintf(fp, "%s %d %.2f\n", s1.name, s1.age, s1.gpa) >= 0;
  int close_ok = fclose(fp) != EOF;
  if (!write_ok || !close_ok) {
    fprintf(stderr, "Failed to save text student.\n");
    return EXIT_FAILURE;
  }

  printf("Loading student from binary file...\n");
  if (load_student_binary(bin_file, &loaded) != 0) {
    fprintf(stderr, "Failed to load binary student.\n");
    return EXIT_FAILURE;
  }
  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);
  long text_bytes = file_size(txt_file);
  long binary_bytes = file_size(bin_file);
  if (text_bytes < 0 || binary_bytes < 0) {
    fprintf(stderr, "Failed to determine file sizes.\n");
    return EXIT_FAILURE;
  }
  printf("Text file size: %ld bytes\n", text_bytes);
  printf("Binary file size: %ld bytes\n", binary_bytes);
  return EXIT_SUCCESS;
}

int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) return -1;
  size_t written = fwrite(s, sizeof(Student), 1, fp);
  int closed = fclose(fp);
  return (written == 1 && closed != EOF) ? 0 : -1;
}

int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;
  size_t read = fread(out, sizeof(Student), 1, fp);
  int closed = fclose(fp);
  return (read == 1 && closed != EOF) ? 0 : -1;
}

long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) return -1;
  if (fseek(fp, 0, SEEK_END) != 0) {
    fclose(fp);
    return -1;
  }
  long size = ftell(fp);
  if (fclose(fp) == EOF) return -1;
  return size;
}
