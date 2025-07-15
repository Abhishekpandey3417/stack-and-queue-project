#include<stdio.h>
 
#define SIZE 3
 
//queue structure 
struct queue
{
    int values[SIZE];
    int front;
    int rear;
};

 
void enqueue(int);
int dequeue();
int isEmpty();
int isFull();
void display();
 
//glob
struct queue q;
 
int main()

{
    q.front = -1;
    q.rear = -1;
    int user_choice, data;
    char user_active = 'Y';
 
    while (user_active == 'Y' || user_active == 'y')
    {
        printf("\n--------Queue Program------\n");
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");
        
        
        printf("\n\nEnter your choice: ");
        scanf("%d", &user_choice);
 
        switch(user_choice)
        {
            case 1:
                printf("\nEnter Data: ");
                scanf("%d", &data);
                enqueue(data);
                break;
                
            case 2:
                if (!isEmpty())
                {
                    data = dequeue();
                    printf("\n* %d was removed!\n", data);
                }
                else
                {
                    printf("\nQueue is Empty!\n");
                }
                break;
                      case 3:
                display();
                printf("\n");
                break;
 
            case 4:
                printf("\n\tProgram was terminated!\n\n");
                return 1;
 
            default:
                printf("\n\tInvalid Choice\n");
        }
             printf("\nDo You want to continue? ");
        fflush(stdin);
        scanf(" %c", &user_active);
    }
    return 0;
}


int isEmpty()
{
    if (q.front == -1 || q.front > q.rear)
    {
        return 1;
    } 
    return 0;    
}
 
int isFull()
{
    if (q.rear == SIZE - 1)
    {
        return 1;
    } 
    return 0;    
}

void enqueue(int data)
{
    if (isFull())
    {
        printf("\nQueue is Full!\n");
        return;
    } 
    if (isEmpty())
    {
        q.front += 1;    
    } 
    q.rear += 1;
    q.values[q.rear] = data;
    printf("\n* %d was inserted!\n", data);
}

int dequeue() 
{
    if (!isEmpty())
    {    
        int data = q.values[q.front];
        q.front += 1;
        return data;
    }
}


void display()
{
    if (isEmpty())
    {
        printf("\nQueue is Empty\n");
        return;
    }
    printf("\n");
    int begin = q.front;
    while (begin <= q.rear)
    {
        printf("%d ", q.values[begin]);
        begin += 1;
    }
}
