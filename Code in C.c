#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node {
int rank;
struct _node *parent;
} node;

void makeset(int m, int n, node arr[m][n]);
node *findset(node *to_find);//returns address of the top node of the tree
void mergeset(node a, node b);
void findtreasure(int m, int n, node C[m][n], int H[m-1][n], int V[m][n-1]);
void printgrid(int m, int n, int H[m-1][n], int V[m][n-1]);

void main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    int m, n;
    if (argc < 3)
    {
        m = 10;
        n = 10;
    }
    else
    {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }

    node C[m][n];
    int H[m-1][n];
    int V[m][n-1];

    for (int i =0; i < m-1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            H[i][j] = 1;//1 means not broken;
        }
    }

    for (int i =0; i < m; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            V[i][j] = 1;//1 means not broken;
        }
    }

    makeset(m, n, C);//all the nodes are now disjoint;

    printf("The final chamber can be reached from the start chamber.\n");
    printf("\nInitial Grid");
    printgrid(m ,n, H, V);
    findtreasure(m , n, C, H, V);
    printf("\n\n\nFinal Grid");
    printgrid(m, n, H, V);

}

void makeset(int m, int n, node C[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j].rank = 0;
            C[i][j].parent = &C[i][j];
        }
    }
}

node *findset(node *to_find)//returns address of the top node of the tree
{
    if (to_find->parent != to_find)
    {
        to_find->parent = findset(to_find->parent);
    }
    return to_find->parent;
}

void mergeset(node x, node y)
{
    node *addr_x = findset(&x);
    node *addr_y = findset(&y);

    if (addr_x->rank > addr_y->rank)
    {
        addr_y->parent = addr_x;
    }
    else if (addr_x->rank < addr_y->rank)
    {
        addr_x->parent = addr_y;
    }
    else
    {
        addr_x->parent = addr_y;
        addr_y->rank++;
    }
}

void findtreasure(int m, int n, node C[m][n], int H[m-1][n], int V[m][n-1])
{
    int breaks = m*n-1;
    while (breaks > 0)
    {
        int h_or_v = rand()%2;
        if (h_or_v == 1 && m > 1)//horizontal wall
        {
            int i = rand()%(m-1); //from 0 to m-1
            int j = rand()%n; //from 0 to n

            if (H[i][j] == 0)
            {
                continue;//wall already broken;
            }
            if (findset(&C[i][j]) == findset(&C[i+1][j]))
            {
                continue; //dont break the wall
            }
            else
            {
                H[i][j] = 0;//break the wall;
                breaks--;
                mergeset(C[i][j], C[i+1][j]);
            }

        }
        else if(h_or_v == 0 && n > 1)//vertical wall
        {
            int i = rand()%m;
            int j = rand()%(n-1);

            if (V[i][j] == 0)
            {
                continue;
            }
            if (findset(&C[i][j]) == findset(&C[i][j+1]))
            {
                continue; //dont break the wall
            }
            else
            {
                V[i][j] = 0;//break the wall;
                breaks--;
                mergeset(C[i][j], C[i][j+1]);
            }
        }
    }
}

void printgrid(int m, int n, int H[m-1][n], int V[m][n-1])
{
    printf("\n+   ");
    for (int i = 1; i < n; i++)
    {
        printf("+---");
    }
    printf("+\n");
    for (int i = 0; i < m; i++)
    {
        printf("|   ");
        for (int j = 0; j < n-1; j++)
        {
            if (V[i][j] == 1)
                printf("|   ");
            else
                printf("    ");
        }
        if ( i!= m-1)
            printf("|");
        printf("\n");
        if (i < m-1)
        {
            for (int j = 0; j < n; j++)
            {
                if (H[i][j] == 1)
                    printf("+---");
                else
                    printf("+   ");
            }
            printf("+\n");
        }

    }
    for (int i = 0; i < n; i++)
    {
        printf("+---");
    }
    printf("+");
}
