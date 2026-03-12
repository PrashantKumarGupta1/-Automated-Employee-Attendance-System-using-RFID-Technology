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

	/*Start of Program*/

	int i,j,f;                     // Loop variables and flag variable
	char id[13],time[30];          // Buffers to store RFID ID and time/date
	//123456789111 01:01:12 01/12/2024  (Example incoming format)


	// Open the serial port. Change device path as needed
	// (currently set to standard FTDI USB-UART cable device)
	while(1)                       // Infinite loop to continuously read RFID data
	{
		int serial_port = open("/dev/ttyUSB0", O_RDWR);  // Open serial port in read/write mode

		// Create new termios structure
		struct termios tty;        // Structure used for configuring serial communication

		// Read existing serial port settings
		if(tcgetattr(serial_port, &tty) != 0) {
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno)); // Print error message
			return 1;               // Exit program if error occurs
		}

		tty.c_cflag &= ~PARENB;    // Disable parity bit
		tty.c_cflag &= ~CSTOPB;    // Use one stop bit
		tty.c_cflag &= ~CSIZE;     // Clear data size bits
		tty.c_cflag |= CS8;        // Set 8 bits per byte
		tty.c_cflag &= ~CRTSCTS;   // Disable hardware flow control (RTS/CTS)
		tty.c_cflag |= CREAD | CLOCAL;  // Enable receiver and ignore modem control lines

		tty.c_lflag &= ~ICANON;    // Disable canonical mode (raw input)
		tty.c_lflag &= ~ECHO;      // Disable input echo
		tty.c_lflag &= ~ECHOE;     // Disable erase echo
		tty.c_lflag &= ~ECHONL;    // Disable newline echo
		tty.c_lflag &= ~ISIG;      // Disable special signal characters (Ctrl+C etc.)

		tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable software flow control
		tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable special input handling

		tty.c_oflag &= ~OPOST;     // Disable output processing
		tty.c_oflag &= ~ONLCR;     // Disable newline to CR/LF conversion

		// tty.c_oflag &= ~OXTABS;  // Prevent tab conversion (not supported on Linux)
		// tty.c_oflag &= ~ONOEOT;  // Prevent removal of EOT characters (not supported on Linux)

		tty.c_cc[VTIME] = 10;      // Timeout for read (1 second = 10 deciseconds)
		tty.c_cc[VMIN] = 33;       // Minimum characters required for read to return

		// Set baud rate to 9600
		cfsetispeed(&tty, B9600);  // Input speed
		cfsetospeed(&tty, B9600);  // Output speed

		// Apply serial port settings
		if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno)); // Print error
			return 1;               // Exit if configuration fails
		}

		// Write to serial port (currently disabled)
		// unsigned char msg[50] ={'v','e','c','t','o','r','\n'};
		// write(serial_port, msg, sizeof(msg));

		// usleep(100);             // Delay if needed

		// Allocate memory buffer for reading serial data
		char read_buf [256];       // Buffer to store incoming serial data

		// Clear buffer before receiving data
		memset(&read_buf, '\0', sizeof(read_buf));

		// Read data from serial port
		int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

		// Check if read error occurred
		if (num_bytes < 0) {
			printf("Error reading: %s", strerror(errno)); // Print error message
			return 1;
		}

		// Print received serial data
		printf("%s\n",read_buf);

		// Extract RFID ID (first 12 characters)
		for(i=0;i<12;i++)
			id[i]=read_buf[i];      // Copy RFID number
		id[i]='\0';                // Null terminate string

		// Extract date and time (remaining part)
		for(j=13;j<30;j++)
			time[j-13]=read_buf[j]; // Copy timestamp
		time[j-13]='\0';           // Null terminate time string

		printf("%s\n",time);       // Print extracted time

		int c=0,k;                 // Counter and loop variable
		char s1[50],s2[50],name[20]; // Buffers for database record, log record, and employee name

		FILE *fp=fopen("database","r"); // Open employee database file

		while(fgets(s1,50,fp))     // Read each line from database
		{     
			if(strstr(s1,id))      // Check if scanned RFID exists in database
			{   
                               f=1;  // Set flag if card found

				for(k=13;s1[k]!='\n';k++)   // Extract employee name from database line
					name[k-13]=s1[k];

				name[k-13]=0;       // Null terminate name string

				printf("%s\n",name); // Print employee name

				FILE *fq=fopen("log_file","a+"); // Open log file

				while(fscanf(fq,"%s",s2)!=-1)   // Read existing log entries
				{  
					if(strcmp(s2,name)==0)  // Count occurrences of employee name
						c++;
				}

				// Check IN or OUT entry based on count
				if(c%2==0)
				{
					fprintf(fq,"ID= %s NAME= %s IN-TIME %s \n",id,name,time); // Log IN time
					fclose(fq);
					break;
				}
				else
				{
					fprintf(fq,"ID= %s NAME= %s OUT-TIME %s \n",id,name,time); // Log OUT time
					fclose(fq);
					break;
				}
}
}

		/*
		If RFID card not found in database
		This code allows adding new employee details
		(Currently disabled)
		*/

		/*if(f==0)
		{
			printf("CARD NOT FOUND\r\nPLEASE ENTER THE NEW EMPLOYEE NAME\n");
			printf("enter the name for the rfid\n");
			scanf("%s",name);

			FILE *file=fopen("database","a+");
			fprintf(file,"%s %s\n",id,name);
			fclose(file);

			FILE *log_file=fopen("log_file","a+");
			fprintf(log_file,"%s %s %s\n",id,name,time);
			fclose(log_file);

			printf("new rfid and name added in database and log_file\n");
		}*/

		fclose(fp);   // Close database file
	}

}
