/* ********************************************************** vector.cpp *** *
 * �٥��ȥ륯�饹
 *
 * Copyright (C) 2006 Yasuyuki SUGAYA <sugaya@iim.ics.tut.ac.jp>
 *
 *                                    Time-stamp: <06/12/27 22:27:19 sugaya>
 * ************************************************************************* */
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cmath>
#include "macros.h"
#include "vector.h"

/* ************************************************************************* */
static bool
IsZero (double	val,
	double	epsilon = -1) {
  if (epsilon == -1) epsilon = MATH_DBL_EPSILON;
  if (fabs (val) < epsilon) {
    return true;
  } else {
    return false;
  }
}

/* ************************************************************************* *
 * ���󥹥ȥ饯�� & �ǥ��ȥ饯��
 * ************************************************************************* */

/* �ǥե���ȥ��󥹥ȥ饯�� ************************************************ */
Vector::Vector (void) {
  data = 0;
  dimension = 0;
  reference = false;  
}

/* ��������ꤷ�����󥹥ȥ饯�� ******************************************** */
Vector::Vector (int _dimension) {
  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");
    return;
  }
  data = new double [_dimension];
  dimension = _dimension;
  reference = false;
  
  for (int n = 0; n < dimension; n++) data[n] = 0.0;
}

/* �������ͤ���ꤷ�����󥹥ȥ饯�� **************************************** */
Vector::Vector (int	_dimension,
		double	a,...) {
  va_list	ptr;

  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");    
    return;
  }
  data = new double [_dimension];
  dimension = _dimension;
  reference = false;
  
  *data = a;
  va_start (ptr, a);
  for (int n = 1; n < dimension; n++) data[n] = (double) va_arg (ptr, double);
  va_end (ptr);
}

/* �������ͤ���ꤷ�����󥹥ȥ饯�� **************************************** */
Vector::Vector (int	_dimension,
		double	*a) {
  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");        
    return;
  }
  data = new double [_dimension];
  dimension = _dimension;
  reference = false;
  
  for (int n = 0; n < dimension; n++) data[n] = a[n];
}

/* �٥��ȥ����ꤷ�����󥹥ȥ饯�� **************************************** */
Vector::Vector (const Vector&	v) {
  if (v.dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");        
    return;
  }
  data = new double [v.dimension];
  dimension = v.dimension;
  reference = false;
  
  for (int n = 0; n < dimension; n++) data[n] = v.data[n];
}

/* �٥��ȥ���ϰϤ���ꤷ�����󥹥ȥ饯�� ********************************** */
Vector::Vector (const Vector&	v,
		int		start_index,
		int 		_dimension) {
  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");
    return;
  }
  
  int end_index = start_index + _dimension - 1;
  
  if (start_index < 0 || end_index >= v.dimension) {
    fprintf (stderr, "Specified index is out of range.\n");
    return;
  }
  data = new double [_dimension];
  dimension = _dimension;
  reference = false;
  
  for (int n = 0, m = start_index; n < dimension; n++, m++) {
    data[n] = v.data[m];
  }
}

/* �ǥ��ȥ饯�� ************************************************************ */
Vector::~Vector (void) {
  if (!reference && data) delete [] data;
  data = 0;
  dimension = 0;
  reference = false;
}

/* ************************************************************************* *
 * ���Х��������ؿ�
 * ************************************************************************* */

/* �٥��ȥ�����ǿ� ******************************************************** */
int
Vector::Dimension (void) const {
  return dimension;
}

/* �٥��ȥ�����Ǥ���Ф� ************************************************ */
double&
Vector::operator[] (int	index) {
  if (index >= 0 && index < dimension) {
    return data[index];
  } else {
    fprintf (stderr, "Specified index is out of range.\n");
    return data[0];
  }
}

/* �٥��ȥ�����Ǥ���Ф� ************************************************ */
const double&
Vector::operator[] (int	index) const {
  if (index >= 0 && index < dimension) {
    return data[index];
  } else {
    fprintf (stderr, "Specified index is out of range.\n");
    return data[0];
  }
}

/* ************************************************************************* *
 *�������᥽�å�
 * ************************************************************************* */

/* ���ԡ��᥽�å� ********************************************************** */
void
Vector::Copy (Vector&	dst,
	      int	start_index,
	      int 	_dimension) const {
  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");
    return;
  }
  if (dst.dimension < _dimension) {
    fprintf (stderr,
	     "Dimension of destination vector must be greater than "
	     "specified dimension.\n");
    return;
  }
  int end_index = start_index + _dimension - 1;

  if (start_index < 0 || end_index >= dimension) {
    fprintf (stderr, "Specified index is out of range.\n");
    return;
  }
  for (int n = 0, m = start_index; n < _dimension; n++, m++) {
    dst.data[n] = data[m];
  }
}

/* ���ȥ٥��ȥ�κ��� ****************************************************** */
void
Vector::ReferenceVector (Vector&	ref,
			 int		start_index,
			 int		_dimension) const {
  if (_dimension < 1) {
    fprintf (stderr, "Vector dimension must be greater than zero.\n");
    return;
  }
  int end_index = start_index + _dimension - 1;

  if (start_index < 0 || end_index >= dimension) {
    fprintf (stderr, "Specified index is out of range.\n");
    return;
  }
  if (ref.data && ref.reference == false) delete[] ref.data;
  ref.dimension = _dimension;
  ref.reference = true;

  ref.data = data + start_index;
}

/* �����κ����� ************************************************************ */
void
Vector::Initialize (int	_dimension) {
  if (!reference) {
    if (data) delete[] data;
    data = new double [_dimension];
    dimension = _dimension;
    for (int n = 0; n < _dimension; n++) data[n] = 0.0;
  } else {
    fprintf (stderr, "Can not apply Initialize for reference vector.\n");    
  }
}

/* ���Ƥ����Ǥ���ꤷ���ͤǤ����᥽�å� ********************************** */
void
Vector::Fill (double val) {
  for (int n = 0; n < dimension; n++) data[n] = val;
}

/* ���Ƥ����Ǥ�0�Ǥ����᥽�å� ******************************************* */
void
Vector::Clear (void) {
  for (int n = 0; n < dimension; n++) data[n] = 0.0;
}

/* �ͤ����� **************************************************************** */
void
Vector::Set (double a, ...) {
  va_list	ptr;

  *data = a;
  va_start (ptr, a);
  for (int n = 1; n < dimension; n++) data[n] = (double) va_arg (ptr, double);
  va_end (ptr);
}

/* �ͤ����� **************************************************************** */
void
Vector::Set (double *a) {
  for (int n = 0; n < dimension; n++) data[n] = a[n];
}

/* �ͤ����� **************************************************************** */
void
Vector::Set (int	index,
	     double	val) {
  if (CheckRange (index)) {
    data[index] = val;
  } else {
    fprintf (stderr, "Specified index is out of range.\n");
  }
}

/* �ͤ����촹�� ************************************************************ */
void
Vector::Swap (int	index_i,
	      int	index_j) {
  if (CheckRange (index_i) && CheckRange (index_j)) {
    double	temp = data[index_i];
    data[index_i] = data[index_j];
    data[index_j] = temp;
  } else {
    fprintf (stderr, "Specified index is out of range.\n");
  }
}

/* ���ϥ᥽�å� ************************************************************ */
void
Vector::Print (FILE		*fp,
	       const char 	*format,
	       const char 	*message) const {
  if (message) fprintf (fp, "%s( ", message);
  for (int n = 0; n < dimension; n++) fprintf (fp, format, data[n]);
  if (message) fprintf (fp, " )");
  fprintf (fp, "\n");
}

/* ************************************************************************* *
 * ���ڥ졼��
 * ************************************************************************* */

/* �٥��ȥ������ ********************************************************** */
Vector&
Vector::operator= (const Vector& v) {
  if (this != &v) {
    if (dimension == v.dimension) {
      for (int n = 0; n < dimension; n++) data[n] = v.data[n];
    } else {
      fprintf (stderr, "Dimensions of two vectors do not match.\n");
    }
  }
  return *this;
}

/* �٥��ȥ�βû� ********************************************************** */
Vector&
Vector::operator+= (const Vector& v) {
  if (dimension == v.dimension) {
    for (int n = 0; n < dimension; n++) data[n] += v.data[n];
  } else {
    fprintf (stderr, "Dimensions of two vectors do not match.\n");
  }
  return *this;
}

/* �٥��ȥ�θ��� ********************************************************** */
Vector&
Vector::operator-= (const Vector& v) {
  if (dimension == v.dimension) {
    for (int n = 0; n < dimension; n++) data[n] -= v.data[n];
  } else {
    fprintf (stderr, "Dimensions of two vectors do not match.\n");
  }
  return *this;
}

/* �٥��ȥ�������軻 **************************************************** */
Vector&
Vector::operator*= (double	val) {
  for (int n = 0; n < dimension; n++) data[n] *= val;
  return *this;
}

/* �٥��ȥ������ǽ��� **************************************************** */
Vector&
Vector::operator/= (double	val) {
  if (!IsZero (val)) {
    for (int n = 0; n < dimension; n++) data[n] /= val;
  } else {
    fprintf (stderr, "Specified value is nearly zero.\n");
  }	
  return *this;
}

/* �٥��ȥ�βû� ********************************************************** */
Vector
operator+ (const Vector&	a,
	   const Vector&	b) {
  if (a.dimension == b.dimension) {
    Vector	c(a);
    for (int n = 0; n < a.dimension; n++) c.data[n] += b.data[n];
    return c;
  } else {
    fprintf (stderr, "Dimensions of two vectors do not match.\n");
    return 0;
  }	
}

/* �٥��ȥ�����ȿž ****************************************************** */
Vector
operator- (const Vector&	v) {
  Vector	b(v.dimension);
  
  for (int n = 0; n < b.dimension; n++) b.data[n] = -v.data[n];
  return b;
}

/* �٥��ȥ�θ��� ********************************************************** */
Vector
operator- (const Vector&	a,
	   const Vector&	b) {
  if (a.dimension == b.dimension) {
    Vector	c(a);
    for (int n = 0; n < a.dimension; n++) c.data[n] -= b.data[n];
    return c;
  } else {
    fprintf (stderr, "Dimensions of two vectors do not match.\n");
    return 0;
  }	
}

/* �٥��ȥ�������軻 **************************************************** */
Vector
operator* (const Vector&	a,
	   double		val) {
  Vector	b(a.dimension);
  for (int n = 0; n < a.dimension; n++) b.data[n] = a.data[n] * val;
  return b;
}

/* �٥��ȥ�������軻 **************************************************** */
Vector
operator* (double		val,
	   const Vector&	a) {
  Vector	b(a.dimension);
  for (int n = 0; n < a.dimension; n++) b.data[n] = a.data[n] * val;
  return b;
}

/* �٥��ȥ�������軻 **************************************************** */
Vector
operator/ (const Vector&	a,
	   double		val) {
  if (!IsZero (val)) {
    Vector	b(a.dimension);
    for (int n = 0; n < a.dimension; n++) b.data[n] = a.data[n] / val;
    return b;    
  } else {
    fprintf (stderr, "Specified value is nearly zero.\n");
    return 0;
  }
}

/* ************************************************************************* *
 * �ե��ɴؿ�
 * ************************************************************************* */

/* �Υ��׻� ************************************************************** */
double
Norm (const Vector& v) {
  double	norm = 0.0;

  for (int n = 0; n < v.Dimension(); n++) {
    double val = v[n];
    norm += (val * val);
  }
  return sqrt (norm);
}

/* �Υ���1�ˤ����������黻 *********************************************** */
Vector
Normalize (const Vector&	v) {
  double	norm = Norm (v);

  if (IsZero (fabs (norm))) {
    Vector a(v);	
    return a;
  } else {
    Vector a(v);
    return a / norm;
  }
}

/* �Ǹ�����Ǥ������Ǥ���黻 ******************************************** */
Vector
ZOperator (const Vector&	v) {
  double	val = v[v.Dimension() - 1];

  if (!IsZero (val)) {
    Vector a(v.Dimension());	
    for (int n = 0; n < a.Dimension(); n++) {
      a[n] = v[n] / val;
    }
    return a;
  } else {
    fprintf (stderr,
	     "The last element is nearly zero. Can not apply ZOperation.\n");
    return 0;
  }  
}

/* ���ѷ׻� **************************************************************** */
double
operator, (const Vector&	a,
	   const Vector&	b) {
  if (a.Dimension() == b.Dimension()) {
    double inner = 0.0;
    for (int n = 0; n < a.Dimension(); n++) inner += a[n] * b[n];
    return inner;
  } else {
      fprintf (stderr, "Dimensions of two vectors do not match.\n");
    return 0;
  }  
}

/* ���ѷ׻� **************************************************************** */
Vector
operator% (const Vector&	a,
	   const Vector&	b) {
  if (a.Dimension() != b.Dimension()) {
    fprintf (stderr, "Dimensions of two vectors do not match.\n");
    return 0;
  }
  if (a.Dimension() < 3) {
    fprintf (stderr,
	     "The dimension must be greater that three for "
	     "the outer product.\n");
    return 0;
  }
  Vector c(a.Dimension());
  int dim = c.Dimension();
  for (int n = 0; n < c.Dimension(); n++) {
    c[n] = (a[(n + 1) % dim] * b[(n + 2) % dim] -
	    a[(n + 2) % dim] * b[(n + 1) % dim]);
  }
  return c;
}

/* �٥��ȥ뻰���� ********************************************************** */
double
TripleProduct (const Vector&	a,
	       const Vector&	b,
	       const Vector&	c) {
  return ((a % b), c);
}

/* �٥��ȥ����� ********************************************************** */
bool
operator== (const Vector&	a,
	    const Vector&	b) {
  if (a.Dimension() == b.Dimension() && IsZero (fabs (Norm (a - b)))) {
    return true;
  } else {
    return false;
  }
}

/* �٥��ȥ����� ********************************************************** */
bool
operator!= (const Vector&	a,
	    const Vector&	b) {
  if (a.Dimension() == b.Dimension() && IsZero (fabs (Norm (a - b)))) {
    return false;
  } else {
    return true;
  }
}

/* ����ǥå����Υ����å� ************************************************** */
bool
Vector::CheckRange (int	index) const {
  if (index >= 0 && index < dimension) {
    return true;
  } else {
    return false;
  }
}

/* *************************************************** End of vector.cpp *** */
