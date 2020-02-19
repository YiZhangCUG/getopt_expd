/*
 * C++ library of a expanded version of the getopt library.
 *
 * Copyright (c) 2019-2029 Yi Zhang (zhangyiss@icloud.com)
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _GETOPT_EXPD_H
#define _GETOPT_EXPD_H
#include "iostream"
#include "string.h"
#include "unistd.h"
#include "sys/ioctl.h"
#include "sstream"
#include "getopt.h"

/**
 * @brief      Expanded version of the 'option' structure.
 * 
 * This library is built upon the getopt library developed by the GNU. We 
 * expand the 'option' structure to include some helpful information. Since
 * we need to keep the new structure aggregate, we declare our 'expd_option'
 * structure just as the original 'option' structure at beginning, followed 
 * some new variables.
 */
struct expd_option
{
	/**
	 * The first four variables are as the same as the original 'option' structure
	 * that is defined in getopt.h. Their types and orders must not be changed to
	 * ensure they can be accessed by the 'getopt' functions correctly.
	 */
	const char *name;
	int has_arg;
	int *flag;
	int val;
	/**
	 * The following three variables we added here are mainly used to generate the
	 * 'help' page. The variable 'info' represents a short message that explains what
	 * the option does. 'format' express the argument's format that the option takes.
	 * Additionally, The variable 'manda' indicates whether the option is mandatory 
	 * or optional.
	 */
	const char *info;
	const char *format;
	bool manda;
};

/**
 * @brief      Convert pointer types and call for the original getopt_long function.
 * 
 * This function takes the same arguments as the original 'getopt_long' function, except
 * that we use the 'expd_option' structure in stead of the 'option' structure. This function
 * simply convert the pointer of 'expd_option' into the type of 'option' and call for
 * the 'getopt_long' function.
 *
 * @param[in]  argc          The count of arguments
 * @param      argv          The arguments array
 * @param[in]  optstring     The optstring
 * @param      exp_longopts  The expanded longopts
 * @param      longindex     The longindex
 *
 * @return     Option value
 */
int getopt_long_expand(int argc, char * const argv[], const char *optstring, 
	expd_option *expd_longopts, int *longindex);

/**
 * @brief      display formatted help information in terminal
 * 
 * This function will display formated help information in the terminal using
 * the standard error output. We choose the error output to avoid unexpected
 * redirection and make sure the information will appear in the terminal.
 *
 * @param[in]  proname       The program's name.
 * @param[in]  brief         The brief information show right after the program's name.
 * @param[in]  exp_longopts  The pointer of expanded longopts
 */
void getopt_long_help(const expd_option *expd_longopts, const char* proname, 
	const char* brief);

/**
 * @brief      Display the help information of one option indicated by its id.
 *
 * @param[in]  val   The option's value
 * @param      exp_longopts  The expanded longopts
 */
void getopt_long_option_info(int val, const expd_option *expd_longopts);

#endif //_GETOPT_EXPD_H