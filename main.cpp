lude "coordinate.h"
#include <time.h>

static int global_coord_id = 0; // Global counter for coord_id

void add_coordinate(Coordinate **list_end, float x, float y) {
    Coordinate *new_coord = (Coordinate *)malloc(sizeof(Coordinate));
    if (!new_coord) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = ++global_coord_id;
    new_coord->next = NULL;

    if (*list_end) {
        new_coord->previous = *list_end;
        (*list_end)->next = new_coord;
    } else {
        new_coord->previous = NULL;
    }

    *list_end = new_coord;
}

void forward_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning;
    while (current) {
        printf("Coordinate ID: %d, X: %.2f, Y: %.2f\n", current->coord_id, current->x, current->y);
        current = current->next;
    }
}

void backward_display(Coordinate *list_end) {
    Coordinate *current = list_end;
    while (current) {
        printf("Coordinate ID: %d, X: %.2f, Y: %.2f\n", current->coord_id, current->x, current->y);
        current = current->previous;
    }
}

void delete_coordinate(Coordinate **list_beginning, int coord_id_to_delete) {
    Coordinate *current = *list_beginning;

    while (current) {
        if (current->coord_id == coord_id_to_delete) {
            if (current->previous) {
                current->previous->next = current->next;
            } else {
                *list_beginning = current->next;
            }

            if (current->next) {
                current->next->previous = current->previous;
            }

            free(current);
            printf("Coordinate with ID %d deleted.\n", coord_id_to_delete);
            return;
        }
        current = current->next;
    }

    printf("Coordinate with ID %d not found.\n", coord_id_to_delete);
}

int list_length(Coordinate *list_beginning) {
    int length = 0;
    Coordinate *current = list_beginning;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

void closest_to(Coordinate *list_beginning, float x, float y) {
    Coordinate *current = list_beginning;
    Coordinate *closest = NULL;
    float min_distance = -1;

    while (current) {
        float distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2));
        if (min_distance == -1 || distance < min_distance) {
            min_distance = distance;
            closest = current;
        }
        current = current->next;
    }

    if (closest) {
        printf("Closest coordinate: ID: %d, X: %.2f, Y: %.2f\n", closest->coord_id, closest->x, closest->y);
        printf("Distance: %.2f\n", min_distance);
    } else {
        printf("No coordinates found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_coordinates>\n", argv[0]);
        return 1;
    }

    int num_coordinates = atoi(argv[1]);
    if (num_coordinates <= 0) {
        printf("Invalid number of coordinates.\n");
        return 1;
    }

    srand(time(NULL));

    Coordinate *list_beginning = NULL;
    Coordinate *list_end = NULL;

    // Add random coordinates to the list
    for (int i = 0; i < num_coordinates; i++) {
        float x = (float)(rand() % 100) / 10.0;
        float y = (float)(rand() % 100) / 10.0;
        add_coordinate(&list_end, x, y);
        if (i == 0) {
            list_beginning = list_end;
        }
    }

    // Display the list from beginning to end
    printf("\nCoordinates (Forward Display):\n");
    forward_display(list_beginning);

    // Display the list from end to beginning
    printf("\nCoordinates (Backward Display):\n");
    backward_display(list_end);

    // Find the closest coordinate to a random point
    float random_x = (float)(rand() % 100) / 10.0;
    float random_y = (float)(rand() % 100) / 10.0;
    printf("\nClosest to (%.2f, %.2f):\n", random_x, random_y);
    closest_to(list_beginning, random_x, random_y);

    // Delete a random coordinate from the list
    int random_id_to_delete = (rand() % num_coordinates) + 1;
    printf("\nDeleting coordinate with ID %d:\n", random_id_to_delete);
    delete_coordinate(&list_beginning, random_id_to_delete);

    // Display the list again
    printf("\nCoordinates after deletion (Forward Display):\n");
    forward_display(list_beginning);

    return 0;
}

