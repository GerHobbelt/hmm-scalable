//
//  inputconvert.cpp
//  HMM
//
//  Created by Yudelson, Michael on 7/22/13.
//
//

#include "utils.h"
#include "InputUtil.h"
using namespace std;

char source_format = 't';
char target_format = 'b';
struct param param;

void exit_with_help() {
	printf(
		   "Usage: inputconvert [options] source_file [target_file]\n"
		   "options:\n"
		   "-s : source file format 't' - text, 'b' - binary  (default is 't' - text)\n"
		   "-t : target file format 't' - text, 'b' - binary  (default is 'b' - binary)\n"
           "-d : delimiter for multiple skills per observation; 0-single skill per\n"
           "     observation (default), otherwise -- delimiter character, e.g. '-d ~'.\n"
		   );
	exit(1);
}

void parse_arguments(int argc, char **argv, char *input_file_name, char *output_file_name) {
	// parse command line options, starting from 1 (0 is path to executable)
	// go in pairs, looking at whether first in pair starts with '-', if not, stop parsing arguments
	int i;
	for(i=1;i<argc;i++)
	{
		if(argv[i][0] != '-') break; // end of options stop parsing
		if(++i>=argc)
			exit_with_help();
		switch(argv[i-1][1])
		{
			case 's':
				source_format = argv[i][0];
                if( source_format!='t' && source_format!='b') {
					fprintf(stderr,"ERROR! source format should be either text 't', or binary 'b'\n");
					exit_with_help();
				}
				break;
			case 't':
				target_format = argv[i][0];
                if( target_format!='t' && target_format!='b') {
					fprintf(stderr,"ERROR! target format should be either text 't', or binary 'b'\n");
					exit_with_help();
				}
				break;
            case  'd':
				param.multiskill = argv[i][0]; // just grab first character (later, maybe several)
                break;
			default:
				fprintf(stderr,"unknown option: -%c\n", argv[i-1][1]);
				exit_with_help();
				break;
		}
	}
//    post-argument checks
    if( source_format == target_format) {
        fprintf(stderr,"ERROR! source and target formats should not be the same");
        exit_with_help();
    }
	
	// next argument should be input file name
	if(i>=argc) // if not
		exit_with_help(); // leave
	
	strcpy(input_file_name, argv[i++]); // copy and advance
	
	if(i>=argc) { // no output file name specified
        if(target_format=='b')
            strcpy(output_file_name,"output.bin");
        else
            strcpy(output_file_name,"output.txt");
	} else {
		strcpy(output_file_name,argv[i++]); // copy and advance
    }

}

int main (int argc, char ** argv) {
    
	clock_t tm0 = clock();
    printf("starting conversion...\n");
	char input_file[1024];
	char output_file[1024];
    
	set_param_defaults(&param);
	parse_arguments(argc, argv, input_file, output_file);
    
    if( source_format=='t') {
        InputUtil::readTxt(input_file, &param);
        printf("reading done\n");
        InputUtil::toBin(&param, output_file);
        printf("writing done\n");
    }
    else {
        InputUtil::readBin(input_file, &param);
    }
    printf("before destroy\n");
	// free data
	destroy_input_data(&param);
	
	if(param.quiet == 0)
		printf("overall time running is %8.6f seconds\n",(NUMBER)(clock()-tm0)/CLOCKS_PER_SEC);
    return 0;
}

