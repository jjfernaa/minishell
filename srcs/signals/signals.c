#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
