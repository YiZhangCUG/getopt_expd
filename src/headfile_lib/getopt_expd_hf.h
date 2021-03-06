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

/**
 * @brief      Display a string massage using the standard error output.
 *
 * @param[in]  f_space     The front space before the printing.
 * @param[in]  b_space     The end space before the printing.
 * @param[in]  hang_space  The hang space starting from the second line.
 * @param[in]  ws          window size of the terminal
 * @param[in]  msg         The message
 */
void display_line(int f_space, int b_space, int hang_space, const winsize *ws, std::string msg);

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
	const char* brief)
{
	// Default layout. One can only change this by recompile the library.
	int front_space = 0, back_space = 10;

	int line_length;
	std::string m1, m2, m3;
	std::string segment;
	std::stringstream ss_message;

	//获取终端窗口的行列数
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// We firstly display the program's name which is assumed to be the first argument.
	m1 = proname;
	m2 = brief;
	m1 += m2;
	display_line(front_space, back_space, 4, &w, m1);
	std::cerr << std::endl;

	// display usage
	int loop_index = 0;
	m2 = proname;
	m1 = "Usage: " + m2;
	while(1)
	{
		if (longopts[loop_index].name != 0 && expd_longopts[loop_index].format != 0)
		{
			m2 = (char)longopts[loop_index].val;
			m3 = expd_longopts[loop_index].format;
			if (!expd_longopts[loop_index].manda)
				m1 += " [-" + m2 + m3 +"]";
			else m1 += " -" + m2 + m3;
			loop_index++;
		}
		else if (longopts[loop_index].name != 0)
		{
			m2 = (char)longopts[loop_index].val;
			if (!expd_longopts[loop_index].manda)
				m1 += " [-" + m2 + "]";
			else m1 += " -" + m2;
			loop_index++;
		}
		else break;
	}
	display_line(front_space, back_space, 7, &w, m1);
	std::cerr << std::endl;

	//找到最长的选项作为排版的依据
	int temp_len, remain_len, max_opt_length = -1;
	loop_index = 0;
	while(1)
	{
		if (longopts[loop_index].name != 0)
		{
			temp_len = strlen(longopts[loop_index].name);
			max_opt_length = std::max(max_opt_length, temp_len + 1);
			loop_index++;
		}
		else break;
	}

	m1 = "Options:";
	display_line(front_space, back_space, 0, &w, m1);

	// display usage
	loop_index = 0;
	while(1)
	{
		if (longopts[loop_index].name != 0)
		{
			for (int j = 0; j < front_space+2; j++)
				std::cerr << " ";

			temp_len = strlen(longopts[loop_index].name) + 1;
			remain_len = max_opt_length - temp_len;
			std::cerr << "-" << (char)longopts[loop_index].val << "    --" 
			<< longopts[loop_index].name << "    ";
			for (int j = 0; j < remain_len; j++)
				std::cerr << " ";

			ss_message.clear();
			ss_message.str(expd_longopts[loop_index].info);
			line_length = front_space + back_space + max_opt_length + 14;
			while(ss_message >> segment)
			{
				if ((line_length+segment.length()+1) <= w.ws_col)
				{
					std::cerr << segment << " ";
					line_length += (segment.length()+1);
				}
				else
				{
					std::cerr << std::endl;
					for (int j = 0; j < front_space+max_opt_length+13; j++)
						std::cerr << " ";
					std::cerr << segment << " ";
					line_length = (segment.length()+13+max_opt_length+front_space+back_space);
				}
			}
			std::cerr << std::endl;

			loop_index++;
		}
		else break;
	}
	std::cerr << std::endl;

	m1 = "This page is generated by the 'getopt_expd' library automatically.";
	display_line(front_space, back_space, 4, &w, m1);
	return;
}

/**
 * @brief      Display the help information of one option indicated by its id.
 *
 * @param[in]  val   The option's value
 * @param      exp_longopts  The expanded longopts
 */
void getopt_long_option_info(int val, const option *longopts, const option_info *expd_longopts)
{
	//获取终端窗口的行列数
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	std::string m1, m2;
	int loop_index = 0;
	while (1)
	{
		if (longopts[loop_index].name != 0)
		{
			if (longopts[loop_index].val == val)
			{
				m1 = "Option: -";
				m2 = (char)longopts[loop_index].val;
				m1 += m2;
				m2 = expd_longopts[loop_index].format;
				m1 += m2 + " ";
				m2 = expd_longopts[loop_index].info;
				m1 += m2;
				display_line(0, 10, 4, &w, m1);
			}
			loop_index++;
		}
		else break;
	}
	return;
}

void display_line(int f_space, int b_space, int hang_space, const winsize *ws, std::string msg)
{
	int line_length = f_space + b_space;
	std::string segment;
	std::stringstream ss_message;

	ss_message.clear();
	ss_message.str(msg);
	while (ss_message >> segment)
	{
		if ((line_length+segment.length()) <= ws->ws_col)
		{
			if (line_length == f_space+b_space)
			{
				for (int i = 0; i < f_space; i++)
					std::cerr << " ";
				std::cerr << segment << " ";
				line_length += segment.length()+1;
			}
			else
			{
				std::cerr << segment << " ";
				line_length += segment.length()+1;
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < f_space+hang_space; i++)
				std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+1+hang_space+f_space+b_space);
		}
	}
	std::cerr << std::endl;
	return;
}

#endif //_GETOPT_EXPD_H