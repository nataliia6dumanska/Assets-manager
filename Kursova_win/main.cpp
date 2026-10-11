
#include "Finance.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew Kursovawin::Finance());

    return 0;
}