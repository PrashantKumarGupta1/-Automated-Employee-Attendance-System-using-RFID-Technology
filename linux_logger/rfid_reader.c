/// C library headers
#include <stdio.h>      // Standard input-output functions like printf()
#include <string.h>     // String handling functions like strcmp(), strstr(), memset()

// Linux headers
#include <fcntl.h>      // File control options like O_RDWR
#include <errno.h>      // Error handling and strerror() function
#include <termios.h>    // POSIX terminal control definitions for serial communication
#include <unistd.h>     // Functions like read(), write(), close()

int main()
{

	/* Start of Program */

	int i,j,f=0;                     // Loop variables and flag variable
	char id[13],time[30];            // Buffers to store RFID ID and combined time/date
	char scan_time[15];              // Buffer to store extracted time
	char scan_date[15];              // Buffer to store extracted date

	// Example incoming data format from embedded system
	// 123456789111 01:01:12 01/12/2024


	// Infinite loop to continuously read RFID data
	while(1)
	{
		// Open serial port in read/write mode
		int serial_port = open("/dev/ttyUSB0", O_RDWR);

		// Structure used for configuring serial communication
		struct termios tty;

		// Read existing serial port settings
		if(tcgetattr(serial_port, &tty) != 0)
		{
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		// ----- Serial Port Configuration -----

		tty.c_cflag &= ~PARENB;      // Disable parity
		tty.c_cflag &= ~CSTOPB;      // Use one stop bit
		tty.c_cflag &= ~CSIZE;       // Clear data size bits
		tty.c_cflag |= CS8;          // Set 8 data bits
		tty.c_cflag &= ~CRTSCTS;     // Disable hardware flow control
		tty.c_cflag |= CREAD | CLOCAL; // Enable receiver and ignore modem lines

		tty.c_lflag &= ~ICANON;      // Disable canonical input mode
		tty.c_lflag &= ~ECHO;        // Disable echo
		tty.c_lflag &= ~ECHOE;       // Disable erase echo
		tty.c_lflag &= ~ECHONL;      // Disable newline echo
		tty.c_lflag &= ~ISIG;        // Disable signals (Ctrl+C etc.)

		tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
		tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable special input handling

		tty.c_oflag &= ~OPOST;       // Disable output processing
		tty.c_oflag &= ~ONLCR;       // Disable newline conversion

		tty.c_cc[VTIME] = 10;        // Timeout for read (1 second)
		tty.c_cc[VMIN] = 33;         // Minimum characters required

		// Set baud rate to 9600
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);

		// Apply serial port configuration
		if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
		{
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		// Buffer to store incoming serial data
		char read_buf[256];

		// Clear buffer before reading
		memset(&read_buf, '\0', sizeof(read_buf));

		// Read data from serial port
		int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

		// Check for read error
		if (num_bytes < 0)
		{
			printf("Error reading: %s", strerror(errno));
			return 1;
		}

		// Print received raw data
		printf("%s\n",read_buf);


		// -------- Extract RFID ID --------

		for(i=0;i<12;i++)
			id[i] = read_buf[i];     // Copy first 12 characters as RFID ID

		id[i] = '\0';               // Null terminate RFID string


		// -------- Extract Time + Date --------

		for(j=13;j<30;j++)
			time[j-13] = read_buf[j];   // Copy time and date section

		time[j-13] = '\0';          // Null terminate string

		printf("%s\n",time);        // Print extracted timestamp


		// Split time and date into two variables
		sscanf(time,"%s %s",scan_time,scan_date);


		int c=0,k;                  // Counter for IN/OUT logic
		char s1[50],s2[50],name[20];// Buffers for database and log processing

		// Open employee database file
		FILE *fp = fopen("database","r");

		// Read database line by line
		while(fgets(s1,50,fp))
		{
			// Check if RFID ID exists in database
			if(strstr(s1,id))
			{
				f = 1;  // Card found flag

				// Extract employee name from database line
				for(k=13;s1[k]!='\n';k++)
					name[k-13] = s1[k];

				name[k-13] = 0;  // Null terminate name

				printf("%s\n",name); // Print employee name


				// -------- Open CSV Attendance File --------

				FILE *fq = fopen("attendance.csv","a+");

				// Move file pointer to end
				fseek(fq,0,SEEK_END);

				// Check file size
				long size = ftell(fq);

				// If file is empty, write CSV header
				if(size == 0)
				{
					fprintf(fq,"RFID_ID,NAME,TYPE,TIME,DATE\n");
				}

				// Count previous entries of this employee
				while(fscanf(fq,"%s",s2)!=-1)
				{
					if(strcmp(s2,name)==0)
						c++;
				}

				// Even count → IN entry
				if(c%2==0)
				{
					fprintf(fq,"%s,%s,IN,%s,%s\n",id,name,scan_time,scan_date);
					fclose(fq);
					break;
				}

				// Odd count → OUT entry
				else
				{
					fprintf(fq,"%s,%s,OUT,%s,%s\n",id,name,scan_time,scan_date);
					fclose(fq);
					break;
				}
			}
		}


		/*
		If RFID card is not found in database
		This section allows adding new employee
		(Currently disabled)
		*/

		/*
		if(f==0)
		{
			printf("CARD NOT FOUND\n");
			printf("Enter employee name for this RFID\n");

			scanf("%s",name);

			FILE *file=fopen("database","a+");
			fprintf(file,"%s %s\n",id,name);
			fclose(file);

			FILE *log_file=fopen("attendance.csv","a+");
			fprintf(log_file,"%s,%s,IN,%s,%s\n",id,name,scan_time,scan_date);
			fclose(log_file);

			printf("New employee added successfully\n");
		}
		*/

		fclose(fp);   // Close database file
	}

}
