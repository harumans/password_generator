//First project in C by harumans

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WHT "\e[0;37m"  // white color
#define BWHT "\e[1;37m" // bold white color
#define YEL "\e[0;33m"  // yellow color
#define BYEL "\e[1;33m" // bold yellow color
#define MAX 2048


// function declarations
void menu();
void generate_password(char *name, int length);
void password_checker(char *name);
void help();
int main()
{
    menu();
    system("PAUSE");
}
void menu()
{
    int choice;
    char name[31];
    printf(YEL "\n\n\n\tWelcome to password generator \n\n" WHT);
    printf(YEL "\t 1." WHT);
    printf("Generate a new password \n");
    printf(YEL "\t 2." WHT);
    printf("View old passwords \n");
    printf(YEL "\t 3." WHT);
    printf("Help\n");
    printf(YEL "\t 4." WHT);
    printf("Exit\n");
    printf("\n\tEnter your choice : " BWHT);
    scanf("%d", &choice);
    printf(WHT "\n");
    if (choice == 1 || choice == 2)
    {
        printf("Please enter your password's name : ");
        scanf("%s", &name);
    }
    switch (choice)
    {
    case 1: //generate a password
        int length = 7;
        while (length < 8)
        {
            printf(YEL "NOTE:" WHT "(password should be at least 8 characters)"
                       " Please enter your password's length : ");
            scanf("%d", &length);
        }
        system("CLS");
        generate_password(name, length);
        break;
    case 2:// check for an old password
        system("CLS");
        password_checker(name);
        break;
    case 3://guid to use the programme
        system("CLS");
        help();
        break;
    case 4://exit 
        exit(0);
        break;
    }
}
void generate_password(char *name, int length)
{
    int c;
    char *password = malloc(length + 1);
    char *symbols = "!@#$^&*()'";
    int symbols_length = strlen(symbols);
    char *uppercase = "QWERTYUIOPLKJHGFDSAZXCVBNM";
    int uppercase_length = strlen(uppercase);
    char *numbers = "1234567890";
    int numbers_length = strlen(numbers);
    char *lowercase = "qwertyuiopasdfghjklmnbvcxz";
    int lowercase_length = strlen(lowercase);
    FILE *ptr;
    char buffer[MAX];
    char *holder;
    int found = 0;
    ptr = fopen("password.txt", "r");//file that contains passwords
    if (ptr == NULL)//in case the file could't open  
        printf(BYEL "\n\n\n\tERROR :" WHT " COULD NOT OPEN THE FILE");
    while (fgets(buffer, MAX, ptr) != NULL)//reading content of the file
    {
        holder = strtok(buffer, "|");//separate and store the first string from the password with '|'
        if (strcmp(holder, name) == 0)//compare the two strings to check if the password is already in  
        {
            // the name is aleardy used AKA old password
            found = 1;
            break;
        }
    }
    if (found == 1)//if found a existing name 
    {
        printf(BYEL "\n\n\n\tERROR:" WHT " YOU ALREADY HAVE A PASSWORD WITH THAT NAME '%s'\n\n", name);
    }
    else //if not it'll generate a new password for that name
    {

        fclose(ptr); 
        srand(time(NULL) * getpid());//random seed
        for (int i = 0; i < length; i++)
        {
            int pick = rand() % 4;
            if (pick == 0)
                password[i] = symbols[rand() % symbols_length];
            else if (pick == 1)
                password[i] = uppercase[rand() % uppercase_length];
            else if (pick == 2)
                password[i] = numbers[rand() % numbers_length];
            else
                password[i] = lowercase[rand() % lowercase_length];
        }
        password[length] = '\0';
        printf(YEL "\n\n\n\tPassword :" WHT "  %s\n\n", password);
        ptr = fopen("password.txt", "a");
        if (ptr != NULL)
        {
            fprintf(ptr, "%s|%s\n", name, password);
        }
        else
            printf("could't open the file \n");
        fclose(ptr);
        free(password);
    }
    printf(YEL "\t 1." WHT);
    printf("Back to the menu\n");
    printf(YEL "\t 2." WHT);
    printf("Exit\n");
    printf("\n\tEnter your choice : " BWHT);
    scanf("%d", &c);
    printf(WHT "\n");
    if (c == 1)
    {
        system("CLS");
        menu();
    }
    else
        exit(0);
}
void help()
{

    int c, d, f;
    printf(YEL "\n\n\n\tThe Help section\n\n" WHT);
    printf(YEL "\t 1." WHT);
    printf("How to generate a password ? \n");
    printf(YEL "\t 2." WHT);
    printf("How to see your generated passwords ?\n");
    printf(YEL "\t 3." WHT);
    printf("Back to the menu\n\n");
    printf("\tEnter your choice : " BWHT);
    scanf("%d", &c);
    printf(WHT "\n");
    if (c == 1)
    {
        system("CLS");
        printf(YEL "\n\n\n\tHow to generate a password : \n" WHT);
        puts("\n\t   To generate a password you need to follow these steps : \t");
        printf(BYEL "\nSTEP 1\t:" WHT "  In the menu section click 1 (i.e,Generate a new password).\n");
        printf(BYEL "\nSTEP 2\t:" WHT "  After clicking '1' it will ask you to enter a name\n");
        printf("         " YEL "  NOTE:" WHT " (make sure to not put any space in the name). \n");
        printf(BYEL "\nSTEP 3\t:" WHT "  After enter your desired name it will ask you to enter a length to your password\n");
        printf("         " YEL "  NOTE:" WHT " (password should be at least 8 characters or above it).\n");
        printf(BYEL "\nSTEP 4\t:" WHT "  The programme should generate you a random & safe password.\n \n \n");
        printf(YEL "\t   1." WHT);
        printf("Back to the menu \n");
        printf(YEL "\t   2." WHT);
        printf("Exit \n\n");
        printf("\tEnter your choice : " BWHT);
        scanf("%d", &d);
        printf(WHT "\n");
        if (d == 1)
        {
            system("CLS");
            menu();
        }
        else
            exit(0);
    }
    else if (c == 2)
    {
        system("CLS");
        printf(YEL "\n\n\n\tHow to see your old passwords : \n" WHT);
        puts("\n\t   To see your old passwords you need to follow these steps : \t");
        printf(BYEL "\nSTEP 1\t:" WHT "  In the menu section click 2 (i.e,View old passwords).\n");
        printf(BYEL "\nSTEP 2\t:" WHT "  After clicking '2' enter the password name you wish to see \n");
        printf("         " YEL "  NOTE:" WHT " (make sure to not put any space in the name). \n");
        printf(BYEL "\nSTEP 3\t:" WHT "  The programme will print the password with the name you typed.\n \n \n");
        printf(YEL "\t   1." WHT);
        printf("Back to the menu \n");
        printf(YEL "\t   2." WHT);
        printf("Exit \n\n");
        printf("\tEnter your choice : " BWHT);
        scanf("%d", &f);
        printf(WHT "\n");
        if (f == 1)
        {
            system("CLS");
            menu();
        }
        else
            exit(0);
    }
    else
    {
        system("CLS");
        menu();
    }
}

void password_checker(char *name)//checking if the password is already in with the same trick
{
    int choice;
    int found = 0;
    char *holder;
    char reader[MAX];
    char old_pass[MAX];
    FILE *ptr = fopen("password.txt", "r");
    while (fgets(reader, MAX, ptr) != NULL)
    {
        holder = strtok(reader, "|");
        if (strcmp(reader, name) == 0)
        {
            // found a existing name i.e password
            // copy password
            holder = strtok(NULL, "|");
            strcpy(old_pass, holder);
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("\n\n\n\tThe password with the name " YEL "'%s'" WHT " is : " YEL "%s" WHT "\n\n", name, old_pass);
    }
    else
        printf(BYEL "\n\n\n\tERROR :" WHT " YOU DON'T HAVE A PASSWORD WITH THAT NAME '%s'\n\n", name);

    printf(YEL "\t 1." WHT);
    printf("Back to the menu\n");
    printf(YEL "\t 2." WHT);
    printf("Exit\n\n");
    printf("\tEnter your choice : " BWHT);

    scanf("%d", &choice);
    printf(WHT "\n");
    if (choice == 1)
    {
        system("CLS");
        menu();
    }
    else
        exit(0);
}
