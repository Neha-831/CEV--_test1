#include<stdio.h>
int main()
{
int array[50],position,c,n,value;
printf("enter no of elements in the array\n");
scanf("%d",&n);
printf("enter %d elements\n",n);
for(c=0;c<n;c++)
scanf("%d",&array[c]);
printf("please enter the location where you want to insert an new element\n");
scanf("%d",&position);
printf("please enter the value\n");
scanf("%d",&value);
for(c=n;c>=position-1;c--)
array[c+1]=array[c];
array[position-1]=value;
printf("resultant array is \n");
for(c=0;c<=n;c++)
printf("%d\n",array[c]);
return 0;
}
