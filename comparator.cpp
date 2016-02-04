/*
 * Description : Function comparator is a tool to compare functions codes in different (<!--or same!-->)
 *               It's different than diff in the fact that it allows comparison of single functions
 *               undependantly from the position of the function code in the files
 * Author      : Oussema Harbi <oussema.elharbi@gmail.com>
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>

#define RED_COLOR     "\e[31m"
#define GREEN_COLOR   "\e[32m"
#define BLUE_COLOR    "\e[33m"
#define DEFAULT_COLOR "\e[0m"

using namespace std;

/* ToDo : manage command line options correctly via getopt */
static const bool verbose = false;
static const bool ignore_spaces = true;

void usage(char* app_name)
{
  cout << "Usage: " << app_name << " function_1 file_1 function_2 file_2" << endl;
  cout << "The output will be the different lines between the 2 impelementaions" << endl;
}


int  findFunction(char* function_name, fstream& src)
{
    string line, function(function_name);
    int counter = 0;
    /* ToDo : Add check for ; character to avoid function call instead of definition */
    do {
        getline(src, line);
        counter++;
    } while (src.good() && (line.find(function) == string::npos));

    if (!src.good())
    {
        counter = 0;
    }
    return counter;
}

/* How to call : comparator function_1 file_1 function_2 file_2 */
int main(int argc, char* argv[])
{
    int err = 0;
    int counter_1, counter_2, block_counter_1 = 0, block_counter_2 = 0;
    bool in_function = true, identical = true;
    string line_1, line_2, orig_1, orig_2;
    fstream file_1, file_2;

    cout << endl;
    if (argc != 5)
    {
      usage(argv[0]);
    }

    /* Open files */
    file_1.open(argv[2], ios_base::in);
    file_2.open(argv[4], ios_base::in);

    /* Find functions */
    counter_1 = findFunction(argv[1], file_1);
    if (counter_1)
    {
        if (verbose)
        {
            cout << " Function " << argv[1] << " found at line " << counter_1 << endl;
        }
    } else {
        cout << RED_COLOR << " Function " << argv[1] << " not found in file !!" << DEFAULT_COLOR << endl;
        err = -1;
        goto io_error;
    }

    counter_2 = findFunction(argv[3], file_2);
    if (counter_2)
    {
        if (verbose)
        {
            cout << " Function " << argv[3] << " found at line " << counter_2 << endl;
        }
    } else {
        cout << RED_COLOR << " Function " << argv[3] << " not found in file !!" << DEFAULT_COLOR << endl;
        err = -1;
        goto io_error;;
    }

    /* Find differences */
    do {
        do {
            getline(file_1, line_1);
            counter_1++;
            orig_1 = string(line_1);
            if (ignore_spaces)
            {
                orig_1.erase(std::remove_if(orig_1.begin(), orig_1.end(), ::isspace), orig_1.end());
            }
        } while (orig_1.size() == 0 && file_1.good());

        do {
            getline(file_2, line_2);
            counter_2++;
            orig_2 = string(line_2);
            if (ignore_spaces)
            {
                orig_2.erase(std::remove_if(orig_2.begin(), orig_2.end(), ::isspace), orig_2.end());
            }
        } while (orig_2.size() == 0 && file_2.good());

        if ((orig_1.size() > 0) &&
            (orig_2.size() > 0) &&
            (orig_1.compare(orig_2) != 0))
        {
            identical = false;
            cout << GREEN_COLOR << "1::" << counter_1 << "->" << line_1 << DEFAULT_COLOR << endl;
            cout << BLUE_COLOR  << "2::" << counter_2 << "->" << line_2 << DEFAULT_COLOR << endl;
            cout << endl;
        }
        /* ToDo : Handle multiple block delimiters in same line */
        if (line_1.find("{") != string::npos)
        {
            block_counter_1++;
        }
        if (line_1.find("}") != string::npos)
        {
            block_counter_1--;
        }
        if (line_2.find("{") != string::npos)
        {
            block_counter_2++;
        }
        if (line_2.find("}") != string::npos)
        {
            block_counter_2--;
        }
        if (block_counter_1 == 0 || block_counter_2 == 0)
        {
            in_function = false;
        }
    } while (file_1.good() && file_2.good() && in_function);

    if (!file_1.good() || !file_2.good())
    {
        cout << " An error occured at lines 1::" << counter_1 << " , 2::" << counter_2 << " while comparing code !" << endl;
        err = -1;
    }

    if (identical)
    {
        cout << "Functions are identical !!" << endl;
    }

io_error:
    /* Clean up and exit */
    file_1.close();
    file_2.close();

    return err;
}
