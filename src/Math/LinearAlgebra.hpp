#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

// C++ Standard Libraries
#include <array>
#include <vector>
#include <cmath>

namespace Math {

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

Math::LinearAlgebra::Vector2D operator+(const Math::LinearAlgebra::Vector2D& addend_1,
										const Math::LinearAlgebra::Vector2D& addend_2);

Math::LinearAlgebra::Vector2D operator-(const Math::LinearAlgebra::Vector2D& minuend,
										const Math::LinearAlgebra::Vector2D& subtrahend);

Math::LinearAlgebra::Matrix2D operator+(const Math::LinearAlgebra::Matrix2D& addend_1,
										const Math::LinearAlgebra::Matrix2D& addend_2);

Math::LinearAlgebra::Matrix2D operator-(const Math::LinearAlgebra::Matrix2D& first,
										const Math::LinearAlgebra::Matrix2D& second);

Math::LinearAlgebra::Vector2D operator*(const Math::LinearAlgebra::Vector2D& vector,
										double scalar);

Math::LinearAlgebra::Matrix2D operator*(const Math::LinearAlgebra::Matrix2D& matrix,
										double scalar);

double operator*(const Math::LinearAlgebra::Vector2D& first,
				 const Math::LinearAlgebra::Vector2D& second);

Math::LinearAlgebra::Vector2D operator*(const Math::LinearAlgebra::Matrix2D& matrix,
										const Math::LinearAlgebra::Vector2D& vector);

Math::LinearAlgebra::Matrix2D operator*(const Math::LinearAlgebra::Matrix2D& first,
										const Math::LinearAlgebra::Matrix2D& second);


#endif
