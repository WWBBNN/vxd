/* ************************************************************ matrix.h *** *
 * ���󥯥饹 �ء����ե�����
 *
 * Copyright (C) 2006 Yasuyuki SUGAYA <sugaya@iim.ics.tut.ac.jp>
 *
 *                                    Time-stamp: <2008-03-07 13:50:30 sugaya>
 * ************************************************************************* */
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"
#include <vcl_cmath.h>
#include <vcl_cstdio.h>
#include "macros.h"

typedef double  *double_ptr;

/* ************************************************************************* */
static bool
IsZero (double  val,
        double  epsilon = -1) {
  if (epsilon == -1) epsilon = MATH_DBL_EPSILON;
  if (vcl_fabs (val) < epsilon) {
    return true;
  } else {
    return false;
  }
}

/* ���󥯥饹 ************************************************************** */
class Matrix {
 private:
  int           row;
  int           col;
  int           nelements;
  bool          reference;
  double        *data;
  double        **data_ptr;

 public:

  /* ���󥹥ȥ饯�� & �ǥ��ȥ饯�� */
  Matrix        (void);
  Matrix        (int _row, int _col);
  Matrix        (int _row, int _col, double a, ...);
  Matrix        (int _row, int _col, double *a);
  Matrix        (int _row, int _col, double **a);
  Matrix        (const Matrix& a);
  Matrix        (const Vector& v, int _row, int _col);  
  Matrix        (const Matrix& a,
                 int start_row, int start_col, int _row, int _col);
  Matrix        (const Vector& a, const Vector& b);
  Matrix        (const Vector& a, double angle);

  ~Matrix       (void);  

  /* ���Х��������᥽�å� */
  int           Row             (void) const;
  int           Column          (void) const;
  double*       operator[]      (int            index);
  const double* operator[]      (int            index) const;
  Vector        operator()      (int            index) const;
  Vector        RowVector       (int            index) const;
  Vector        ColumnVector    (int            index) const;  
    
  /* �����᥽�å� */
  void          Copy            (Matrix&        dst,
                                 int            start_row,
                                 int            start_col,
                                 int            _row,
                                 int            _col) const;
  void          ReferenceMatrix (Matrix&        ref,
                                 int            start_row,
                                 int            start_col,
                                 int            _row,
                                 int            _col) const;
  void          Initialize      (int            _row,
                                 int            _col);
  void          Fill            (double         val);
  void          Clear           (void);
  void          Unit            (void);
  void          Diagonal        (double         a, ...);
  void          Set             (double         a, ...);
  void          Set             (double         *a);
  void          Set             (double         **a);
  void          Set             (int            index_row,
                                 int            index_col,
                                 double         val);
  void          SetColumn       (int            index_col,
                                 int            start_row,
                                 const Vector&  v);
  void          SetRow          (int            index_row,
                                 int            start_col,
                                 const Vector&  v);
  void          SwapColumn      (int            index_i,
                                 int            index_j);
  void          SwapRow         (int            index_i,
                                 int            index_j);
  bool          IsSquare        (void);
  bool          IsSymmetric     (void);
  double        CoFactor        (int            index_i,
                                 int            index_j) const ;
 
  bool          LUDecomp        (Matrix&        LU,
                                 int            *permutation,
                                 double         *determinant) const;
  bool          Eigen           (Vector         &eval,
                                 Matrix         &evec,
                                 double         eps = 1.0e-15) const;
  bool          SvDecomp        (Matrix&        U,
                                 Matrix&        W,
                                 Matrix&        V) const;
  
  /* ���ڥ졼�� */
  Matrix&       operator=       (const Matrix&  a);
  Matrix&       operator+=      (const Matrix&  a);
  Matrix&       operator-=      (const Matrix&  a);
  Matrix&       operator*=      (double         val);
  Matrix&       operator/=      (double         val);
  friend Matrix operator+       (const Matrix& a, const Matrix& b);
  friend Matrix operator-       (const Matrix& a);
  friend Matrix operator-       (const Matrix& a, const Matrix& b);
  friend Matrix operator*       (const Matrix& a, double val);
  friend Matrix operator*       (double val, const Matrix& a);  
  friend Vector operator*       (const Matrix& a, const Vector& v);
  friend Matrix operator*       (const Matrix& a, const Matrix& b);
  friend Matrix operator/       (const Matrix& a, double val);
  friend Matrix operator%       (const Matrix& a, const Vector& v);
  friend Matrix operator%       (const Vector& v, const Matrix& a);
  //friend matrix       operator%       (const Matrix& a, const Matrix& b);
  friend double operator,       (const Matrix& a, const Matrix& b);
  friend bool   operator==      (const Matrix& a, const Matrix& b);
  friend bool   operator!=      (const Matrix& a, const Matrix& b);
    
  /* �ե��ɴؿ� */    
  friend double Norm            (const Matrix&  a);
  friend Matrix Normalize       (const Matrix&  a);
  friend Matrix Transpose       (const Matrix&  a);
  friend Matrix ProjectionMatrix(const Vector&  v);
  friend double Trace           (const Matrix&  a);
  friend double Determinant     (const Matrix&  a);
  friend int    Rank            (const Matrix&  a);
  friend Matrix Inverse         (const Matrix&  a);
  friend Matrix GeneralInverse  (const Matrix&  a,
                                 int            rank = 0)
  {
      /* *******************************************************************/
      if (a.row != a.col) {
          fprintf (stderr, "Matrix size must be square.\n");
          return Matrix (a);
      }
      Matrix        evec, Inv (a.row, a.col);
      Vector        eval;
      
      if (rank == 0) rank = Rank (a);
      
      a.Eigen (eval, evec);
      for (int n = 0; n < rank; n++) {
          if (!IsZero (eval[n]))  Inv += 1.0 / eval[n] * Matrix (evec(n), 
                                                                 evec(n));
      }
      return Inv;
  }

  friend Vector Diagonal        (const Matrix&  a);
  friend Matrix Diagonal        (const Vector&  v);
  friend Vector ToVector        (const Matrix&  a);
  bool          CheckRange      (int            index_row,
                                 int            index_col) const;
  friend int    HouseholderSolve(const Matrix&  a,
                                 const Vector&  b,
                                 Vector&        x);             

};

#endif /* __MATRIX_H__ */

/* ***************************************************** End of matrix.h *** */
