#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROD 100
#define BARCODE_SIZE 4
#define NAME_SIZE 50
 
struct Product {
	char barcode[BARCODE_SIZE + 1];
	char name[NAME_SIZE];
	int price;
	int discount;
};
struct Check_item {
	struct Product prod;
	int quantity;
	int total_discount;
};
struct Check {
	struct Check_item item[MAX_PROD];
	int item_count;
	int total_cost;
	int total_discount;
	int final_amount;
};

struct Product prods[MAX_PROD];
int prod_count = 0;
struct Check current_check;

void init_prod() {
	struct Product init_prod[] = {
		{"1564", "Bread", 47, 5}, {"9318", "Tea", 125, 22},
		{"1458", "Potato", 65, 45}, {"2346", "Milk", 207, 18},
		{"0715", "Oil", 165, 12}
	};
	for (int i = 0; i < 5; i++) {
		prods[i] = init_prod[i];
	}
	prod_count = 5;
}
void init_check() {
	current_check.item_count = 0;
	current_check.total_cost = 0;
	current_check.total_discount = 0;
	current_check.final_amount = 0;
}
int is_valid_barcode(const char* barcode) {
	int len;
	for (len = 0; barcode[len] != '\0'; len++);
	if (len != BARCODE_SIZE) {
		return 0;
	}
	for (int i = 0; i < BARCODE_SIZE; i++) {
		if (barcode[i] < '0' || barcode[i] > '9') {
			return 0;
		}
	}
	return 1;
}
int find_prod(const char* barcode) {
	for (int i = 0; i < prod_count; i++) {
		int flag = 1;
		for (int j = 0; j < BARCODE_SIZE + 1; j++) { 
			if (barcode[j] != prods[i].barcode[j]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			return i;
		}
	}
	return -1;
}
void read_str(char* buf, int max_size) {
	int i = 0;
	char c;
	while (i < max_size - 1 && (c = getchar()) != '\n' && c != EOF) {
		buf[i] = c;
		i++;
	}
	buf[i] = '\0';
	if (c != '\n' && c != EOF) {
		while ((c = getchar()) != '\n' && c != EOF);
	}
}
void add_prod() {
	if (prod_count >= MAX_PROD) {
		printf("Product limit!\n");
		return;
	}
	struct Product new_prod;
	printf("--- Adding a new product ---\n");

	do {
		printf("Enter the barcode (4 digits): ");
		read_str(new_prod.barcode, BARCODE_SIZE + 1);
		if (!is_valid_barcode(new_prod.barcode)) {
			printf("Error: The barcode must contain exactly 4 digits!\n");
		}
		else if (find_prod(new_prod.barcode) != -1) {
			printf("Error: Such a barcode already exists!\n");
		}
		else {
			break;
		}
	} while (1);

	printf("Enter the product name: ");
	read_str(new_prod.name, NAME_SIZE);

	printf("Enter the price(rub): ");
	if (scanf("%d", &new_prod.price) != 1) {
		printf("Error: Invalid price input!\n");
		while (getchar() != '\n');
		return;
	}
	while (getchar() != '\n');

	do {
		printf("Enter the discount(1-50): ");
		if (scanf("%d", &new_prod.discount) != 1) {
			printf("Error: Invalid discount input!\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');
		if (new_prod.discount < 1 || new_prod.discount > 50) {
			printf("Error: Discount must be in range(1-50)!\n");
		}
		else {
			break;
		}
	} while (1);
	prods[prod_count] = new_prod;
	prod_count++;
	printf("Product added successfully!\n");
}
void scan_and_show() {
	char barcode[BARCODE_SIZE + 1];
	printf("Enter barcode:");
	read_str(barcode, BARCODE_SIZE + 1);
	int ind = find_prod(barcode);
	if (ind == -1) {
		printf("Product not found!\n");
	}
	else {
		printf("Product: %s, Price: %d rub, Discount: %d%%\n",
			prods[ind].name, prods[ind].price, prods[ind].discount);
	}
}
void scan_and_check() {
	char barcode[BARCODE_SIZE + 1];
	printf("Enter barcode:");
	read_str(barcode, BARCODE_SIZE + 1);
	int ind = find_prod(barcode);
	if (ind == -1) {
		printf("Product not found!\n");
		return;
	}
	if (current_check.item_count >= MAX_PROD) {
		printf("Check is full!\n");
		return;
	}
	int quant = 0;
	printf("Enter quantity:");
	scanf("%d", &quant);
	while (getchar() != '\n');
	if (quant <= 0) {
		printf("Invalid quantity!\n");
		return;
	}
	current_check.item[current_check.item_count].prod = prods[ind];
	current_check.item[current_check.item_count].quantity = quant;
	current_check.item[current_check.item_count].total_discount =
		(prods[ind].price * prods[ind].discount / 100) * quant;
	current_check.item_count++;
	printf("Product added to check!\n");
}
void show_check() {
	printf("--- Current check ---\n");
	if (current_check.item_count == 0) {
		printf("Check is empty\n");
		return;
	}
	for (int i = 0; i < current_check.item_count; i++) {
		printf("%s:  Price:%d rub  Quantity:%d  Discount:%d rub  Total:%d rub\n",
			current_check.item[i].prod.name, current_check.item[i].prod.price,
			current_check.item[i].quantity, current_check.item[i].total_discount,
			current_check.item[i].quantity * current_check.item[i].prod.price
			- current_check.item[i].total_discount);
	}
}
void gen_fin() {
	printf("\n--- Final Check ---\n");
	if (current_check.item_count == 0) {
		printf("Check is empty\n");
		return;
	}

	int total = 0;
	int total_dis = 0;

	for (int i = 0; i < current_check.item_count; i++) {
		int item_total = current_check.item[i].quantity * current_check.item[i].prod.price;
		int item_final = item_total - current_check.item[i].total_discount;

		printf("%s:  Price:%d rub  Quantity:%d  Discount:%d rub  Total:%d rub\n",
			current_check.item[i].prod.name,
			current_check.item[i].prod.price,
			current_check.item[i].quantity,
			current_check.item[i].total_discount,
			item_final);

		total += item_total;
		total_dis += current_check.item[i].total_discount;
	}

	current_check.total_cost = total;
	current_check.total_discount = total_dis;
	current_check.final_amount = total - total_dis;

	printf("-------------------\n");
	printf("Total: %d rub\n", current_check.total_cost);
	printf("Total discount: %d rub\n", current_check.total_discount);
	printf("Final amount: %d rub\n", current_check.final_amount);
	printf("-------------------\n");

	int c;
	do {
		printf("Select an action:\n");
		printf("0 - Finish work\n");
		printf("1 - Start a new check\n");
		printf("Your choice: ");
		if (scanf("%d", &c) != 1) {
			printf("Invalid input!\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');

		if (c == 1) {
			printf("Starting a new check...\n\n");
			init_check();
			break;
		}
		else if (c == 0) {
			printf("Exiting program...\n");
			break;
		}
		else {
			printf("Incorrect operation selection! Try again.\n");
		}
	} while (1);
}

void menu() {
	printf("=== Electronic cashbox ===\n");
	printf("1.Add product\n");
	printf("2.Scan and show the product\n");
	printf("3.Scan and add to check\n");
	printf("4.Show current check\n");
	printf("5.Generate a final check\n");
	printf("0.Exit\n");
	printf("Select an operation:");
}
int main() {
	init_prod();
	init_check();

	int c;
	do {
		menu();
		if (scanf("%d", &c) != 1) {
			printf("Invalid input!\n");
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');

		switch (c) {
		case 1:
			add_prod();
			break;
		case 2:
			scan_and_show();
			break;
		case 3:
			scan_and_check();
			break;
		case 4:
			show_check();
			break;
		case 5:
			gen_fin();
			break;
		case 0:
			printf("The end!\n");
			break;
		default:
			printf("Incorrect operation selection!\n");
		}
	} while (c != 0);
	return 0;
}