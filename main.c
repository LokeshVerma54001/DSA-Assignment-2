#include<stdio.h>
#include<string.h>
#include "bignum.h"
int main(){
    //Note: For anyone who is reading the multiplication and divison only works for positive numbers - Lokesh Verma
    char num1[100], num2[100];
    char o;
    printf("Enter the first number:");
    gets(num1);
    printf("Enter the second number:");
    gets(num2);
    printf("Entrer the opetraion you want to perform:(+,-,*,/)");
    scanf("%c", &o);
    switch(o){
        case '+':
            add(num1, num2);
            break;
        case '-':
            sub(num1, num2);
            break;
        case '*':
            mult(num1, num2);
            break;
        case '/':
            divide(num1, num2);
            break;
        default:
            printf("Invalid Operand.");
            break;
    }
}