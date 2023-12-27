#include <stdio.h>
#include <stdlib.h>

// Function to display the movement of the disk head
void displayHeadMovement(int current, int next) {
    printf("Move disk head from %d to %d\n", current, next);
}

// Function to calculate the total head movement
int calculateTotalHeadMovement(int requestSequence[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;

    // Traverse the request sequence
    for (int i = 0; i < numRequests; i++) {
        // Calculate the absolute difference between current and next request
        int movement = abs(currentHeadPosition - requestSequence[i]);

        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i]);

        // Update the current head position
        currentHeadPosition = requestSequence[i];

        // Add the movement to the total head movement
        totalHeadMovement += movement;
    }

    return totalHeadMovement;
}

int main() {
    int numRequests, initialPosition;

    // Get user input for the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    // Get user input for the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initialPosition);

    // Get user input for the sequence of disk requests
    int requestSequence[numRequests];
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requestSequence[i]);
    }

    // Calculate and display the total head movement
    int totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition);
    printf("Total head movement using FIFO: %d\n", totalHeadMovement);

    return 0;
}
/*
7
50
82,170,43,140,24,16,190
*/
/*
function displayHeadMovement(current, next)
    print "Move disk head from " + current + " to " + next

function calculateTotalHeadMovement(requestSequence[], numRequests, initialPosition)
    totalHeadMovement = 0
    currentHeadPosition = initialPosition

    for i = 0 to numRequests - 1
        movement = absolute(currentHeadPosition - requestSequence[i])
        displayHeadMovement(currentHeadPosition, requestSequence[i])
        currentHeadPosition = requestSequence[i]
        totalHeadMovement += movement

    return totalHeadMovement

function main()
    numRequests = user_input("Enter the number of disk requests")
    initialPosition = user_input("Enter the initial position of the disk head")

    for i = 0 to numRequests - 1
        requestSequence[i] = user_input("Enter disk request " + (i + 1))

    totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition)
    print "Total head movement using FIFO: " + totalHeadMovement
*/