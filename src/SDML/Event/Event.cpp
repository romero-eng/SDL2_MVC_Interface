#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Event.hpp"


SDML::Video::Window SDML::Event::WindowEvent::FindWindow(const SDL_Event& event)
{
	Video::Window found_window;

	if(windows.size() == 0) {
		found_window = windows[0];
	} else {

		std::size_t current_window_index = 0;
		bool found = false;
		while(current_window_index < windows.size() && !found) {
			found = windows[current_window_index].GetID() == event.window.windowID;
			if(!found) { current_window_index++; } 
		}

		found_window = windows[current_window_index];
	}

	return found_window;
}


SDML::Event::WindowEvent::WindowEvent(const SDL_Event& event,
									  const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point},
									  																			  window{this->FindWindow(event)},
																												  event{event.window.event},
																												  data1{event.window.data1},
																												  data2{event.window.data2} {}


std::string SDML::Event::WindowEvent::to_string() const
{
	Misc::Printables event_description {"Window Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(this->GetTimeStamp()));
	event_description.add_printable("Window", this->window.GetTitle());
	event_description.add_printable("Event", this->event);
	event_description.add_printable("Data1", this->data1);
	event_description.add_printable("Data2", this->data2);

	return event_description.print();
}


SDML::Event::QuitEvent::QuitEvent(const SDL_Event& event,
			                      const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point} {}


std::string SDML::Event::QuitEvent::to_string() const
{
	Misc::Printables event_description {"Quit Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(this->GetTimeStamp()));

	return event_description.print();
}


SDML::Event::GenericEvent::GenericEvent(const SDL_Event& event,
			                            const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point},
																												    type_integer{event.type} {}


std::string SDML::Event::GenericEvent::to_string() const
{
	Misc::Printables event_description {"Generic Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(this->GetTimeStamp()));
	event_description.add_printable("Type", fmt::format("{:#x}", this->GetTypeInteger()));

	return event_description.print();
}


uint32_t SDML::Event::GenericEvent::GetTypeInteger() const { return this->type_integer; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::WindowEvent& event)
{ return output << event.to_string() << std::endl; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::QuitEvent& event)
{ return output << event.to_string() << std::endl; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::GenericEvent& event)
{ return output << event.to_string() << std::endl; }



#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
