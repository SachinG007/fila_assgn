#include <math.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <vector>
// #include <random>
#include <string>
#include "function.h"
// #include "bandit-agent.cpp"

using namespace std;

float cum_rewards[25] = {0};
int total_pulls[25] = {0};
float bandit_probs[25] = {0};
int ArmToPull = 0;
int prev_arm = 0;

// C function to find maximum in arr[] of size n
int largest(float arr[], int n)
{
    // Initialize maximum element
    float max = arr[0];
    int max_index = 0;
 
    // Traverse array elements from second and
    // compare every element with current max  
    for (int i = 0; i < n; i++){
        if (arr[i] > max){
            max = arr[i];
            max_index = i;
          }
    }

    return max_index;
}

int random(int x, int y, int p)
{       
        // Generate a number from 1 to 100
        float r = rand() % 1000 + 1;     // v2 in the range 1 to 100  
        r = r/1000;    
        cout<<"gene r"<<r<<endl;
        // r is smaller than px with probability px/100
        if (r <= p)
            return x;
 
        else
            return y;
}

int epsilon_greedy(int pulls, float reward, int numArr)
{

    //to be done only the first time
    if(pulls == 0){
        for(int i=0;i<numArr;i++){
            cum_rewards[i] = 0;
            total_pulls[i] = 0;
            bandit_probs[i] = 0;
        }
    }

    if(pulls!=0){
        cum_rewards[ArmToPull] = cum_rewards[ArmToPull] + reward;
        total_pulls[ArmToPull] = total_pulls[ArmToPull] + 1;
        bandit_probs[ArmToPull] = cum_rewards[ArmToPull]/total_pulls[ArmToPull];
    }

    float pulls_f = pulls;
    float epsilon = 1/(pulls_f+1);
    cout<<"epsilon"<<epsilon<<endl;
    int exploit = random(0,1,epsilon);

    if(pulls<20){
      cout<<bandit_probs[0]<<endl;
      cout<<bandit_probs[1]<<endl;
      cout<<bandit_probs[2]<<endl;
      cout<<bandit_probs[3]<<endl;
      cout<<bandit_probs[4]<<endl;
      cout<<bandit_probs[5]<<endl;
      cout<<bandit_probs[6]<<endl;
    }


    if(exploit==0){
        //do explore
        cout<<"explore"<<endl;
        ArmToPull = rand() % numArr ;
        return ArmToPull;
    }

    else {
        //exploit
        cout<<"exploit"<<endl;
        ArmToPull = largest(bandit_probs,numArr);
        return ArmToPull;
    }


    // return 2;
}
