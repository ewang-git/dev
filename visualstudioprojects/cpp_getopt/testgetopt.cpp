#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

int
main (int argc, char **argv) {
  int c;
  int digit_optind = 0;

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    // format ( longoption, no_param|required_param,
    static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"version", no_argument, 0, 1},
      {"verbose", 0, 0, 2},
      {"rtn", required_argument, 0, 'r'},
      {"base", required_argument, 0, 'b'},
      {"f", required_argument, 0, 'f'},
      {"o", required_argument, 0, 'o'},
      {"max", required_argument, 0, 'm'},
      {"time", required_argument, 0, 't'},
      {0, 0, 0, 0}
    };

    //c = getopt_long_only (argc, argv, "hvr:b:f:o:m:t:",
    c = getopt_long (argc, argv, "hvr:b:f:o:m:t:",
                     long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 'h':           // -help
      printf ("option %s\n", long_options[option_index].name);
      break;

    case 1:                     // -version
      printf ("option %s\n", long_options[option_index].name);
      break;

    case 2:                     // -verbose
      printf ("option %s\n", long_options[option_index].name);
      break;

    case 'r':           // -rtn
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;
    case 'b':           // -base
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;

    case 'f':           // -f
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;

    case 'm':           // -max
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;

    case 't':           // -time
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;

    case 'o':           // -o
        if (!optarg){
                printf("argument required for option %s\n",long_options[option_index].name);
        }
        printf("option %s with argument %s\n",long_options[option_index].name, optarg);
                break ;


    case '?':
      printf("?????????????????????");
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }

    if (optind < argc) {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      printf ("%s ", argv[optind++]);
    printf ("\n");
  }

  exit (0);
}