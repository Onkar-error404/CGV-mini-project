#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

#define MAX_STACK_SIZE 10
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ELEMENT_HEIGHT 0.2
#define ELEMENT_WIDTH 0.8

int stack[MAX_STACK_SIZE];
int top = -1;

void push(int value) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("Stack is full. Cannot push.\n");
        return;
    }
    stack[++top] = value;
    glutPostRedisplay(); // Trigger window redraw
}

void pop() {
    if (top == -1) {
        printf("Stack is empty. Cannot pop.\n");
        return;
    }
    top--;
    glutPostRedisplay(); // Trigger window redraw
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);

    float windowCenterX = 0.0; // Center position of the window
    float windowCenterY = 0.0;

    // Calculate the total height occupied by the containers
    float totalHeight = (top + 1) * ELEMENT_HEIGHT;

    // Calculate the starting position of the last container
    float startPosY = windowCenterY - totalHeight / 2.0 + ELEMENT_HEIGHT / 2.0;

    if (top == -1) {
        // Draw container rectangle for an empty stack
        float xPos = windowCenterX - ELEMENT_WIDTH / 2.0;
        float yPos = windowCenterY - ELEMENT_HEIGHT / 2.0;

        glBegin(GL_LINE_LOOP);
        glVertex2f(xPos, yPos - ELEMENT_HEIGHT / 2.0);
        glVertex2f(xPos, yPos + ELEMENT_HEIGHT / 2.0);
        glVertex2f(xPos + ELEMENT_WIDTH, yPos + ELEMENT_HEIGHT / 2.0);
        glVertex2f(xPos + ELEMENT_WIDTH, yPos - ELEMENT_HEIGHT / 2.0);
        glEnd();

        // Draw "Empty" label
        glColor3f(1.0, 0.0, 0.0); // Red color
        glRasterPos2f(xPos - 0.2, yPos);
        const char* emptyLabel = "Empty";
        int labelLength = strlen(emptyLabel);
        for (int j = 0; j < labelLength; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, emptyLabel[j]);
        }
    } else {
        for (int i = 0; i <= top; i++) {
            float xPos = windowCenterX - ELEMENT_WIDTH / 2.0;
            float yPos = startPosY + i * ELEMENT_HEIGHT;

            // Draw container rectangle
            glBegin(GL_LINE_LOOP);
            glVertex2f(xPos, yPos - ELEMENT_HEIGHT / 2.0);
            glVertex2f(xPos, yPos + ELEMENT_HEIGHT / 2.0);
            glVertex2f(xPos + ELEMENT_WIDTH, yPos + ELEMENT_HEIGHT / 2.0);
            glVertex2f(xPos + ELEMENT_WIDTH, yPos - ELEMENT_HEIGHT / 2.0);
            glEnd();

            // Get the number string
            char buffer[10];
            sprintf(buffer, "%d", stack[i]);

            // Calculate the center alignment
            int numLength = strlen(buffer);
            float xOffset = (ELEMENT_WIDTH - numLength * 0.18) / 2.0;

            // Calculate the raster position
            float rasterX = xPos + xOffset;
            float rasterY = yPos - ELEMENT_HEIGHT / 4.0;

            // Set the raster position
            glRasterPos2f(rasterX, rasterY);

            // Draw element value
            for (int j = 0; j < numLength; j++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[j]);
            }
        }
    }

    // Draw pointer to top element
    if (top >= 0) {
        float xPos = windowCenterX - ELEMENT_WIDTH / 2.0 - 0.1;
        float yPos = startPosY + top * ELEMENT_HEIGHT + ELEMENT_HEIGHT / 2.0;

        // Draw pointer line
        glBegin(GL_LINES);
        glVertex2f(xPos, yPos);
        glVertex2f(xPos - 0.2, yPos + 0.1);
        glEnd();

        // Draw "top" label
        glColor3f(1.0, 0.0, 0.0); // Red color
        glRasterPos2f(xPos - 0.25, yPos + 0.15);
        const char* topLabel = "top";
        int labelLength = strlen(topLabel);
        for (int j = 0; j < labelLength; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, topLabel[j]);
        }
    }

    glFlush();
    glutSwapBuffers();
}




void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
        case 'P':
            if (top == -1)
                printf("Stack is empty.\n");
            else
                pop();
            break;
        case 's':
        case 'S':
            if (top == -1)
                printf("Stack is empty.\n");
            else {
                printf("Stack contents: ");
                for (int i = top; i >= 0; i--)
                    printf("%d ", stack[i]);
                printf("\n");
            }
            break;
        case 'u':
        case 'U': {
            int value;
            printf("Enter a value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        }
        default:
            break;
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Stack Display");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

