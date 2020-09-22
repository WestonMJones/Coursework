/*****************************************************************************/
/* Assignment 5: Cache Simulator  ********************************************/
/* Name: Weston Jones ********************************************************/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void **mm_alloc( int rows, int columns )
{
    return 0;
}

int main()
{

    // Start variables
    int assoc, algo, size, num_sets;

    // Get associativity
    printf("Enter associativity (1, 2, 4): \n");
    scanf("%d", &assoc);

    // Define size and number of sets
    size = 256;
    num_sets = size / assoc;

    printf("\nCache size %d items\n",size );
    printf("Cache has associativity of %d\n",assoc );
    printf("Cache has %d sets \n\n",num_sets );

    printf("Choose either 1) LRU or 2) Belady: \n");
    scanf("%d",&algo);
    printf("\n");

    int accesses = 1000;

    // Initialize hits and misses
    int hits = 0;
    int misses = 0;

    // Read in all the memory traces

    int * trace = calloc(accesses,sizeof(int));

    for (int i=0;i<accesses;i++) {
        scanf("%d",&trace[i]);
    }

    




    printf("Starting Simulation...\n");

    if (assoc==1) {
        // Direct Mapping Case

        // Create array of size 256 and initalize to zero
        int * sets = calloc(num_sets,sizeof(int));
        for (int i=0;i<accesses;i++) {
            sets[i]=0;
        }

        //  Loop through traces
        for (int i=0;i<accesses;i++) {

            // calculate requested block in cache
            int block = trace[i] % num_sets;

            // If block ontains right data, it's a hit
            if (sets[block]==trace[i]) {
                // Hit
                hits++;

            // Else, it's a miss and retrieve data from main memory
            } else {
                // Miss
                misses++;
                sets[block]=trace[i];
            }
        }


    } else if (algo==1) {
        // LRU Case

        // Create a 2D array of ints to represent the cache
        int ** sets = calloc(num_sets,sizeof(int *));

        // Create a parallel array to hold usage information on each cache location
        int ** count = calloc(num_sets,sizeof(int *));

        // Initialize everything to zero
        for (int i=0;i<num_sets;i++) {
            sets[i] = calloc(assoc,sizeof(int));
            count[i] = calloc(assoc,sizeof(int));

            for (int x=0;x<assoc;x++) {
                sets[i][x]=0;
                count[i][x]=0;
            }
        }

        // Loop through the trace
        for (int a=0;a<accesses;a++) {

            // Calculate set
            int set = trace[a] % num_sets;

            // Create variable with placeholder variable 
            int block_accessed = -1;

            // Loop through the associated subsets
            for (int b=0;b<assoc;b++) {

                // If the data is already present, it's a hit.
                if (trace[a]==sets[set][b]) {
                    hits++;
                    block_accessed = b;

                    // Increment the time-since-last-usage count for each address
                    for (int c=0;c<assoc;c++) {
                        count[set][c]++;
                    }

                    // Reset the usage count for the block that contains the requested address
                    count[set][block_accessed]=0;

                    break;

                }


            }

            // If block_accessed wasn't changed, there was a miss.
            if (block_accessed==-1) {
                misses++;
                block_accessed = 0;

                // Find block in set that's the last to be used
                for (int c=0;c<assoc;c++) {
                    if (count[set][c]>count[set][block_accessed]) {
                        block_accessed = c;
                    }
                }

                // Increment time-since-last usage count for all blocks in set
                for (int c=0;c<assoc;c++) {
                   count[set][c]++;
                }

                // Reset usage count for block about to be reset
                count[set][block_accessed] = 0;

                // replace the block with the new address
                sets[set][block_accessed] = trace[a];

            }




        }





    } else if (algo==2) {
        // Belady

        // Initalize 2D array to represent cache
        int ** sets = calloc(num_sets,sizeof(int*));

        // Create a 1D array of size = to the associativity 
        int * count = calloc(assoc,sizeof(int));

        // Initialize the sets array to zeros
        for (int x=0;x<num_sets;x++) {
            sets[x] = calloc(assoc,sizeof(int));
            for (int y=0;y<assoc;y++) {
                sets[x][y]=0;
            }
        }

        // Loop through the trace
        for (int a=0;a<accesses;a++) {
            int set = trace[a] % num_sets;
            int block_accessed = -1; // variable to mark whether hit or miss occured

            // If the requested data it found, it's a hit
            for (int b=0;b<assoc;b++) {
                if (sets[set][b]==trace[a]) {
                    hits++;
                    block_accessed = 0;
                }
            }


            // If block_accessed wasn't changed, it's a hit
            if (block_accessed==-1) {
                misses++;

                // Update count to hold the indices in trace of next time that location in cache is requested
                for (int b=0;b<assoc;b++) {
                    count[b]=1001; // Default is that it's never found again 

                    // Loop through the trace again - checking for next occurance of that address
                    for (int i=a;i<accesses;i++) {
                        int next_set = trace[i] % num_sets;

                        // If found, update the count
                        if (sets[next_set][b]==trace[i]) {
                            count[b]=i;
                            break;
                        }


                    }
                }

                // Pick the block in the current set that is requested again the latest
                int highest_count = 0;
                block_accessed = 0;
                for (int b=0;b<assoc;b++) {
                    if (count[b]>highest_count) {
                        highest_count = count[b];
                        block_accessed = b;
                    }
                }

                // Store the data in the block that will be requested again farthest in the future
                sets[set][block_accessed] = trace[a];


            }
        }


    } else {
        printf("Something went wrong!\n");
    }






    float rate = ((float) hits)/ ((float) accesses);

    printf("Statistics:\n");
    if (algo==1) {
        printf("LRU & Cache Associativity: %d\n", assoc);
    } else {
        printf("Belady & Cache Associativity: %d\n", assoc);
    }
    printf("Cache Accesses: %d\n",accesses);
    printf("Cache Hits: %d\n",hits );
    printf("Cache Misses: %d\n",misses );
    printf("Overall Hit Rate: %.6f\n", rate);

    return 0;
}
