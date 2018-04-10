#include <stdio.h>

int main()
{

	printf("Hello, World!\n\n");

	int number;

    	printf("Enter an integer: ");  
    
    	scanf("%d", &number);  
    
    	printf("You entered: %d\n\n", number);
    
        int firstNumber, secondNumber, sumOfTwoNumbers;
    
        printf("Enter two integers: ");

        scanf("%d %d", &firstNumber, &secondNumber);

        sumOfTwoNumbers = firstNumber + secondNumber;

        printf("%d + %d = %d\n", firstNumber, secondNumber, sumOfTwoNumbers);       
        
        
        
        
        
      int numberr;

      printf("Enter an integer: ");
    
      scanf("%d", &numberr);

     if(number % 2 == 0)
        printf("%d is even.\n\n", numberr);
     else
        printf("%d is odd.\n\n", numberr);       
      
      
          char c;
    printf("Enter a character:");

    // Reads character input from the user
    scanf("%c", &c);  
    
    // %d displays the integer value of a character
    // %c displays the actual character
    printf("ASCII value of %c = %d\n", c, c);
      
      
      
      
      
      
      
      
      
      
      
        
        printf("Program will now exit.\n\n");
        
	return 0;

}
