#include "SDLFileOps.h"

#include <SDL.h>

/////////////////////////////////////////////////
CSDLFileOps::CSDLFileOps(ISystem* systemContext)
	:m_pSystem(systemContext)
{
}

/////////////////////////////////////////////////
std::string CSDLFileOps::readFile(const std::string& file)
{
	std::string content = "";
	SDL_RWops* rw = SDL_RWFromFile(file.c_str(), "rb");

	if (rw != NULL) {
		Sint64 res_size = SDL_RWsize(rw);
		char* res = (char*)malloc(res_size + 1);

		Sint64 nb_read_total = 0, nb_read = 1;
		char* buf = res;
		while (nb_read_total < res_size && nb_read != 0) {
			nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
			nb_read_total += nb_read;
			buf += nb_read;
		}
		SDL_RWclose(rw);
		if (nb_read_total != res_size) {
			free(res);
			return NULL;
		}

		res[nb_read_total] = '\0';
		content = res;
	}

	return content;
}
