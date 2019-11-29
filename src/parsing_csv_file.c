/**
 * Implementation of the CSV parser.
 */
#include "parsing_csv_file.h"

Boolean parser_parse_csv_file(char *file_name,
                              int lines_to_skip,
                              int *time_in_minutes,
                              char *sensor_name,
                              float *sensor_value)
{
    Boolean end_of_file;
    float   time;
    FILE    *ifp;
    char    buf[MAX_ROW_LIMIT];
    char    *field;
    int     field_count = 0;
    int     remainder;
    int     row_count = 0;
    int     temp;

    ifp = fopen(file_name, INPUT_MODE);
    if (ifp == NULL)
    {
        /**
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
            /**
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
                    time = strtod(field, NULL);
                    temp = time * 100;
                    remainder = (temp % 100);
                    (*time_in_minutes) = ((int)time * 60) + remainder;
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

    end_of_file = feof(ifp);
    fclose(ifp);
    return end_of_file;
}
