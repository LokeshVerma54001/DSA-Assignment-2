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

void divide(char num1[], char num2[]) {
    int i, j, divi = 0, divit = 0, res = 0;
    int n1 = atoi(num1),n2,ress;
    n2 = atoi(num2);
    struct node* head1 = NULL, *head2 = NULL, *temp1, *resH = NULL, *temp2;
    struct node* tail1 = head1, *tail2 = head2, *resT = resH;
    temp1=head1;
    printf("First number:");
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }printf("\nSecond number:");
    temp1 = head2;
    while(temp1){
        printf("%d", temp1->data);
        temp1=temp1->next;
    }ress = n1/n2;
    for(i=0;num1[i]!='\0';i++){
        new_node(&head1, &tail1, num1[i] - '0');
    }for(j = 0; num2[j] != '\0'; j++){
        new_node(&head2, &tail2, num2[j] - '0');
    }if(length(head1) < length(head2)){
        printf("Dividend Number Must Be Bigger Than Divisor!\n");
        return;
    }while (1) {
        int quotient = 0;
        while (divi < 1) {
            if (i >= length(head1)) {
                break;
            }divi = divi * 10 + head1->data;
            head1 = head1->next;
            i++;
        }if(i >= length(head1)){
            break;
        }while(divit < divi){
            divit = divit * 10 + head2->data;
            head2 = head2->next;
        }while(divit >= divi){
            divit -= divi;
            quotient++;
        }new_node(&resH, &resT, quotient);
    }printf("answer = %d ",ress);
}


#endif