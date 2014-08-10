#include <cstdio>
#include <cstdlib>
#include <cerrno>


enum token_t
{
	WORD,
	NUMBER,
	END = -1,
	COMMA,
	COMMENT

} token_t;


int main(int argc, char **argv)
{
	if ( argc != 2 )
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else 
    {

    }

	return 0;
}