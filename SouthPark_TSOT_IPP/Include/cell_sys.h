#pragma once
#include "definitions.h"
#include <sys/timer.h>
#include <xstring>
#include <cellstatus.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/prx.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <math.h>
#include <fastmath.h>
#include <cellstatus.h>
#include <sys/timer.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <spu_printf.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/process.h>
#include <netdb.h>
#include "cell/http/client.h"
#include "cell/http/error.h"
#include "cell/http/net_error.h"
#include "cell/http/util.h"
#include "cell/dbgrsx.h"
#include "cell_interop.h"
// http

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cell/http.h>
#include <netex/net.h>
#define OK 0;

#pragma once


template <class TYPE_A>
inline bool is(TYPE_A a, TYPE_A b) {
	return a == b;
}

inline char* raw(std::string s) {
	return  &s[0];
}
int get_address(void* foo) {
	return reinterpret_cast<int>(&foo);
}
void defaultStub(...) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
size_t len(const char* str) {
	size_t length = 0;
	while (*str != '\0') {
		++length;
		++str;
	}
	return length;
}
char* cat(char* destination, const char* source) {
	char* result = destination;

	// Move to the end of the destination string
	while (*destination != '\0') {
		++destination;
	}

	// Copy the source string to the end of the destination
	while (*source != '\0') {
		*destination = *source;
		++destination;
		++source;
	}

	// Null-terminate the result
	*destination = '\0';

	return result;
}
int ca(int a) {
	return a;
}
void* read(int address) {
	return (void*)(address);
}
int is_char_integer(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
int length(char* s) {
	int len = 0;
	while (*s != 0) {
		len++;
		++s;
	}
	return len;
}
// Function to remove a word from a string
bool str_remove_word(char* str, const char* wordToRemove) {
	bool f = false;
	// Iterate through the string
	while (*str) {
		// Find the occurrence of the word in the string
		const char* wordStart = str;
		const char* wordEnd = wordToRemove;
		while (*wordEnd && *wordStart == *wordEnd) {
			++wordStart;
			++wordEnd;
		}

		// If the entire word is found, shift the remaining characters
		if (!*wordEnd) {
			while (*wordStart) {
				*str++ = *wordStart++;
			}
			*str = '\0'; // Null-terminate the string
			return true;
		}

		// Move to the next character in the string
		++str;
	}
	return f;
}
// Function to check if a specific word is present in a char*
bool str_contain(const char* str, const char* word) {
	while (*str != '\0') {
		// Check if the current substring matches the target word
		const char* tempStr = str;
		const char* tempWord = word;

		while (*tempStr != '\0' && *tempWord != '\0' && *tempStr == *tempWord) {
			tempStr++;
			tempWord++;
		}

		if (*tempWord == '\0') {
			// The entire word was found
			return true;
		}

		// Move to the next character in the main string
		str++;
	}

	// The word was not found
	return false;
}
void clear_str(char* str) {
	strcpy(str, "\0");
	
}

int is_char_letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return false;
	return true;
}
#pragma once
int asm_SetPresenceDetails_Hook(SceNpBasicPresenceDetails2* pres, uint32_t options)
{
	__nop(); __nop(); __nop(); __nop(); __nop();
}
int sceNpBasicSetPresenceDetails_Hook(SceNpBasicPresenceDetails2* pres, uint32_t options)
{
	strncpy(pres->status, "Insert Text", 30);

	return asm_SetPresenceDetails_Hook(pres, options);
}
#define GetPointer(X) *(int*)(X)
typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
typedef void VOID;
typedef void* PVOID;
typedef unsigned int uint;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef uint32_t* uintaddr;
// Function to extract a substring from a string
char* str_extract_sub(const char* str, int start, int length) {
	if (str == nullptr || start < 0 || length < 0) {
		return nullptr;  // Invalid arguments
	}

	// Calculate the length of the original string
	int originalLength = 0;
	const char* temp = str;
	while (*temp != '\0') {
		++originalLength;
		++temp;
	}

	// Check if the start index is within bounds
	if (start >= originalLength) {
		return nullptr;  // Start index out of bounds
	}

	// Calculate the actual length of the substring
	int actualLength = std::min(length, originalLength - start);

	// Allocate memory for the substring
	char* substring = new char[actualLength + 1];  // +1 for null terminator

	// Copy the substring from the original string
	for (int i = 0; i < actualLength; ++i) {
		substring[i] = str[start + i];
	}

	// Null-terminate the substring
	substring[actualLength] = '\0';

	return substring;
}
// Formatting
int _snprintf(char* buffer, size_t size, const char* format, ...) {
	if (buffer == nullptr || size == 0 || format == nullptr) {
		return -1;  // Invalid arguments
	}

	va_list args;
	va_start(args, format);

	int written = 0;
	size_t remaining = size;

	while (*format != '\0' && remaining > 1) {
		if (*format == '%' && *(format + 1) != '\0') {
			// Handle format specifiers
			char specifier = *(format + 1);

			switch (specifier) {
			case 'd': {
				int value = va_arg(args, int);
				written += _sys_snprintf(buffer + written, remaining, "%d", value);
				break;
			}
			case 's': {
				const char* str = va_arg(args, const char*);
				written += _sys_snprintf(buffer + written, remaining, "%s", str);
				break;
			}
			case 'x':
			{
				const char* str = va_arg(args, const char*);
				written += _sys_snprintf(buffer + written, remaining, "%x", str);
				break;
			}
			// Add more format specifiers as needed

			default:
				buffer[written++] = *format;
				break;
			}

			format += 2;  // Move past the format specifier
		}
		else {
			buffer[written++] = *format;
			format++;
		}

		remaining = size - written;
	}

	va_end(args);

	// Null-terminate the result
	if (written < size) {
		buffer[written] = '\0';
	}
	else {
		// Insufficient space, set the last character to null terminator
		buffer[size - 1] = '\0';
	}

	return written;
}
// Function to find the index of a target character in a string
int str_index_of(const char* str, char target) {
	if (str == nullptr) {
		return -1;  // Invalid string
	}

	const char* tempStr = str;  // Use a separate pointer for iteration
	int index = 0;

	while (*tempStr != '\0') {
		if (*tempStr == target) {
			return index;  // Found the character, return its index
		}

		++tempStr;
		++index;
	}

	return -1;  // Character not found in the string
}
// Compare
int str_compare(const char* str1, const char* str2)
{
	int diff = 0;

	if (*(str1) == 0x00 || *(str2) == 0x00) { return -1; }

	for (int i = 0; i < 0x600; i++)
	{
		if (*(str1 + i) == 0x00 || *(str2 + i) == 0x00) { break; }
		if (*(str1 + i) != *(str2 + i)) { diff++; }
	}

	return diff;
}

// Equals
bool str_equals(const char* str1, const char* str2) {
	int a = len(str1);
	int b = len(str2);

	if (a != b) {
		return false;
	}
	else {
		int i = 0;

		// Use additional pointers for comparison without modifying original pointers
		const char* ptr1 = str1;
		const char* ptr2 = str2;

		while (i < a) {
			char ac = *ptr1++;
			char bc = *ptr2++;

			if (ac != bc) {
				return false;
			}

			i++;
		}

		return true;
	}
}
// Function to find the first occurrence of any character from the 'charset' in 'str'
char* _strpbrk(const char* str, const char* charset) {
	if (str == nullptr || charset == nullptr) {
		return nullptr;  // Invalid arguments
	}

	while (*str != '\0') {
		const char* charInCharset = charset;
		while (*charInCharset != '\0') {
			if (*str == *charInCharset) {
				return const_cast<char*>(str);  // Found a match
			}
			++charInCharset;
		}
		++str;
	}

	return nullptr;  // No match found
}

char* _strtok(char* str, const char* delimiter) {
	static char* lastToken = nullptr;  // Holds the state between calls

	// If a new string is given, update the lastToken
	if (str != nullptr) {
		lastToken = str;
	}

	// If there's no more string to tokenize, return nullptr
	if (lastToken == nullptr || *lastToken == '\0') {
		return nullptr;
	}

	// Find the next occurrence of the delimiter
	char* tokenStart = lastToken;
	char* tokenEnd = _strpbrk(lastToken, delimiter);

	// If the delimiter is found, replace it with null terminator
	if (tokenEnd != nullptr) {
		*tokenEnd = '\0';
		lastToken = tokenEnd + 1;  // Move to the next character after the delimiter
	}
	else {
		lastToken = nullptr;  // No more tokens
	}

	return tokenStart;
}
// 
void splitAndRetrieve(const char* input, char* result) {
	int i = 0;

	// Find the position of '=' in the input string
	while (input[i] != '=' && input[i] != '\0') {
		i++;
	}

	// If '=' is found, copy the right part to the result
	if (input[i] == '=') {
		int j = 0;
		while (input[i + 1 + j] != '\0') {
			result[j] = input[i + 1 + j];
			j++;
		}

		// Set the null terminator at the end of the result
		result[j] = '\0';
	}
	else {
		// If '=' is not found, set an empty string in the result
		result[0] = '\0';
	}
}
// find the index of the next occurrence of a specific symbol (i) in a character sequence (sequence). It starts searching from the position indicated by the parameter i and returns the index of the found symbol.
int find_next_symbol(const char* sequence, int i) {
	const char* find_1 = sequence;
	int index = 0;
	while (*find_1 != '\0' && *find_1 != '\n' && *find_1 != i) {
		index++;
		find_1++;
	}
	return index;
}
//  this function compares characters in the given sequence and substring until the end of either one is reached or a difference is found. It returns true if the sequence starts with the provided substring and false otherwise.
bool startsWith(const char* sequence, char* compare) {
	if (sequence == 0) { return false; }
	if (compare == 0) { return false; }
	const char* seq = sequence;
	const char* comp = compare;
	int diffs = 0;
	int ch = 0;
	while ((ch = *seq) != '\0' && (*compare != '\0')) {
		if (ch != *compare) {
			diffs++;
		}
		compare++;
		seq++;
	}
	return diffs == 0;
}
// Function to extract the filename from a path
char* extractFilename(const char* path) {
	if (path == NULL) {
		return NULL; // Handle invalid input
	}

	// Find the last occurrence of '/'
	const char* lastSlash = path;
	const char* current = path;

	while (*current != '\0') {
		if (*current == '/') {
			lastSlash = current + 1; // Move one position after the last '/'
		}
		++current;
	}

	// If '/' is not found, the entire path is the filename
	if (*lastSlash == '\0') {
		return NULL; // Empty filename
	}

	// Calculate the length of the filename
	size_t filenameLength = _sys_strlen(lastSlash);

	// Allocate memory for the filename
	char* filename = (char*)_sys_malloc((filenameLength + 1) * sizeof(char)); // +1 for the null terminator

	if (filename == NULL) {
		return NULL; // Memory allocation failed
	}

	// Copy the filename to the new buffer
	_sys_strcpy(filename, lastSlash);

	return filename;
}
bool isNotWeird(char c) {
	return c >= 33 && c < 127;
}
bool isNotWeird(char* str) {
	if (!str) {
		return false;
	}
	else
	{
		char* cc = str;
		while (*cc != '\0') {
			if (!isNotWeird(*cc)) {
				return false;
				break;
			}
			cc++;
		}
		return true;
	}
}

// Convert a hex character to its decimal equivalent
int hexCharToDecimal(char hexChar) {
	if (hexChar >= '0' && hexChar <= '9') {
		return hexChar - '0';
	}
	else if (hexChar >= 'A' && hexChar <= 'F') {
		return hexChar - 'A' + 10;
	}
	else if (hexChar >= 'a' && hexChar <= 'f') {
		return hexChar - 'a' + 10;
	}
	return -1;  // Invalid hex character
}

void aptf(char* file, char buf[] = 0, int size = 0) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	err = cellFsClose(fd);
}
void aptff(char* file, char buf[] = 0)
{
	aptf(file, buf, strlen(buf));
}
// Convert a hexadecimal string to an RGB color
bool hexStringToColor(const char* hexString, int* red, int* green, int* blue) {
	if (hexString == NULL || red == NULL || green == NULL || blue == NULL) {
		return false;
	}

	*red = 0;
	*green = 0;
	*blue = 0;

	// Skip the '0x' or '0X' prefix if present
	if (hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X')) {
		hexString += 2;
	}

	// Iterate through the hex string
	int index = 0;
	while (*hexString != '\0') {
		if (index >= 200) {
			char* f = "/dev_hdd0/tmp/dclient/session_log.log";
			aptff(f, "Parsing hex failed when received: ");
			aptff(f, (char*)hexString);
			aptff(f, "as param\n");
			red = 0;
			green = 0;
			blue = 0;
			return false;
			break;

		}
		*red = (*red << 4) + hexCharToDecimal(*hexString++);
		*green = (*green << 4) + hexCharToDecimal(*hexString++);
		*blue = (*blue << 4) + hexCharToDecimal(*hexString++);
		index++;
	}

	return true;
}

namespace HTTP
{
#define __WEB_H

	//int _HTTP_POOL_BUFFER = 0x10030000;
#define HTTP_POOL_SIZE      (64 * 1024)
#define HTTP_POOL_BUFFER 0x10030000 //change this to an address with a free size of 0x10000 bytes
	static char r_buffer[0x6000];  //MAX is 0x6000

	void memCpy(void* destination, const void* source, size_t num)
	{
		for (int i = 0; i < num; i++)
		{
			*((char*)destination + i) = *((char*)source + i);
		}
	}


	void memFree(char* ptr, int len)
	{
		for (int i = 0; i < len; i++)
		{
			*(char*)(ptr + i) = 0x00;
		}
	}


	int strCmp(const char* str1, const char* str2)
	{
		int diff = 0;

		if (*(str1) == 0x00 || *(str2) == 0x00) { return -1; }

		for (int i = 0; i < 0x600; i++)
		{
			if (*(str1 + i) == 0x00 || *(str2 + i) == 0x00) { break; }
			if (*(str1 + i) != *(str2 + i)) { diff++; }
		}

		return diff;
	}

	void SendRequest(char* url, char* retBuffer, int bufMaxLen) //url = url to request ("http://www.google.com/")    | retBuffer = ptr where the answer will be written to  | bufMaxLen = Max length of the buffer
	{
		if (bufMaxLen > 0x6000) { return; } //ERROR, bufMaxLen is TOO BIG

		CellHttpClientId client = 0;
		CellHttpTransId trans = 0;
		CellHttpUri uri;
		int ret;
		bool has_cl = true;
		uint64_t length = 0;
		uint64_t recvd;
		size_t poolSize = 0;
		void* uriPool = NULL;
		void* httpPool = NULL;
		const char* serverName;
		size_t localRecv = 0;

		serverName = url;  //set url
		memFree(r_buffer, bufMaxLen);
		sys_net_initialize_network(); //init network
		httpPool = (void*)HTTP_POOL_BUFFER; //address to: 0x10000 free bytes

		if (httpPool == NULL)
		{
			ret = -1;
			goto end;
		}

		ret = cellHttpInit(httpPool, HTTP_POOL_SIZE);
		if (ret < 0)
		{
			goto end;
		}

		ret = cellHttpCreateClient(&client);
		if (ret < 0)
		{
			goto end;
		}

		ret = cellHttpUtilParseUri(NULL, serverName, NULL, 0, &poolSize);
		if (ret < 0)
		{
			goto end;
		}

		char uriPoolAlloc[0x1024]; //allocate some space for the uri (a bit too much but eh)
		uriPool = uriPoolAlloc;
		if (NULL == uriPool)
		{
			goto end;
		} //fail

		ret = cellHttpUtilParseUri(&uri, serverName, uriPool, poolSize, NULL);
		if (ret < 0)
		{
			memFree((char*)uriPool, sizeof(uriPool));
			goto end;
		}

		ret = cellHttpCreateTransaction(&trans, client, CELL_HTTP_METHOD_GET, &uri);
		memFree((char*)uriPool, sizeof(uriPool));

		if (ret < 0)
		{
			goto end;
		}

		ret = cellHttpSendRequest(trans, NULL, 0, NULL); //send it :D
		{//make a new scope for the status
			int code = 0;
			ret = cellHttpResponseGetStatusCode(trans, &code);
			if (ret < 0)
			{
				goto end;
			}

		}//end of status scope

		ret = cellHttpResponseGetContentLength(trans, &length);

		if (ret < 0)
		{
			if (ret == CELL_HTTP_ERROR_NO_CONTENT_LENGTH)
			{
				has_cl = false;
			}
			else
			{
				goto end;
			}
		}

		recvd = 0;

		while ((!has_cl) || (recvd < length))
		{
			ret = cellHttpRecvResponse(trans, r_buffer, bufMaxLen - 1, &localRecv);
			if (ret < 0) { goto end; }
			else if (localRecv == 0) break;
			recvd += localRecv;
			r_buffer[localRecv] = '\0'; //null terminate it
		}
		ret = 0;
		{
			for (int i = 0; i < bufMaxLen; i++)
			{
				retBuffer = r_buffer;
			}
		}  //OUTPUT

		// shutdown procedures
	end:
		if (trans)
		{
			cellHttpDestroyTransaction(trans);
			trans = 0;
		}

		if (client)
		{
			cellHttpDestroyClient(client); client = 0;
		}

		cellHttpEnd();  //END OF HTTP

		if (httpPool)
		{
			memFree((char*)httpPool, sizeof(httpPool));
			httpPool = NULL;
		}

		sys_net_finalize_network();
	}
}

char mem(int address, int index) {
	return *(char*)(ca(address + (index)));
}
template<typename R, typename... Arguments> inline R Call(long long function, Arguments... args)
{
	int toc_t[2] = { function, 0x014CDAB0 };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}

uint reintepret_uint(int unsign)
{
	return (uint)(unsign);
}
char* desreference_stringptr(unsigned int i) {
	char* s = (char*)i;
	if (s) {
		if (*s != '\0') {
			if (_sys_strlen(s) > 2) {

				return (char*)i;
			}
			else return "(null)";
		}
		else return "(null)";
	}
	else return "(null)";
}
bool is_null_str(char* r) {
	return r == 0 || (r[0] == '(' && r[1] == 'n' && r[2] == 'u' && r[3] == 'l' && r[4] == 'l' && r[5] == ')');
}
int str_atoi(char* str)
{
	// Initialize result
	int res = 0;
	for (int i = 0; (*(str + i)) != '\0'; ++i)
		if ((*(str + i)) != ' ') {
			res = res * 10 + (*(str + i)) - '0';
		}

	// return result.
	return res;
}


void get_temperature(uint32_t a, uint32_t* b)
{
	system_call_2(383, (uint64_t)(uint32_t)a, (uint64_t)(uint32_t)b);
}
int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}

void WriteMemory(int address, char hex)
{
	*(int*)address = hex;
}

//Console Commands
void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}


int write_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}

int read_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}

//Hook Functions
int Memcpy(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}

void PatchInJump(int Address, int Destination) {
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	for (int i = 0; i < 4; i++) {
		*(int*)(Address + (i * 4)) = FuncBytes[i];

	}
}

struct memInfo_s
{ // in bytes;
	uint32_t total;
	uint32_t available;
};

struct memUsage_s
{ // in kilobytes
	float total;
	float free;
	float used;
	float percent;
};

memUsage_s GetMemoryUsage()
{
	sys_memory_info_t mem;
	memInfo_s mem_info;
	sys_memory_get_user_memory_size(&mem);
	mem_info.total = mem.total_user_memory;
	mem_info.available = mem.available_user_memory;
	memUsage_s mem_usage;
	mem_usage.total = static_cast<float>(mem_info.total) / 1024.0;
	mem_usage.free = static_cast<float>(mem_info.available) / 1024.0;
	mem_usage.used = mem_usage.total - mem_usage.free;
	mem_usage.percent = (mem_usage.used * 100.0) / mem_usage.total;

	return mem_usage;
}

void patcher(int Address, int Destination, bool Linked)
{
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000)
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	FuncBytes[2] = 0x7D6903A6; // mtctr    %r11
	FuncBytes[3] = 0x4E800420; // bctr
	if (Linked)
		FuncBytes[3] += 1; // bctrl
	Memcpy((void*)Address, FuncBytes, 4 * 4);
}


void hookfunction(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub) {
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(functionStartAddress, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x20);
	sys_dbg_write_process_memory(functionStub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, hookFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, hookFunctionStub, 0x10);
}

void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
}

int saveValue[2] = { 0x01DA0000, 0x33A00000 };
int highestVal[2] = { 0x01DF0000, 0x36000000 };

int getHighestValue(int index, int checkAddr)
{
	if (checkAddr > saveValue[index] && checkAddr < highestVal[index])
	{
		char getVal[1];
		int val = sys_dbg_read_process_memory_ps3mapi(checkAddr, getVal, 1);
		_sys_printf("addr: %i | mem: %s\n", checkAddr, (val == -2147418099 ? "False" : "True"));
		if (val != -2147418099)
		{
			saveValue[index] = checkAddr + 1;
			return checkAddr;
		}
		else
			return 0x000101C0;
	}
	else
	{
		//_sys_printf("saved %i at %i\n", saveValue[index], index);
		return saveValue[index];
	}
}

void WriteBytes(int address, char* input, int length)
{
	for (int i = 0; i < length; i++) {
		*(char*)(ca(address + (i))) = input[i];
	}
	*(char*)(ca(address + (length))) = 0x00;
}

char byteArrayz[1000][100];
char _byteArrayz[100];

char* ReadBytes(int index, int address, int length)
{
	for (int i = 0; i < length; i++)
	{
		byteArrayz[index][i] = *(char*)(ca(address + (i)));
	}
	return byteArrayz[index];
}

char* ReadBytes(int address, int length)
{
	for (int i = 0; i < length; i++)
	{
		_byteArrayz[i] = *(char*)(ca(address + (i)));
	}
	return _byteArrayz;
}

char returnRead[100][100];
char _returnRead[100];

char* readStr(int ofs)
{
	char* str = (char*)ca(ofs);
	if (strlen(str) < 50)
		return str;
	else
		return "error";
}
char* ReadString(int address)
{
	memset(&_returnRead[0], 0, sizeof(_returnRead));
	int strlength = 100;
	char* StrBytes = ReadBytes(address, strlength);
	for (int i = 0; i < strlength; i++)
	{
		if (StrBytes[i] != 0x00)
			_returnRead[i] = StrBytes[i];
		else
			break;
	}
	return _returnRead;
}

char* ReadString(int index, int address)
{
	memset(&returnRead[index][0], 0, sizeof(returnRead[index]));
	int strlength = 100;
	char* StrBytes = ReadBytes(index, address, strlength);
	for (int i = 0; i < strlength; i++)
	{
		if (StrBytes[i] != 0x00)
			returnRead[index][i] = StrBytes[i];
		else
			break;
	}
	return returnRead[index];
}

int WriteString(int address, char* string) {
	int FreeMem = 0x01D62000;
	int strlength = strlen(string);
	char* strpointer = *(char**)FreeMem = string;
	char* StrBytes = ReadBytes(50, *(int*)FreeMem, strlength);
	WriteBytes(address, StrBytes, strlength);
	*(char*)(ca(address + strlength + 1)) = 0x00;
	return strlength;
}

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char itoaBuff[100][100];
char* itoa(int index, int n) {
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {		/* generate digits in reverse order */
		itoaBuff[index][i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		itoaBuff[index][i++] = '-';
	itoaBuff[index][i] = '\0';
	reverse(itoaBuff[index]);
	return itoaBuff[index];
}

void sys_sleep(uint64_t milliseconds)
{
	sys_timer_usleep(milliseconds * 1000);
}



int getMemOfs = 0x01D00200;
int getMemInterval = 100;
char* getChar(int intVal)
{
	int getOfs = getMemOfs + getMemInterval * (70 + intVal);
	return (char*)getOfs;
}

void setg(int intVal, int value)
{
	int getOfs = getMemOfs + getMemInterval * intVal;
	*(int*)getOfs = value;
}
bool isAlphanumeric(char ch) {
	// Check if the character is an alphanumeric character
	bool flag = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
	bool flag2 = ch != '-' && ch != '_';
	return flag && (!flag2);
}// Function to check if a string ends with a specified suffix
bool endsWith(const char* str, const char* suffix) {
	// Find the lengths of the suffix
	int suffixLength = 0;
	while (suffix[suffixLength] != '\0') {
		++suffixLength;
	}

	// Find the length of the string
	const char* tempStr = str;
	while (*tempStr != '\0') {
		++tempStr;
	}
	int strLength = tempStr - str;

	// If the suffix is longer than the string, it can't be a match
	if (suffixLength > strLength) {
		return false;
	}

	// Compare the suffix with the end of the string
	int suffixIndex = 0;
	for (int i = strLength - suffixLength; i < strLength; ++i) {
		if (str[i] != suffix[suffixIndex]) {
			return false; // Mismatch found
		}
		++suffixIndex;
	}

	// If we reached this point, the suffix matches the end of the string
	return true;
}

bool containsAlphanumeric(const char* str) {
	while (*str) {
		if (isAlphanumeric(*str) != 0) {
			// The current character is alphanumeric
			return true;
		}
		++str;
	}
	// No alphanumeric characters found
	return false;
}
int g(int intVal)
{
	int getOfs = getMemOfs + getMemInterval * intVal;
	return *(int*)getOfs;
}

float getFloat(int intVal)
{
	int getOfs = getMemOfs + getMemInterval * (50 + intVal);
	return *(float*)getOfs;
}

bool getBool(int intVal)
{
	int getOfs = getMemOfs + getMemInterval * intVal;
	return *(bool*)getOfs + 3;
}

//Console Commands

namespace http_util
{
	char* removespace(const char* notify) {
		char buffer[0x500];
		_sys_strcat(buffer, notify);
		for (int i = 0; i < 0x500; i++) {
			if (buffer[i] == ' ') {
				buffer[i] = '+';
			}
		}
		return buffer;
	}
	char* SendRequest(char* URL, char* Path) {
		struct sockaddr_in SocketAddress;
		char bufferReturn[500];
		char RequestBuffer[1000];
		_sys_memset(RequestBuffer, 0x00, 1000);
		SocketAddress.sin_addr.s_addr = ((unsigned long)gethostbyname(URL)->h_addr);
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_port = htons(80);
		int Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (connect(Socket, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) != 0) {
			return "";
		}
		_sys_strcat(RequestBuffer, "GET /");
		_sys_strcat(RequestBuffer, Path);
		_sys_strcat(RequestBuffer, "\r\nConnection: close\r\n\r\n");

		send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
		while (recv(Socket, bufferReturn, 500, 0) > 0) {
			return bufferReturn;
		}
		socketclose(Socket);
	}
	void Notify(const char* notify) {
		char buffer[0x200];
		_sys_snprintf(buffer, 0x200, "notify.ps3mapi?msg=%s", notify);
		_sys_printf("%s\n", buffer);
		SendRequest("127.0.0.1", buffer);
	}
}

namespace ps3
{
	void WriteSingleByte(int address, unsigned int value)
	{
		char byts[]{ value };
		WriteBytes(address, byts, 1);
	}
	float ReadSingleFloat(int Address)
	{
		return *(float*)Address;
	}
	float floatArray[100];
	float* ReadFloat(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			floatArray[i] = *(float*)(address + (i * 0x04));
		}
		return floatArray;
	}

	char byteArrayz[100];
	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArrayz[i] = *(char*)(address + (i));
		}
		return byteArrayz;
	}

	void WriteFloat(int address, float* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(float*)(address + (i * 4)) = input[i];
		}
	}

	void WriteSingleFloat(int Address, float Input)
	{
		*(float*)Address = Input;
	}

	void WriteBytes(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}
	void WriteByte(int Address, unsigned char Input)
	{
		*(unsigned char*)Address = Input;
	}
	float intArray[100];
	float* ReadInt(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			intArray[i] = *(int*)(address + (i * 0x04));
		}
		return intArray;
	}

	void WriteInt(int address, int* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(int*)(intArray + (i * 0x04)) = input[i];
		}
	}
	void WriteInt32(int Address, int Input)
	{
		*(int*)Address = Input;
	}

	void WriteString(int address, char* string)
	{
		int FreeMem = 0x1D00000;
		int strlength = strlen(string);
		*(char**)FreeMem = string;
		char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
		WriteBytes(address, StrBytes, strlength);
	}
	struct readstr
	{
		char returnRead[100];
	}ReturnRead[1000];
	int strcount;

	char* ReadStringz(int address)
	{
		strcount++;
		memset(&ReturnRead[strcount].returnRead[0], 0, sizeof(ReturnRead[strcount].returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				ReturnRead[strcount].returnRead[i] = StrBytes[i];
			else
				break;
		}
		return ReturnRead[strcount].returnRead;
	}
	char byteArray[400];
	char* ReadBytesC(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}
	char returnRead[100];
	char* ReadStringC(int address)
	{
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytesC(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}
	int ReadInt32(int Address)
	{
		return *(int*)Address;
	}
	char* ReadString(int Address)
	{
		return (char*)Address;
	}
	char returnReadd[100];
	char* ReadStringzz(int address, bool IncludeSpaces) {
		int strlength = 100;
		char* StrBytes = ps3::ReadBytes(address, strlength);

		char StopBytes = 0x00;
		if (!IncludeSpaces)
			StopBytes = 0x20;

		for (int i = 0; i < strlength; i++)
			returnReadd[i] = 0;
		for (int i = 0; i < strlength; i++) {
			if (StrBytes[i] != StopBytes)
				returnReadd[i] = StrBytes[i];
		}
		return returnReadd;
	}
};

namespace NyTekCFW
{
	typedef unsigned char byte;
	typedef char* String;
	typedef void* DWORD;
	typedef void* PVOID;
	char byteArrayz[0x10];
	void sleep(usecond_t time)
	{
		sys_timer_usleep(time * 1000);
	}
	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArrayz[i] = *(char*)(address + (i));
		}
		return byteArrayz;
	}
	void WriteBytes(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}
	void WriteString(int off, char* tct)
	{
		int strlength = strlen(tct);
		*(char**)off = tct;
		WriteBytes(off, ReadBytes(*(int*)off, strlength), strlength);
		*(byte*)(off + strlength) = 0;
	}
	void Zone(int Offset, float Zoned[])
	{
		*(float*)Offset = Zoned[0];
		*(float*)(Offset + 4) = Zoned[1];
		*(float*)(Offset + 8) = Zoned[2];
	}

	int FloatToHex(float value)
	{
		float f = value;
		int i = *(reinterpret_cast<int*>(&f));
		return i;
	}

	int IntToHex(int value)
	{
		int i = value;
		int result = *(reinterpret_cast<int*>(&i));
		return result;
	}
}

void WriteMemory(char address, char value)
{
	char HEX[] = { NyTekCFW::IntToHex(value) };
	sys_dbg_write_process_memory(address, &HEX, sizeof(HEX));
	sys_dbg_write_process_memory_ps3mapi(address, &HEX, sizeof(HEX));
}


void StubGameRender(uint32_t r3, uint32_t r4)
{
	// interop
	__nop(); __nop(); __nop(); __nop(); __nop();
}
void GetMemoryInfo()
{
	static sys_memory_info stat; size_t* FreeMemory, * UsedMemory; int HeapFree;
	sys_memory_get_user_memory_size(&stat);

	*FreeMemory = stat.available_user_memory;
	*FreeMemory += HeapFree;
	*UsedMemory = stat.total_user_memory - *FreeMemory;
	const size_t RETAIL_SIZE = 213 * 1024 * 1024;
	if (stat.total_user_memory > RETAIL_SIZE)
	{
		*FreeMemory -= stat.total_user_memory - RETAIL_SIZE;
	}
	else
	{
		*FreeMemory = 0;
		*UsedMemory = 0;
	}
	return;
}

char* toSign(int character) {
	char s[]{ (char)character };
	return s;
}
char* sys_append(char* a, char* b) {
	char inp[200];
	_sys_snprintf(inp, 200, "%s%s", a, b);
	return inp;
}

unsigned long djb2Hash(const char* str) {
	unsigned long hash = 5381;
	const char* currentChar;

	for (currentChar = str; *currentChar != '\0'; ++currentChar) {
		hash = ((hash << 5) + hash) + *currentChar; // hash * 33 + currentChar
	}

	return hash;
}
// Destructorrpy
namespace Vector {

	size_t customStrlen(const char* str) {
		size_t len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return len;
	}
	int customAtoi(const char* str) {
		int result = 0;
		int sign = 1;
		if (*str == '-') {
			sign = -1;
			++str;
		}
		while (*str >= '0' && *str <= '9') {
			result = result * 10 + (*str - '0');
			++str;
		}

		return sign * result;
	}
	int customIsDigit(char c) {
		return (c >= '0' && c <= '9');
	}
	int customIsSpace(char c) {
		return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
	}
	char* customStrncpy(char* dest, const char* src, size_t n) {
		size_t i;
		for (i = 0; i < n && src[i] != '\0'; ++i) {
			dest[i] = src[i];
		}
		for (; i < n; ++i) {
			dest[i] = '\0';
		}
		return dest;
	}
	int parseVector3(const char* vectorStr, int* x, int* y, int* z) {
		// Initialize variables
		*x = *y = *z = 0;

		// Parse x
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*x = customAtoi(vectorStr);

		// Skip to next part
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}

		// Parse y
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*y = customAtoi(vectorStr);

		// Skip to next part
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}

		// Parse z
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*z = customAtoi(vectorStr);

		return 1; // Successful parsing
	}
}

char readStrWide[200];
// 
char* readWide(uint address, int len = 16) {
	int leng = len * 2;
	int index = 0;
	for (int i = 0; i < (leng); i += 2) {
		int c = *(unsigned char*)(address + i);
		if (c == 0) {
			c = *(unsigned char*)(address + i + 1);
			if (c != 0) {
				readStrWide[index] = c;
				index++;
			}
		}
		else
		{
			readStrWide[index] = c;
			index++;
		}
	}
	return readStrWide;
}
template <class T>
int arr_size(T* arr) {

	return sizeof(arr) / sizeof(arr[0]);
}

int ca2(int addr)
{
	//char getVal[1];
	//int val = sys_dbg_read_process_memory_ps3mapi(addr, getVal, 1);
	//_sys_printf("addr: %i | mem: %s\n", addr, (val == -2147418099 ? "False" : "True"));
	//if (val != -2147418099)
	//	return addr;
	//else
	//	return 0x000101C0;
	if (0x00010000 < addr && getHighestValue(0, addr) > addr ||
		0x10000000 < addr && 0x10EF0000 > addr ||
		0x10F30000 < addr && 0x11060000 > addr ||
		0x11220000 < addr && 0x136A0000 > addr ||
		0x20000000 < addr && 0x20060000 > addr ||
		0x30000000 < addr && getHighestValue(1, addr) > addr ||
		0x40000000 < addr && 0x40010000 > addr ||
		0x40100000 < addr && 0x40110000 > addr ||
		0x40200000 < addr && 0x40210000 > addr ||
		0x40300000 < addr && 0x40310000 > addr ||
		0x50000000 < addr && 0x52000000 > addr ||
		0x60000000 < addr && 0x64000000 > addr ||
		0xC0000000 < addr && 0xCF900000 > addr ||
		0xD0010000 < addr && 0xD0020000 > addr ||
		0xD0030000 < addr && 0xD0050000 > addr ||
		0xD0060000 < addr && 0xD00A0000 > addr ||
		0xD00B0000 < addr && 0xD0130000 > addr ||
		0xD0160000 < addr && 0xD02A0000 > addr ||
		0xD02B0000 < addr && 0xD02F0000 > addr)
		return addr;
	else
	{
		char getVal[1];
		int val = sys_dbg_read_process_memory_ps3mapi(addr, getVal, 1);
		//_sys_printf("addr: %i | mem: %s\n", addr, (val == -2147418099 ? "False" : "True"));
		if (val != -2147418099)
			return addr;
		else
			return 0x000101C0;
	}
}

#pragma region OVERRIDE_NEW
#pragma once
#include <yvals.h> // for _CSTD
#include <xstddef> // for _THROW1
#include <new> // for nothrow_t
void* operator new(std::size_t size) _THROW1(_XSTD bad_alloc) // allocate or throw exception
{
	return _sys_malloc(size);
}
void* operator new(std::size_t size, const _STD nothrow_t&) _THROW0() // allocate or return null pointer
{
	return _sys_malloc(size);
}
void* operator new(size_t size, size_t align)
{
	return _sys_memalign(align, size);
}
void* operator new(size_t size, size_t align, const _STD nothrow_t&) _THROW0()
{
	return _sys_memalign(align, size);
}
void* operator new[](std::size_t size) _THROW1(_XSTD bad_alloc)	// allocate array or throw exception
{
	return _sys_malloc(size);
}
void* operator new[](std::size_t size, const _STD nothrow_t&)  // allocate array or return null pointer
	{
		return _sys_malloc(size);
	}
	void* operator new[](size_t size, size_t align)
		{
			return operator new(size, align);
		}
		void* operator new[](size_t size, size_t align, const _STD nothrow_t&)
			{
				return operator new(size, align);
			}
			void operator delete(void* mem) _THROW0()  // delete allocated storage
			{
				_sys_free(mem);
			}
			// The rest of these deletes will be called if the correspond call to
				// new throws an exception.
			void operator delete(void* mem, const _STD nothrow_t&)
			{
				_sys_free(mem);
			}
			void operator delete(void* ptr, void* prt2)
			{
				return operator delete(ptr);
			}
			void operator delete(void* ptr, size_t align)
			{
				return operator delete(ptr);
			}
			void operator delete(void* ptr, size_t align, const _STD nothrow_t&) _THROW0()
			{
				return operator delete(ptr);
			}
			void operator delete(void* ptr, size_t align, void* prt2)
			{
				return operator delete(ptr);
			}
			void operator delete[](void* mem)  // delete allocated array
				{
					_sys_free(mem);
				}
				void operator delete[](void* mem, const _STD nothrow_t&) _THROW0() // delete if nothrow array new fails -- REPLACEABLE
				{
					_sys_free(mem);
				}
				void operator delete[](void* ptr, void* prt2)
					{
						return operator delete(ptr, prt2);
					}
					void operator delete[](void* ptr, size_t align)
						{
							return operator delete(ptr, align);
						}
						void operator delete[](void* ptr, size_t align, const _STD nothrow_t&) _THROW0()
						{
							return operator delete(ptr, align);
						}
						void operator delete[](void* ptr, size_t align, void* prt2)
							{
								return operator delete(ptr, align);
							}

#pragma endregion

							int threaded(void(*entry), const char* name = "threaded_function") {
								uint64 t;
								static uint32_t func = *(uintaddr)entry;
								int errn = sys_ppu_thread_create(&t, [](uint64)->void
									{
										void(*s)() = (void(*)())func;
										s();
									}, 0, 1500, 5000, 0, name);
								return errn;
							}

