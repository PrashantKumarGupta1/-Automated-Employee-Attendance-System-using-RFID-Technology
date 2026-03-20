// C libraries
#include <stdio.h>      // Standard input-output functions (printf, scanf)
#include <string.h>     // String handling functions (strstr, strcmp, memset)

// Linux headers for serial communication
#include <fcntl.h>      // File control (open)
#include <errno.h>      // Error handling
#include <termios.h>    // UART configuration
#include <unistd.h>     // read, write, close

int main()
{
    int i, j, f;                      // i, j → loop counters | f → flag for card found
    char id[13], time[30];            // id → 12-byte RFID | time → timestamp string

    while(1)                          // Infinite loop for continuous scanning
    {
        int serial_port = open("/dev/ttyUSB0", O_RDWR); // Open serial port

        struct termios tty;           // Structure to hold UART settings

        if(tcgetattr(serial_port, &tty) != 0) { // Get current UART settings
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
            return 1;
        }

        tty.c_cflag &= ~PARENB;       // Disable parity bit
        tty.c_cflag &= ~CSTOPB;       // Use 1 stop bit
        tty.c_cflag &= ~CSIZE;        // Clear data size bits
        tty.c_cflag |= CS8;           // Set 8-bit data
        tty.c_cflag &= ~CRTSCTS;      // Disable hardware flow control
        tty.c_cflag |= CREAD | CLOCAL;// Enable receiver, ignore modem control

        tty.c_lflag &= ~ICANON;       // Disable canonical mode (raw input)
        tty.c_lflag &= ~ECHO;         // Disable echo
        tty.c_lflag &= ~ECHOE;        // Disable erase echo
        tty.c_lflag &= ~ECHONL;       // Disable newline echo
        tty.c_lflag &= ~ISIG;         // Disable signal chars (Ctrl+C etc.)

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Raw input

        tty.c_oflag &= ~OPOST;        // Disable output processing
        tty.c_oflag &= ~ONLCR;        // Disable newline conversion

        tty.c_cc[VTIME] = 10;         // Read timeout (1 second)
        tty.c_cc[VMIN] = 33;          // Minimum 33 bytes required

        cfsetispeed(&tty, B9600);     // Set input baud rate
        cfsetospeed(&tty, B9600);     // Set output baud rate

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) { // Apply UART config
            printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            return 1;
        }

        char read_buf[256];           // Buffer to store received UART data
        memset(&read_buf, '\0', sizeof(read_buf)); // Clear buffer

        int num_bytes = read(serial_port, &read_buf, sizeof(read_buf)); // Read data

        if (num_bytes < 0) {          // Check read error
            printf("Error reading: %s", strerror(errno));
            return 1;
        }

        printf("Received: %s\n", read_buf); // Print received data

        for(i = 0; i < 12; i++)       // Extract first 12 chars (RFID ID)
            id[i] = read_buf[i];
        id[i] = '\0';                 // Null terminate ID string

        for(j = 13; j < 30; j++)      // Extract timestamp (skip space at index 12)
            time[j - 13] = read_buf[j];
        time[j - 13] = '\0';          // Null terminate time string

        printf("Timestamp: %s\n", time); // Print timestamp

        char only_time[15], only_date[15]; // Buffers for separated values
        sscanf(time, "%s %s", only_time, only_date); // Split time & date

        int c = 0, k;                 // c → entry count | k → loop variable
        char s1[50], name[20];        // s1 → database line | name → employee name

        f = 0;                        // Initialize flag (card not found)

        FILE *fp = fopen("database", "r"); // Open database file

        while(fp && fgets(s1, 50, fp)) // Read each line from database
        {
            if(strstr(s1, id))        // Check if ID exists
            {
                f = 1;                // Mark as found

                for(k = 13; s1[k] != '\n'; k++) // Extract name after ID
                    name[k - 13] = s1[k];
                name[k - 13] = 0;     // Null terminate name

                printf("Employee: %s\n", name); // Print name

                FILE *fq = fopen("attendance.csv", "a+"); // Open CSV file

                fseek(fq, 0, SEEK_END); // Move to end of file
                if(ftell(fq) == 0)      // If file is empty
                {
                    fprintf(fq, "ID,NAME,STATUS,TIME,DATE\n"); // Add header
                }

                rewind(fq);             // Move pointer to beginning

                char file_id[20], file_name[20], status[10], t[20], d[20];

                while(fscanf(fq, "%[^,],%[^,],%[^,],%[^,],%s\n",
                             file_id, file_name, status, t, d) != EOF)
                {
                    if(strcmp(file_name, name) == 0) // Match employee name
                        c++;          // Count entries
                }

                if(c % 2 == 0)        // Even count → IN
                {
                    fprintf(fq, "%s,%s,IN,%s,%s\n",
                            id, name, only_time, only_date);
                    printf("IN marked\n");
                }
                else                  // Odd count → OUT
                {
                    fprintf(fq, "%s,%s,OUT,%s,%s\n",
                            id, name, only_time, only_date);
                    printf("OUT marked\n");
                }

                fclose(fq);           // Close CSV file
                break;                // Exit loop after match
            }
        }
/*
        if(f == 0)                    // If ID not found in database
        {
            printf("CARD NOT FOUND\nEnter employee name: ");
            scanf("%s", name);        // Take new employee name

            FILE *file = fopen("database", "a+"); // Open database file
            fprintf(file, "%s %s\n", id, name);   // Add new record
            fclose(file);            // Close database

            FILE *fq = fopen("attendance.csv", "a+"); // Open CSV

            fseek(fq, 0, SEEK_END);  // Move to end
            if(ftell(fq) == 0)       // If empty
            {
                fprintf(fq, "ID,NAME,STATUS,TIME,DATE\n"); // Add header
            }

            fprintf(fq, "%s,%s,IN,%s,%s\n",
                    id, name, only_time, only_date); // First entry as IN

            fclose(fq);              // Close CSV

            printf("New employee added & IN marked\n");
        }

        if(fp) fclose(fp);           // Close database file
        close(serial_port);          // Close serial port*/
    }
}
