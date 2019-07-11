/*
 * Copyright (C) 2019 Tokyo System House co.,ltd.
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

#ifndef COB_JSON_H
#define COB_JSON_H

/* JSON functions */
COB_EXPIMP int CBL_JSON_PARSE			(unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_FREE			(unsigned char *);
COB_EXPIMP int CBL_JSON_GET_TYPE		(unsigned char *);
COB_EXPIMP int CBL_JSON_GET_KEY_START	(unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_GET_KEY_NEXT	(unsigned char *, unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_GET_ARRLEN		(unsigned char *);
COB_EXPIMP int CBL_JSON_GET_VALUE		(unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_GET_OBJECT		(unsigned char *, unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_GET_OBJECT_L	(unsigned char *, unsigned char *, unsigned char *);
COB_EXPIMP int CBL_JSON_GET_OBJECT_A	(unsigned char *, unsigned char *, unsigned char *);

#endif /* COB_JSON_H */
