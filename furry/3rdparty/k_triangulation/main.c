/* ************************************************************** main.c *** *
 * 2�����κ�Ŭ����¬�̥ץ����
 *
 * Copyright (C) 2008 Yasuyuki SUGAYA <sugaya@iim.ics.tut.ac.jp>
 *
 *                                    Time-stamp: <08/12/09 17:37:15 sugaya>
 * ************************************************************************* */
#include <stdio.h>
#include <stdlib.h>
#include "libmatrix.h"
#include "getargs.h"
#include "misc.h"
#include "twoview_triangulation.h"

/* ************************************************************************* */
int
main (int	argc,
      char	**argv) {
  Argument *arg;
  if (!getargs (argc, argv, &arg)) usage (arg, argv[0]);

  /* �ͱƹ�����ɤ߹��� */
  Matrix Pm1(3, 4), Pm2(3, 4);
  read_projection_matrix (arg->P_filename[0], arg->F0, Pm1);
  read_projection_matrix (arg->P_filename[1], arg->F0, Pm2);  

  /* ���ù���η׻� */
  Matrix F(3, 3);
  calc_fundamental_matrix (Pm1, Pm2, F);
  
  /* �б����ǡ������ɤ߹��� */
  Matrix X1, X2;
  read_image_data (arg->data_filename[0], arg->F0, X1);
  read_image_data (arg->data_filename[1], arg->F0, X2);  
  int npoints = X1.Column();
  
  /* ��������(�ᥤ��롼��) */
  double e;
  for (int p = 0; p < npoints; p++) {
    Vector x1(3), x2(3);
    e = two_view_triangulation_fast (X1(p), X2(p), F, x1, x2, arg->F0,
				     arg->max_iters, arg->convergence);
    X1.SetColumn (p, 0, x1);
    X2.SetColumn (p, 0, x2);    
  }
  /* ��̤ν��� */
  write_image_data (arg->out_filename[0], arg->F0, X1);
  write_image_data (arg->out_filename[1], arg->F0, X2);  

  return 0;
}

/* ******************************************************* End of main.c *** */
