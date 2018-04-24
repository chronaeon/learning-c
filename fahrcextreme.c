#include <stdio.h>

/*print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300; floating-point version */
main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; 	/* lower limit of temperature table */
	upper = 9000000000000;    /* upper limit */
	step = 500;	/* step size */

	celsius = lower;
	printf("Celsius to Farenheit Conversion Table by Steps of 20 Degrees\n");
	while (celsius <= upper) {
		fahr = celsius * 9/5 + 32;
		printf("%3.0f %6.5f\n", celsius, fahr);
		celsius = celsius + step;
	}
}

