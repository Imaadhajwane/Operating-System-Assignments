#include <stdio.h>
#include <stdlib.h>

// Function to display the movement of the disk head
void displayHeadMovement(int current, int next) {
    printf("Move disk head from %d to %d\n", current, next);
}

// Function to perform C-SCAN disk scheduling
int calculateTotalHeadMovementCSCAN(int requestSequence[], int numRequests, int initialPosition) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;
    int upperBound = 199;  // Assuming the disk size is 200

    // Sort the request sequence in ascending order
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requestSequence[j] > requestSequence[j + 1]) {
                // Swap the requests if they are out of order
                int temp = requestSequence[j];
                requestSequence[j] = requestSequence[j + 1];
                requestSequence[j + 1] = temp;
            }
        }
    }

    // Find the index of the current head position in the sorted sequence
    int currentIndex = 0;
    while (currentIndex < numRequests && requestSequence[currentIndex] < currentHeadPosition) {
        currentIndex++;
    }

    // Perform C-SCAN scheduling in the forward direction
    for (int i = currentIndex; i < numRequests; i++) {
        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i]);
        totalHeadMovement += abs(currentHeadPosition - requestSequence[i]);
        currentHeadPosition = requestSequence[i];
    }

    // Move to the upper bound
    displayHeadMovement(currentHeadPosition, upperBound);
    totalHeadMovement += abs(currentHeadPosition - upperBound);
    currentHeadPosition = upperBound;

    // Move to the lower bound
    displayHeadMovement(currentHeadPosition, 0);
    totalHeadMovement += abs(currentHeadPosition - 0);
    currentHeadPosition = 0;

    // Perform C-SCAN scheduling in the reverse direction
    for (int i = 0; i < currentIndex; i++) {
        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i]);
        totalHeadMovement += abs(currentHeadPosition - requestSequence[i]);
        currentHeadPosition = requestSequence[i];
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

    // Calculate and display the total head movement for C-SCAN
    int totalHeadMovement = calculateTotalHeadMovementCSCAN(requestSequence, numRequests, initialPosition);
    printf("Total head movement using C-SCAN: %d\n", totalHeadMovement);

    return 0;
}
/*
7
50
1
82,170,43,140,24,16,190*/
/*
Function displayHeadMovement(current, next):
    Print "Move disk head from", current, "to", next

Function calculateTotalHeadMovementCSCAN(requestSequence, numRequests, initialPosition):
    totalHeadMovement = 0
    currentHeadPosition = initialPosition
    upperBound = 199  // Assuming the disk size is 200

    // Sort the request sequence in ascending order
    Sort(requestSequence)

    // Find the index of the current head position in the sorted sequence
    currentIndex = 0
    While currentIndex < numRequests and requestSequence[currentIndex] < currentHeadPosition:
        currentIndex++

    // Perform C-SCAN scheduling in the forward direction
    For i = currentIndex to numRequests - 1:
        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i])
        totalHeadMovement += Abs(currentHeadPosition - requestSequence[i])
        currentHeadPosition = requestSequence[i]

    // Move to the upper bound
    displayHeadMovement(currentHeadPosition, upperBound)
    totalHeadMovement += Abs(currentHeadPosition - upperBound)
    currentHeadPosition = upperBound

    // Move to the lower bound
    displayHeadMovement(currentHeadPosition, 0)
    totalHeadMovement += Abs(currentHeadPosition - 0)
    currentHeadPosition = 0

    // Perform C-SCAN scheduling in the reverse direction
    For i = 0 to currentIndex - 1:
        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i])
        totalHeadMovement += Abs(currentHeadPosition - requestSequence[i])
        currentHeadPosition = requestSequence[i]

    Return totalHeadMovement

// Main function
Function main():
    numRequests, initialPosition = GetUserInput()

    // Get user input for the sequence of disk requests
    requestSequence = GetUserInputForSequence(numRequests)

    // Calculate and display the total head movement for C-SCAN
    totalHeadMovement = calculateTotalHeadMovementCSCAN(requestSequence, numRequests, initialPosition)
    Print "Total head movement using C-SCAN:", totalHeadMovement
*/