

            

 
    #// Compute minimum coins required for all
    #// values from 1 to V
    #for (int i=1; i<=V; i++)
    #{
        #// Go through all coins smaller than i
        #for (int j=0; j<m; j++)
          #if (coins[j] <= i)
          #{
              #int sub_res = table[i-coins[j]];
              #if (sub_res != INT_MAX && sub_res + 1 < table[i])
                  #table[i] = sub_res + 1;
          #}
    #}
    #return table[V];
#}

