#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXR_REC 10  
#define MAX_BLOCK_SIZE 256      
typedef struct {
    int cle;  //  for sorting *imprtant one
    int data; // Other data 
} Tenreg;
typedef struct {
    Tenreg records[MAXR_REC];
    int NB;  
} Tbloc;

bool read_block(FILE *file, Tbloc *buffer) {
    if (fread(buffer, sizeof(Tbloc), 1, file) == 1) {
        return true;
    }
    return false; 
}
void write_block(FILE *file, Tbloc *buffer) {
    fwrite(buffer, sizeof(Tbloc), 1, file);
}
void merge_files(const char *file1_name, const char *file2_name, const char *file3_name) {
    FILE *file1 = fopen(file1_name, "rb");
    FILE *file2 = fopen(file2_name, "rb");
    FILE *file3 = fopen(file3_name, "wb");
    if (!file1 || !file2 || !file3) {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }
    Tbloc buf1, buf2, buf3;
    int i1 = 1, i2 = 1, i3 = 1;
    int j1 = 0, j2 = 0, j3 = 0;
    bool continu = true;
    bool buf1_loaded = read_block(file1, &buf1);
    bool buf2_loaded = read_block(file2, &buf2);
    buf3.NB = 0;

    while (continu) {
        if (j1 < buf1.NB && j2 < buf2.NB) {
            Tenreg e1 = buf1.records[j1];
            Tenreg e2 = buf2.records[j2];
            Tenreg e;
            //  s8ir fihm
            if (e1.cle <= e2.cle) {
                e = e1;
                j1++;
            } else {
                e = e2;
                j2++;
            }
            // Write buf3 fi file3 if it is full
            if (j3 >= MAXR_REC) {
                buf3.NB = j3;
                write_block(file3, &buf3);
                buf3.NB = 0;
                j3 = 0;
            }
             // nplacie fi buf3
            buf3.records[j3] = e;
            j3++;
        } else {
            // Check if we need to load a new block from file1
            if (j1 >= buf1.NB && buf1_loaded) {
                buf1_loaded = read_block(file1, &buf1);
                j1 = 0;
            }
            // Check if we need to load a new block from file2
            if (j2 >= buf2.NB && buf2_loaded) {
                buf2_loaded = read_block(file2, &buf2);
                j2 = 0;
            }
            // If both files are exhausted, exit
            if (!buf1_loaded && !buf2_loaded) {
                continu = false;
            }
        }
    }
    // ntaakdou esque rah complete
    Tbloc *buf = buf1_loaded ? &buf1 : &buf2;
    int j = buf1_loaded ? j1 : j2;
    //wtf is this part????
    while (j < buf->NB) {
        buf3.records[j3] = buf->records[j];
        j3++;
        j++;
        // Write buf3 if full
        if (j3 >= MAXR_REC) {
            buf3.NB = j3;
            write_block(file3, &buf3);
            j3 = 0;
        }
    }
    // Write the last part of buf3 if it has records
    if (j3 > 0) {
        buf3.NB = j3;
        write_block(file3, &buf3);
    }
    fclose(file1);
    fclose(file2);
     Tbloc buffer4;
    write_block(file3, &buffer4);
    fclose(file3);
    printf("Files merged successfully into '%s'.\n", file3_name);
} 
int main() {
    const char *file1 = "file_patientA.bin";
    const char *file2 = "file_patientB.bin";
    const char *file3 = "file_patientTotal.bin";

    merge_files(file1, file2, file3);
    return 0;
} 
