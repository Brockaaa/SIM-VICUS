/*	IBK Math Kernel Library
	Copyright (c) 2001-2016, Institut fuer Bauklimatik, TU Dresden, Germany

	Written by A. Nicolai, A. Paepcke, H. Fechner, St. Vogelsang
	All rights reserved.

	This file is part of the IBKMK Library.

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors
	   may be used to endorse or promote products derived from this software without
	   specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	This library contains derivative work based on other open-source libraries,
	see LICENSE and OTHER_LICENSES files.

*/

#ifndef IBKMK_DenseMatrixH
#define IBKMK_DenseMatrixH

#include <vector>
#include <stdexcept>
#include <cmath>
#include <cstring>

#include <IBK_configuration.h>
#include <IBK_assert.h>
#include <IBK_FormatString.h>

namespace IBKMK {

/*! A simple matrix implementation.

	This is an implementation for a square dense matrix with corresponding math algorithms.
	Resizing is possible, see resize() for details.

	Data storage is column-based, the element (2,5) has the index [2 + 5*n] in the linear
	memory array.
*/
class DenseMatrix {
public:
	/*! Default construction.
		Creates an empty matrix.
	*/
	DenseMatrix() : m_n(0) {}
	/*! Initialisation constructor.
		Creates a matrix with the dimensions: n x n
	*/
	DenseMatrix(unsigned int n) {
		resize(n);
	}

	/*! Initialization constructor with initial value.
		Creates a matrix with the dimensions: n x n and sets all elements to 'value'.
	*/
	DenseMatrix(unsigned int n, double value) : m_data(n*n, value), m_n(n), m_pivots(n) { }


	/*! Returns a reference to the element at the coordinates [i, j].
		\param i Matrix row, 0 <= i < n
		\param j Matrix column, 0 <= j < n
		\code
		A(i,j) = 6;
		\endcode
	*/
	double & operator()(unsigned int i, unsigned int j) {
		IBK_ASSERT(i < m_n);
		IBK_ASSERT(j < m_n);
		return m_data[i + j*m_n];
	}

	/*! Returns a constant reference to the element at the coordinates [i, j].
		\param i Matrix row, 0 <= i < n
		\param j Matrix column, 0 <= j < n
		\code
		val = A.value(i,j);
		\endcode
		When an element is requested, that is not part of the
		matrix pattern the function returns a zero instead.
	*/
	double value(unsigned int i, unsigned int j) const {
		IBK_ASSERT(i < m_n);
		IBK_ASSERT(j < m_n);
		return m_data[i + j*m_n];
	}

	/*! Returns the number of rows/columns in the matrix. */
	unsigned int n() const { return m_n; }

	/*! Resizes the matrix (all data is lost if size differs from previous size). */
	void resize(unsigned int n);

	/*! Swaps the content of the matrix with the content of another matrix.
		This is efficient because only internal pointers are exchanged.
	*/
	void swap(DenseMatrix & mat);

	/*! Empties the matrix and sets its dimensions to 0. */
	void clear() { m_data.clear(); m_n = 0; }

	/*! Fills the matrix with the given value. */
	void fill(double value) { IBK_ASSERT(m_n != 0); std::fill(m_data.begin(), m_data.end(), value); }

	/*! Sets the matrix values to zero. */
	void setZero() { IBK_ASSERT(m_n != 0); std::memset(&m_data[0], 0, sizeof(double)*m_n*m_n); }

	/*! Returns true is matrix is empty. */
	bool isEmpty() const { return m_n == 0; }

	/*! Performs an LU factorization of the matrix which is the first step in solving an equation system Ax = b.
		The lower and upper triangular matrices are stored in place of the original matrix.
		Uses built-in pivot vector.
		\sa backsolve()
		\return Returns error code != 0 if LU decomposition fails. Error code is row of matrix + 1 that
				became singular during decomposition.
	*/
	int lu();

	/*! Solves the linear system of equations Ax = b using back-solution when
		A is already stored as LU factorized matrix.
		Uses built-in pivot vector.
		\sa lu().
	*/
	void backsolve(double * b) const;

	/*! Multiplication operation for this simple matrix with a vector.
		\param b The vector (size n).
		\param rhs The resulting vector (size n).
	*/
	void multiply(const double * b, double * res) const;

	/*! Returns the row sum norm of the matrix. */
	double rowSumNorm();
	/*! Returns the column sum norm of the matrix. */
	double columnSumNorm();
	/*! Returns the condition based of the row sum norm of the matrix. */
	double conditionRowBased();
	/*! Returns the condition based of the column sum norm of the matrix. */
	double conditionColBased();

	/*! Calculates the normalized maximum residual of the solution to the linear equation solution A*x = d.
		The residuals are calculated for each line and the absolute maximum of all residuals is returned normalized by the
		left hand side of the equation.
		\param d Const reference to a vector with the right-hand-side of the equation system (at least rows() elements).
		\param x Reference to a vector with the result.
		\return Returns absolute value of maximum normalized residual.
	*/
	double max_residual(const double * d, const double * x) const;

	/*! Gives access to raw memory holding the matrix data. */
	std::vector<double> & data() { return m_data; }


	/*! Dumps the matrix to an output stream in human-readibly.
		\param out Output stream (ASCII).
		\param b Pointer to vector to print alongside matrix, size = n, nullptr if no vector to print.
		\param eulerFormat If true, prints in Euler-Mathtoolbox format
		\param width Column width for matrix output (precision is expected to be set as stream property)
		\param matrixLabel The label to be used for defining the matrix in Euler format, defaults to 'A'
		\param vectorLabel The label to be used for defining the vector b in Euler format, defaults to 'b'
	*/
	void write(std::ostream & out, double * b = nullptr, bool eulerFormat = false, unsigned int width=4,
					   const char * const matrixLabel = "A", const char * const vectorLabel = "b") const;


private:

	std::vector<double>			m_data;		///< Storage member, stores data column based using index [row + col*n]
	unsigned int				m_n;		///< Dimension of the matrix, n x n

	std::vector<long int>		m_pivots;		///< Pivoting vector, used for lu() factorization, resized on first call to lu().

}; // class DenseMatrix
// ---------------------------------------------------------------------------


} // namespace IBKMK

#endif // IBKMK_DenseMatrixH
