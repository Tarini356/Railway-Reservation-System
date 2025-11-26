#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constants ---
#define MAX_SEATS 10 // Total number of seats in the train car

// --- Data Structure for a Seat ---
struct Seat {
    int seat_number;
    int is_booked;      // 0 for Available, 1 for Booked
    char passenger_name[50];
};

// --- Function Prototypes ---
void display_menu();
void initialize_seats(struct Seat seats[]);
void display_seat_status(const struct Seat seats[]);
void book_seat(struct Seat seats[]);
void cancel_reservation(struct Seat seats[]);

// --- Main Function ---
int main() {
    struct Seat train_car[MAX_SEATS];
    int choice;

    // 1. Setup the system
    initialize_seats(train_car);

    // 2. Main loop for the system
    do {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input
            printf("\n\n❌ Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            choice = 0; // Force loop to continue
            continue;
        }

        switch (choice) {
            case 1:
                display_seat_status(train_car);
                break;
            case 2:
                book_seat(train_car);
                break;
            case 3:
                cancel_reservation(train_car);
                break;
            case 4:
                printf("\n\n👋 Thank you for using the Railway Reservation System. Goodbye!\n\n");
                break;
            default:
                printf("\n\n⚠️ Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
        printf("\n----------------------------------------\n");

    } while (choice != 4);

    return 0;
}

// ----------------------------------------
// --- Function Implementations ---
// ----------------------------------------

/**
 * @brief Displays the main menu options to the user.
 */
void display_menu() {
    printf("\n\n========================================\n");
    printf("     🚄 RAILWAY RESERVATION SYSTEM\n");
    printf("========================================\n");
    printf("1. Display Seat Status\n");
    printf("2. Book a Seat\n");
    printf("3. Cancel Reservation\n");
    printf("4. Exit\n");
    printf("----------------------------------------\n");
}

/**
 * @brief Initializes all seats to 'Available'.
 * @param seats The array of Seat structures.
 */
void initialize_seats(struct Seat seats[]) {
    for (int i = 0; i < MAX_SEATS; i++) {
        seats[i].seat_number = i + 1; // Seat numbers from 1 to MAX_SEATS
        seats[i].is_booked = 0;
        strcpy(seats[i].passenger_name, "");
    }
}

/**
 * @brief Prints the current status of all seats. [attachment_0](attachment)
 * @param seats The array of Seat structures.
 */
void display_seat_status(const struct Seat seats[]) {
    int available_count = 0;
    printf("\n\n--- CURRENT SEAT STATUS ---\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i].is_booked == 1) {
            printf("Seat %-2d: **BOOKED** (Passenger: %s)\n", 
                   seats[i].seat_number, 
                   seats[i].passenger_name);
        } else {
            printf("Seat %-2d: Available\n", seats[i].seat_number);
            available_count++;
        }
    }
    printf("\nTotal Available Seats: **%d** / %d\n", available_count, MAX_SEATS);
}

/**
 * @brief Handles the process of booking an available seat.
 * @param seats The array of Seat structures.
 */
void book_seat(struct Seat seats[]) {
    int seat_num;
    char name_buffer[50];

    printf("\n--- SEAT BOOKING ---\n");
    printf("Enter seat number (1 to %d) to book: ", MAX_SEATS);
    if (scanf("%d", &seat_num) != 1) {
        printf("\n❌ Invalid input for seat number.\n");
        while(getchar() != '\n');
        return;
    }
    // Clear buffer after number input
    while(getchar() != '\n'); 

    // 1. Input Validation
    if (seat_num < 1 || seat_num > MAX_SEATS) {
        printf("\n❌ Invalid seat number. Please choose between 1 and %d.\n", MAX_SEATS);
        return;
    }

    // Adjust to array index (0-based)
    int index = seat_num - 1;

    // 2. Check Availability
    if (seats[index].is_booked == 1) {
        printf("\n❌ Seat %d is already booked by %s.\n", seat_num, seats[index].passenger_name);
        return;
    }

    // 3. Get Passenger Name
    printf("Enter passenger name (max 49 chars): ");
    if (fgets(name_buffer, sizeof(name_buffer), stdin) == NULL) {
        printf("\n❌ Error reading name.\n");
        return;
    }
    // Remove trailing newline character from fgets
    name_buffer[strcspn(name_buffer, "\n")] = 0; 

    if (strlen(name_buffer) == 0) {
         printf("\n❌ Name cannot be empty.\n");
        return;
    }


    // 4. Perform Booking
    seats[index].is_booked = 1;
    strcpy(seats[index].passenger_name, name_buffer);
    printf("\n✅ SUCCESS! Seat **%d** has been booked for **%s**.\n", seat_num, seats[index].passenger_name);
}

/**
 * @brief Handles the process of canceling a booked seat.
 * @param seats The array of Seat structures.
 */
void cancel_reservation(struct Seat seats[]) {
    int seat_num;

    printf("\n--- CANCELLATION ---\n");
    printf("Enter seat number (1 to %d) to cancel: ", MAX_SEATS);
    if (scanf("%d", &seat_num) != 1) {
        printf("\n❌ Invalid input for seat number.\n");
        while(getchar() != '\n');
        return;
    }

    // 1. Input Validation
    if (seat_num < 1 || seat_num > MAX_SEATS) {
        printf("\n❌ Invalid seat number. Please choose between 1 and %d.\n", MAX_SEATS);
        return;
    }

    // Adjust to array index (0-based)
    int index = seat_num - 1;

    // 2. Check if Booked
    if (seats[index].is_booked == 0) {
        printf("\n❌ Seat %d is already available (not booked).\n", seat_num);
        return;
    }

    // 3. Perform Cancellation
    printf("\nAre you sure you want to cancel the reservation for **%s** on seat %d? (y/n): ", 
           seats[index].passenger_name, seat_num);
    
    char confirmation;
    // Clear buffer after previous number input
    while(getchar() != '\n'); 

    if (scanf("%c", &confirmation) != 1 || (confirmation != 'y' && confirmation != 'Y')) {
        printf("\n⚠️ Cancellation aborted.\n");
        return;
    }

    seats[index].is_booked = 0;
    strcpy(seats[index].passenger_name, ""); // Clear the name
    printf("\n✅ SUCCESS! Reservation for seat **%d** has been **cancelled**.\n", seat_num);
}