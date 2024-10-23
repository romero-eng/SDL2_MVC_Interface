#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PrettyPrint.hpp"


std::string Logging::time_to_string(const std::chrono::time_point<std::chrono::system_clock>& time_point)
{   
    return fmt::format("{:%I:%M:%S %p} [{:d} ms]",
					   fmt::localtime(std::chrono::system_clock::to_time_t(time_point)),
					   std::chrono::duration_cast<std::chrono::milliseconds>(time_point - std::chrono::floor<std::chrono::seconds>(time_point)).count());
}


std::string Logging::date_and_time_to_string(const std::chrono::time_point<std::chrono::system_clock>& time_point)
{
   
    return fmt::format("{:%A, %B %d, %I:%M:%S %p %Z} [{:d} ms]",
					   fmt::localtime(std::chrono::system_clock::to_time_t(time_point)),
					   std::chrono::duration_cast<std::chrono::milliseconds>(time_point - std::chrono::floor<std::chrono::seconds>(time_point)).count());
}


const char* Logging::Printables::get_title() { return this->title.c_str(); }

void Logging::Printables::set_title(const char* new_title) { this->set_title(std::string {new_title}); }

void Logging::Printables::set_title(std::string new_title) { this->title = new_title; }

void Logging::Printables::add_printable(const char* key, bool value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, bool value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::string{value ? "True" : "False"}}); }

void Logging::Printables::add_printable(const char* key, uint32_t value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, uint32_t value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Logging::Printables::add_printable(const char* key, int value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, int value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Logging::Printables::add_printable(const char* key, float value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, float value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Logging::Printables::add_printable(const char* key, const char* value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, const char* value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::string{value}}); }

void Logging::Printables::add_printable(const char* key, const std::string& value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, const std::string& value) { this->printables.push_back(std::pair<std::string, std::string> {key, value}); }

void Logging::Printables::add_printable(const char* key, const std::vector<std::string>& value) { this->add_printable(std::string {key}, value); }

void Logging::Printables::add_printable(const std::string& key, const std::vector<std::string>& value) { this->printables.push_back(std::pair<std::string, std::string> {key, fmt::format("[{}]", fmt::join(value, ", "))}); }

void Logging::Printables::add_printable(Printables& printables) { this->printables.push_back(printables); }

void Logging::Printables::copy_into_printables(Printables printables) { this->printables.push_back(printables); }

std::string Logging::Printables::print(std::size_t prior_level)
{
	std::size_t num_tab_spaces {6};

	std::size_t max_key_length {0};
	std::size_t current_key_length;
	for(const std::variant<Printables, std::pair<std::string, std::string>>& printable : printables)
	{
		if(std::holds_alternative<std::pair<std::string, std::string>>(printable)) {
			current_key_length = std::get<std::pair<std::string, std::string>>(printable).first.length();
			max_key_length = max_key_length < current_key_length ? current_key_length : max_key_length;
		}
	}

	bool non_empty_title {this->title != ""};
	std::size_t index_offset {static_cast<std::size_t>(non_empty_title ? 2 : 0)};
	std::vector<std::string> lines (this->printables.size() + index_offset);

	if(non_empty_title) {
		lines[0] = \
			fmt::format("{:{prior_indentation}s}{Title:s}:",
						"",
						fmt::arg("prior_indentation", num_tab_spaces*prior_level),
						fmt::arg("Title", this->title));
		lines[1] = \
			fmt::format("{:{prior_indentation}s}{:-^{Title_Length}s}",
						"",
						"",
						fmt::arg("prior_indentation", num_tab_spaces*prior_level),
						fmt::arg("Title_Length", this->title.length() + 1));
	}

	for(std::size_t index = index_offset; index < lines.size(); index++) {
		if(std::holds_alternative<std::pair<std::string, std::string>>(this->printables[index - index_offset])) {
			lines[index] = \
				fmt::format("{:{prior_indentation}s}{key:>{key_length}s}: {value:s}",
							"",
							fmt::arg("prior_indentation", num_tab_spaces*prior_level),
							fmt::arg(		"key", std::get<std::pair<std::string, std::string>>(this->printables[index - index_offset]).first),
							fmt::arg("key_length", max_key_length),
							fmt::arg(	  "value", std::get<std::pair<std::string, std::string>>(this->printables[index - index_offset]).second));
		} else {
			lines[index] = "\n" + std::get<Printables>(this->printables[index-index_offset]).print(prior_level + 1) + "\n";
		}
	}

	return fmt::format("{}", fmt::join(lines, "\n"));
}

void Logging::Printables::clear() { this->printables.clear(); }

std::ostream& operator<<(std::ostream& output, Logging::Printables& printables) { return output << printables.print(); }

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
