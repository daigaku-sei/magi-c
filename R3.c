#include <stdio.h>

void deleteAndInsertLine(const char* filename, int n, int m) {
    // Open the file in read mode
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    // Create a temporary file to store the modified content
    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(file);
        return;
    }

    char line[1000];
    int count = 1;

    // Read each line from the original file
    while (fgets(line, sizeof(line), file)) {
        // If the current line is the nth line, skip it
        if (count == n) {
            count++;
            continue;
        }

        // Write the line to the temporary file
        fputs(line, temp);

        // If the current line is the mth line, insert the nth line after it
        if (count == m) {
            // Open the original file again in read mode
            FILE* original = fopen(filename, "r");
            if (original == NULL) {
                printf("Unable to open the file.\n");
                fclose(file);
                fclose(temp);
                return;
            }

            // Skip m lines in the original file
            for (int i = 1; i <= m; i++) {
                fgets(line, sizeof(line), original);
            }

            // Write the nth line after the mth line
            fputs(line, temp);

            // Close the original file
            fclose(original);
        }

        count++;
    }

    // Close the files
    fclose(file);
    fclose(temp);

    // Remove the original file
    remove(filename);

    // Rename the temporary file to the original filename
    rename("temp.txt", filename);

    printf("Line deleted and inserted successfully.\n");
}

int main() {
    const char* filename = "example.txt";
    int n = 3;  // Line number to delete
    int m = 5;  // Line number to insert after

    deleteAndInsertLine(filename, n, m);

    return 0;
}
