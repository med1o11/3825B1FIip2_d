#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDS 50
#define MAX_NAME_LEN 15

struct row {
    char name[MAX_NAME_LEN + 1];
    int age;
};

int choose_sort() {
    printf("Choose sorting algorithm:\n");
    printf("1 - Quick sort.\n");
    printf("2 - Selection sort.\n");
    printf("3 - Merge sort.\n");

    int t = 0;
    while (scanf("%d", &t) != 1 || t > 3 || t < 1) {
        printf("Incorrect input. Please try again.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    return t;
}

int partition(struct row* arr, int low, int high) {
    int pivot = arr[high].age;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].age < pivot) {
            i++;
            struct row t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }

    struct row t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;

    return i + 1;
}

void quick_sort(struct row* arr, int low, int high) {
    if (low < high) {
        int t = partition(arr, low, high);
        quick_sort(arr, low, t - 1);
        quick_sort(arr, t + 1, high);
    }
}

void selection_sort(struct row* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int mn = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].age < arr[mn].age) {
                mn = j;
            }
        }
        if (mn != i) {
            struct row t = arr[i];
            arr[i] = arr[mn];
            arr[mn] = t;
        }
    }
}

void merge(struct row* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct row* left_arr = (struct row*)malloc(n1 * sizeof(struct row));
    struct row* right_arr = (struct row*)malloc(n2 * sizeof(struct row));

    if (!left_arr || !right_arr) {
        free(left_arr);
        free(right_arr);
        return;
    }

    for (i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (left_arr[i].age <= right_arr[j].age) {
            arr[k] = left_arr[i++];
        }
        else {
            arr[k] = right_arr[j++];
        }
        k++;
    }

    while (i < n1) {
        arr[k++] = left_arr[i++];
    }

    while (j < n2) {
        arr[k++] = right_arr[j++];
    }

    free(left_arr);
    free(right_arr);
}

void merge_sort(struct row* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int read_file(struct row* arr) {
    FILE* fptr = fopen("People.in.txt", "r");
    if (fptr == NULL) {
        printf("Error: Cannot open input file.\n");
        return 0;
    }

    int n = 0;
    while (n < MAX_RECORDS) {
        char line[100];
        if (fgets(line, sizeof(line), fptr) == NULL) {
            break;
        }

        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
            continue;
        }

        char name[MAX_NAME_LEN + 1];
        int age;

        if (sscanf(line, "%15s %d", name, &age) == 2) {
            strncpy(arr[n].name, name, MAX_NAME_LEN);
            arr[n].name[MAX_NAME_LEN] = '\0';
            arr[n].age = age;
            n++;
        }
        else {
            printf("Warning: Line %d has incorrect format: %s", n + 1, line);
        }
    }

    fclose(fptr);
    return n;
}

void write_file(struct row* arr, int n) {
    FILE* fptr = fopen("People.out.txt", "w");
    if (fptr == NULL) {
        printf("Error: Cannot create output file.\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(fptr, "%-15s\t%d\n", arr[i].name, arr[i].age);
    }

    fclose(fptr);
}

int main() {
    char r = 'y';

    while (r == 'y') {
        struct row* arr = (struct row*)calloc(MAX_RECORDS, sizeof(struct row));
        if (arr == NULL) {
            printf("\nCould not allocate memory.\n");
            return -1;
        }

        int n = read_file(arr);
        if (n == 0) {
            printf("\nNo data read from file or file is empty.\n");
            free(arr);
            return -1;
        }

        printf("\nRead %d records from file.\n", n);

        int option = choose_sort();

        clock_t t = clock();
        switch (option) {
        case 1:
            quick_sort(arr, 0, n - 1);
            break;
        case 2:
            selection_sort(arr, n);
            break;
        case 3:
            merge_sort(arr, 0, n - 1);
            break;
        }
        t = clock() - t;
        double time = ((double)t) / CLOCKS_PER_SEC;

        write_file(arr, n);

        printf("\nSorted data:\n");
        printf("%-15s\t%s\n", "Name", "Age");
        printf("-------------------------------\n");
        for (int i = 0; i < n; ++i) {
            printf("%-15s\t%d\n", arr[i].name, arr[i].age);
        }

        printf("\nSorted data is stored in People.out.txt.\n");
        printf("Sorting took %lf seconds\n", time);
        printf("\nWould you like to sort again with different sorting algorithm? (y/n)\n");

        int c;
        while (scanf(" %c", &r) != 1 || (r != 'n' && r != 'y')) {
            printf("Incorrect input. Please enter 'y' or 'n': ");
            while ((c = getchar()) != '\n' && c != EOF) {}
        }

        while ((c = getchar()) != '\n' && c != EOF) {}

        free(arr);
    }

    printf("\nBye Bye!\n");
    return 0;
}