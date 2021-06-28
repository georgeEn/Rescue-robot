#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int driving_mode = 0;
char coming_from = 'O'; // we always start on an empty space

// THIS IS THE FUNCTION YOU IMPLEMENT
int move(char *world)
{
    // Functions for robot and target location
    int robot_index, target_index, target_index_NS_cord, robot_index_NS_cord;
    int width, robot_index_WE_cord, target_index_WE_cord;
    int nexmove=1;

    for (int i=0; i<200; ++i)
    {
        if (world[i]=='\n')
        {
            width= i+1;
            break;
        }
    }



    for (int i=0; i<200; ++i)
    {
        if (world[i]=='R')
        {
            robot_index=i;
            //The robot Location;
            break;
        }
    }



    for (int i=0; i<200; ++i)
    {
        if (world[i]=='T')
        {
            target_index=i;
            //The Target Location;
            break;
        }
    }



    printf("\n width = %d \n", width);
    //Position in NS and WE coordinate;
    robot_index_NS_cord= robot_index / width;
    robot_index_WE_cord= robot_index % width;
    target_index_NS_cord= target_index / width;
    target_index_WE_cord= target_index % width;
    int NS_distance= robot_index_NS_cord - target_index_NS_cord;
    int WE_distance= robot_index_WE_cord - target_index_WE_cord;

    printf (" NS distance= %d, WS distance = %d \n", NS_distance, WE_distance);

    if(abs(WE_distance) <= abs(NS_distance))
    {
         if(NS_distance >= 0)
        {
           if ( world [robot_index-(width+1)] == 'O' && driving_mode == 0 && coming_from=='O' )
           {return 1;}

           else if ( world [robot_index-(width+1)] == '~' && driving_mode == 0 && coming_from=='O')
            {

                return 5;




            }
            else if ( world [robot_index-(width+1)] == 'O' && driving_mode == 1 && coming_from=='~')
                {

                    return 5;

                }
                else
                {

                    return 1;

                }










        }
        else
        {

            return 3; // south
        }
    }
    else
    {
        if(WE_distance >= 0)
        {
            if (world [robot_index-1] != '#')
            {return 4;} // west
            else if (world [robot_index-1] == '#')
            {
                if(NS_distance >= 0)
                {
                if(world[robot_index-(width+1)] != '#')
                    {return 1;}
                else
                {
                    if (world[robot_index+(width+1)] != '#')
                    {return 3;}
                }

                }
            }
            else {return 1;}
        }

        else
        {

            return 2; //east
        }
    }

}


//Driving mode


// Return target index
int update_world(int movement, char *world, int robot_index, int width)
{
    int target_index = 0;
    // NORTH
    if(movement == 1)
    {
        target_index = robot_index-(width+1); // +1 for the newline
    }
    // SOUTH
    else if(movement == 3)
    {
        target_index = robot_index+(width+1); // +1 for the newline
    }
    // EAST
    else if(movement == 2)
    {
        target_index = robot_index+1;
    }
    // WEST
    else if(movement == 4)
    {
        target_index = robot_index-1;
    }
    else if(movement == 5)
    {
        printf("Toggling mode!\n");
        target_index = robot_index;
        if(driving_mode == 0)
        {
            driving_mode = 1;
        }
        else
        {
            driving_mode = 0;
        }
    }

    // ACTION
    if(world[target_index] == 'O')
    {
        if(driving_mode != 0)
        {
            printf("FAILURE, tried to drive on land in land water!");
            exit(1);
        }
        else
        {
            world[target_index] = 'R';
            world[robot_index] = coming_from;
            coming_from = 'O';
            return target_index;
        }
    }
    // Stay in the same location (used for driving mode toggling)
    else if(world[target_index] == 'R')
    {
        return target_index;
    }
    else if(world[target_index] == '#')
    {
        printf("%s", world);
        printf("%c", '\n');
        printf("FAILURE, crashed into a wall!");
        exit(1);
    }
    else if(world[target_index] == '~')
    {
        if(driving_mode != 1)
        {
            printf("FAILURE, entered water in land mode!");
            exit(1);
        }
        else
        {
            // TODO handle coming from water
            world[target_index] = 'R';
            world[robot_index] = coming_from;
            coming_from = '~';
            return target_index;
        }

    }
    else if(world[target_index] == 'T')
    {
        world[target_index] = 'R';
        world[robot_index] = 'O';
        printf("%s", world);
        printf("%c", '\n');
        printf("SUCCESS, target found!");
        exit(0);
    }
}

int main()
{
    const int MAX_STEPS = 200;
    int step = 1;

    int movement;
    int width = 20; // excluding newlines

    // The maps
    char world1[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','T','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','R','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    char world2[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','R','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','T','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    char world3[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','R','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','T','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    char world4[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','R','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','T','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    char world5[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','#','#','#','#','#','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','#','T','O','O','#','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','#','#','#','O','#','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','R','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    char world6[200] =
    {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','T','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','~','~','~','~','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','~','~','~','~','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','R','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n'
    };

    // world
    char world[200];
    memcpy(world, world1, sizeof(world1));

    // Initialize target and robot positions
    // Assumes only one target, one robot
    unsigned int elements = sizeof(world)/sizeof(world[0]);

    // Initialize the index of the robot and the target.
    // Assumes exactly one robot and one target
    int robot_index;
    int target_index;

    for(int i = 0; i < elements; i++)
    {
        if (world[i] == 'R')
        {
            robot_index = i;
        }
        if (world[i] == 'T')
        {
            target_index = i;
        }
    }

    // Print the initial world
    printf("Starting position: %c", '\n');
    // Debug output
    // printf("Robot index: %i / target index: %i %c", robot_index, target_index, '\n');
    printf("%s", world);
    printf("%c", '\n');

    while(step <= MAX_STEPS)
    {
        printf("After step number %i: %c", step, '\n');

        movement = move(world);
        robot_index = update_world(movement, world, robot_index, width);
        printf("%s", world);
        printf("%c", '\n');
        step = step+1;
    }
    if(step >= MAX_STEPS)
    {
        printf("FAILURE, maximum number of steps exceeded.");
    }
}
