/**
 * @file parsing_csv_file.c
 *
 * @brief Implementation of the CSV parser.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca - Carleton University
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca - Carleton University
 * @author Jason Miller - jasonmiller@cmail.carleton.ca - Carleton University
 */

#include "parsing_csv_file.h"

Boolean parser_parse_csv_file(char *file_name,
                              int lines_to_skip,
                              int *time_in_minutes,
                              char *sensor_name,
                              float *sensor_value)
{
    Boolean end_of_file;
    FILE *ifp;
    char buf[MAX_ROW_LIMIT];
    char *field;
    char *time_field;
    char save_ptr_line[MAX_ROW_LIMIT] = {'\0'};
    int time_field_count;
    int field_count = 0;
    int row_count = 0;
    int minutes;
    int hours;

    ifp = fopen(file_name, INPUT_MODE);
    if (ifp == NULL)
    {
        /*
         * If we fail to open the file, then we need to abort the program,
         * there is nothing to be done.
         */
        printf("Can't open input file %s\n", file_name);
        printf("Error - %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, MAX_ROW_LIMIT, ifp))
    {
        field_count = 0;
        row_count++;

        if (row_count <= lines_to_skip)
        {
            /*
             * We will have already parsed these lines, so we can skip them
             * from here on out.
             */
            continue;
        }

        field = strtok(buf, ",");
        while (field)
        {
            switch (field_count)
            {
            case 0: /* Timestamp */
                /*
                 * We need to be careful here - strtok is not reentrant, 
                 * and probably shouldn't be used here, but the reentrant
                 * version isn't available on Windows. So insead we will
                 * copy the time into a seperate string so we can parse
                 * that ourselves seperately.
                 */
                strcpy(&save_ptr_line[0], field);
                break;

            case 1: /* Sensor Name */
                strncpy(sensor_name, field, MAX_SENSOR_NAME_SIZE);
                break;

            case 2: /* Sensor Value*/
                (*sensor_value) = strtod(field, NULL);
                break;
            }

            field = strtok(NULL, ",");
            field_count++;
        }

        break;
    }

    /*
     * Here is where we can finally parse the timestamp. We have parsed a row
     * of the input file, and will not be parsing another line until we call
     * this function again. It will be safe to use strtok on a different string
     * at this point.
     */
    time_field_count = 0;
    time_field = strtok(save_ptr_line, ".");
    while (time_field)
    {
        switch (time_field_count)
        {
        case 0: /* Hours */
            hours = strtod(time_field, NULL);
            break;
        case 1: /* Minutes */
            minutes = strtod(time_field, NULL);
            break;
        }

        time_field = strtok(NULL, ".");
        time_field_count++;
    }

    (*time_in_minutes) = (hours * 60) + minutes;

    end_of_file = feof(ifp);
    fclose(ifp);
    return end_of_file;
}
