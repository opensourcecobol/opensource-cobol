/*
 * Copyright (C) 2007-2009 Roger While
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,
 * or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

#ifndef COB_LOCAL_H
#define COB_LOCAL_H

/* We use this file to prototype things that should not be
   exported to user space
*/

#if defined(__GNUC__) && defined(linux) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
#define COB_HIDDEN	__attribute__ ((visibility("hidden")))
#else
#define COB_HIDDEN
#endif

#define COB_ATTR_INIT(v,w,x,y,z)	do { \
	attr.type = v; \
	attr.digits = w; \
	attr.scale = x; \
	attr.flags = y; \
	attr.pic = z; \
	} while (0)

#ifdef	COB_PARAM_CHECK
#define	COB_CHK_PARMS(x, z)	\
	do { \
		if (cob_call_params < z) { \
			cob_runtime_error (parm_msg, #x, z); \
			cob_stop_run (1); \
		} \
	} while (0)
#else
#define	COB_CHK_PARMS(x, z)
#endif

COB_HIDDEN extern int			cob_screen_initialized;
COB_HIDDEN extern int			cob_got_exception;
COB_HIDDEN extern unsigned int		cob_orig_line;
COB_HIDDEN extern const char		*cob_orig_statement;
COB_HIDDEN extern const char		*cob_orig_program_id;
COB_HIDDEN extern const char		*cob_orig_section;
COB_HIDDEN extern const char		*cob_orig_paragraph;

COB_HIDDEN extern void		cob_memcpy		(cob_field *,
							 unsigned char *,
							 const int);
COB_HIDDEN extern void		cob_exit_fileio		(void);
COB_HIDDEN extern void		cob_field_to_string	(const cob_field *, char *);
COB_HIDDEN extern void		cob_init_numeric	(void);
COB_HIDDEN extern void		cob_init_termio		(void);
COB_HIDDEN extern void		cob_init_fileio		(void);
COB_HIDDEN extern void		cob_init_call		(void);
COB_HIDDEN extern void		cob_init_intrinsic	(void);
COB_HIDDEN extern void		cob_init_strings	(void);
COB_HIDDEN extern void		cob_init_move		(void);
COB_HIDDEN extern void		cob_screen_terminate	(void);
COB_HIDDEN extern void		cob_screen_set_mode	(size_t);
COB_HIDDEN extern int		cob_real_get_sign	(cob_field *);
COB_HIDDEN extern void		cob_real_put_sign	(cob_field *, const int);
COB_HIDDEN extern long long	cob_get_long_long	(cob_field *);

#endif /* COB_LOCAL_H */
