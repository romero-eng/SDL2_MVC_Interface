#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PrettyPrint.hpp"

const char* Misc::Printables::get_title() { return this->title.c_str(); }

void Misc::Printables::set_title(const char* new_title) { this->title = std::string {new_title}; }

void Misc::Printables::set_title(std::string new_title) { this->title = new_title; }

void Misc::Printables::add_printable(const char* key, bool value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, std::string{value ? "True" : "False"}}); }

void Misc::Printables::add_printable(const std::string& key, bool value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::string{value ? "True" : "False"}}); }

void Misc::Printables::add_printable(const char* key, uint32_t value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, std::to_string(value)}); }

void Misc::Printables::add_printable(const std::string& key, uint32_t value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Misc::Printables::add_printable(const char* key, int value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, std::to_string(value)}); }

void Misc::Printables::add_printable(const std::string& key, int value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Misc::Printables::add_printable(const char* key, float value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, std::to_string(value)}); }

void Misc::Printables::add_printable(const std::string& key, float value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::to_string(value)}); }

void Misc::Printables::add_printable(const char* key, const char* value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, std::string{value}}); }

void Misc::Printables::add_printable(const std::string& key, const char* value) { this->printables.push_back(std::pair<std::string, std::string> {key, std::string{value}}); }

void Misc::Printables::add_printable(const char* key, const std::string& value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, value}); }

void Misc::Printables::add_printable(const std::string& key, const std::string& value) { this->printables.push_back(std::pair<std::string, std::string> {key, value}); }

void Misc::Printables::add_printable(const char* key, const std::vector<std::string>& value) { this->printables.push_back(std::pair<std::string, std::string> {std::string{key}, fmt::format("[{}]", fmt::join(value, ", "))}); }

void Misc::Printables::add_printable(const std::string& key, const std::vector<std::string>& value) { this->printables.push_back(std::pair<std::string, std::string> {key, fmt::format("[{}]", fmt::join(value, ", "))}); }

void Misc::Printables::add_printable(Printables& printables) { this->printables.push_back(printables); }

void Misc::Printables::copy_into_printables(Printables printables) { this->printables.push_back(printables); }

std::string Misc::Printables::print(std::size_t prior_level)
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

void Misc::Printables::clear() { this->printables.clear(); }

std::ostream& operator<<(std::ostream& output, Misc::Printables& printables) { return output << printables.print(); }

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
