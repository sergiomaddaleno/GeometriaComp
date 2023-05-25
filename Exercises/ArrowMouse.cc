#include <graphics.h>
#include <stdio.h>

int main()
{
    // Initialize graphics window
    initwindow(640, 480, "Arrow Demo");

    // Set up arrow parameters
    int arrowWidth = 10;
    int arrowHeight = 20;
    int arrowStartX = 50;
    int arrowStartY = 50;

    // Draw initial arrow
    setcolor(YELLOW);
    line(arrowStartX, arrowStartY, arrowStartX + arrowWidth, arrowStartY);
    line(arrowStartX + arrowWidth, arrowStartY, arrowStartX + arrowWidth - arrowHeight, arrowStartY + arrowHeight);
    line(arrowStartX + arrowWidth, arrowStartY, arrowStartX + arrowWidth - arrowHeight, arrowStartY - arrowHeight);

    // Loop until user presses a key
    while (!kbhit()) {
        // Get mouse position
        int mouseX = mousex();
        int mouseY = mousey();

        // Update arrow size based on mouse position
        arrowWidth = mouseX / 10;
        arrowHeight = mouseY / 10;

        // Redraw arrow with new size
        cleardevice();
        setcolor(YELLOW);
        line(arrowStartX, arrowStartY, arrowStartX + arrowWidth, arrowStartY);
        line(arrowStartX + arrowWidth, arrowStartY, arrowStartX + arrowWidth - arrowHeight, arrowStartY + arrowHeight);
        line(arrowStartX + arrowWidth, arrowStartY, arrowStartX + arrowWidth - arrowHeight, arrowStartY - arrowHeight);
    }

    // Close graphics window
    closegraph();
    return 0;
}
