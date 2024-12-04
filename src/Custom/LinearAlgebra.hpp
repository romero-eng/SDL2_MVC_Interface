#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

// C++ Standard Libraries
#include <array>
#include <vector>
#include <cmath>

namespace Custom {

	namespace LinearAlgebra {

		class Vector2D
		{
		public:

			double x;
			double y;

			constexpr Vector2D(double x, double y) : x{x}, y{y} {}

			constexpr Vector2D() : Vector2D(0, 0) {}

			constexpr std::array<int, 2> round() const { return {static_cast<int>(x), static_cast<int>(y)}; }

		};

		class Matrix2D
		{
		public:

			Vector2D left_column;
			Vector2D right_column;

			constexpr Matrix2D(Vector2D left_column, Vector2D right_column): left_column{left_column}, right_column{right_column} {}

			constexpr Matrix2D(): Matrix2D({}, {}) {}

		};
	}
}

Custom::LinearAlgebra::Vector2D operator+(const Custom::LinearAlgebra::Vector2D& addend_1,
										  const Custom::LinearAlgebra::Vector2D& addend_2);

Custom::LinearAlgebra::Vector2D operator-(const Custom::LinearAlgebra::Vector2D& minuend,
										  const Custom::LinearAlgebra::Vector2D& subtrahend);

Custom::LinearAlgebra::Matrix2D operator+(const Custom::LinearAlgebra::Matrix2D& addend_1,
										  const Custom::LinearAlgebra::Matrix2D& addend_2);

Custom::LinearAlgebra::Matrix2D operator-(const Custom::LinearAlgebra::Matrix2D& first,
										  const Custom::LinearAlgebra::Matrix2D& second);

Custom::LinearAlgebra::Vector2D operator*(const Custom::LinearAlgebra::Vector2D& vector,
										  double scalar);

Custom::LinearAlgebra::Matrix2D operator*(const Custom::LinearAlgebra::Matrix2D& matrix,
										  double scalar);

double operator*(const Custom::LinearAlgebra::Vector2D& first,
				 const Custom::LinearAlgebra::Vector2D& second);

Custom::LinearAlgebra::Vector2D operator*(const Custom::LinearAlgebra::Matrix2D& matrix,
										  const Custom::LinearAlgebra::Vector2D& vector);

Custom::LinearAlgebra::Matrix2D operator*(const Custom::LinearAlgebra::Matrix2D& first,
										  const Custom::LinearAlgebra::Matrix2D& second);


#endif
