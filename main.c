#include "main.h"

/**
 *
 *
 *
 */
int main(int argc, char **argv)
{
	shell_info *infosh;
	(void) argc;

	signal(SIGINT, com_get); /* bulidin fun ,signal(SIGINT, get_sigint);*/
	commands_s(&infosh, argv); /* set_data(&datash, av)*/
	display(&infosh);
	_free(&infosh);
	if (infosh.s < 0)
	{
		return (255);
	}
	return (infosh.s);
}
