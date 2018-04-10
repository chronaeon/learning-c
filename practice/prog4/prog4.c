/* Multiline
Comment */

// Single line comment

#include <stdio.h>
#include <string.h>

#define MYNAME "Micah Dameron"

int global_var = 100;

main(){

	char first_letter = 'M';

	int age = 28;

	long int super_big_num = -327670000;

	float pi_value = 3.14159;

	double really_big_pi = 3.14159314159314159314159;

	printf("\n");

	printf("This will print to screen\n\n");

	printf("I am %d years old\n\n", age);

	printf("Big Number %ld\n\n", super_big_num);

	printf("Pi = %.5f\n\n", pi_value);
	
	printf("Pi = %.15f\n\n", really_big_pi); // This one estimates the 15th digit by rounding up.
	printf("The first letter in my name is %c\n\n", first_letter);

	printf("My Name is %s\n\n", "Micah");

	char my_name[14] = "Micah Dameron";

	printf("My Name is %s\n\n", my_name);

	strcpy(my_name, "MD");

	printf("My Name is %s\n\n", my_name);
}
// A variable is a box in memory that's going to allow you to save all your data.
