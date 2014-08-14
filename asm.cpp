#include "virtue.h"
#include <fstream> // for file IO, this is about the only C++ feature that's being used here
#include <ctype.h> // for isdigit()

#define DDREF(ptr) *(*ptr) /* double reference a pointer */


// lexer token types
enum token_t
{
	WORD,
	INTEGER,
	FLOAT,
	HALT,
	COMMA,
	DOT,
	SEMI,
	COLON,
	COMMENT,
	ENDL,
	NUMBER
};

enum operation_t
{
	MOV,
	PUSH,
	POP,
	NONE
};

struct Token
{
	token_t type;
	char* str;
};

operation_t str2op( char* str )
{
	if (!strcmp(str,"mov"))
		return MOV;
	else if (!strcmp(str,"push"))
		return PUSH;
	else if (!strcmp(str,"pop"))
		return POP;
	else return NONE;
}





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
static void getNextToken( const char** stream, Token* token )
{
	const char* start = *stream;

	// end of file
	if (!stream || !DDREF(stream))
	{
		token->type = HALT;
		token->str  = (char*)"\n";
		return;
	}

	// ignore whitespaces
	while ( DDREF(stream) == ' ' || DDREF(stream) == '\t' )
	{
		start++;
		(*stream)++;
	}

	// At minimum, one char is consumed,
	// The one char is read into the token string and the stream pointer is advnaced by 1
	token->str = (char*)malloc(sizeof(char));
	strncpy(token->str,start,1);
	(*stream)++;

	if ( *start == '.') { token->type = DOT; return; }
	if ( *start == ',') { token->type = COMMA; return; }
	if ( *start == ';') { token->type = SEMI; return; }
	if ( *start == ':') { token->type = COLON; return; }
	if ( *start == '\n' || DDREF(stream) == '\r' ) { token->type = ENDL; return; }

	// assume WORD but check for NUMBER
	token->type = WORD;
	if ( isdigit( DDREF(stream) ) )
		token->type = NUMBER;

	// read an alphanumeric WORD or NUMBER
	while ( *stream && DDREF(stream)
		&& DDREF(stream) != ';' && DDREF(stream) != ':' 
		&& DDREF(stream) != ' ' && DDREF(stream) != '\t' 
		&& DDREF(stream) != '\n' && DDREF(stream) != ',' )
	{
		// increment the stream by one char
		(*stream)++;
	}

	size_t dist = *stream - start;
	token->str = (char*)realloc( token->str, dist * sizeof(char));
	strncpy(token->str,start,dist );
	return;
}

// TODO
// static const uint8_t toOpcode( uint8_t inst, uint8_t* operands, size_t argc, ... )
// {
// 	return 0;
// }

/**
 *
 * Convert a register name to an integer (unsigned 8 bit)
 *
 * :param name - register name (r00-r31)
 *
 */
// static const uint8_t toRegCode( const char* name )
// {
// 	uint8_t reg = (uint8_t)atoi(name + sizeof(char));
// 	return reg;
// }

static void assertTokenMatch( token_t type, Token* token )
{
	if ( token->type != type )
		std::cerr << ;
	// std::cerr << 
}



/**
 *
 * Gather the next token from the file stream
 *
 * :param stream - a pointer to the current point in the file stream
 * :param end - pointer to the end of the file stream
 *
 */
static void assemble ( const char* stream, const char* end, std::ostream& os )
{
	Token* token = new Token();

	do
	{
		// read the next instruction from the stream
		getNextToken(&stream,token);

		switch ( token->type )
		{
			// case LABEL :
			// case ATSIGN :
			case WORD :
			{
				// convert the token into an operation_t
				operation_t op = str2op(token->str);

				switch ( op )
				{
					case PUSH :

						// Register name
						getNextToken(&stream,token);
						assertTokenMatch(WORD,token`);

						// Comma
						getNextToken(&stream,token);
						assertTokenMatch(COMMA,token);

						// Immediate or Register
						getNextToken(&stream,token);
						assertTokenMatch(NUMBER|WORD,token);

						break;
					case POP :
						getNextToken(&stream,token);
						if ( token->type == WORD )

						break;
					case MOV :
						break;
					default :
						// std::cerr << sprintf((char*)"Unexpected token %s.",token->str);
						break;
				}

				break;
			}
			case SEMI :
				// consume comments
				do
				{
					getNextToken(&stream, token);
				}
				while ( token->type != ENDL && token->type != HALT );
				break;
			default : 
				break;
		}
	}
	while ( token->type != HALT );
}

static void read_asm( std::istream& is, std::ostream& os )
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
	assemble( stream, end, os );
}


int main(int argc, char **argv)
{
	// no input arguments
	if ( argc != 2 ) 
		std::cerr << "LEX: error: no input files.\n"; 
	
	// input arguments
	else 
	{
		std::ifstream is( argv[1], std::ios::in | std::ios::binary );
		std::ofstream os( "bytecode", std::ios::out | std::ios::binary );
		if ( is && os )
		{
			read_asm(is,os);
			os.close();
			is.close();
		}
		else
		{
			std::cerr << "LEX: error: could not access the file '" << argv[1] << "' for reading.\n";
		}
    }
	return 0;
}