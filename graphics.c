#include <stdio.h>

char canvas[30][60];

int shapeType[100];
int sRow[100], sCol[100];
int sW[100], sH[100];
int shapeCount = 0;

void initializeCanvas();
void clearCanvas();
void displayCanvas();
void drawLine(int row,int col,int length);
void drawRectangle(int row,int col,int width,int height);
void drawTriangle(int row,int col,int size);
void drawCircle(int centerX,int centerY,int radius);
void redrawAll();
void addShape();

void initializeCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void clearCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row,int col,int length)
{
    for(int i=0;i<length;i++)
    {
        canvas[row][col+i]='*';
    }
}

void drawRectangle(int row,int col,int width,int height)
{
    for(int i=0;i<width;i++)
    {
        canvas[row][col+i]='*';
        canvas[row+height-1][col+i]='*';
    }

    for(int i=0;i<height;i++)
    {
        canvas[row+i][col]='*';
        canvas[row+i][col+width-1]='*';
    }
}

void drawTriangle(int row,int col,int size)
{
    for(int i=0;i<size;i++)
    {
        canvas[row+i][col]='*';
        canvas[row+size-1][col+i]='*';
        canvas[row+i][col+i]='*';
    }
}

void drawCircle(int centerX,int centerY,int radius)
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            int dx=i-centerX;
            int dy=j-centerY;
            int d=dx*dx+dy*dy;

            if(d>=radius*radius-radius &&
               d<=radius*radius+radius)
            {
                canvas[i][j]='*';
            }
        }
    }
}

void redrawAll()
{
    clearCanvas();

    for(int i=0;i<shapeCount;i++)
    {
        if(shapeType[i]==1)
            drawLine(sRow[i],sCol[i],sW[i]);

        else if(shapeType[i]==2)
            drawRectangle(sRow[i],sCol[i],sW[i],sH[i]);

        else if(shapeType[i]==3)
            drawCircle(sRow[i],sCol[i],sW[i]);

        else if(shapeType[i]==4)
            drawTriangle(sRow[i],sCol[i],sW[i]);
    }
}

void addShape()
{
    printf("\n--- ADD SHAPE ---\n");
    printf("1-Line 2-Rectangle 3-Circle 4-Triangle\n");

    printf("Enter Type: ");
    scanf("%d",&shapeType[shapeCount]);

    printf("Enter Row and Column: ");
    scanf("%d%d",&sRow[shapeCount],&sCol[shapeCount]);

    printf("Enter Width/Size/Radius: ");
    scanf("%d",&sW[shapeCount]);

    printf("Enter Height (0 if not needed): ");
    scanf("%d",&sH[shapeCount]);

    shapeCount++;

    redrawAll();

    printf("Shape Added Successfully\n");
}

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Add Shape\n");
        printf("2. Display Canvas\n");
        printf("3. Clear Canvas\n");
        printf("4. Exit\n");
        printf("Enter Choice: ");

        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                displayCanvas();
                break;

            case 3:
                clearCanvas();
                shapeCount=0;
                printf("Canvas Cleared\n");
                break;

            case 4:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice!=4);

    return 0;
}
