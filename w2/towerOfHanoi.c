#include <stdio.h>

void solveHanoi(int numDisks, char *fromRod, char *toRod, char *otherRod) {
    if (numDisks == 1) {
        printf("Move disk 1 from %s to %s\n", fromRod, toRod);
        return;
    }
    // Move n-1 disks from 'fromRod' to 'otherRod' using 'toRod' as auxiliary.
    solveHanoi(numDisks - 1, fromRod, otherRod, toRod);
    
    // Move the nth disk from 'fromRod' to 'toRod'.
    printf("Move disk %d from %s to %s\n", numDisks, fromRod, toRod);
    
    // Move the n-1 disks from 'otherRod' to 'toRod' using 'fromRod' as auxiliary.
    solveHanoi(numDisks - 1, otherRod, toRod, fromRod);
}

int main(void) {
    int numDisks;
    printf("Enter the number of disks: ");
    if (scanf("%d", &numDisks) != 1 || numDisks < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    
    // Use "A" as the source, "C" as the destination, and "B" as the auxiliary rod.
    solveHanoi(numDisks, "A", "C", "B");
    
    return 0;
}
