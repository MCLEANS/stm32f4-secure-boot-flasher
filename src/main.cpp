#include "main.h"
#include "iostream"

#define READ_CHUNK_SIZE 256

int main(int argc, char* argv[]){

    struct stat results;
    /* Size of the binary file in bytes */
    uint32_t binary_size = 0;

    const char* firmware_file = "../test_binary/firmware.bin";

    /** Check if the binary file exists and read its size */
    if(stat(firmware_file,&results) != 0){
        printf("Error in getting file details, check that file exists and is placed correctly\n");
    }else{
        binary_size = results.st_size;

        printf("Binary Size %u \n ", binary_size);
        char chunk_buffer[READ_CHUNK_SIZE];

        std::ifstream firmware_binary(firmware_file, std::ios::in | std::ios::binary);

        if(!firmware_binary){
            printf("Error opening binary file for reading \n");
            return -1;
        }

        int num_of_chunks = binary_size / READ_CHUNK_SIZE;
        int chunk_rem = binary_size % READ_CHUNK_SIZE;

        progressbar chunk_progress_bar(num_of_chunks);

        for(int i = 0; i < num_of_chunks; i++){
            memset(chunk_buffer,0,READ_CHUNK_SIZE);
            firmware_binary.read(chunk_buffer, READ_CHUNK_SIZE);
            chunk_progress_bar.update();
            usleep(20000);
        }

        /** Read remaining data that dont file a full chunk */
        if(chunk_rem > 0){
            memset(chunk_buffer,0,READ_CHUNK_SIZE);
            firmware_binary.read(chunk_buffer, chunk_rem + 1);
        }

        std::cout<<"\nbuffer position : "<<firmware_binary.tellg()<<std::endl;
        if(firmware_binary.eof()){
            printf("File successfully read \n");
        }

        /** Close binary file */
        firmware_binary.close();


    }
    return 0;
}