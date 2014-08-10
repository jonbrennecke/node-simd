#include <fstream>
#include <istream>
#include <string>
#include <regex>
#include <map>
#include <iostream>

/**
 *
 * instruction
 *
 */
// struct instruction
// {
// 	instruction* next;

// };

auto reg_consts = std::regex_constants::ECMAScript | std::regex_constants::icase;

/**
 *
 * LEXICON - The input to our very basic lexer/tokenizer
 *
 */
std::map<std::string, std::regex> lexicon = {
	{ "WS", std::regex("^[ \\t\\n\\r\\f\\v]+", reg_consts ) },
	{ "WORD", std::regex("^([a-zA-Z]\\w*)", reg_consts ) },
	{ "COMMENT", std::regex("^;.*?[$\\n]", reg_consts ) },
	{ "COMMA", std::regex("^,", reg_consts ) },
	{ "EOF", std::regex("^$", reg_consts ) },
	{ "NUMBER", std::regex("^([\\-]?[0-9]+(\\.[0-9]+)?)", reg_consts ) },
};

std::map<std::string, std::regex> parsicon = {
	{ "WS", std::regex("^[ \\t\\n\\r\\f\\v]+") },
};


// std::regex reg_mov( reg_str_mov, std::regex_constants::icase );

int main()
{

	// tokenize some assembly!


	// TODO file names should eventually come from CLI args
	std::string filename_in = "./test.asm";
	std::string filename_out = "./test.bytecode";

	// open two binary file streams
	// one for input & one for output
	std::ifstream is(filename_in, std::ios::in | std::ios::binary);
	std::ofstream os(filename_out, std::ios::out | std::ios::binary);
	if ( is && os )
	{
		// read the entire file into a string
		std::string buffer((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());

		// consume the entire buffer
		while ( buffer.length() )
		{
			/**
			 *
			 * loop through each field in the lexicon and match it to the start of the buffer
			 *
			 * the substring of the buffer that is matched will be consumed
			 *
			 */

			// save the buffer length; if nothing is consumed after looping through the lexicon
			// then an Unexpected Token Error is reported
			size_t buffer_len = buffer.length();

			std::smatch lex_match;
			for (auto it = lexicon.begin(); it != lexicon.end(); ++it)
			{
				if ( std::regex_search(buffer, lex_match, it->second) ) 
				{
					// assume that there is no capture group
					size_t match_index = 0;

					// just testing
					// os << '[' << it->first << ']';

					/**
					 * This statement only evaluates if there is a capture group.
					 *
					 * The first sub_match is the whole string; the next
					 * sub_match is the first parenthesized expression.
					 */
					if (lex_match.size() > 1) {
						match_index = 1;

						std::ssub_match base_sub_match = lex_match[1];
						std::string base = base_sub_match.str();

						// testing
						std::cout << it->first << " ==> " << base << '\n';

					}

					// consume the buffer up to the starting position of the match
					buffer.erase(buffer.begin(),buffer.begin() + lex_match.length(match_index));

					// break since we found a match
					break;
				}
			}

			if ( buffer.length() == buffer_len ) {

				// trim whitespace from end of reported problem string
				std::cout << "ERROR: Unexpected token at: '" << buffer.substr(0,10) << "'" << std::endl;
				os << buffer;
				break;
			}
		}

		os.close();
		is.close();
	}
	else {

	}
}