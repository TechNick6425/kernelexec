#include <3ds.h>
#include <stdio.h>
#include <svchax.h>

int main(int argc, char** argv)
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    printf("KernelExec by TechNick6425\n");
    printf("Version 0.0.1a\n");

    printf("\nExploiting svchax...\n");
    svchax_init();

    if(__ctr_svchax != 1)
    {
        printf("Exploiting failed.\n");
        printf("Press START to exit.\n");

        while(aptMainLoop())
        {
            hidScanInput();
            if(hidKeysDown() & KEY_START) break;
        }

        return 1;
    }

    printf("Exploit successful.\n");
    printf("Loading payload from kernelexec.bin...\n");

    sdmcInit();
    FILE* payload = fopen("kernelexec.bin", "rb");

    if(payload == NULL)
    {
        printf("Payload load failed.\n");
        printf("Press START to exit.\n");

        while(aptMainLoop())
        {
            hidScanInput();
            if(hidKeysDown() & KEY_START) break;
        }

        return 2;
    }

    fseek(payload,0,SEEK_END);
	off_t size = ftell(payload);
	fseek(payload,0,SEEK_SET);

    u8* buffer;
    buffer = malloc(size);

    off_t bytesRead = fread(buffer,1,size,payload);

    if(bytesRead != size)
    {
        printf("Payload loaded incorrectly.\n");
        printf("Press START to exit.\n");

        while(aptMainLoop())
        {
            hidScanInput();
            if(hidKeysDown() & KEY_START) break;
        }

        return 3;
    }

    fclose(payload);

    void (*payload_func) (void);
    payload_func = (void (*)())payload;
    printf("Executing payload...");
    payload_func();

    printf("Payload returned. Success!\n");
    printf("Press START to exit.\n");

    while(aptMainLoop())
    {
        hidScanInput();
        if(hidKeysDown() & KEY_START) break;
    }

    return 0;
}
