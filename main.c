#include <stdlib.h>
#include <stdio.h>

#include "utilities/cbmp.h"
#include "utilities/states_enum.h"
#include "utilities/types.h"

int main(int argc, char const *argv[])
{
    STATES state, nextState=INIT;
    BOOL run=TRUE;

    while (run)
    {
        state=nextState;
        switch (state)
        {
        case INIT:
            printf("Init");
            nextState=EXIT;
            break;

        case EXIT:
            printf("Exit");
            run=FALSE;
            break;

        default:
            printf("Error");
            run=FALSE;
            break;
        }
    }
    return 0;
}
