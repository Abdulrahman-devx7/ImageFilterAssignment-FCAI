#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    
    // Replace BabyPhotoshop with whatever your namespace is if you change it
    BabyPhotoshop::MyForm form;
    Application::Run(% form);
    
    return 0;
}
