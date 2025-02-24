struct Character_Stream
{
	char buffer[256];
	unsigned int size;
	unsigned int offset;
};

char character_stream_get(struct Character_Stream *stream);
void character_stream_unget_last(struct Character_Stream *stream);

enum Token_Type
{
	TOKEN_TYPE_LPAREN,
	TOKEN_TYPE_RPAREN,
	TOKEN_TYPE_REAL,
	TOKEN_TYPE_PLUS,
	TOKEN_TYPE_MINUS,
	TOKEN_TYPE_EXPONENT,
	TOKEN_TYPE_MULT,
	TOKEN_TYPE_DIV,
	TOKEN_TYPE_ANS
};

struct Token
{
	enum Token_Type type;
	float real_value;
};

struct Token_Stream
{
	int unget_buffer_is_full;
	struct Token unget_buffer;

	struct Character_Stream character_stream;
};

struct Token token_stream_get_next(struct Token_Stream *stream);
void token_stream_unget_last(struct Token_Stream *stream);
