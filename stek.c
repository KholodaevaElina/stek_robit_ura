#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define THERE_IS_NOTHING_IN_THE_STACK -1
#define MAX_LENGTH_COMMAND 100
#define MAX_SIZE_STEK 10
#define MAX_LENGTH_NUMBER 35

double division (double* stek, int index_of_top);

double mul (double* stek, int index_of_top);

double sub (double* stek, int index_of_top);

double add (double* stek, int index_of_top);

void pop (double* stek, int* p_index_of_top);

void memset_0__for_double (double* arr, int size_arr);

void push (double number, int* p_index_of_top, double* stek);

int number_of_characters_in_the_file (FILE* file);

int swap_n_to_0_and_find_number_of_lines (char* text, int size_text);

void arrange_pointers (char* text, int size_text, char** p_lines, int number_of_lines);

int is_punctuation_mark_or_number (char c);

void fill_array_letter_a (char* arr, int size_arr);


int main () {
	FILE* input_file = NULL;
        if ((input_file = fopen ("input.txt", "r")) == NULL)
		printf ("Cannot open the file");

	int n_characters_in_the_file = number_of_characters_in_the_file (input_file);

	char* command_list = (char*) calloc (n_characters_in_the_file, sizeof (char));
	fread (command_list, sizeof (char), n_characters_in_the_file, input_file);
        
	int number_of_lines = swap_n_to_0_and_find_number_of_lines (command_list, n_characters_in_the_file);

        char** p_lines = (char**) calloc (number_of_lines, sizeof (char*));
	arrange_pointers (command_list, n_characters_in_the_file, p_lines, number_of_lines);

        double* stek = (double*) calloc (MAX_SIZE_STEK, sizeof (double));
        memset_0__for_double (stek, MAX_SIZE_STEK);

        int index_of_top = THERE_IS_NOTHING_IN_THE_STACK;
        
	for (int i = 0; i < number_of_lines; i++) {
        	int pointer_shift = 0;
        	char command [MAX_LENGTH_COMMAND] = {};

		while (isalpha(*(p_lines[i] + pointer_shift))) {
				command[pointer_shift] = *(p_lines[i] + pointer_shift);
				pointer_shift++;
		}

        	int is_push = 0;
	        if (command[0] == 'P' || command[0] == 'p')
        	if (command[1] == 'U' || command[1] == 'u')
         	if (command[2] == 'S' || command[2] == 's')
                if (command[3] == 'H' || command[3] == 'h')
                        is_push = 1;

             	if (is_push == 0) {
	                if (command[0] == 'P' || command[0] == 'p')
		        if (command[1] == 'O' || command[1] == 'o')
	        	if (command[2] == 'P' || command[2] == 'p') 
		        	pop (stek, &index_of_top);
        	} 
	       	if (is_push == 0) {
                        if (command[0] == 'A' || command[0] == 'a')
                        if (command[1] == 'D' || command[1] == 'd')
                        if (command[2] == 'D' || command[2] == 'd') 
                                printf ("The sum of the two outermost elements of the stack is %lg\n", add (stek, index_of_top));	
			
                } 
		if (is_push == 0) {
                        if (command[0] == 'S' || command[0] == 's')
                        if (command[1] == 'U' || command[1] == 'u')
                        if (command[2] == 'B' || command[2] == 'b') 
                                printf ("The difference between the two extreme elements of the stack is %lg\n", sub (stek, index_of_top));
                } 
		if (is_push == 0) {
                        if (command[0] == 'M' || command[0] == 'm')
                        if (command[1] == 'U' || command[1] == 'u')
                        if (command[2] == 'L' || command[2] == 'l') 
                                printf ("The product of the two outermost elements of the stack is %lg\n", mul (stek, index_of_top));
                }  
		if (is_push == 0) {
                        if (command[0] == 'D' || command[0] == 'd')
                        if (command[1] == 'I' || command[1] == 'i')
                        if (command[2] == 'V' || command[2] == 'v')
			if (command[3] == 'I' || command[3] == 'i')
			if (command[4] == 'S' || command[4] == 's')
			if (command[5] == 'I' || command[5] == 'i')
			if (command[6] == 'O' || command[6] == 'o')
			if (command[7] == 'N' || command[7] == 'n')
                                printf ("The quotient of the two outermost elements of the stack is %lg\n", division (stek, index_of_top));
                }

		

	        if (is_push == 1) {

			while (*(p_lines[i] + pointer_shift) > '9' || *(p_lines[i] + pointer_shift) < '0')
				pointer_shift++;
			char number_to_push [MAX_LENGTH_NUMBER];
			fill_array_letter_a (number_to_push, MAX_LENGTH_NUMBER);

			int n_characters_in_a_number = 0;

			while (*(p_lines[i] + pointer_shift) <= '9' && *(p_lines[i] + pointer_shift) >= '0') {
                                number_to_push[n_characters_in_a_number] = *(p_lines[i] + pointer_shift);
				n_characters_in_a_number++;
                                pointer_shift++;
			}

			push (atoi (number_to_push), &index_of_top, stek);
		}	
        }
	
	free (stek);
        free (command_list);
        free (p_lines);
}

/*
 * @brief This function fills an array of characters with a lowercase letter a
 *
 * @param[in] arr (type: char*, the array to be filled with the letter a)
 * @param[in] size_arr (type: int, lenght of array)
 * */ 
void fill_array_letter_a (char* arr, int size_arr) {
	assert (arr != NULL);

	for (int i = 0; i < size_arr; i++) 
		arr[i] ='a';
}

/*
 * @brief This function returns the quotient of the two outermost elements of the stack
 * (in the numerator of the fraction, the outermost element of the stack)
 *
 * @param[in] stek (type: double*, a pointer to the stack whose elements are to be divided) \везде написать, что именно указатель и посмотреть чтобы был написан стек а не массив
 * @param[in] index_of_top (type: int, the number of the outermost element of the stack)
 *
 * @return the quotient of the two outermost elements of the stack
 * */
double division (double* stek, int index_of_top) {
        assert (index_of_top >= 1);
	assert (stek[index_of_top - 1] != 0);
	assert (stek != NULL);

        return (stek [index_of_top] / stek[index_of_top - 1]);
}

/*
 * @brief This function returns the product of the two outermost elements of the stack
 *
 * @param[in] stek (type: double*, a pointer to the stack whose elements are to be multiplied) \везде написать, что именно указатель
 * @param[in] index_of_top (type: int, the number of the outermost element of the stack)
 *
 * @return product of the two outermost elements of the stack
 * */
double mul (double* stek, int index_of_top) {
        assert (index_of_top >= 1);
	assert (stek != NULL);

        return (stek [index_of_top] * stek[index_of_top - 1]);
}

/*
 * @brief This function returns the sum of the two outermost elements of the stack
 *
 * @param[in] stek (type: double*, a pointer to the stack whose elements to subtract) \везде написать, что именно указатель
 * @param[in] index_of_top (type: int, the number of the outermost element of the stack)
 *
 * @return the difference of the two outermost elements of the stack
 * */
double sub (double* stek, int index_of_top) {
        assert (index_of_top >= 1);
	assert (stek != NULL);

        return (stek [index_of_top] - stek[index_of_top - 1]);
}

/*
 * @brief This function returns the sum of the two outermost elements of the stack
 *
 * @param[in] stek (type: double*, the stack of elements to be added)
 * @param[in] index_of_top (type: int, the number of the outermost element of the stack)
 *
 * @return the sum of the two outermost elements of the stack
 * */
double add (double* stek, int index_of_top) {
	assert (index_of_top >= 1);
	assert (stek != NULL);
        
	return (stek [index_of_top] + stek[index_of_top - 1]);
}

/* @brief This function returns the edge of the stack
 *
 * @param[in] stek (type: double*, pointer to the stack from which to get the extreme element)
 * @param[in] index_of_top 
 * */ 
void pop (double* stek, int* p_index_of_top) {
	assert (*p_index_of_top != THERE_IS_NOTHING_IN_THE_STACK);
	assert (stek != NULL);
	assert (p_index_of_top != NULL);

        double top_element = stek[*p_index_of_top];
	stek[*p_index_of_top] = 0.0; 
	*p_index_of_top--;

	printf ("Top element = %lg\n", top_element);
}

/*
 * @brief This function fills an array of type double with zeros
 *
 * @param[in] arr (type: double*, an array to be filled with zeros)
 * @param[in] size_arr (type int, length of array)
 * */
void memset_0__for_double (double* arr, int size_arr) {
	assert (arr != NULL);
	assert (size_arr >= 0);

	for (int i = 0; i < size_arr; i++)
		arr[i] = 0.0;
}


/*
 * @brief This function adds an item to the stack
 *
 * @param[in] number (type: double, the number to add to the stack)
 * @param[in] index_of_top (type: int*, pointer to a variable that contains the index of the outermost element of the stack)
 * @param[in] stek (type: double*, stack pointer)
 * */
void push (double number, int* p_index_of_top, double* stek) {
	assert (p_index_of_top != NULL);
	assert (stek != NULL);

        stek[*p_index_of_top + 1] = number;
        (*p_index_of_top)++; 
}


/*
 * @brief This function returns the number of characters in the file
 *
 * @param[in] file (type FILE*)
 *
 * @return number of characters in the file
 * */
int number_of_characters_in_the_file (FILE* file) {
        assert (file != NULL);

        fseek (file, 0, SEEK_END);
        int n_characters_in_the_file = ftell (file);
        fseek (file, 0, SEEK_SET);
        return n_characters_in_the_file;
}

/**
 * @brief This function finds the number of lines in the source text
 *  and replaces the carriage return character with a line end character
 *
 *  @param[in] text (a string containing text)
 *  @param[in] size_text
 *
 *  @return number_of_lines
 *  **/
int swap_n_to_0_and_find_number_of_lines (char* text, int size_text) {
    int i = 0, number_of_lines = 0;

    assert (text != NULL);

    for (i = 0; i < size_text; i++) {
        if (text[i] == '\n') {
            text[i] = '\0';
	    number_of_lines++;
	}
    }

    return number_of_lines;
}

/*
 * @brief This function places pointers to the beginning of lines
 *
 * @param[in] text (a string conraining text)
 * @param[in] size_text
 * @param[in] p_lines (array of pointers)
 * **/
void arrange_pointers (char* text, int size_text, char** p_lines, int number_of_lines) {
    int i = 0, is_new_string = 0, k = 0;

    assert (text != NULL);

    for (i = 0; i < size_text; i++) {
        if (text[i] != ' ' && is_new_string == 0 && is_punctuation_mark_or_number (text [i])) {
	    p_lines[k] = &text[i];
            k++;
            is_new_string = 1;
        }

	if (text[i] == '\0')
	    is_new_string = 0;

    }
}

/*
 * @brief This function checks if a character is a punctuation mark
 * The function determines whether the symbol belongs to the set {. , ! ? * % @ $ # ( ) / : ; ~ ` -}
 *
 * @param[in] c (input char)
 *
 * @return 1 if the character is one of the listed punctuation marks, 0 owervise
 * */
int is_punctuation_mark_or_number (char c) {
    if (c != '.' && c != ',' && c != '!' && c != '?' && c != '*')
    if (c != '%' && c != '@' && c != '$' && c != '#' && c != '(')
    if (c != '/' && c != ':' && c != ';' &&  c != ')' && c != '~')
    if (c != '`' && c != '1' && c != '2' && c != '3' && c != '4')
    if (c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '0')
        return 1;

    return 0;
}

