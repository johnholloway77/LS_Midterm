#include "./flags.h"
#include <stdio.h>

int checkFlags(int flags)
{
    if(flags == 0){
        printf("No flags set\n");
        return 0;
    }

    if(flags & A_FLAG){
        printf("A_FLAG set\n");
    }
    if(flags & a_FLAG){
        printf("a_FLAG set\n");
    }
    if(flags & c_FLAG){
        printf("c_FLAG set\n");
    }
    if(flags & F_FLAG){
        printf("F_FLAG set\n");
    }
    if(flags & f_FLAG){
        printf("f_FLAG set\n");
    }
    if(flags & h_FLAG){
        printf("h_FLAG set\n");
    }
    if(flags & i_FLAG){
        printf("i_FLAG set\n");
    }
    if(flags & k_FLAG){
        printf("k_FLAG set\n");
    }
    if(flags & l_FLAG){
        printf("l_FLAG set\n");
    }
    if(flags & n_FLAG){
        printf("n_FLAG set\n");
    }
    if(flags & q_FLAG){
        printf("q_FLAG set\n");
    }
    if(flags & R_FLAG){
        printf("R_FLAG set\n");
    }
    if(flags & r_FLAG){
        printf("r_FLAG set\n");
    }
    if(flags & S_FLAG){
        printf("S_FLAG set\n");
    }
    if(flags & s_FLAG){
        printf("s_FLAG set\n");
    }
    if(flags & t_FLAG){
        printf("t_FLAG set\n");
    }
    if(flags & u_FLAG){
        printf("u_FLAG set\n");
    }
    if(flags & w_FLAG){
        printf("w_FLAG set\n");
    }


    return 0;
}
