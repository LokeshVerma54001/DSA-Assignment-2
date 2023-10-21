#ifndef BIGNUM_H
#define BIGNUM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct node{
    int data;
    struct node *next, *prev;
};

void new_node(struct node **head, struct node **tail,int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data=data;
    if(*head==NULL){
        temp->next =NULL;
        temp->prev=NULL;
        *head = temp;
        *tail = temp;
        return;
    }if(*head == *tail){
        temp->next = NULL;
        (*head)->next = temp;
        temp->prev = *head;
        *tail = temp;
        return;
    }else{temp->next = NULL;
    temp->prev = *tail;
    (*tail)->next = temp;
    *tail = temp;
    }
}

int length(struct node *head){
    int count=0;
    struct node *ptr = head;
    while(ptr){
        count++;
        ptr=ptr->next;
    }return count;
}

void swap(struct node **ptr1, struct node **ptr2){
    struct node *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void add(char num1[], char num2[]){
    int i,carry = 0; 
    char symbol;
    struct node *head1=NULL, *head2=NULL, *temp1, *resH=NULL;
    struct node *tail1 = head1, *tail2 = head2,*resT = resH;
    for(i=0;num1[i]!='\0';i++){
        symbol = num1[i];
        new_node(&head1,&tail1,symbol - '0');
    }for(i=0;num2[i]!='\0';i++){
        symbol = num2[i];
        new_node(&head2,&tail2,symbol - '0');
    }temp1=head1;
    printf("First number:");
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }printf("\nSecond number:");
    temp1 = head2;
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }while(tail1!=NULL||tail2!= NULL||carry!=0){
        int sum = carry;
        if(tail1 != NULL){
            sum += tail1->data;
            temp1 = tail1;
            tail1 = tail1->prev;
            free(temp1);
        }if(tail2 != NULL){
            sum += tail2->data;
            temp1 = tail2;
            tail2 = tail2->prev;
            free(temp1);
        }carry = sum / 10;
        sum %= 10;
        new_node(&resH, &resT, sum);
    }printf("\nResult = ");
    temp1 = resT;
    while(temp1){
        printf("%d", temp1->data);
        resT = temp1;
        temp1=temp1->prev;
        free(resT);
    }
}

void sub(char num1[], char num2[]){
    int i, j,sub=0, bor = 0, flag = 0;
    struct node *head1=NULL, *head2=NULL, *temp1, *resH=NULL;
    struct node *tail1 = head1, *tail2 = head2,*resT = resH;
    for(i=0;num1[i]!='\0';i++){
        new_node(&head1,&tail1,num1[i]-'0');
    }for(i=0;num2[i]!='\0';i++){
        new_node(&head2, &tail2, num2[i]-'0');
    }temp1=head1;
    printf("First number:");
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }printf("\nSecond number:");
    temp1 = head2;
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }if(strcmp(num1, num2)<0){
        swap(&head1, &head2);
        swap(&tail1, &tail2);
        flag = 1;
    }while(tail1||tail2||bor){
        sub = 0;
        bor = 0;
        if(tail1){
            sub = tail1->data;
            temp1 = tail1;
            tail1 = tail1->prev;
            free(temp1);
        }if(tail2){
            sub = sub - tail2->data;
            temp1 = tail2;
            tail2 = tail2->prev;
            free(temp1);
        }if(sub<0){
            sub = sub +10;
            bor = 1;
            if(tail1){
                tail1->data = tail1->data - 1;
            }
        }new_node(&resH, &resT, sub);
    }printf("\nResult = ");
    if(flag){
        printf("-");
    }temp1 = resT;
    while(temp1){
        printf("%d", temp1->data);
        resT = temp1;
        temp1=temp1->prev;
        free(resT);
    }
}

void mult(char num1[], char num2[]){
    int i, j,mult=0, carry = 0, flag = 0;
    struct node *head1=NULL, *head2=NULL, *temp1, *resH=NULL, *temp2;
    struct node *tail1 = head1, *tail2 = head2,*resT = resH;
    for(i=0;num1[i]!='\0';i++){
        new_node(&head1,&tail1,num1[i]-'0');
    }for(j=0;num2[j]!='\0';j++){
        new_node(&head2, &tail2, num2[j]-'0');
    }temp1=head1;
    printf("First number:");
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }printf("\nSecond number:");
    temp1 = head2;
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }if(strcmp(num1, num2)<0){
        swap(&head1, &head2);
        swap(&tail1, &tail2);
        flag = 1;
    }int len1 = length(head1);
    int len2 = length(head2);
    i = len1 + len2;
    while(i){
        new_node(&resH, &resT, 0);
        i--;
    }struct node *tail2Iter = tail2;
    for(i=0;i<len2;i++){
        temp1 = tail1;
        temp2 = resT;
        carry = 0;
        while(temp1){
            mult = temp1->data * tail2Iter->data + temp2->data + carry;
            carry = mult / 10;
            mult = mult % 10;
            temp2->data = mult;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }tail2Iter = tail2Iter->prev;
        resT = resT->prev;
    }printf("\nResult = ");
    temp1 = resH;
    while (temp1) {
        printf("%d", temp1->data);
        temp1 = temp1->next;
    }
}


void division(char num1[], char num2[]) {
    int i, j, flag = 0;
    int dividend = 0, res;
    struct node *head1 = NULL, *head2 = NULL, *temp1, *resH = NULL, *temp2;
    struct node *tail1 = head1, *tail2 = head2, *resT = resH;

    // Create linked lists for num1 and num2
    for (i = 0; num1[i] != '\0'; i++) {
        new_node(&head1, &tail1, num1[i] - '0');
    }
    for (j = 0; num2[j] != '\0'; j++) {
        new_node(&head2, &tail2, num2[j] - '0');
    }

    // Print input numbers
    temp1 = head1;
    printf("First number: ");
    while (temp1) {
        printf("%d", temp1->data);
        temp1 = temp1->next;
    }
    temp1 = head2;
    printf("\nSecond number: ");
    while (temp1) {
        printf("%d", temp1->data);
        temp1 = temp1->next;
    }

    // Check if the dividend is smaller than the divisor
    temp1 = head1;
    temp2 = head2;
    while (temp1 && temp2) {
        if (temp1->data < temp2->data) {
            flag = 1;
            break;
        } else if (temp1->data > temp2->data) {
            flag = 0;
            break;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    if (flag) {
        printf("Dividend number must be bigger than the divisor!\n");
        return;
    }

    // Initialize the result quotient
    int len1 = length(head2);
    while (len1) {
        new_node(&resH, &resT, 0);
        len1--;
    }
    printf("ok");
    // Perform long division
    temp1 = head1;
    temp2 = resH;
    int len_dividend = 0;
    int divi = 0;

    while (temp1) {
        dividend = dividend * 10 + temp1->data;
        len_dividend++;

        while (dividend >= divi || len_dividend < length(head2)) {
            // Calculate the quotient for this step
            temp2->data = dividend / divi;
            res = dividend % divi;

            // Shift left the remainder
            dividend = res;
            len_dividend++;
            temp1 = temp1->next;
            if (!temp1)
                break;
            divi = divi * 10 + temp1->data;
        }

        temp2 = temp2->next;
    }

    // Print the result quotient
    temp1 = resH;
    printf("\nQuotient = ");
    while (temp1) {
        printf("%d", temp1->data);
        temp1 = temp1->next;
    }

    // Print the remainder
    printf("\nRemainder = %d\n", res);
}







#endif