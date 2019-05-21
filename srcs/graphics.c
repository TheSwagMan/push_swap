#include "checker.h"

#ifdef GRAPHIC_MODE

int		graph_init(t_graph_env *env)
{
	env->win = NULL;
	env->is_running = 1;
	env->dir = 1;
	env->refresh = 1;
	env->delay = 10;
	env->paused = 1;
	env->step = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 \
			|| SDL_CreateWindowAndRenderer(1280, 720, \
				SDL_WINDOW_FULLSCREEN_DESKTOP, &(env->win), &(env->rend)))
		return (0);
	return (1);
}

void	graph_quit(t_graph_env *env)
{
	SDL_DestroyRenderer(env->rend);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
}

void	graph_events(t_graph_env *env)
{
	while (SDL_PollEvent(&(env->event)))
	{
		if (env->event.type == SDL_QUIT)
			env->is_running = 0;
		if (env->event.type == SDL_KEYDOWN)
		{
			if (env->event.key.keysym.sym == SDLK_ESCAPE)
				env->is_running = 0;
			if (env->event.key.keysym.sym == SDLK_SPACE)
				env->paused = !env->paused;
			if (env->event.key.keysym.sym == SDLK_DOWN)
				env->delay = env->delay > 0 ? env->delay - 1 : 0;
			if (env->event.key.keysym.sym == SDLK_UP)
				env->delay++;
			if (env->event.key.keysym.sym == SDLK_LEFT)
				env->step = -1;
			if (env->event.key.keysym.sym == SDLK_RIGHT)
				env->step = 1;
			if (env->event.key.keysym.sym == SDLK_r)
				env->dir *= -1;
		}
	}
}

void	graph_refresh(t_graph_env *env, t_ps_bench *bench)
{
	SDL_Rect	r;

	SDL_SetRenderDrawColor(env->rend, 200, 200, 200, 255);
	SDL_RenderClear(env->rend);
	r.w = 1;
	r.y = 0;
	SDL_GetWindowSize(env->win, &r.x, &r.h);
	r.x /= 2;
	SDL_SetRenderDrawColor(env->rend, 100, 100, 100, 255);
	SDL_RenderFillRect(env->rend, &r);
	SDL_RenderPresent(env->rend);
	(void)bench;
}

void	graph_loop(t_graph_env *env, t_ps_bench *bench)
{
	int	to_wait;

	graph_init(env);
	to_wait = 0;
	env->refresh = 1;
	while (env->is_running)
	{
		graph_events(env);
		if (to_wait <= 0)
		{
			to_wait = env->delay;
			env->step = env->dir;
		}
		else if (!env->paused)
			to_wait--;
		if (env->step == 1)
			bench_step_forward(bench);
		if (env->step == -1)
			bench_step_backward(bench);
		env->refresh = env->step ? 1 : env->refresh;
		if (env->refresh)
			graph_refresh(env, bench);
		env->refresh = 0;
		SDL_Delay(STEP_DLY);
	}
	graph_quit(env);
}

#endif
