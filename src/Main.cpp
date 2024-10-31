#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "Logging/Logfile.hpp"
#include "SDML/Subsystem.hpp"
#include "SDML/Image.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "SDML/Events/Event.hpp"
#include "SDML/Events/EventMisc.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <memory>


constexpr std::string LOGFILE_NAME {"Test"};
constexpr std::string WINDOW_TITLE {"Test"};
constexpr std::array<int, 2> WINDOW_AREA {640, 480};
constexpr std::array<uint8_t, 3> WHITE {0xFF, 0xFF, 0xFF};
constexpr std::array<uint8_t, 3> BLACK {0x00, 0x00, 0x00};


std::vector<std::array<int, 2>> custom_calculate_line_points(const std::array<std::array<int, 2>, 2> line)
{
	/*
	Problem Definition:
	-------------------

		Draw a discretized version of the line (y = mx + b) defined by the points {(x1, y1), (x1, y1)}

	Algorithm:
	----------

		Basically, for a non-steep monotonically increasing line, step along the x-axis, and
		for each step, increment the y-value in case the actual line goes above the midpoint.
		The equations below are a generalized formalization of this procedure for all non-steep
		lines (for steep lines, switch the x and y axes).

		1)  define: Δx = x2 - x1

		2)  define: Δy = y2 - y1

		3)  define: x[n] = the array of points along the x-axis selected by this algorithm
						   where the beginning and end points are defined by the user-selected
						   points (i.e., x[0] = x_1 and x[N + 1] = x_2)

		4)  define: y[n] = the array of points along the y-axis selected by this algorithm
						   where the beginning and end points are defined by the user-selected
						   points (i.e., y[0] = y_1 and y[N + 1] = y_2)

						   WARNING: y[n] != y(x[n])

								=> y(x[n]) = mx[n] + b (i.e., y(x[n]) refers to the y-coordinates of the
														calculated points along the continuous line, not
														to the points selected by the algorithm which
														approximate this continuous line)
					 		__
						   |
						   |	 1,  x >= 0
		5) define sgn(x) = |
						   |	-1,  x < 0
						   |__

		6)  for n=1 to n=N: (with N being the number of steps to take along the x-axis)
		    ---------------

			    x[n + 1] = x[n] + sgn(Δx)

						    __
					       |
					       |  y[n] + sgn(Δy) ,  |y(x[n + 1]) - y[n]| >= 0.5
			    y[n + 1] = |
					       |	  y[n]		 , 	|y(x[n + 1]) - y[n]| < 0.5
					       |__

	Computational Optimization:
	---------------------------

		The calculation of the decision on whether or not to increment along the y-axis
		is computationally optimized as below:

				|y(x[n + 1]) - y[n]| >= 0.5  --------->  2|(n + 1)Δy - (N + 1)*(y[n] - y[0])| >= (N + 1)

		How this transformation is both equivalent and more computationally efficient is an
		exercise left up to the reader.

	*/

	const auto& [point_1, point_2] = line;
    const auto& [x1, y1] = point_1;
    const auto& [x2, y2] = point_2;

	if (point_1 == point_2) {
		throw std::runtime_error("Cannot calculate a drawn line between the same two points");
	}

    int delta_y {y2 - y1};
    int delta_x {x2 - x1};

	int sgn_delta_y {y2 >= y1 ? 1 : -1};
	int sgn_delta_x {x2 >= x1 ? 1 : -1};
    bool steep_slope {std::abs(delta_y) > std::abs(delta_x)};
    std::size_t N {static_cast<std::size_t>(steep_slope ? std::abs(delta_y) : std::abs(delta_x)) - 1};

	std::vector<std::array<int, 2>> points (N + 2);
    points[0] = point_1;
	points[N + 1] = point_2;

	if(delta_y == 0) {
		for (std::size_t n = 0; n < N; n++) {
			points[n + 1] = points[n];
			points[n + 1][0] += sgn_delta_x;
		}
	} else if (delta_x == 0) {
		for (std::size_t n = 0; n < N; n++) {
			points[n + 1] = points[n];
			points[n + 1][1] += sgn_delta_y;
		}
	} else {

	    int tmp_n_plus_one;
    	int tmp_N_plus_one {static_cast<int>(N) + 1};
 
	    for(std::size_t n = 0; n < N; n++) {

	        points[n + 1] = points[n];
    	    tmp_n_plus_one = static_cast<int>(n) + 1;

	        if(steep_slope) {
        	    if ((std::abs(tmp_n_plus_one*delta_x - tmp_N_plus_one*(points[n][0] - points[0][0])) << 1) >= tmp_N_plus_one) {
        	        points[n + 1][0] += sgn_delta_x;
            	}
            	points[n + 1][1] += sgn_delta_y;
    	    } else {
	            if ((std::abs(tmp_n_plus_one*delta_y - tmp_N_plus_one*(points[n][1] - points[0][1])) << 1) >= tmp_N_plus_one) {
            	    points[n + 1][1] += sgn_delta_y;
    	        }
        	    points[n + 1][0] += sgn_delta_x;
        	}
    	}
	}

    return points;
}


std::vector<std::array<int, 2>> custom_calculate_polygon_points(const std::vector<std::array<int, 2>> vertices)
{
	if(vertices.size() < 3) {
		throw std::runtime_error("A polygon can only be defined with a minimum of three vertices");
	}

	std::vector<std::array<std::array<int, 2>, 2>> lines;
	std::vector<std::array<int, 2>> points;

	for(std::size_t i = 0; i < vertices.size() - 1; i++) {
		lines.push_back({vertices[i], vertices[i + 1]});
	}
	lines.push_back({vertices[vertices.size() - 1], vertices[0]});

	for(std::array<std::array<int, 2>, 2> line : lines) {
		for(std::array<int, 2> point : custom_calculate_line_points(line)) {
			points.push_back(point);
		}
	}

	return points;
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawEntireTarget();
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(custom_calculate_polygon_points({{50, 50}, {100, 50}, {100, 100}}));
		paintbrush.Update();
		
		std::optional<std::unique_ptr<SDML::Events::Event>> current_event;
		bool quit = false;

		while(!quit) {
			current_event = SDML::Events::PollEvent();
			while(current_event.has_value()){
				quit = quit ? quit : current_event.value()->Quit();
				current_event = SDML::Events::PollEvent();
			}
		}

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
		Logging::MainLogFile.Write(error_message.what());
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
