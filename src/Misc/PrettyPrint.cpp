#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PrettyPrint.hpp"


std::string Misc::FormatKeyValuePairsForPrinting(const std::vector<std::pair<std::string, allowed_value_types>>& key_value_pairs,
												 const std::string& title)
{
    std::size_t max_key_length {0};
	std::size_t current_key_length;
    for(const std::string& key: std::views::elements<0>(key_value_pairs))
	{
    	current_key_length = key.length();
	    if(max_key_length < current_key_length){
		    max_key_length = current_key_length;
		}
    }

    std::size_t offset {2};
	std::vector<std::string> printable_keys_value_pairs {key_value_pairs.size() + offset};
    printable_keys_value_pairs[0] = fmt::format("{:s}:", title);
	printable_keys_value_pairs[1] = fmt::format("{:-^{}s}", "", title.length() + 1);

    for(std::size_t index = offset; index < printable_keys_value_pairs.size(); index++)
	{
		if (std::holds_alternative<bool>(key_value_pairs[index - offset].second))
		{
		    printable_keys_value_pairs[index] = \
			    fmt::format("{key:>{key_length}s}: {value:s}",
				    		fmt::arg("key", key_value_pairs[index - offset].first),
				        	fmt::arg("key_length", max_key_length),
						    fmt::arg("value", std::get<bool>(key_value_pairs[index - offset].second) ? "True" : "False"));
    	} else if (std::holds_alternative<Uint32>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:d}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", std::get<Uint32>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<int>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:d}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", std::get<int>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<float>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:f}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
							fmt::arg("value", std::get<float>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<const char*>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:s}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", std::get<const char*>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<std::string>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:s}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", std::get<std::string>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<std::string_view>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:s}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", std::get<std::string_view>(key_value_pairs[index - offset].second)));
    	} else if (std::holds_alternative<std::vector<std::string>>(key_value_pairs[index - offset].second)) {
	    	printable_keys_value_pairs[index] = \
		    	fmt::format("{key:>{key_length}s}: {value:s}",
			    			fmt::arg("key", key_value_pairs[index - offset].first),
				    		fmt::arg("key_length", max_key_length),
					    	fmt::arg("value", fmt::format("[{}]", fmt::join(std::get<std::vector<std::string>>(key_value_pairs[index - offset].second), ", "))));
    	} else {
	    	throw std::runtime_error(fmt::format("Unrecognized type for the '{key:s}' Key in the '{:s}' Key-Value Pairs",
		    								  	 fmt::arg("key", key_value_pairs[index - offset].first),
			    							  	 title));
		}
	}

	return std::string {fmt::format("{}", fmt::join(printable_keys_value_pairs, "\n"))};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
