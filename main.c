#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Customer {
  char name[100];
  double balance;
  char bankid[10];
};

char *GenerateRandomDigits(int length) {
  srand(time(NULL));
  char *digits = (char *)malloc(length + 1);
  for (int i = 0; i < length; i++) {
    digits[i] = (rand() % 10) + '0';
  }
  digits[length] = '\0';
  return digits;
}

char *CreateAccount(char *username) {
  char date[7];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(date, "%02d%02d%02d", tm.tm_year % 100, tm.tm_mon + 1, tm.tm_mday);
  char *randomDigits = GenerateRandomDigits(4);
  char *id = (char *)malloc(10);
  sprintf(id, "%s-%s", date, randomDigits);
  free(randomDigits);
  return id;
}

void Deposit(struct Customer *user, double balance) {
  if (balance >= 1) {
    user->balance += balance;
  } else {
    printf("Invalid amount!\n");
  }
}

void Withdraw(struct Customer *user, double balance) {
  if (balance >= 1) {
    user->balance += balance;
  } else {
    printf("Invalid amount!\n");
  }
}

int main() {
  printf("Welcome to Evergreen Banking\n");
  char data[100];
  printf("Type your name: ");
  fgets(data, 100, stdin);
  data[strcspn(data, "\n")] = '\0';
  if (strlen(data) == 0) {
    printf("Name is invalid!\n");
    return 0;
  }
  struct Customer user;
  char *id = CreateAccount(data);
  strcpy(user.name, data);
  user.balance = 0.0;
  strcpy(user.bankid, id);
  free(id);

  bool active = true;
  while (active) {
    printf("\nSelect an option\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Quit\n");
    // printf("4. Deposit\n");

    int option;
    printf("Enter your choice: ");
    scanf("%d", &option);
    getchar();

    double amount;
    switch (option) {
    case 1:
      printf("Balance: $%.2f\n", user.balance);
      break;
    case 2:
      printf("Enter the amount to deposit: ");
      scanf("%lf", &amount);
      getchar();
      Deposit(&user, amount);
      printf("Deposit successful!\n");
      break;
    case 3:
      printf("Enter the amount to deposit: ");
      scanf("%lf", &amount);
      getchar();
      if (user.balance >= amount) {
        Withdraw(&user, amount);
        printf("Withdraw successful!\n");
        break;
      } else {
        printf("Insufficient funds!\n");
        break;
      }
    case 4:
      active = false;
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid option! Please try again.\n");
      break;
    }
  }

  return 0;
}
