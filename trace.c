		switch ( token->type )
		{
			// os << token->str;
			// printf(token->str);
			case WORD :
				printf("%s -- %s\n","WORD", token->str );
				break;
			case INTEGER :
				printf("%s -- %s\n","INTEGER", token->str );
				break;
			case FLOAT :
				printf("%s -- %s\n","FLOAT", token->str );
				break;
			case HALT :
				printf("%s -- %s\n","HALT", token->str );
				break;
			case COMMA :
				printf("%s -- %s\n","COMMA", token->str );
				break;
			case DOT :
				printf("%s -- %s\n","DOT", token->str );
				break;
			case SEMI :
				printf("%s -- %s\n","SEMI", token->str );
				break;
			case COLON :
				printf("%s -- %s\n","COLON", token->str );
				break;
			case COMMENT :
				printf("%s -- %s\n","COMMENT", token->str );
				break;
			case ENDL :
				printf("%s -- %s\n","ENDL", token->str );
				break;
			case NUMBER :
				printf("%s -- %s\n","NUMBER", token->str );
				break;