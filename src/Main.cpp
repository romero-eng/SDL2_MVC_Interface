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

constexpr int difference {5};
constexpr std::array<std::array<int, 2>, 2> line {{{4, 200}, {300, 6}}};
constexpr std::array<std::array<int, 2>, 2> modified_line {{{line[0][0], line[0][1] + difference},
															{line[1][0], line[1][1] + difference}}};
constexpr std::array<uint8_t, 4> WHITE {0xFF, 0xFF, 0xFF, 0xFF};


std::vector<std::array<int, 2>> custom_line_drawing(const std::array<std::array<int, 2>, 2> line)
{
	/*
	Problem Definition:
	-------------------

		Draw a discretized version of the line defined by the points {(x1, y1), (x1, y1)}
		Assume a non-steep slope (slope < 1)

	Algorithm:
	----------

		Δx = x2 - x1

		Δy = y2 - y1

		for n=1 to n=N:
		---------------

			x[n + 1] = x[n] + sgn(Δx), where x[0] = x_1 and x[N + 1] = x_2

						__
					   |
					   |  y[n] + sgn(Δy) ,  sgn(Δy)[y(x[n + 1]) - y[n]] >= 0.5
			y[n + 1] = |														, where y[0] = y1 and y[N + 1] = y2
					   |	  y[n]		 , 	sgn(Δy)[y(x[n + 1]) - y[n]] < 0.5
					   |__

	Computational Optimization:
	---------------------------

		sgn(Δy)[y(x[n + 1]) - y[n]] >= 0.5  --------->  2[(n + 1)Δy - (N + 1)*Δy[n]] >= sgn(Δy)*(N + 1), where Δy[n] = y[n] - y[0]

	For non-steep slopes:
	---------------------

		Switch the x and y-axes within the algorithm

	*/

	const auto& [point_1, point_2] = line;
    const auto& [x1, y1] = point_1;
    const auto& [x2, y2] = point_2;

    int delta_y {y2 - y1};
    int delta_x {x2 - x1};
	int sgn_delta_y {y2 >= y1 ? 1 : -1};
	int sgn_delta_x {x2 >= x1 ? 1 : -1};
    bool steep_slope {std::abs(delta_y) > std::abs(delta_x)};
    std::size_t N {static_cast<std::size_t>(steep_slope ? std::abs(delta_y) - 1 : std::abs(delta_x) - 1)};

    std::vector<std::array<int, 2>> points(N + 2);
    points[0] = point_1;
    points[N + 1] = point_2;

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

    return points;
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetBlendMode(SDML::Video::Blending::Mode::REPLACE);
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawPoints(custom_line_drawing(line));
		paintbrush.DrawLine(modified_line);
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
