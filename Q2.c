/*
Patrick Copp
1007602
3490A4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct word {
	char text[25];
  int count;
	double probability;
	struct word *leftTree;
	struct word *rightTree;
}words;

void print( words * head );
int isItIn(char *buffer,words *all [2045],int count);
void clearBuffer(char * buffer);
void greedyAlgorithm(words *all [],words *bst [],int n,int q,int r);
int compare(const void *s1, const void *s2);
words* sortedArrayToBST(words * arr[], int start, int end);
void printInorder(words* node);
words* search(words* root, char * key);




int main()
{
  FILE *fp=fopen("data_7.txt","r");
  words *allWords [2045];
  for(int i=0;i<2045;i++)
  {
    allWords[i]=malloc(sizeof(words));
  }
  char *buffer=malloc(30);
  int hold=1,count=0,count2=0,lastchar=1; //0 means letter was last

  //reads all words into allWords
  while (fp!=NULL && hold>-1 && hold<128)
  {
    if((hold>64 && hold<91) || (hold>96 && hold<123))
    {
      lastchar=0;
      buffer[count]=hold;
      count++;
    }
    else if(lastchar==0)
    {

      strcpy(allWords[count2]->text,buffer);
      clearBuffer(buffer);
      count2++;
      count=0;
      lastchar=1;
    }
    hold=fgetc(fp);
  }

  words *all [600];
  for(int i=0;i<600;i++)
  {
    all[i]=malloc(sizeof(words));
  }
  int newCount=0;
  for(int i=0;i<2045;i++)
  {
    int in=isItIn(allWords[i]->text,all,newCount);
    if(in==-1)
    {
      strcpy(all[newCount]->text,allWords[i]->text);
      all[newCount]->count=1;
      newCount++;
    }
    else
    {
      all[in]->count+=1;
    }
  }

  //sets probability
  qsort(all,600,sizeof(words*),compare);
  for(int i=0;i<600;i++)
  {
    //printf("%s ",all[i]->text);
    all[i]->probability=(float)all[i]->count/2045;
    all[i]->leftTree=NULL;
    all[i]->rightTree=NULL;
    if(strcmp("of",all[i]->text)==0)
    {
      //printf("of: %lf",all[i]->probability);
    }
  }



  words* root=sortedArrayToBST(all, 0, 599);
  //printf("\n%s %lf\n",root->text,root->probability);
  //printf("%s %lf\n",root->leftTree->text,root->leftTree->probability);
  //printf("%s %lf\n",root->rightTree->text,root->rightTree->probability);
  //printInorder(root);

  printf("Enter a word to search for: ");
  char user[30];
  scanf("%[^\n]%*c", user);

  words *hi=search(root,user);

  if(hi==NULL)
  {
    printf("Could not find.\n");
  }


  return 0;
}
//finds if word is duplicated
int isItIn(char *buffer,words *allWords[2045],int count)
{
  for(int i=0;i<count;i++)
  {
    if(strcmp(allWords[i]->text,buffer)==0)
    {
      //printf("duplicate %s\n",buffer);
      return i;
    }
  }
  return -1;
}
//clears
void clearBuffer(char * buffer)
{
  for(int i=0;i<30;i++)
  {
    buffer[i]='\0';
  }
}


int compare(const void *s1, const void *s2)
{
  const words *a=*(const void **)s1;
  const words *b=*(const void **)s2;
  if(strcmp(a->text,b->text)>0)
  {
    return 1;
  }
  else if(strcmp(a->text,b->text)<0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

/*void greedyAlgorithm(words *all [],words *bst [],int n,int q,int r)
{
  printf("Q: %d\n",q);
  printf("N: %d\n",n);
  printf("R: %d\n",r);

  if(n<1)
  {
    printf("n<1\n\n");
    return;
  }
  if(n==1)
  {
    printf("n=1\n\n");
    bst[r]=all[0];
    return;
  }

  double maxProb=0;
  int largest=-1;
  for(int i=q;i<n;i++)
  {
    if(all[i]->probability>maxProb)
    {
      maxProb=all[i]->probability;
      largest=i;
    }
  }
  printf("Highest: %d\n\n",largest);

  words *bstLeft [largest-1];
  for(int i=q;i<largest-1;i++)
  {
    bstLeft[i]=malloc(sizeof(words));
    bstLeft[i]=all[i];
  }
  words *bstRight [n-largest];
  for(int i=largest+1;i<n;i++)
  {
    bstRight[i]=malloc(sizeof(words));
    bstRight[i]=all[i];
  }

  bst[r]=all[largest];
  //bst[n*2+1]=greedyAlgorithm(bstLeft,bst,largest-1);
  //bst[n*2+2]=greedyAlgorithm(bstRight,bst,n-largest);
  printf("left\n");
  greedyAlgorithm(bstLeft,bst,largest-1,q,2*r+1);
  printf("right\n");
  greedyAlgorithm(bstRight,bst,n-largest+1,largest+1,2*r+2);


}*/

/*
	calcBST(word[n], probability[n], BST[n])
		for i (0 to n - 1)
			if (probability[i] > largest)
				largest = i

		add word[largest] to correct index of BST
		calcBST(word[0 -> largest - 1], probability[0 -> largest - 1], BST[n])
		calcBST(word[largest + 1, n], probability[largest + 1, n], BST[n])

*/
void printInorder(words* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->leftTree);

    /* then print the data of node */
    printf("%s ",node->text);

    printInorder(node->rightTree);
}

//places elements into tree
words* sortedArrayToBST(words * arr[], int start, int end)
{
  //printf("Start:\t%d\n",start);
  //printf("End\t%d\n",end);
    if (start > end)
    {
      return NULL;
    }
    if(start==end)
    {
      //printf("Start=end, returning\n");
      return arr[start];
    }


    /* Get the middle element and make it root */
    double maxProb=0;
    int mid=-1;
    for(int i=start;i<end;i++)
    {
      if(arr[i]->probability>maxProb)
      {
        maxProb=arr[i]->probability;
        mid=i;
      }
    }
    //printf("Largest:\t%d\n",mid);
    words *root = arr[mid];

    /* Recursively construct the left subtree
    and make it left child of root */
    root->leftTree = sortedArrayToBST(arr, start,mid - 1);

    /* Recursively construct the right subtree
    and make it right child of root */
    root->rightTree = sortedArrayToBST(arr, mid + 1, end);

    return root;
}
//searches tree
words* search(words* root, char * key)
{
    // Base Cases: root is null or key is present at root

    if (root == NULL)
    {
      printf("Not found.\n");
      return root;
    }

    if(strcmp(root->text,key)==0)
    {
      printf("Compared with %s (%lf), found\n",root->text,root->probability);
      return root;
    }


    // Key is greater than root's key
    if (strcmp(root->text,key)<0)
    {
      printf("Compared with %s (%lf), go right subtree\n",root->text,root->probability);
      return search(root->rightTree, key);
    }


    // Key is smaller than root's key
    printf("Compared with %s (%lf), go left subtree\n",root->text,root->probability);
    return search(root->leftTree, key);
}





//dsds
