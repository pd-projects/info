
#include <m_pd.h>
#include <g_canvas.h>

#define DEBUG(x)
//#define DEBUG(x) x 

/*------------------------------------------------------------------------------
 *  CLASS DEF
 */
static t_class *coords_class;

typedef struct _coords {
    t_object x_obj;
    t_canvas* canvas;
} t_coords;

/*------------------------------------------------------------------------------
 * IMPLEMENTATION                    
 */

static void coords_output(t_coords* x)
{
	DEBUG(post("coords_output"););
	t_atom coords_data[9];
	t_int gop = x->canvas->gl_isgraph + x->canvas->gl_hidetext;
    SETFLOAT(coords_data, (x->canvas->gl_isgraph) ? x->canvas->gl_x1 : 0);
    SETFLOAT(coords_data+1, (x->canvas->gl_isgraph) ? x->canvas->gl_y1 : 0);
    SETFLOAT(coords_data+2, (x->canvas->gl_isgraph) ? x->canvas->gl_x2 : 0);
    SETFLOAT(coords_data+3, (x->canvas->gl_isgraph) ? x->canvas->gl_y2 : 0);
	SETFLOAT(coords_data+4, (x->canvas->gl_isgraph) ? x->canvas->gl_pixwidth : 0);
	SETFLOAT(coords_data+5, (x->canvas->gl_isgraph) ? x->canvas->gl_pixheight : 0);
	SETFLOAT(coords_data+6, (x->canvas->gl_isgraph) ? gop : 0);
	SETFLOAT(coords_data+7, (x->canvas->gl_isgraph) ? x->canvas->gl_xmargin : 0);
	SETFLOAT(coords_data+8, (x->canvas->gl_isgraph) ? x->canvas->gl_ymargin : 0);
	
	outlet_list(x->x_obj.ob_outlet, &s_list, 9, coords_data);
}


static void *coords_new(t_symbol *s) 
{
	t_coords *x = (t_coords *)pd_new(coords_class);
	outlet_new(&x->x_obj, &s_list);
    x->canvas = canvas_getcurrent();
	return (x);
}

void coords_setup(void) 
{
	DEBUG(post("coords_setup"););
	coords_class = class_new(gensym("coords"), 
								  (t_newmethod)coords_new, 
								  0,
								  sizeof(t_coords), 
								  0, 
								  0);
	/* add inlet datatype methods */
	class_addbang(coords_class,(t_method) coords_output);
}
