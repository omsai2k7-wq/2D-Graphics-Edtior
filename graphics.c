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
void deleteShape();
void modifyShape();
void listShape();

void saveDrawing();
void loadDrawing();

void initializeCanvas()
{
    int i,j;

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void clearCanvas()
{
    int i,j;

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void displayCanvas()
{
    int i,j;

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row,int col,int length)
{
    int i;

    for(i=0;i<length && col+i<60;i++)
    {
        if(row>=0 && row<30)
            canvas[row][col+i]='*';
    }
}

void drawRectangle(int row,int col,int width,int height)
{
    int i;

    for(i=0;i<width;i++)
    {
        if(row>=0 && row<30 && col+i<60)
            canvas[row][col+i]='*';

        if(row+height-1<30 && col+i<60)
            canvas[row+height-1][col+i]='*';
    }

    for(i=0;i<height;i++)
    {
        if(row+i<30 && col<60)
            canvas[row+i][col]='*';

        if(row+i<30 && col+width-1<60)
            canvas[row+i][col+width-1]='*';
    }
}

void drawTriangle(int row,int col,int size)
{
    int i;

    for(i=0;i<size;i++)
    {
        if(row+i<30 && col<60)
            canvas[row+i][col]='*';

        if(row+size-1<30 && col+i<60)
            canvas[row+size-1][col+i]='*';

        if(row+i<30 && col+i<60)
            canvas[row+i][col+i]='*';
    }
}

void drawCircle(int centerX,int centerY,int radius)
{
    int i,j;

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
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
    int i;

    clearCanvas();

    for(i=0;i<shapeCount;i++)
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

void listShape()
{
    int i;

    if(shapeCount==0)
    {
        printf("\nNo shapes available\n");
        return;
    }

    printf("\nStored Shapes:\n");

    for(i=0;i<shapeCount;i++)
    {
        printf("Index %d -> Type=%d Row=%d Col=%d Width=%d Height=%d\n",
               i,shapeType[i],sRow[i],sCol[i],sW[i],sH[i]);
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

void deleteShape()
{
    int index,i;

    if(shapeCount==0)
    {
        printf("No shapes available\n");
        return;
    }

    listShape();

    printf("Enter Shape Index To Delete: ");
    scanf("%d",&index);

    if(index<0 || index>=shapeCount)
    {
        printf("Invalid Index\n");
        return;
    }

    for(i=index;i<shapeCount-1;i++)
    {
        shapeType[i]=shapeType[i+1];
        sRow[i]=sRow[i+1];
        sCol[i]=sCol[i+1];
        sW[i]=sW[i+1];
        sH[i]=sH[i+1];
    }

    shapeCount--;

    redrawAll();

    printf("Shape Deleted\n");
}

void modifyShape()
{
    int index;

    if(shapeCount==0)
    {
        printf("No shapes available\n");
        return;
    }

    listShape();

    printf("Enter Shape Index To Modify: ");
    scanf("%d",&index);

    if(index<0 || index>=shapeCount)
    {
        printf("Invalid Index\n");
        return;
    }

    printf("Enter New Type: ");
    scanf("%d",&shapeType[index]);

    printf("Enter New Row and Column: ");
    scanf("%d%d",&sRow[index],&sCol[index]);

    printf("Enter New Width/Size/Radius: ");
    scanf("%d",&sW[index]);

    printf("Enter New Height: ");
    scanf("%d",&sH[index]);

    redrawAll();

    printf("Shape Modified\n");
}

void saveDrawing()
{
    FILE *fp;
    int i,j;

    fp=fopen("drawing.txt","w");

    if(fp==NULL)
    {
        printf("Error Opening File\n");
        return;
    }

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
        {
            fputc(canvas[i][j],fp);
        }
        fputc('\n',fp);
    }

    fclose(fp);

    printf("Drawing Saved\n");
}

void loadDrawing()
{
    FILE *fp;
    int i,j;

    fp=fopen("drawing.txt","r");

    if(fp==NULL)
    {
        printf("drawing.txt not found\n");
        return;
    }

    for(i=0;i<30;i++)
    {
        for(j=0;j<60;j++)
        {
            canvas[i][j]=fgetc(fp);
        }
        fgetc(fp);
    }

    fclose(fp);

    printf("Drawing Loaded\n");
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
        printf("3. Delete Shape\n");
        printf("4. Modify Shape\n");
        printf("5. Clear Canvas\n");
        printf("6. List Shapes\n");
        printf("7. Exit\n");
        printf("8. Save Drawing\n");
        printf("9. Load Drawing\n");

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
                deleteShape();
                break;

            case 4:
                modifyShape();
                break;

            case 5:
                clearCanvas();
                shapeCount=0;
                printf("Canvas Cleared\n");
                break;

            case 6:
                listShape();
                break;

            case 7:
                printf("Exiting Program...\n");
                break;

            case 8:
                saveDrawing();
                break;

            case 9:
                loadDrawing();
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice!=7);

    return 0;
}
