/******************************fifio pagereplacement algorithm******************************/
#include<stdio.h>


void fifo(int arr[20],int n,int size){
    //Creating array for block storage
    int frames[n];
    //Initializing each block with -1
    for (int i=0;i<n;i++)
        frames[i]=-1;

    //Index to insert element
    int index=-1;

    //Counters Initializing page_miss and page_miss
    int page_miss=0;
    int page_hits=0;

    //Traversing each symbol in fifo
    for (int i=0;i<size;i++)
    {
        int symbol=arr[i];
        int flag=0;
        //traversing another loop to search and insert the elements
        for(int j=0;j<n;j++)
        {
            //if there is element from string is already in memory the set flag to 1
            if (symbol==frames[j])
            {
                flag=1;
                break;
            }
        }
        //this means when th flag is set to 1 there is page hit the element is already in memory
        //increase the page_hit counter
        if (flag==1)
        {
            //display the symbol and Frames
            printf("\nSymbol: %d  Frame: ",symbol);
            for (int j=0;j<n;j++)
                printf("%d ",frames[j]);
            page_hits+=1;
        }
        else
        {
            //is the memory is empty the add the string elements in it 
            index=(index+1)%n;//starting for the starting of the memory array
            frames[index]=symbol;//assign symbol to frames[index] which have been just fiiled with single element of the loop
            page_miss+=1;//this is page_miss since we entered the element which was not in the memory
            //display the symbol and Frames
            printf("\nSymbol: %d  Frame: ",symbol);
            for (int j=0;j<n;j++)
                printf("%d ",frames[j]);
        }
    }
    //calcualate the page_miss and page_hits
    printf("\nPage hits: %d",page_hits);
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
    
    printf("\nelements are:");
    for(i=0;i<size;i++){
        printf("%d ", arr[i]); 
    }
    
    printf("\nenter no.of frames :");
    scanf("%d",&n);
    
    fifo(arr,n,size);
}