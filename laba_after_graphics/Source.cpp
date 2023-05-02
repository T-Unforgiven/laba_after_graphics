#include "MyForm.h"

using namespace labaaftergraphics;

[STAThreadAttribute]
int main(array<String^>^ arsv) {
	Application::Run(gcnew MyForm());
	return 0;
}