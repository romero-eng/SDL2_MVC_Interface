#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "LinearAlgebra.hpp"


std::array<std::array<double, 2>, 2> Custom::LinearAlgebra::rotation_matrix(double angle_degrees)
{
	double angle_radians {(M_PI/180)*angle_degrees};

	return {{{ std::cos(angle_radians), std::sin(angle_radians)},
			 {-std::sin(angle_radians), std::cos(angle_radians)}}};
}


std::vector<std::array<double, 2>> Custom::LinearAlgebra::translate_and_rotate_vectors(std::vector<std::array<double, 2>> vectors,
														    	    	    	       double angle_degrees,
															    	    	           std::array<double, 2> center)
{
	std::vector<std::array<double, 2>> new_vectors (vectors.size());
	std::array<std::array<double, 2>, 2> new_rotation_matrix {rotation_matrix(angle_degrees)};

	for(std::size_t n = 0; n < vectors.size(); n++) {
		new_vectors[n] = new_rotation_matrix*vectors[n] + center;
	}

	return new_vectors;
}


std::vector<std::array<int, 2>> Custom::LinearAlgebra::round_double_vectors_to_int_vectors(const std::vector<std::array<double, 2>> double_vertices)
{
	std::vector<std::array<int, 2>> int_vertices (double_vertices.size());

	for(std::size_t n = 0; n < double_vertices.size(); n++){
		int_vertices[n] = {static_cast<int>(std::round(double_vertices[n][0])),
						   static_cast<int>(std::round(double_vertices[n][1]))};
	}

	return int_vertices;
}


std::array<double, 2> operator+(const std::array<double, 2>& first_vector,
								const std::array<double, 2>& second_vector) {
	return {first_vector[0] + second_vector[0],
			first_vector[1] + second_vector[1]};
}


double operator*(const std::array<double, 2>& first_vector,
								const std::array<double, 2>& second_vector) {
	return {first_vector[0]*second_vector[0] + first_vector[1]*second_vector[1]};
}


std::array<double, 2> operator*(const std::array<std::array<double, 2>, 2>& matrix,
								const std::array<double, 2>& vector) {
	return {matrix[0]*vector, matrix[1]*vector};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
