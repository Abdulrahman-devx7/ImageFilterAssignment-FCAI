//====================================================================================
//======================================Part 2========================================
// Assignment: CS213 - Object Oriented Programming - Assignment 1 (Part 2)
// Section Number : 14, Only Mahmoud: S27
// 
// Team Members & Task Allocation:
// 1. Mahmoud Ahmed Hassan Mohamed  | ID: 20240544 | Filters: 1, 5, 9, 13
// 2. Ziad Mohamed Abdul Rafe Wahba | ID: 20250259 | Filters: 2, 6, 10, 14
// 3. Abdulrahman Nabil Ali Muhammed| ID: 20250376 | Filters: 3, 7, 11, 15
// 4. Mohamed Tarek Ahmed Ali       | ID: 20250570 | Filters: 4, 8, 12, 16
//
// NOTE: Only the first student in the list is signed in a different section --SECTION 27--, but is persistent with the same TA: Maya Kamal.
// THE REST OF TEAM MEMBERS ARE SIGNED IN --SECTION 14--
//====================================================================================
//====================================================================================

//==============================================================================================
//======================================FILES EXPLANATION========================================
// 
// This main.cpp file is considered the orchestrator that's responsible for initializing and actually running the Windows
// Forms application. The running process carries on like this:
// - There is a header file plus an implementation file called "filters". The implementation file is where
// you will ACTUALLY find the implementation of each filter written by me and my teammates.
// 
// - There's a .cpp file that's called stb.cpp. This file's role is more compiler-related. Meaning that it resolved some linker 
// issues and prevents recompiling header files more than once.
// 
// - MyForm.h is the presentation and control layer of our application. It implements the Graphical User Interface (GUI) using C++/CLI and Windows Forms,
// manages user interactions (events and dialogs), and acts as the bridge connecting high-level .NET UI controls to our native C++ image processing engine.
// 
// - THE SPECIAL ADDITION: ImageHistory.h
// This specific header file, suggested and created by Mohamed Tarek, runs on a doubly linked list. It seamlessly integrates the Image_class library 
// provided by Dr. Mohamed into the linked list's engine, traversing backwards and forwards throughout the linked list's nodes via pointers. Each node represents 
// a single snapshot of the loaded image that has had filters applied to it. This structure as a whole is the deep engine in our program running the 
// "Backward" and "Forward" buttons you see in the GUI to traverse the images if you encountered one you don't like.
// 
//==============================================================================================
//======================================Part 2==================================================

#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    
    BabyPhotoshop::MyForm form;
    Application::Run(% form);
    
    return 0;
}
