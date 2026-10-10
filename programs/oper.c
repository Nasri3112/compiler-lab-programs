#include <stdio.h>
#include <string.h>

int main()
{
    char stack[50][10], ip[50][10], opt[10][10][2], ter[10][10];
    int i, j, k, n, top = 0, col = 0, row = 0;

    /* Initialize arrays */
    for (i = 0; i < 50; i++)
    {
        strcpy(stack[i], "");
        strcpy(ip[i], "");
    }

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            opt[i][j][0] = '\0';

    /* Input terminals */
    printf("Enter the no. of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals:\n");
    for (i = 0; i < n; i++)
        scanf("%s", ter[i]);

    /* Input precedence table */
    printf("\nEnter the table values:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter the value for %s %s: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    /* Display precedence table */
    printf("\nOPERATOR PRECEDENCE TABLE:\n");
    printf("\t");

    for (i = 0; i < n; i++)
        printf("%s\t", ter[i]);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t", ter[i]);

        for (j = 0; j < n; j++)
            printf("%c\t", opt[i][j][0]);

        printf("\n");
    }

    /* Initialize stack with $ */
    strcpy(stack[top], "$");

    /* Input string */
    printf("\nEnter the input string separated by spaces: ");
    i = 0;

    while (1)
    {
        scanf("%s", ip[i]);

        if (strcmp(ip[i], "$") == 0)
            break;

        i++;
    }

    /* Display parsing table */
    printf("\n%-25s%-25s%-25s\n",
           "STACK", "INPUT STRING", "ACTION");

    printf("%-25s", stack[0]);

    for (j = 0; j <= i; j++)
        printf("%s ", ip[j]);

    printf("\n");

    j = 0;

    while (j <= i)
    {
        row = -1;
        col = -1;

        /* Find row */
        for (k = 0; k < n; k++)
        {
            if (strcmp(stack[top], ter[k]) == 0)
            {
                row = k;
                break;
            }
        }

        /* Find column */
        for (k = 0; k < n; k++)
        {
            if (strcmp(ip[j], ter[k]) == 0)
            {
                col = k;
                break;
            }
        }

        if (row == -1 || col == -1)
        {
            printf("\nString is not accepted\n");
            break;
        }

        /* Accept */
        if (strcmp(stack[top], "$") == 0 &&
            strcmp(ip[j], "$") == 0)
        {
            printf("\nString is accepted\n");
            break;
        }

        /* Shift */
        else if (opt[row][col][0] == '<' ||
                 opt[row][col][0] == '=')
        {
            strcpy(stack[++top], opt[row][col]);
            strcpy(stack[++top], ip[j]);

            printf("Shift %s", ip[j]);
            j++;
        }

        /* Reduce */
        else if (opt[row][col][0] == '>')
        {
            while (top >= 0 && strcmp(stack[top], "<") != 0)
                top--;

            if (top >= 0)
                top--;

            printf("Reduce");
        }

        else
        {
            printf("\nString is not accepted\n");
            break;
        }

        /* Print current stack */
        printf("\n");

        for (k = 0; k <= top; k++)
            printf("%s", stack[k]);

        printf("\t\t\t");

        /* Print remaining input */
        for (k = j; k <= i; k++)
            printf("%s ", ip[k]);

        printf("\t\t\t");
    }

    return 0;
}

