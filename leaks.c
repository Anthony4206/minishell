#include <stdlib.h>
#include <unistd.h>

int main()
{
	while (42)
	{
		system("leaks minishell");
		sleep(2);
	}
}
