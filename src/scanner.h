#ifndef __NSL_SCANNER_H__
#define __NSL_SCANNER_H__

#include <string.h>

#define token_get_name(token) (token_strings[token-T_GLOBAL])

#define BUFFER_SIZE 4096
#define TOKEN_SIZE_MAX 100

//这里定义一些类型，主要是关键字和一些相关的类型，遇到再往里加
typedef enum  _TokenType {
	T_GLOBAL = 257,
	T_ID, //表示字母开始的数字或字符串，可用来表示函数名，常量等
	T_NUMBER, //表示任何数字常量
	T_IF,T_ELSE,T_ENDIF,//表示if else,endif
	T_FOR,T_WHILE,T_SWITCH,T_CASE,T_BREAK,T_CONTINUE,T_GOTO,T_DO,//表示switch
	T_UNSIGNED,		//表示字符类型相关 unsigned 可以定义无符号数。
	T_ENUM,T_TYPEDEF,T_STRUCT,//定义结构相关类型
    T_BIT_AND,T_BIT_OR,T_BIT_XOR,T_LT,T_LE,T_GT,T_GE,T_EQ,T_NEQ,T_AND,T_OR,T_NOT,//表示运算符
	T_COLON,T_SEMI,T_POUND,T_LC,T_RC,T_LP,T_RP,T_COMMA,	   //表示各种分隔符#{}();:<>\\''"%&
	T_ASSIGN,T_PLUS,T_MINUS,T_MUL,T_DIV,T_MOD,//如果需要支持，可以再往里加
	T_INCLUDE,T_DEFINE,//表示一些头文件和一些固定值的定义,include,define
	T_LITERAL,//表示两个双引号中间的任意内容
	T_ERROR,//表示出错时的类型
	//下面是C--扩展中固有的一些关键字
	T_STATE,//表示状态
	T_SUB,
	T_CTS, //表示从客户端到服务器端
	T_STC, //表示从服务器端到客户端
	T_START,T_END,//表示状态开始，状态结束
	T_REGEX,//正则串
	T_DONE,
    T_DOLLAR,//还有$号未定义,璧如$proto这该如何表示
	T_COMMENT//取得注释
}TokenType;

extern const char *token_strings[];

typedef struct _Token
{
	TokenType t; //这个token的类型
	char * c;//指向的位置，如果是数字，则指向的字符串为数字类型，最后需要将其转换为对应的数字

}Token;

//ScannerState;记录当前scanner的状态,暂先保存如下状态，如果需要，然后再加
typedef enum {
ST_START,
ST_ID, //可以用来表示函数名或常量
ST_ERROR,
ST_DONE,
ST_COMMENT,
ST_NUMBER,
ST_STRING,
ST_EQ,
ST_LE,
ST_GE,
ST_AND,
ST_OR,
}ScannerState;

//一个记录相关信息的结构
typedef struct {
	char *input; //指向缓冲区
	int linecount;//记录第几行
	int length;//记录长度,这个文件的总长度
	int index;//记录第几个索引。
}scanner_rc_t;

typedef struct  
{
	TokenType t;
	const char *reserved_name;
}ReservedKeyword;


TokenType lookup_reserved_keyword(const char *str);
//some function we need to do
//打开文件进行扫描,读取文件信息
int scanner_open_file(scanner_rc_t *rc, const char *filename);

//设置相关缓冲区
int scanner_set_input();
//通过输入字符串来设置相关缓冲区
int scanner_set_input_from_string();

//根据一个输入字符来判断
TokenType scanner_get_one_char_token(scanner_rc_t *rc,char c);


//得到一个字符的操作
Token scanner_get_next_token(scanner_rc_t *);

void scanner_get_error(scanner_rc_t *);

int scanner_get_curr_line(scanner_rc_t *rc);

void scanner_debug(scanner_rc_t *rc);



#endif
