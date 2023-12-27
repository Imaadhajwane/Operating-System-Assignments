// Elevator Algorithm, move in one direction will its very end (moves till the last of that side, but while coming back it does not
// move till the ending of the other side)


#include <stdio.h>
#include <stdlib.h>

// Function to display the movement of the disk head
void displayHeadMovement(int current, int next) {
    printf("Move disk head from %d to %d\n", current, next);
}

// Function to calculate the total head movement using SCAN algorithm
int calculateTotalHeadMovement(int requestSequence[], int numRequests, int initialPosition, int direction) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialPosition;

    // Sort the request sequence based on the direction
    if (direction == 0) {
        // Sort in ascending order
        for (int i = 0; i < numRequests - 1; i++) {
            for (int j = 0; j < numRequests - i - 1; j++) {
                if (requestSequence[j] > requestSequence[j + 1]) {
                    // Swap
                    int temp = requestSequence[j];
                    requestSequence[j] = requestSequence[j + 1];
                    requestSequence[j + 1] = temp;
                }
            }
        }
    } else {
        // Sort in descending order
        for (int i = 0; i < numRequests - 1; i++) {
            for (int j = 0; j < numRequests - i - 1; j++) {
                if (requestSequence[j] < requestSequence[j + 1]) {
                    // Swap
                    int temp = requestSequence[j];
                    requestSequence[j] = requestSequence[j + 1];
                    requestSequence[j + 1] = temp;
                }
            }
        }
    }

    // Find the index of the current head position in the sorted sequence
    int currentIndex = 0;
    while (currentIndex < numRequests && requestSequence[currentIndex] < currentHeadPosition) {
        currentIndex++;
    }

    // Perform SCAN scheduling
    for (int i = currentIndex; i < numRequests; i++) {
        // Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i]);

        // Update the total head movement
        totalHeadMovement += abs(currentHeadPosition - requestSequence[i]);

        // Update the current head position
        currentHeadPosition = requestSequence[i];
    }

    // Move to the end or beginning depending on the direction
    if (direction == 0) {
        // Move to the end
        displayHeadMovement(currentHeadPosition, 199); // Assuming the disk size is 200
        totalHeadMovement += abs(currentHeadPosition - 199);
    } else {
        // Move to the beginning
        displayHeadMovement(currentHeadPosition, 0);
        totalHeadMovement += abs(currentHeadPosition);
    }

    return totalHeadMovement;
}

int main() {
    int numRequests, initialPosition, direction;

    // Get user input for the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    // Get user input for the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initialPosition);

    // Get user input for the direction (0 for left, 1 for right)
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Get user input for the sequence of disk requests
    int requestSequence[numRequests];
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requestSequence[i]);
    }

    // Calculate and display the total head movement for SCAN
    int totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition, direction);
    printf("Total head movement using SCAN: %d\n", totalHeadMovement);

    return 0;
}
/*
7
50
1
82,170,43,140,24,16,190*/
/*
function displayHeadMovement(current, next):
    print "Move disk head from " + current + " to " + next

function calculateTotalHeadMovement(requestSequence, numRequests, initialPosition, direction):
    totalHeadMovement = 0
    currentHeadPosition = initialPosition

    # Sort the request sequence based on the direction
    if direction == 0:
        # Sort in ascending order
        sort(requestSequence)  # Assume a sorting function
    else:
        # Sort in descending order
        reverseSort(requestSequence)  # Assume a reverse sorting function

    # Find the index of the current head position in the sorted sequence
    currentIndex = 0
    while currentIndex < numRequests and requestSequence[currentIndex] < currentHeadPosition:
        currentIndex++

    # Perform SCAN scheduling
    for i in currentIndex to numRequests - 1:
        # Display the head movement
        displayHeadMovement(currentHeadPosition, requestSequence[i])

        # Update the total head movement
        totalHeadMovement += abs(currentHeadPosition - requestSequence[i])

        # Update the current head position
        currentHeadPosition = requestSequence[i]

    # Move to the end or beginning depending on the direction
    if direction == 0:
        # Move to the end
        displayHeadMovement(currentHeadPosition, 199)  # Assuming the disk size is 200
        totalHeadMovement += abs(currentHeadPosition - 199)
    else:
        # Move to the beginning
        displayHeadMovement(currentHeadPosition, 0)
        totalHeadMovement += abs(currentHeadPosition)

    return totalHeadMovement

# Main program
numRequests = input("Enter the number of disk requests: ")
initialPosition = input("Enter the initial position of the disk head: ")
direction = input("Enter the direction (0 for left, 1 for right): ")

# Get user input for the sequence of disk requests
requestSequence = []
print("Enter the disk request sequence:")
for i in range(numRequests):
    request = input("Request " + str(i + 1) + ": ")
    requestSequence.append(request)

# Calculate and display the total head movement for SCAN
totalHeadMovement = calculateTotalHeadMovement(requestSequence, numRequests, initialPosition, direction)
print("Total head movement using SCAN: " + totalHeadMovement)
*/