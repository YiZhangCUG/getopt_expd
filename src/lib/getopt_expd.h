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
 * This library is dependent on the getopt library. We firstly need
 * to expand the 'option' structure to include help information. Since
 * we need to keep the new structure aggregate, we declare our 'expd_option'
 * structure just as the original 'option' structure with an additional
 * constant char* "info", which needs to be converted to the 'option' structure later.
 */
struct expd_option
{
	const char *name;
	int has_arg;
	int *flag;
	int val;
	const char *info;
	const char *format;
	bool manda;
};

/**
 * @brief      Convert pointer types and call for the original getopt_long function.
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
 * @param[in]  proname       The program's name.
 * @param[in]  brief         The brief information show right after the program's name.
 * @param[in]  exp_longopts  The pointer of expanded longopts
 */
void getopt_long_help(const expd_option *expd_longopts, const char* proname, 
	const char* brief);

#endif //_GETOPT_EXPD_H