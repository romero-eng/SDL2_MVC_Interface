#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

// C++ Standard Libraries
#include <array>
#include <vector>
#include <cmath>

namespace Custom {

	namespace LinearAlgebra {

		std::array<std::array<double, 2>, 2> rotation_matrix(double angle_degrees);

		std::vector<std::array<double, 2>> translate_and_rotate_vectors(std::vector<std::array<double, 2>> vectors,
																	    double angle_degrees,
																	    std::array<double, 2> center);

		std::vector<std::array<int, 2>> round_double_vectors_to_int_vectors(const std::vector<std::array<double, 2>> double_vertices);
	}

}

std::array<double, 2> operator+(const std::array<double, 2>& first_vector,
								const std::array<double, 2>& second_vector);


double operator*(const std::array<double, 2>& first_vector,
				 const std::array<double, 2>& second_vector);


std::array<double, 2> operator*(const std::array<std::array<double, 2>, 2>& matrix,
								const std::array<double, 2>& vector);


#endif
