#define MYNAME "Derek Banas"

int global_var = 100;

main(){
	
	char middle_initial;

	printf("What is your middle initial? ");

	scanf(" %c", &middle_initial);

	printf("What is your middle initial? ");

	char first_name[30], last_name[30];

	printf("What is your name? ");

	scanf(" %s %s", first_name, last_name);

	printf("Your Name is %s %c %s\n\n", first_name, middle_initial, last_name);

	int month, day, year;

	printf("What's your birth date? ");

	scanf(" %d/%d/%d", &month, &day, &year);
	
	printf("\nBirth Date %d/%d/%d\n\n", month, day, year);


}
#include <stdio.h>
int main()
{
    int rows, coef = 1, space, i, j;

    printf("Enter number of rows: ");
    scanf("%d",&rows);

    for(i=0; i<rows; i++)
    {
        for(space=1; space <= rows-i; space++)
            printf("  ");

        for(j=0; j <= i; j++)
        {
            if (j==0 || i==0)
                coef = 1;
            else
                coef = coef*(i-j+1)/j;

            printf("%4d", coef);
        }
        printf("\n");
    }

    return 0;
}
