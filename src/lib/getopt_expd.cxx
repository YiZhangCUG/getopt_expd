#include "getopt_expd.h"

/**
 * @brief      Convert pointer types and call for the original getopt_long function.
 *
 * @param[in]  argc          The count of arguments
 * @param      argv          The arguments array
 * @param[in]  optstring     The optstring
 * @param      expd_longopts  The expanded longopts
 * @param      longindex     The longindex
 *
 * @return     Option value
 */
int getopt_long_expand(int argc, char * const argv[], const char *optstring, 
	expd_option *expd_longopts, int *longindex)
{
	// convert expd_option* to option*
	// this is valid only if the two structures had same variables.
	static const option *longopts = (option*)(&expd_longopts);
	// call for the getopt_long function
	return getopt_long(argc, argv, optstring, longopts, longindex);
}

/**
 * @brief      display formatted help information in terminal
 *
 * @param[in]  proname       The program's name.
 * @param[in]  brief         The brief information show right after the program's name.
 * @param[in]  expd_longopts  The pointer of expanded longopts
 */
void getopt_long_help(const expd_option *expd_longopts, const char* proname, 
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
	ss_message.clear(); ss_message.str(m1);
	line_length = front_space + back_space;
	while(ss_message >> segment)
	{
		if ((line_length+segment.length()+1) <= w.ws_col)
		{
			if (line_length == (front_space + back_space))
			{
				for (int i = 0; i < front_space; i++)
					std::cerr << " ";
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
			else
			{
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < front_space+8; i++)
				std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+9+front_space+back_space);
		}
	}
	std::cerr << std::endl << std::endl;

	// display usage
	int loop_index = 0;
	m1 = proname;
	while(1)
	{
		if (expd_longopts[loop_index].name != 0 && expd_longopts[loop_index].format != 0)
		{
			m2 = (char)expd_longopts[loop_index].val;
			m3 = expd_longopts[loop_index].format;
			if (!expd_longopts[loop_index].manda)
				m1 += " [-" + m2 + m3 +"]";
			else m1 += " -" + m2 + m3;
			loop_index++;
		}
		else if (expd_longopts[loop_index].name != 0)
		{
			m2 = (char)expd_longopts[loop_index].val;
			if (!expd_longopts[loop_index].manda)
				m1 += " [-" + m2 + "]";
			else m1 += " -" + m2;
			loop_index++;
		}
		else break;
	}

	ss_message.clear(); ss_message.str(m1);
	line_length = front_space + back_space + 4;
	while(ss_message >> segment)
	{
		if ((line_length+segment.length()+1) <= w.ws_col)
		{
			if (line_length == (front_space + back_space + 4))
			{
				for (int i = 0; i < front_space; i++)
					std::cerr << " ";
				std::cerr << "Usage:  " << segment << " ";
				line_length += (segment.length()+1);
			}
			else
			{
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < front_space+8; i++)
				std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+10+front_space+back_space);
		}
	}
	std::cerr << std::endl << std::endl;

	//找到最长的选项作为排版的依据
	int temp_len, remain_len, max_opt_length = -1;
	loop_index = 0;
	while(1)
	{
		if (expd_longopts[loop_index].name != 0)
		{
			temp_len = strlen(expd_longopts[loop_index].name);
			max_opt_length = std::max(max_opt_length, temp_len + 1);
			loop_index++;
		}
		else break;
	}

	// display usage
	loop_index = 0;
	std::cerr << "Options:" << std::endl;
	while(1)
	{
		if (expd_longopts[loop_index].name != 0)
		{
			for (int j = 0; j < front_space+2; j++)
				std::cerr << " ";

			temp_len = strlen(expd_longopts[loop_index].name) + 1;
			remain_len = max_opt_length - temp_len;
			std::cerr << "-" << (char)expd_longopts[loop_index].val << "    --" << expd_longopts[loop_index].name << "    ";
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

	ss_message.clear(); ss_message.str("This page is generated by the 'getopt_info' library automatically.");
	line_length = front_space + back_space;
	while(ss_message >> segment)
	{
		if ((line_length+segment.length()+1) <= w.ws_col)
		{
			if (line_length == (front_space + back_space))
			{
				for (int i = 0; i < front_space; i++)
					std::cerr << " ";
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
			else
			{
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < front_space+8; i++)
				std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+9+front_space+back_space);
		}
	}
	std::cerr << std::endl;
	return;
}