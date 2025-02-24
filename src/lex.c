#include "lex.h"

char character_stream_get(struct Character_Stream *stream)
{
	if(stream->offset + 1 == stream->size)
	{
		return '\0';
	}

	return stream->buffer[stream->offset++];
}
void character_stream_unget_last(struct Character_Stream *stream)
{
	stream->offset--;
}

struct Token token_stream_get_next(struct Token_Stream *stream)
{
	struct Token out;

	if(stream->unget_buffer_is_full)
	{
		out = stream->unget_buffer;
		stream->unget_buffer_is_full = 0;
	}
	else
	{
		unsigned char current_char = character_stream_get(&(stream->character_stream));
		int past_decimal = 0;
		float divisor = 1;
		out.real_value = 0.0;
		switch(current_char)
		{
			case '(':
				out.type = TOKEN_TYPE_LPAREN;
				break;
			case ')':
				out.type = TOKEN_TYPE_RPAREN;
				break;
			case '+':
				out.type = TOKEN_TYPE_PLUS;
				break;
			case '-':
				out.type = TOKEN_TYPE_MINUS;
				break;
			case '*':
				out.type = TOKEN_TYPE_MULT;
				break;
			case '/':
				out.type = TOKEN_TYPE_DIV;
				break;
			case '^':
				out.type = TOKEN_TYPE_EXPONENT;
				break;
			case 'A': /* Ans */
				out.type = TOKEN_TYPE_ANS;
				character_stream_get(&(stream->character_stream));
				character_stream_get(&(stream->character_stream));
				break;
			default: /*It's numerical*/
				out.type = TOKEN_TYPE_REAL;
				out.real_value = current_char - '0';
				current_char = character_stream_get(&(stream->character_stream));
				while((current_char >= '0' && current_char <= '9') || (current_char == '.'))
				{
					if(past_decimal)
					{
						divisor *= 10;
						out.real_value += (current_char - '0') / divisor;
					}
					else
					{
						if(current_char == '.')
						{
							past_decimal = 1;
						}
						else
						{
							out.real_value *= 10;
							out.real_value += current_char - '0';
						}
					}
					current_char = character_stream_get(&(stream->character_stream));
				}
				character_stream_unget_last(&(stream->character_stream));
				break;
		}
		stream->unget_buffer = out;
	}

	return out;
}

void token_stream_unget_last(struct Token_Stream *stream)
{
	stream->unget_buffer_is_full = 1;
}
