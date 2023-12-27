// SSTF = Shortest Seek Time First
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

    // Array to track whether a request has been visited
    int visited[numRequests];
    for (int i = 0; i < numRequests; i++) {
        visited[i] = 0; // Initialize all requests as not visited
    }

    // Perform SSTF scheduling
    for (int i = 0; i < numRequests; i++) {
        int minSeekTime = INT_MAX;
        int nextIndex = -1;

        // Find the closest unvisited request
        for (int j = 0; j < numRequests; j++) {
            if (!visited[j]) {
                int seekTime = abs(currentHeadPosition - requestSequence[j]);
                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    nextIndex = j;
                }
            }
        }

        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[nextIndex]);

        // Update the total head movement
        totalHeadMovement += minSeekTime;

        // Update the current head position
        currentHeadPosition = requestSequence[nextIndex];

        // Mark the request as visited
        visited[nextIndex] = 1;
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

    // Calculate and display the total head movement for SSTF
    int totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition);
    printf("Total head movement using SSTF: %d\n", totalHeadMovement);

    return 0;
}
/*
7
50
82,170,43,140,24,16,190*/
/*
function displayHeadMovement(current, next):
    print "Move disk head from", current, "to", next

function calculateTotalHeadMovement(requestSequence, numRequests, initialPosition):
    totalHeadMovement = 0
    currentHeadPosition = initialPosition
    visited = array of size numRequests initialized to false

    for i from 0 to numRequests - 1:
        minSeekTime = INFINITY
        nextIndex = -1

        for j from 0 to numRequests - 1:
            if not visited[j]:
                seekTime = abs(currentHeadPosition - requestSequence[j])
                if seekTime < minSeekTime:
                    minSeekTime = seekTime
                    nextIndex = j

        displayHeadMovement(currentHeadPosition, requestSequence[nextIndex])
        totalHeadMovement += minSeekTime
        currentHeadPosition = requestSequence[nextIndex]
        visited[nextIndex] = true

    return totalHeadMovement

function main():
    numRequests = user_input("Enter the number of disk requests")
    initialPosition = user_input("Enter the initial position of the disk head")
    requestSequence = array of size numRequests

    for i from 0 to numRequests - 1:
        requestSequence[i] = user_input("Enter disk request " + (i + 1))

    totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition)
    print "Total head movement using SSTF:", totalHeadMovement
*/