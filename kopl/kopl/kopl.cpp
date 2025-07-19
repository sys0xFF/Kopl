#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>

std::wstring filters[10];
int filterCount = 0;

void ClearConsole() {
    system("cls");
}

bool IsInFilterList(const std::wstring processName) {
    for (int i = 0; i < filterCount; i++) {
        if (filters[i] == processName) {
            return true;
        }
    }
		return false;
}

void ListProcesses(DWORD mode)
{
    // When we are going to access processes, files etc. We need to open a Handle
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // Always we open a Handle we need to verify if its valid
    if (hSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 processEntry;

    processEntry.dwSize = sizeof(PROCESSENTRY32); // Much Important

    if (Process32FirstW(hSnap, &processEntry)) {
        do {
			switch (mode) {
			case 1:
				wprintf(L"Name: %ls PID: %lu\n", processEntry.szExeFile, processEntry.th32ProcessID);
				break;
			case 2:
                if (IsInFilterList(processEntry.szExeFile)) {
                    wprintf(L"[Filtered] Name: %ls PID: %lu\n", processEntry.szExeFile, processEntry.th32ProcessID);
                }
				break;
            default:
                wprintf(L"Something went wrong\n");
                break;
			}
        } while (Process32NextW(hSnap, &processEntry));
    }

    CloseHandle(hSnap); // Always close handle when u open it

    //return 0;
}

int main() {

    bool running = true;

    unsigned int i = 0;

    while (running) {
        std::cout << "******************************************\n";
        std::cout << "* Welcome to the King of Process Listing *\n";
        std::cout << "******************************************\n\n";
        std::cout << "1. List Processes\n";
        std::cout << "2. Filter List\n";
        std::cout << "3. Exit\n";

        int option;
        std::cout << "Choose an option: ";
        std::cin >> option;

        if (option == 1)
        {
            ListProcesses(1);
            //DWORD pid = GetPIDByProcName(L"svchost.exe");
            //std::cout << pid << '\n';
        }
        else if (option == 2)
        {
            ClearConsole();
            while (true) {
                std::wstring input;
                wprintf(L"Write the process name thats going to be filtered, type 'list' to continue, (ex: svchost.exe)\n");
                std::wcin >> input;

                if (input == L"list") {
                    ClearConsole();
                    ListProcesses(2);
                    break;
                }
                else {
                    if (filterCount < 10) {
                        filters[filterCount++] = input;
                        ClearConsole();
                        wprintf(L"Filter %ls added with success\n", input.c_str()); // c_str its nescessary because %ls expects a wchar_t 
                    }
                    else {
                        ClearConsole();
                        wprintf(L"U already reached the max filters\n");
                    }
                }
            }

        }
        else if (option == 3)
        {
            std::cout << "Good bye!\n";
            running = false;
        }
        else
        {
            ClearConsole();
            std::cout << "Invalid Option!\n";
        }
    }

    return 0;
}