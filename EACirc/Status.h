#ifndef STATUS_H
#define STATUS_H

#define STAT_OK                                 0       // OK
#define STAT_NOT_IMPLEMENTED_YET                1       // REQUESTED BEHAVIOUR NOT IMPLEMENTED YET
#define STAT_NOT_ENOUGHT_MEMORY                 2       // NOT ENOUGHT MEMORY TO COMPLETE REQUESTED OPERATION, TRY TO INCREASE GIVEN MEMORY BUFFER SIZE
#define STAT_DATA_CORRUPTED                     3       // GIVEN DATA ARE NOT IN EXPECTED FORMAT
#define STAT_DATA_INCORRECT_LENGTH              4       // LENGTH OF GIVEN DATA IS INCORRECT
#define STAT_CIPHER_INIT_FAIL                   5       // FAIL TO INICIALIZE CIPHER ENGINE
#define STAT_ENCRYPT_FAIL                       6       // FAIL TO COMPLETE ENCRYPTION OPERATION
#define STAT_DECRYPT_FAIL                       7       // FAIL TO COMPLETE DECRYPTION OPERATION
#define STAT_FILE_OPEN_FAIL                     8       // FAIL TO OPEN TARGET FILE
#define STAT_NOT_ENOUGHT_DATA_TYPE              9       // GIVEN DATA VARIABLE IS UNABLE TO CONTAIN RETURN VALUE
#define STAT_USERDATA_BAD                       10      // DATA OBTAINED FROM USER INPUT ARE INVALID
#define STAT_KEY_LENGTH_BAD                     11      // KEY LENGTH DIFFERS FROM EXPECTED
#define STAT_CONFIG_DATA_READ_FAIL              12      // FAIL TO READ DATA FROM CONFIG FILE
#define STAT_INVALID_ARGUMETS                   13      // INVALID COMMAND LINE ARGUMENTS
#define STAT_CONFIG_INCORRECT                   14      // CONFIGURATION IS NOT CORRECT
#define STAT_INCOMPATIBLE_PARAMETER             15      // PARAMETER LOADED/FOUND IS NOT COMPATIBLE
#define STAT_FILE_WRITE_FAIL                    16      // FILE COULD NOT BE SAVED
#define STAT_CONFIG_SCRIPT_INCOMPLETE           17      // CONFIGURATION FILE IS INCOMPLETE
#define STAT_PROJECT_ERROR                      18      // ERROR IN PROJECT CLASSES
#define STAT_INTENTIONAL_EXIT                   19      // EXITING EACIRC INTENTIONALLY

const char* ErrorToString(int error);

#endif
