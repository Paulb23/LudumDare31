#include "config.h"
#include "../SSL/SSL.h"

static const char *CONFIG_PATH = "../conf/config.ini";

void ld31_loadConfig() {
	dictionary *dict = dictionary_new(0);
	dict = iniparser_load(CONFIG_PATH);

	title = iniparser_getstring(dict, "display:title", "LD 31!");
	window_height = iniparser_getint(dict, "display:window_height", 600);
	window_width  = iniparser_getint(dict, "display:window_width",  800);
	window_res_height = iniparser_getint(dict, "display:window_res_height", 800);
	window_res_width  = iniparser_getint(dict, "display:window_res_width",  600);
}
