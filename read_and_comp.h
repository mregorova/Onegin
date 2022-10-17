
typedef char* string; // string type(pointer to first character in ctring); poemString - is a struct witch contains string an it's length 
typedef struct {
    string str;
    int    len;
} poem_string;

void input (const char* stream, string* text, poem_string** strarr, int* textlen, int* strarrlen);
void output (const char* stream, poem_string* strarr, int len);
int str_comp_rev (const void* f_to_comp, const void* s_to_comp);
int str_comp (const void* f_to_comp, const void* s_to_comp);
void clear_file (const char* stream);
void output_text (const char* stream, const string text);