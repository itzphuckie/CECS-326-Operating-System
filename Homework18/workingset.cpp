#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include<iterator> // for iterators 
#include<vector> // for vectors 

/*
 n is the array size, w is the window size and pages is the list
 of pages.
*/
void workingset(int n, int w, int pages[])
{
  /* This is the header line as shown in the homework assignment */
  printf("Time \t Size \t Set\n");

  /* This print confirms the parameter pass, it shows you how to line
    things up with the headers.*/

//  printf("%d \t %d \t ",n,w);
  for (int i=0; i<n-w+1; i++)
  {
    //initialize vector
    std::vector<int> vect;

  int size = 0;
    for(int j=0; j<w; j++) {
        if(vect.empty()) {
           vect.push_back(pages[j+i]);
        }

      else {
         //loop vector size    
         for(int k=0; k<vect.size(); k++) {
             if(pages[j+i] == vect.at(k)) break;
             //push back if page does not equal vector values and nothing left to compare
              else if(pages[j+i] != vect.at(k) && k+1 >= vect.size()) {
                vect.push_back(pages[j+i]);
                break;

             }

         }

      }
    }
 size = vect.size();
  printf("%d\t %d\t", w + i - 1, size);
  std::vector<int>::iterator itr;
  itr = vect.begin();
     while(itr != vect.end()) {
       printf("%d", *itr);
       itr++;
     }
  printf("\n");
  }
};

int main()
{
  int list1[] = {1,2,3,3,2,3,2,1,2,1,2,1,3,1,3,1,2,3,1};
  int list2[] = {1,2,3,3,4,4,5,3,3,2,1,2,1,2,3,4,5,3,2,4,2,4,2,2};
  /* notice the tricky way of getting the number of integers in the array */
  workingset(sizeof(list1)/sizeof(int),6,list1);
  workingset(sizeof(list2)/sizeof(int),6,list2);
  return 0;
};

