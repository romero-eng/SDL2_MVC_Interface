#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "LinearAlgebra.hpp"


std::array<int, 2> Custom::LinearAlgebra::Vector2D::round() { return {static_cast<int>(x), static_cast<int>(y)}; }


Custom::LinearAlgebra::Vector2D operator+(const Custom::LinearAlgebra::Vector2D& addend_1,
										  const Custom::LinearAlgebra::Vector2D& addend_2)
{ return {addend_1.x + addend_2.x,
		  addend_1.y + addend_2.y}; }


Custom::LinearAlgebra::Vector2D operator-(const Custom::LinearAlgebra::Vector2D& minuend,
										  const Custom::LinearAlgebra::Vector2D& subtrahend)
{ return {minuend.x - subtrahend.x, minuend.y - subtrahend.y}; }


Custom::LinearAlgebra::Matrix2D operator+(const Custom::LinearAlgebra::Matrix2D& addend_1,
										  const Custom::LinearAlgebra::Matrix2D& addend_2)
{ return {addend_1.left_column  + addend_2.left_column,
		  addend_1.right_column + addend_2.right_column}; }


Custom::LinearAlgebra::Matrix2D operator-(const Custom::LinearAlgebra::Matrix2D& minuend,
										  const Custom::LinearAlgebra::Matrix2D& subtrahend)
{ return {minuend.left_column - subtrahend.left_column,
		  minuend.right_column - subtrahend.right_column}; }


Custom::LinearAlgebra::Vector2D operator*(const Custom::LinearAlgebra::Vector2D& vector,
										  double scalar)
{ return {vector.x*scalar, vector.y*scalar}; }


Custom::LinearAlgebra::Matrix2D operator*(const Custom::LinearAlgebra::Matrix2D& matrix,
										  double scalar)
{ return {matrix.left_column*scalar, matrix.right_column*scalar}; }


double operator*(const Custom::LinearAlgebra::Vector2D& first,
				 const Custom::LinearAlgebra::Vector2D& second)
{ return first.x*second.x + first.y*second.y; }


Custom::LinearAlgebra::Vector2D operator*(const Custom::LinearAlgebra::Matrix2D& matrix,
										  const Custom::LinearAlgebra::Vector2D& vector)
{ return {matrix.left_column*vector.x + matrix.right_column*vector.y}; }


Custom::LinearAlgebra::Matrix2D operator*(const Custom::LinearAlgebra::Matrix2D& first,
										  const Custom::LinearAlgebra::Matrix2D& second)
{ return {first*second.left_column, first*second.right_column}; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
