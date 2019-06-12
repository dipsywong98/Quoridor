#include "Ui.h"
#include <iostream>
#include "Log.h"

bool debug = true;


Log d;
Log js;

int main()
{
	std::ofstream fout("output.js");
	d.setF(&fout);
	bool r = false;
	do
	{
		system("CLS");
		d << "debug\n";
		Ui ui;
		ui.main();
		r = ui.restart;
	} while (r);
	return 0;
}
