#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char* GetMemoryBuffer(const unsigned int size)
{
    srand(time(NULL));
    char* b = (char *)malloc(size * sizeof(char));
    unsigned int loc = 0;
    while (loc < size) {
        char ch = 'A' + (char)(rand() %26);
        b[loc++] = ch;
    }

    return b;

}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Usage: writefile <path> <count of mb> <number of times>\n");
        return -1;
    }
    
    char *fname = argv[1];
    unsigned int nData = atoi(argv[2]);
    unsigned int count = atoi(argv[3]);

    printf("Writing to %s, %u times\n", fname, count);
    const unsigned int size = nData * 1024*1024;
    
    printf("Generating random data\n");
    char *pMem = GetMemoryBuffer(size);

    FILE *fp = fopen(fname, "w");
    for(unsigned int i = 0; i < count; ++i)
    {
        printf("Writing %2u: ", i);
        clock_t begin = clock();
        fwrite(pMem, sizeof(char), size, fp);
        fflush(fp);
        clock_t end = clock();
        printf("took %f sec\n", (double)(end - begin) / CLOCKS_PER_SEC);
        fseek(fp, 0, SEEK_SET);
    }

    fclose(fp);
    free(pMem);

    return 0;
}

