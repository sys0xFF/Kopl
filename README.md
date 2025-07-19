# KOPL - King of Process Listing

A console application written in C++ that demonstrates the use of Windows API for system process enumeration and management.

## Overview

KOPL (King of Process Listing) is my first project exploring the Windows API. This application provides a command-line interface to list running processes on a Windows system and apply filters to monitor specific processes.

## Features

- **Process Enumeration**: Lists all running processes with their names and Process IDs (PIDs)
- **Process Filtering**: Allows users to create custom filters to monitor specific processes
- **Interactive Menu**: User-friendly console interface with multiple options
- **Real-time Process Information**: Displays current system processes using Windows API calls

## Windows API Functions Used

This project primarily utilizes the following Windows API functions:

### CreateToolhelp32Snapshot()
- **Purpose**: Creates a snapshot of the specified processes, heaps, modules, and threads
- **Usage**: `CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)`
- **Function**: Captures a snapshot of all processes currently running on the system

### Process32FirstW() and Process32NextW()
- **Purpose**: Iterates through the process snapshot
- **Usage**: Used in combination to enumerate all processes in the snapshot
- **Function**: Retrieves information about the first/next process in the snapshot

### PROCESSENTRY32 Structure
- **Purpose**: Contains process information from the snapshot
- **Key Fields**:
  - `szExeFile`: Process executable filename
  - `th32ProcessID`: Process identifier (PID)
  - `dwSize`: Size of the structure (must be set before use)

### CloseHandle()
- **Purpose**: Closes an open object handle
- **Usage**: Must be called after using any WinAPI function that returns a handle (e.g., CreateToolhelp32Snapshot, OpenProcess, CreateFile)  
- **Function**: Releases system resources associated with the handle

## How It Works

1. **Snapshot Creation**: The application creates a system snapshot using `CreateToolhelp32Snapshot()`
2. **Process Iteration**: Uses `Process32FirstW()` and `Process32NextW()` to iterate through all processes
3. **Data Extraction**: Extracts process name and PID from the `PROCESSENTRY32` structure
4. **Filtering**: Compares process names against user-defined filters
5. **Display**: Outputs the results to the console based on the selected mode

## Building the Project

This project was built using Visual Studio with the following requirements:

- **Compiler**: Microsoft Visual C++ (MSVC)
- **Target Platform**: Windows x64
- **Configuration**: Release/Debug
- **Dependencies**: Windows SDK (for Windows API headers)

### Required Headers
```cpp
#include <windows.h>    // Core Windows API
#include <tlhelp32.h>   // Tool Help API for process enumeration
#include <iostream>     // Standard I/O
#include <string>       // String handling
```

## Usage

1. Run the executable
2. Choose from the menu options:
   - **Option 1**: List all running processes
   - **Option 2**: Set up filters and list only filtered processes
   - **Option 3**: Exit the application

## Learning Outcomes

- Windows API fundamentals
- Process enumeration techniques
- Handle management in Windows
- Wide character string handling (`std::wstring`)
- System snapshot manipulation

