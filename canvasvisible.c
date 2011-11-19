/* --------------------------------------------------------------------------*/
/*                                                                           */
/* object for getting the version of Pd-extended                             */
/* Written by Hans-Christoph Steiner <hans@eds.org>                          */
/*                                                                           */
/* Copyright (c) 2011 Hans-Christoph Steiner                                 */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU General Public License               */
/* as published by the Free Software Foundation; either version 3            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* See file LICENSE for further informations on licensing terms.             */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software Foundation,   */
/* Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.           */
/*                                                                           */
/* --------------------------------------------------------------------------*/

#include "m_pd.h"
#include "g_canvas.h"


/* ------------------------- canvasvisible ---------------------------- */

static t_class *canvasvisible_class;

typedef struct _canvasvisible
{
  t_object  x_obj;
  t_float   x_depth;
  t_canvas  *x_canvas;
} t_canvasvisible;


static void canvasvisible_bang(t_canvasvisible *x)
{
  outlet_float(x->x_obj.ob_outlet, (t_float) glist_isvisible(x->x_canvas));
}

static void canvasvisible_float(t_canvasvisible *x, t_float f)
{
  canvas_vis(x->x_canvas, f);
  outlet_float(x->x_obj.ob_outlet, f);
}

static void canvasvisible_free(t_canvasvisible *x)
{
}

static void *canvasvisible_new(t_floatarg f)
{
  t_canvasvisible *x = (t_canvasvisible *)pd_new(canvasvisible_class);
  t_glist *glist=(t_glist *)canvas_getcurrent();
  t_canvas *canvas=(t_canvas*)glist_getcanvas(glist);

  int depth=(int)f;
  if(depth<0)depth=0;

  while(depth && canvas) {
    canvas=canvas->gl_owner;
    depth--;
  }

  x->x_canvas = canvas;

  outlet_new(&x->x_obj, &s_symbol);
  
  return (x);
}

void canvasvisible_setup(void)
{
  canvasvisible_class = class_new(gensym("canvasvisible"), (t_newmethod)canvasvisible_new,
                               (t_method)canvasvisible_free, sizeof(t_canvasvisible), 0, A_DEFFLOAT, 0);
  class_addfloat(canvasvisible_class, (t_method)canvasvisible_float);
  class_addbang(canvasvisible_class, (t_method)canvasvisible_bang);
}
