#ifndef CHECKER_H
# define CHECKER_H

# include "push_swap.h"

# ifdef GRAPHIC_MODE
#  include "SDL.h"

#  define STEP_DLY	10

typedef struct		s_graph_env
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	int				is_running;
	int				delay;
	int				paused;
	int				refresh;
	int				step;
	int				dir;
	t_inter			vrng;
}					t_graph_env;

void	graph_loop(t_graph_env *env, t_ps_bench *bench);

# endif

#endif
