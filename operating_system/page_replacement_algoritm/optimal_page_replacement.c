#include<stdio.h>
/*#define max 20*/

void optimal(int arr[20],int n,int size)
{
    //declare frames as array to store the page string
    int frames[n],i,j;
    //initilaized all the frames to -1 to keep track
    for(i=0;i<n;i++)
       frames[i] = -1;
    //index to insert elements
    int index = -1;
    //initialize page miss and page hits
    int page_miss=0,page_hit=0;
    
    //pointer or flag to indicate initially frames are filled out or not
    int full=0;
    
    //traversing each symbol
    for(i=0;i<size;i++){
        int symbol = arr[i];
        int flag =0;
        
        for(j=0;j<n;j++){
            if (symbol==frames[j])
            {
                flag=1;
                break;
            }
        }
        
        if (flag==1)
        {
            printf("\nSymbol: %d  Frame: ",symbol);
            for (int j=0;j<n;j++)
                printf("%d ",frames[j]);
            page_hit+=1;
        }
        
        else
        {
            //Frames are still empty
            if (full==0)
            {
                index=(index+1)%n;
                frames[index]=symbol;
                page_miss+=1;
                printf("\nSymbol: %d  Frame: ",symbol);
                for (int j=0;j<n;j++)
                    printf("%d ",frames[j]);

                //Frames filled or not
                if (i==n-1)
                    full=1;
            }
            //Frames are full, then apply optimal page replacement
            else
            {
                //First find the index to replace with
                int pos=-1;
                int index=-1;

                //Traversing each symbol and checking their optimal possibility
                for(int j=0;j<n;j++)
                {
                    //Whether symbol in frame found or not in future cached frame
                    int found=0;
                    for (int k=i+1;k<size;k++)
                    {
                        //If symbol exists in cached string
                        if (frames[j]==arr[k])
                        {
                            found=1;
                            if (pos<k)
                            {
                                pos=k;
                                index=j;
                            }
                            break;
                        } 
                    }
                    //Symbol does not exist in cached frame
                    if (found==0)
                    {
                        pos=size;
                        index=j;
                    }
                }

                //Now assign symbol in lru position
                frames[index]=symbol;

                printf("\nSymbol: %d  Frame: ",symbol);
                for (int j=0;j<n;j++)
                    printf("%d ",frames[j]);
            }
        }
    }
    printf("\nPage hits: %d",page_hit);
    printf("\nPage misses: %d",page_miss);
}


int main(){
    int arr[20],i,j,size,n;
    
    printf("enter the size of array(string) :");
    scanf("%d",&size);
    
    printf("\nenter the string elements :");
    for(i=0;i<size;i++){
        printf("\nenter string %d :",i);
        scanf("%d",&arr[i]);
    }
    
    /*printf("\nelements are:");
    for(i=0;i<size;i++){
        printf("%d ", arr[i]); 
    }*/
    
    printf("enter no.of frames :");
    scanf("%d",&n);
    
    optimal(arr,n,size);
}
