#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

struct Person {
	char name[20];
	char surname[20];
	int age;
	int year;
};

void hello() {
	printf("0. Выход\n");
	printf("1. Загрузка файла\n");
	printf("2. Поиск человека\n");
	printf("3. Добавление человека\n");
	printf("4. Сохранение\n");
}

Person* read(int* size,const char* fname) {
	FILE* f = fopen(fname, "r");
	fscanf_s(f, "%d", size);
	Person* res = (Person*)malloc(sizeof(Person) * (*size));
	for (int i = 0; i < (*size); i++) {
		fscanf_s(f, "%s", res[i].name);
		fscanf_s(f, "%s", res[i].surname);
		fscanf_s(f, "%d", &(res[i].age));
		fscanf_s(f, "%d", &(res[i].year));
	}
	fclose(f);
	return res;
}

void tab(Person* persons, int size) {
	for (int i = 0; i < size; i++) {
		printf("---------------------\n");
		printf("Человек %d\n", i + 1);
		printf("Фамилия: %s\n", persons[i].surname);
		printf("Имя: %s\n", persons[i].name);
		printf("Возраст: %d\n", persons[i].age);
		printf("Год рождения %d\n", persons[i].year);
	}
	printf("-------------------");
}

int search(Person* persons, int size, char* str) {
	int res = -1;
	for (int i = 0; i < size; i++) {
		if (strcmp(persons[i].name, str) == 0) {
			res = i;
			break;
		}
	}
	return res;
}

void write(Person* persons, int size, int s) {
	int code, turn;
	do {
		printf("Сколько людей хотите добавить: ");
		turn = scanf_s("%d", &code);
		switch (code) {
			case 0: break;
			case 1: s = 1; break;
			case 2: s = 2; break;
			case 3: s = 3; break;
			default: if (turn == 0) {
				while (getchar() != '\n');
				printf("Можно вводить только числа\n");
			}
				   if (code < 0 || code > 3) {
					   printf("Можно вводить числа только от 0 до 3\n");
				   }
				   break;
		}
	} while (code != 0);
	if (code == 0) return;
	for (int i = size; i < (s + size); i++) {
		printf("%d человек: \n", i - (size + s) - 4);
		printf("Фамилия: ");
		fgets(persons[i].name, sizeof(persons[i].name), stdin);
		printf("Имя: ");
		fgets(persons[i].surname, sizeof(persons[i].surname), stdin);
		printf("Возраст: ");
		scanf_s("%d", persons[i].age);
		printf("Год рождения: ");
		scanf_s("%d", persons[i].year);
	}
}

void save(Person* persons, int size, const char* fname) {
	FILE* f = fopen(fname, "w");
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++) {
		fputs(persons[i].name, f);
		fputs(persons[i].surname, f);
		fprintf(f, "d\n", persons[i].age);
		fprintf(f, "d\n", persons[i].year);
	}
	fclose(f);
}

int main() {
	setlocale(LC_ALL, "RUS");
	struct Person* persons = nullptr; 
	int size, turn, code, pos;
	char str[20];
	persons = read(&(size) + 3, "Persons.txt");
	int s = size + 3;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
			case 0: break;
			case 1: tab(persons, s); 
				break;
			case 2: pos = search(persons, size, str);
				if (pos == -1) printf("Человека с тайкой фамилией нет в списке\n");
				else printf("Человек с такой фамилией находится в списке по номером %d", pos);
				break;
			case 3: write(persons, size, s);
				size++; 
				break;
			case 4:save(persons, size, "Persons.txt"); break;
			default: if (turn == 0) {
				while (getchar() != '\n');
				printf("Можно вводить только числа\n");
			}
				   if (code < 0 || code > 4) {
					   printf("Можно вводить числа только от 0 до 4\n");
				   }
				   break;
		}
	} while (code != 0);
	free(persons);
}