/*!
 * @file sender.c
 *
 * Beispiel 3
 *
 *@brief Using Semaphores and Shared memory to simulate Server/Client message(sender/receiver)
 *
 * @author Dennis Addo ic16b026
 * @author Robert Niedermaier ic16b089
 * @details More information about the project can be found here
 * @see URL:https://cis.technikum-wien.at/documents/bic/2/bes/semesterplan/lu/beispiel3.html
 *
 * @date 15/05/2017
 *
 * @version 1.0
 *
 * @todo All implentations must be contained in one method structure unless these functions
 * @     are required by other programs/methods
 * @todo ALL errors must be the GNU C EXIT_SUCCESS and FAILURE macros
 * @todo perror and sterror is used to display error informations, functions and error-types
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include "sharedlib.h"


/*! programName   global pointer to hold the program name */
static const char *programName = NULL;


/**\brief
 * Sender:
 * The sender process reads characters from stdin and "sends" these characters to the receiver
 * by writing the characters into the ring buffer. After a new character has been written,
 * the sender process signals the availability of new data to the receiver process
 * (i.e., the processing of the data shall take place in a character by character fashion).
 * - Note that the sending process is allowed to continue writing characters into the ring buffer
 * until memory elements are available in the ring buffer (i.e., initially N memeory elements).
 * Once no more unoccupied memory elements are available, the sending process shall be blocked
 * until at least one unoccupied memory element is available again.
 *
 *
 *
 *
 * */








int main(int argc, char *argv[]) {


    shmseg shm;
    size_t size;
    programName = argv[0];


    if( EXIT_FAILURE == (args_parser(argc,argv,&size)) ){
        return EXIT_FAILURE;
    }
    /* initialise shared memory for read/write by giving a "0" */
    if( shmseg_easy_init(&size,0,&shm) == -1){
        shmseg_easy_clean(&shm);
        return EXIT_FAILURE;
    }

    int c;

    do{
        if (ferror(stdin)) {
            fprintf(stderr, "%s -> fgetc: %s \n", programName, strerror(errno));
            shmseg_easy_clean(&shm);
            return EXIT_FAILURE;
        }

        c = fgetc(stdin);

        if (c == EOF) {
            fprintf(stderr, " fgetc : %s %s \n", programName, strerror(errno));
            shmseg_easy_clean(&shm);
            return -1;
        }

        shm.s_write(&c);

    }while (c != EOF);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, " fflush : %s %s \n", programName, strerror(errno));
        shmseg_easy_clean(&shm);
        return -1;
    }


    return shmseg_easy_clean(&shm);


}
