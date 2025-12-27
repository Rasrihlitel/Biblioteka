#define _CRT_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

struct Person {
	char name[20];
	char surname[20];
	int age;
	int year;
};

void hello() {
	printf("0. Выход\n");
	printf("1. Загрузка файла\n");
	printf("2. Вывод таблицы\n");
	printf("3. Поиск человека\n");
	printf("4. Добавить человека\n");
	printf("5. Сохранение\n");
	printf("6. Удаление\n");
	printf("Ваш выбор: ");
}

struct Person* read(int* size, const char* fname) {
	FILE* f = fopen(fname, "r");
	fscanf_s(f, "%d", size);
	struct Person* res = (struct Person*)malloc(sizeof(struct Person) * (*size));
	if (res == NULL) {
		return NULL;
	}
	for (int i = 0; i < (*size); i++) {
		fscanf_s(f, "%s", res[i].surname, (unsigned)sizeof(res[i].surname));
		fscanf_s(f, "%s", res[i].name, (unsigned)sizeof(res[i].name));
		fscanf_s(f, "%d", &(res[i].age));
		fscanf_s(f, "%d", &(res[i].year));
	}
	fclose(f);
	return res;
}

void tabs(struct Person* persons, int size, int s) {
	for (int i = 0; i < (size - 3 + s) ; i++) {
		printf("--------------------\n");
		printf("Человек %d\n", i + 1);
		printf("Фамилия: %s\n", persons[i].surname);
		printf("Имя: %s\n", persons[i].name);
		printf("Возраст: %d\n", persons[i].age);
		printf("Год рождения: %d\n", persons[i].year);
	}
	printf("--------------------\n");
}

int search(struct Person* persons, int size, char* str) {
	int res = -1;
	for (int i = 0; i < size; i++) {
		if (strcmp(persons[i].surname, str) == 0) {
			res = i;
		}
	}
	return res;
}

void add(struct Person* persons, int size, int* s) {
	while (getchar() != '\n');
	printf("Введите фамилию: ");
	fgets(persons[10 + (*s)].surname, sizeof(persons[10 + (*s)].surname), stdin);
	persons[10 + (*s)].surname[strcspn(persons[10 + (*s)].surname, "\n")] = '\0';
	printf("Введите имя: ");
	fgets(persons[10 + (*s)].name, sizeof(persons[10 + (*s)].name), stdin);
	persons[10 + (*s)].name[strcspn(persons[10 + (*s)].name, "\n")] = '\0';
	printf("Введите возраст: ");
	scanf_s("%d", &(persons[10 + (*s)].age));
	printf("Введите год рождения: ");
	scanf_s("%d", &(persons[10 + (*s)].year));
	(*s)++;
}

void save(struct Person* persons, int size, const char* fname) {
	FILE* f = fopen(fname, "w");
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++) {
		fputs(persons[i].surname, f);
		fprintf(f, "\n");
		fputs(persons[i].name, f);
		fprintf(f, "\n");
		fprintf(f, "%d\n", persons[i].age);
		fprintf(f, "%d\n", persons[i].year);
	}
	fclose(f);
}

void delete(struct Person* persons, int size, char* fam, int*s) {
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(persons[i].surname, fam) == 0) {
			j = i;
		}
	}
	for (int i = j; i < size - 1; i++) {
		persons[i] = persons[i + 1];
	}
	(*s)--;
}

int main() {
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "Rus");
	int code, turn, size, res, s = 0, flag = 0;
	char str[20];
	char fam[20];
	struct Person* persons = NULL;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
		case 0: break;
		case 1:
			flag = 1;
			persons = read(&size, "D:\\prog\\Persons.txt");
			tabs(persons, size, s);
			break;

		case 2:
			if (flag == 0) { printf("Сначала необходимо загрузить файл\n"); break; }
			tabs(persons, size, s);
			break;

		case 3:
			if (flag == 0) { printf("Сначала необходимо загрузить файл\n"); break; }
			while (getchar() != '\n');
			printf("Введите фамилию человека, которого хотите найти: ");
			fgets(str, sizeof(str), stdin);
			str[strcspn(str, "\n")] = '\0';
			res = search(persons, size, str);
			if (res == -1) printf("Человека с такой фамилией нет в списке\n");
			else printf("Человек с такой фамилией находится на %d позиции в списке\n", res + 1);
			break;

		case 4: 
			if (flag == 0) { printf("Сначала необходимо загрузить файл\n"); break; }
			if (s == 3) { printf("Больше нельзя добавить людей\n"); break; }
			add(persons, size, &s);
			tabs(persons, size, s);
			break;

		case 5: 
			if (flag == 0) { printf("Сначала необходимо загрузить файл\n"); break; }
			save(persons, size, "D:\\prog\\Persons.txt");
			break;

		case 6:
			if (flag == 0) { printf("Сначала необходимо загрузить файл\n"); break; }
			if (s == -9) { printf("Больше людей нельзя удалить\n"); break; }
			printf("Введите фамилию человека, которого хотите удалить из списка: ");
			while (getchar() != '\n');
			fgets(fam, sizeof(fam), stdin);
			fam[strcspn(fam, "\n")] = '\0';
			delete(persons, size, fam, &s);
			tabs(persons, size, s);
			break;

		default:
			if (turn == 0) {while (getchar() != '\n');}
			if (code > 2 || code < 0) { printf("Можно вводить числа только от 0 до 2\n");}
			break;
		}
	} while (code != 0);
	free(persons);
	return 0;
}
