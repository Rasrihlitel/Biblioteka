#define _CRT_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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
	printf("Ваш выбор: ");
}

struct Person* read(int* size,const char* fname) {
	FILE* f = fopen(fname, "r");
	fscanf_s(f, "%d", size);
	struct Person* res = (struct Person*)malloc(sizeof(struct Person) * (*size));
	if (res == NULL) {
		printf("ЛОХ");
		return;
	}
	for (int i = 0; i < (*size); i++) {
		fscanf_s(f, "%s", res[i].surname);
		fscanf_s(f, "%s", res[i].name);
		fscanf_s(f, "%d", res[i].age);
		fscanf_s(f, "%d", res[i].year);
	}
	fclose(f);
	return res;
}

void tabs(struct Person* persons, int size) {
	for (int i = 0; i < size; i++) {
		printf("--------------------\n");
		printf("Человек %d", i + 1);
		printf("Фамилия: ");
		scanf_s("%s", persons[i].surname);
		printf("Имя: ");
		scanf_s("%s", persons[i].name);
		printf("Возраст: ");
		scanf_s("%d", &(persons[i].age));
		printf("Год рождения: ");
		scanf_s("%d", &(persons[i].year));
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

int main() {
	setlocale(LC_CTYPE, "Rus");
	int code, turn, size, res;
	char str[20];
	struct Person* persons = NULL;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
			case 0: break;
			case 1: 
				persons = read(&size, "C:\\prog\\Persons.txt");
				tabs(persons, size);
				break;

			case 2:
				printf("Введите фамилию человека, которого хотите найти: ");
				fgets(str, sizeof(str), stdin);
				res = search(persons, size, str);
				if (res == -1) printf("Человека с такой фамилией нет в списке\n");
				else printf("Человек с такой фамилией находится на %d позиции в списке\n", res + 1);
				break;
			default: 
				if (turn == 0) { while (getchar() != '\n'); break;}
				if (code > 2 || code < 0) { printf("Можно вводить числа только от 0 до 2\n"); break; }
				break;
		}
	} while (code != 0);
	free(persons);
	return 0;
}
	} while (code != 0);
	free(persons);

}
