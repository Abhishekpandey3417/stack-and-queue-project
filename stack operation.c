#include <stdio.h>
#define MAX_SIZE 20
 
// function prototyping
void push(int);
int pop(void);
int peek(void);
int is_empty();
int is_full();
void display();

struct stack
{
    int stk[MAX_SIZE];
    int top;
};
 
struct stack st;
 
int main()
{
    st.top = -1;
 
    char userContinue = 'Y';
    int userChoice;
    while (userContinue == 'Y' || userContinue == 'y') {
        printf("\n------ STACK DATA STRUCTURE ------\n\n");
        printf("\n1. Push the data");
        printf("\n2. Pop the data");
        printf("\n3. Peek the data");
        printf("\n4. Display Stack");
        printf("\n5. Exit");
 
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &userChoice);
 
        switch (userChoice)  
        {
        case 1:
            printf("\n\nEnter Data: ");
            scanf("%d", &userChoice);
            push(userChoice);
            break;
        case 2:
            if (!is_empty())
            {
                int data = pop();
                printf("\nValue %d was popped", data);
            } 
            else 
            {
                printf("\n\tStack is Empty!");
            }
            break;
        case 3:
            if (!is_empty())
            {
                int data = peek();
                printf("\nValue %d was peeked", data);
            } 
            else
            {
                printf("\n\tStack is Empty!");
            }
            break;
        case 4:
            display();
            break;
        case 5:
            printf("\n\tProgram Terminated!\n");
            return 1;
            break;
        default:
            printf("\n\tInvalid Choice!");
        }
                printf("\n\nDo you want to continue? ");
        fflush(stdin);
        scanf(" %c", &userContinue);
    }
    return 0;
}
 
int is_full()
{
    if (st.top == MAX_SIZE)
    {
        return 1;
    }
     return 0;
}
 
int is_empty()
{
    if (st.top == -1)
    {
        return 1;
    }
    return 0;
}

void push(int data)
{
    if (is_full())
    {
        printf("\nStack Overflow!");
    }
    else
    {
        st.stk[++st.top] = data;
        printf("\n* %d was inserted", data);
    }
}

 
int pop()
{
    return st.stk[st.top--];
}
 
int peek()
{
    return st.stk[st.top];
}


void display()
{
    if (is_empty())
    {
        printf("\n\tStack is Empty!");
        return;
    }
    for (int i = st.top; i >= 0; i--)
    {
        printf("\n\t%d", st.stk[i]);
    }
}
