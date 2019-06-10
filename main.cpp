#include "Ui.h"

int main()
{
	bool r = false;
	do
	{
		system("CLS");
		Ui ui;
		ui.main();
		r = ui.restart;
	} while (r);
	return 0;
}
