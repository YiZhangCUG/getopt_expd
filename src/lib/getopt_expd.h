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

struct option_info
{
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
void getopt_long_help(const option *longopts, const option_info *expd_longopts, const char* proname, 
	const char* brief);

/**
 * @brief      Display the help information of one option indicated by its id.
 *
 * @param[in]  val   The option's value
 * @param      exp_longopts  The expanded longopts
 */
void getopt_long_option_info(int val, const option *longopts, const option_info *expd_longopts);

#endif //_GETOPT_EXPD_H