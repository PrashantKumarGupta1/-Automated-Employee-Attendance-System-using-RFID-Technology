// Step 1: Embedded system sends data via UART
// Format: RFID_ID + TIME + DATE
// Example: "123456789111 01:01:12 01/12/2024"


// Step 2: Linux system reads serial data
int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));


// Step 3: Extract RFID ID (first 12 characters)
for(i = 0; i < 12; i++)
    id[i] = read_buf[i];
id[i] = '\0';


// Step 4: Extract combined TIME + DATE
for(j = 13; j < 30; j++)
    time[j - 13] = read_buf[j];
time[j - 13] = '\0';


// Step 5: Split TIME and DATE into separate variables
sscanf(time, "%s %s", scan_time, scan_date);
// scan_time → "01:01:12"
// scan_date → "01/12/2024"


// Step 6: Open employee database
FILE *fp = fopen("database", "r");


// Step 7: Match RFID ID with database
while(fgets(s1, 50, fp))
{
    if(strstr(s1, id))
    {
        f = 1;

        // Extract employee name from database
        for(k = 13; s1[k] != '\n'; k++)
            name[k - 13] = s1[k];
        name[k - 13] = 0;


        // Step 8: Open attendance CSV file
        FILE *fq = fopen("attendance.csv", "a+");


        // Step 9: Add CSV header if file is empty
        fseek(fq, 0, SEEK_END);
        if(ftell(fq) == 0)
        {
            fprintf(fq, "RFID_ID,NAME,TYPE,TIME,DATE\n");
        }


        // Step 10: Count previous entries for IN/OUT logic
        while(fscanf(fq, "%s", s2) != -1)
        {
            if(strcmp(s2, name) == 0)
                c++;
        }


        // Step 11: IN / OUT decision logic
        if(c % 2 == 0)
        {
            fprintf(fq, "%s,%s,IN,%s,%s\n",
                    id, name, scan_time, scan_date);
        }
        else
        {
            fprintf(fq, "%s,%s,OUT,%s,%s\n",
                    id, name, scan_time, scan_date);
        }

        fclose(fq);
        break;
    }
}


// Step 12: Close database file
fclose(fp);



// Step 13: (Optional - Currently Disabled)
// New RFID card registration
/*
if(f == 0)
{
    printf("CARD NOT FOUND\n");
    printf("Enter employee name for this RFID\n");

    scanf("%s", name);

    FILE *file = fopen("database", "a+");
    fprintf(file, "%s %s\n", id, name);
    fclose(file);

    FILE *log_file = fopen("attendance.csv", "a+");
    fprintf(log_file, "%s,%s,IN,%s,%s\n",
            id, name, scan_time, scan_date);
    fclose(log_file);
}
*/
