#include <bmp_font.h>

#include <stdlib.h>
#include <rs_manager.h>

void install_bmp_font(char* name, int w, int h, int sep, int border, char* texture) {
	bmp_font_t* font = (bmp_font_t*) malloc(sizeof(bmp_font_t));
	font->texture = rs_manager_get_texture(texture);
	font->w = w;
	font->h = h;
	font->sep = sep;
	font->border = border;

	// Adds font to rs manager
	rs_manager_add_bmp_font(name, font);
}
