#include "checker.h"

#ifdef GRAPHIC_MODE

int		graph_init(t_graph_env *env, t_ps_bench *bench)
{
	size_t	i;

	env->win = NULL;
	env->is_running = 1;
	env->dir = 1;
	env->refresh = 1;
	env->delay = 10;
	env->paused = 1;
	env->step = 0;
	env->vrng.l = bench->sa->stack[0];
	env->vrng.r = bench->sa->stack[0];
	i = 0;
	while (i < bench->sa->sp)
	{
		if (env->vrng.l > bench->sa->stack[i])
			env->vrng.l = bench->sa->stack[i];
		if (env->vrng.r < bench->sa->stack[i])
			env->vrng.r = bench->sa->stack[i];
		i++;
	}
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
			if (env->event.key.keysym.sym == SDLK_ESCAPE
					|| env->event.key.keysym.sym == SDLK_q)
				env->is_running = 0;
			if (env->event.key.keysym.sym == SDLK_SPACE)
				env->paused = !env->paused;
			if (env->event.key.keysym.sym == SDLK_DOWN)
				env->delay = env->delay > 0 ? env->delay - 1 : 0;
			if (env->event.key.keysym.sym == SDLK_UP)
				env->delay++;
			if (env->event.key.keysym.sym == SDLK_LEFT)
				env->step -= 1;
			if (env->event.key.keysym.sym == SDLK_RIGHT)
				env->step += 1;
			if (env->event.key.keysym.sym == SDLK_r)
				env->dir *= -1;
		}
	}
}

void	graph_refresh(t_graph_env *env, t_ps_bench *bench)
{
	SDL_Rect	r;
	size_t		i;

	SDL_SetRenderDrawColor(env->rend, 200, 200, 200, 255);
	SDL_RenderClear(env->rend);
	r.w = 1;
	r.y = 0;
	SDL_GetWindowSize(env->win, &r.x, &r.h);
	r.x /= 2;
	SDL_SetRenderDrawColor(env->rend, 100, 100, 100, 255);
	SDL_RenderFillRect(env->rend, &r);
	SDL_GetWindowSize(env->win, NULL, &r.y);
	i = 0;
	while (i < bench->sa->sp)
	{
		SDL_GetWindowSize(env->win, &r.w, &r.h);
		r.x = ft_map(bench->sa->stack[i], env->vrng, (t_inter){r.w / 4, 0});
		r.w = ft_map(bench->sa->stack[i], env->vrng, (t_inter){10, r.w / 2});
		r.h /= bench->sa->size;
		r.y -= r.h;
		SDL_SetRenderDrawColor(env->rend, 209, 118, 27, 255);
		SDL_RenderFillRect(env->rend, &r);
		SDL_SetRenderDrawColor(env->rend, 200, 200, 200, 255);
		SDL_RenderDrawRect(env->rend, &r);
		i++;
	}
	SDL_GetWindowSize(env->win, NULL, &r.y);
	i = 0;
	while (i < bench->sb->sp)
	{
		SDL_GetWindowSize(env->win, &r.w, &r.h);
		r.x = ft_map(bench->sb->stack[i], env->vrng, (t_inter){r.w / 4, 0})
			+ r.w / 2;
		r.w = ft_map(bench->sb->stack[i], env->vrng, (t_inter){10, r.w / 2});
		r.h /= bench->sa->size;
		r.y -= r.h;
		SDL_SetRenderDrawColor(env->rend, 209, 118, 27, 255);
		SDL_RenderFillRect(env->rend, &r);
		SDL_SetRenderDrawColor(env->rend, 200, 200, 200, 255);
		SDL_RenderDrawRect(env->rend, &r);
		i++;
	}
	SDL_RenderPresent(env->rend);
}

void	graph_loop(t_graph_env *env, t_ps_bench *bench)
{
	int	to_wait;

	graph_init(env, bench);
	to_wait = 1;
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
		env->refresh = env->step ? 1 : env->refresh;
		if (env->step >= 1)
		{
			if (!bench_step_forward(bench))
				env->paused = 1;
			env->step--;
		}
		if (env->step <= -1)
		{
			if (!bench_step_backward(bench))
				env->paused = 1;
			env->step++;
		}
		if (env->refresh)
			graph_refresh(env, bench);
		env->refresh = 0;
		if (env->delay)
			SDL_Delay(STEP_DLY);
	}
	graph_quit(env);
}

#endif
