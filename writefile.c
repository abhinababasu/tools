#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char* GetMemoryBuffer(const unsigned int size)
{
    srand(time(NULL));
    char* b = (char *)malloc(size * sizeof(char));
    unsigned int loc = 0;
    while (loc < size)
    {
        char ch = 'A' + (char)(rand() %26);
        b[loc++] = ch;
    }

    return b;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: writefile <path> <run time in seccond>\n");
        return -1;
    }
    
    char *fname = argv[1];
    float runtime = atof(argv[2]);

    printf("Writing to %s, %f seconds\n", fname, runtime);
    const unsigned int size = 8 * 1024;
    
    printf("Generating random data\n");
    char *pMem = GetMemoryBuffer(size);

    printf("Starting write\n");
    FILE *fp = fopen(fname, "w");
    clock_t begin = clock();
    float timeTaken; 
    do
    {
        for(unsigned int i = 0; i < 8; ++i)
        {
            fwrite(pMem, sizeof(char), size, fp);
            fflush(fp);
        }

        clock_t end = clock();
        timeTaken = (float)(end - begin) / CLOCKS_PER_SEC;
        fseek(fp, 0, SEEK_SET);

    } while (timeTaken < runtime);

    fclose(fp);
    free(pMem);

    return 0;
}

