#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "LinearAlgebra.hpp"


Math::LinearAlgebra::Vector2D operator+(const Math::LinearAlgebra::Vector2D& addend_1,
										const Math::LinearAlgebra::Vector2D& addend_2)
{ return {addend_1.x + addend_2.x,
		  addend_1.y + addend_2.y}; }


Math::LinearAlgebra::Vector2D operator-(const Math::LinearAlgebra::Vector2D& minuend,
										const Math::LinearAlgebra::Vector2D& subtrahend)
{ return {minuend.x - subtrahend.x, minuend.y - subtrahend.y}; }


Math::LinearAlgebra::Matrix2D operator+(const Math::LinearAlgebra::Matrix2D& addend_1,
										const Math::LinearAlgebra::Matrix2D& addend_2)
{ return {addend_1.left_column  + addend_2.left_column,
		  addend_1.right_column + addend_2.right_column}; }


Math::LinearAlgebra::Matrix2D operator-(const Math::LinearAlgebra::Matrix2D& minuend,
										const Math::LinearAlgebra::Matrix2D& subtrahend)
{ return {minuend.left_column - subtrahend.left_column,
		  minuend.right_column - subtrahend.right_column}; }


Math::LinearAlgebra::Vector2D operator*(const Math::LinearAlgebra::Vector2D& vector,
										double scalar)
{ return {vector.x*scalar, vector.y*scalar}; }


Math::LinearAlgebra::Matrix2D operator*(const Math::LinearAlgebra::Matrix2D& matrix,
										double scalar)
{ return {matrix.left_column*scalar, matrix.right_column*scalar}; }


double operator*(const Math::LinearAlgebra::Vector2D& first,
				 const Math::LinearAlgebra::Vector2D& second)
{ return first.x*second.x + first.y*second.y; }


Math::LinearAlgebra::Vector2D operator*(const Math::LinearAlgebra::Matrix2D& matrix,
										const Math::LinearAlgebra::Vector2D& vector)
{ return {matrix.left_column*vector.x + matrix.right_column*vector.y}; }


Math::LinearAlgebra::Matrix2D operator*(const Math::LinearAlgebra::Matrix2D& first,
										const Math::LinearAlgebra::Matrix2D& second)
{ return {first*second.left_column, first*second.right_column}; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
