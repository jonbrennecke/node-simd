#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

// set this to float or long double to change the precision of calculations
typedef double precision_t;

// lexer token types
enum token_t
{
	WORD,
	INTEGER,
	FLOAT,
	END = -1,
	COMMA,
	DOT,
	SEMI,
	COLON,
	COMMENT,
	ENDL,
	NUMBER
};

struct Token
{
	token_t type;
	char* str;
};

// the general purpose floating point registers are r01-r31
const char* registers[] = {
	"r00", "r01", "r02", "r03", "r04", "r05", "r06", "r07", "r08", "r09",
	"r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19",
	"r20", "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29",
	"r30", "r31"
};

/**
 *
 * Gather the next token from the file stream
 *
 * :param stream - a pointer to the current point in the file stream
 * :param text - pointer into which the consumed characters are placed
 *
 *
 */
static Token* getNextToken( const char** stream_ptr )
{
	auto token = new Token();
	const char* stream = *stream_ptr;
	const char* start = stream;

	// end of file
	if (!stream || !*stream)
	{
		token->type = END;
		return token;
	}

	// ignore whitespaces
	while (*stream == ' ' || *stream == '\t' )
	{
		stream++; start++;
	}


	// At minimum, one char is consumed,
	// The one char is read into the token string and the stream pointer is advnaced by 1
	token->str = (char*)malloc(sizeof(char));
	strncpy(token->str,stream,1);
	(*stream_ptr)++;

	if (*stream == '.') { token->type = DOT; return token; }
	if (*stream == ',') { token->type = COMMA; return token; }
	if (*stream == ';') { token->type = SEMI; return token; }
	if (*stream == ':') { token->type = COLON; return token; }
	if (*stream == '\n' || *stream == '\r' ) { token->type = ENDL; return token; }

	// 
	token->type = WORD;

	if ( isdigit(*stream) )
		token->type = NUMBER;

	// read an alphanumeric WORD or NUMBER
	while ( *stream != ',' 
		&& *stream != ';' && *stream != ':' 
		&& *stream != ' ' && *stream != '\t' 
		&& *stream != '\n' && stream && *stream )
	{
		// increment the stream by one char
		stream++;
	}

	size_t dist = stream - start;
	strncpy(token->str,stream,1);
	token->str = (char*)realloc( token->str, dist * sizeof(char));
	strncpy( token->str, start, dist );

	// advance the stream pointer 
	*stream_ptr = stream;

	return token;
}

static const uint8_t toOpcode( uint8_t inst, uint8_t* operands, size_t argc, ... )
{
	return 0;
}

/**
 *
 * Convert a register name to an integer (unsigned 8 bit)
 *
 * :param name - register name (r00-r31)
 *
 */
static const uint8_t toRegCode( const char* name )
{
	uint8_t reg = (uint8_t)atoi(name + sizeof(char));
	return reg;
}



/**
 *
 * Gather the next token from the file stream
 *
 * :param stream - a pointer to the current point in the file stream
 * :param end - pointer to the end of the file stream
 *
 */
static void parse ( const char* stream, const char* end )
{
	const char* start = stream;

	// read the first instruction from the stream
	auto next_token = getNextToken( &stream );

	// std::cout << next_token->str << std::endl;

	do
	{
		if ( next_token->type == WORD ) 
		{
			if ( !strcmp(next_token->str,"pop") ) // opcodes 0 through 3
			{
				uint8_t opcode = 0;
				auto operand = getNextToken( &stream );

				if ( operand->type == WORD )
				{
					uint8_t reg = toRegCode(operand->text);
					opcode++; // opcode 1
				}
				if ( operand->type == NUMBER )
				{
					uint8_t reg = toRegCode(optext);
					opcode+=2; // opcode 2
					// TODO
				}

				// uint8_t opcode = toOpcode( 0,   );
			}
			if ( !strcmp(text,"push") ) // opcode 00 0001
			{

			}
			if ( !strcmp(text,"add") ) // opcode 00 0010
			{

			}
			// "mov", "pop", "push", "add", "sub", "mul", "div"
		}



	} while( stream < end );

}


int main(int argc, char **argv)
{
	// no input arguments
	if ( argc != 2 ) 
	{
		std::cerr << "LEX: error: no input files.\n"; 
	}
	
	// input arguments
	else 
	{
		std::ifstream is( argv[1], std::ios::in | std::ios::binary );
		if ( is )
		{
			// read the entire file into a C string
			is.seekg(0, std::ifstream::end);
			size_t file_size = is.tellg();
			is.seekg(0);
			char buffer[ file_size ];
			is.read(buffer,file_size);

			// start at the beginning of the file
			char* stream = &buffer[0]; 
			char* end = &buffer[file_size];

			// begin parsing the file
			parse( stream, end );

			is.close();
		}
		else
		{
			std::cerr << "LEX: error: could not access the file '" << argv[1] << "' for reading.\n";
		}
    }
	return 0;
}