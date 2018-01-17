/* *********************************************************** getargs.h *** *
 * $B0z?t2r@O4X?t(B $B%X%C%@%U%!%$%k(B
 *
 * Copyright (C) 2008 Yasuyuki SUGAYA <sugaya@iim.ics.tut.ac.jp>
 *
 *                                    Time-stamp: <08/12/09 17:51:06 sugaya>
 * ************************************************************************* */
#ifndef	__COMMON_FUNC_GETARGS_H__
#define	__COMMON_FUNC_GETARGS_H__

/* ************************************************************************* *
 * $B0z?tMQ$N9=B$BN(B
 * 	- $B%W%m%0%i%`$KI,MW$J0z?t$K1~$8$F%a%s%P$rJQ99$7$F$/$@$5$$(B -
 * ************************************************************************* */
typedef struct _Argument {
  char		*P_filename[2];
  char		*data_filename[2];
  char		*out_filename[2];
  int		max_iters;
  double	F0;
  double	convergence;
} Argument;

/* ************************************************************************* *
 * $B4X?t(B
 * ************************************************************************* */

void		usage		(Argument	*arg,
				 char		*cmd);         /* $B;H$$J}I=<((B */
void		version 	(Argument	*arg); /* $B%P!<%8%g%s>pJsI=<((B */
void		argument_free	(Argument	*arg);         /* $B%a%b%j2rJ|(B */
Argument*	argument_new 	(void);                  /* $B0z?t9=B$BN$N@8@.(B */
int		getargs 	(int		argc,        /* $B0z?t2r@O4X?t(B */
				 char		**argv,
				 Argument	**arg);

#endif	/* __COMMON_FUNC_GETARGS_H__ */

/* **************************************************** End of getargs.h *** */
