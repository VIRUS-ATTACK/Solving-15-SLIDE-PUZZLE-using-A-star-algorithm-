#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define N 4
//here we are solving 15 slide puzzle using A* algorithm where
//heuristic h(n)=sum of manhattan distances of all the blocks or estimated cost to goal from n
//shortest distance till the current state is g(n) or cost so far to reach n
//estimated total cost of path through n is f(n) where f(n) = g(n) + h(n)

// defining a structure of a node to store the sliding puzzle,its cost(sum of manhattan distances of all the blocks = g(n)),level h(n),blank block coordinates
typedef struct Node
{
    struct Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
}Node;

//defining a structure of a node of a binary tree
typedef  struct Bstree{
    int data;
    int ton;
    struct Bstree *left;
    struct Bstree *right;
    Node *Slidenode;
}Bstree;

//linked list to store binary digits of a number
typedef struct lin_list{
    int data;
    struct lin_list *next;
}lin_list;

int time=0,space=0;
//converting a given number into binary digits and storing them into a linked
lin_list *binary(int i){
    lin_list *head=NULL;
    while(i!=0){
        lin_list *ptr=(lin_list*)malloc(sizeof(lin_list));
        ptr->data=i%2;
        ptr->next=NULL;
        i=i/2;
        ptr->next=head;
        head=ptr;
    }
    return head;
}

//swaping data between two nodes
void swapData(Bstree *temp1,Bstree *temp2){
    Node *temp3;
    temp3=temp1->Slidenode;
    temp1->Slidenode=temp2->Slidenode;
    temp2->Slidenode=temp3;
}

//recursive function for bubbling the nodes based on comparison of (level g(n) + cost h(n)) of each matrix.
void BubbleDown(Bstree *node){
    Bstree *smallestNode;
    if(node==NULL){
        return;
    }
    if(node->left!=NULL && ((node->left->Slidenode->cost + node->left->Slidenode->level) < (node->Slidenode->cost + node->Slidenode->level))){
        //printf("\n%d????????????????????\n",node->left->Slidenode->cost);
        smallestNode=node->left;
        swapData(node,smallestNode);
        BubbleDown(smallestNode);
    }
    if(node->right!=NULL && ((node->right->Slidenode->cost +  node->right->Slidenode->level) < (node->Slidenode->cost + node->Slidenode->level))){
        //printf("\n%d&&&&&&&&&&&&&&&&&&&&\n",node->right->Slidenode->cost);
        smallestNode=node->right;
        swapData(node,smallestNode);
        BubbleDown(smallestNode);
    }
}

//function for heapifying of a complete binary tree
void heapify(Bstree *root){
    if (root == NULL) {
        return;
    }
    heapify(root->left);
    heapify(root->right);
    BubbleDown(root);
}

//function for finding the total no of inversion pairs  
int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++)
    {
        for (int j = i + 1; j < N * N; j++)
        {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}
 
//function to find the position of blank slide from bottom of the matrix
int findXPosition(int puzzle[N][N])
{
    for (int i = N - 1; i >= 0; i--){
        for (int j = N - 1; j >= 0; j--){
            if (puzzle[i][j] == 0){
				return N - i;
			}
		}
	}
}

//function for checking whether a given matrix is solvable or not based on inversion pairs technique
int isSolvable(int puzzle[N][N])
{
    int invCount = getInvCount((int*)puzzle);
    if (N & 1)
        return !(invCount & 1);
 
    else   
    {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}

//function for deleting the root node of a binary tree and placing the last node of the tree in place of the root node(log(n) operation)
Bstree* pop(Bstree *root){
    Bstree *left=root->left;
    Bstree *right = root->right;
    Bstree *temp=(Bstree*)malloc(sizeof(Bstree)),*temp1=root;
    lin_list *Binaryno=NULL;
    Binaryno=binary(root->ton);
    Binaryno=Binaryno->next;
    if(root->left == NULL && root->right == NULL){
        return NULL;
    }
    else{
        while(Binaryno->next){
            if(Binaryno->data==0){
                temp1=temp1->left;
            }
            else if(Binaryno->data==1){
                temp1=temp1->right;
            }
            Binaryno=Binaryno->next;
        }
        if(Binaryno->data==0){
            temp=temp1->left;
            temp1->left=NULL;
        }
        else if(Binaryno->data==1){
            temp=temp1->right;
            temp1->right=NULL;
        }
        temp->left = root->left;
        temp->right = root->right;
        temp->ton=root->ton - 1;
        free(root);
    }
    return temp;
}

//function for inserting nodes into the binary tree(log(n) operation).
Bstree *push(Bstree *Btree,Node *root){
    lin_list *Binaryno=NULL;
        Bstree *temp=(Bstree*)malloc(sizeof(Bstree)),*temp1=Btree;
        temp->Slidenode=root;
        temp->left=NULL;
        temp->right=NULL;
        
        if(Btree!=NULL){
            Btree->ton=Btree->ton + 1;
            Binaryno=binary(Btree->ton);
            Binaryno=Binaryno->next;
        }
       
        
        if(Btree==NULL){
            Btree=temp;
            Btree->ton = 1;
        }
        else{
            
            while(Binaryno->next){
                if(Binaryno->data==0){
                    temp1=temp1->left;
                }
                else if(Binaryno->data==1){
                    temp1=temp1->right;
                }
                Binaryno=Binaryno->next;
            }
            if(Binaryno->data==0){
                temp1->left=temp;
            }
            else if(Binaryno->data==1){
                temp1->right=temp;
            }
        }
        
    return Btree;
}

//function for copying data to the child matrix
void matcpy(int child[N][N],int parent[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            child[i][j]=parent[i][j];
        }
    }
}

//function for swapping the blank tile of the newly generates child matrix with respective the parent matrix 
//oldX,oldY represents old coordinates and newX,newY represents the new coordinates
void swaptiles(int mat[N][N],int newX,int newY,int oldX,int oldY){
    int temp;
    temp = mat[oldX][oldY];
    mat[oldX][oldY]=mat[newX][newY];
    mat[newX][newY]=temp;
}

//function for calculating the sum of manhattan distances of the sliding puzzle
int calculateCost(int initial[N][N], int final[N][N])
{
    int sum = 0;
    for(int i=0;i<N;i++)
	    {
	        for(int j=0;j<N;j++)
	        {
	            for(int p=0;p<N;p++)
	            {
	                for(int q=0;q<N;q++)
	                {
                        if(initial[i][j] == final[p][q] && initial[i][j] != 0)
                        {
                            if(i>p)
                            {
                                sum = sum + i-p;
                            }
                            if(i<p)
                            {
                                sum = sum + p-i;
                            }
                            if(j>q)
                            {
                                sum = sum + j-q;
                            }
                            if(j<q)
                            {
                                sum = sum + q-j;
                            }
		                }   
	                }
	            }
	        }       
	    }
    return sum;
}

//function for creating the child node of 
Node* newNode(int mat[N][N], int x, int y, int newX,
    int newY, int level, Node* parent)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;

    matcpy(node->mat,mat);
    swaptiles(node->mat,newX,newY,x,y);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}

// Function to print N x N matrix
void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

//function to print the path of the sliding block solution 
void printPath(Node* root)
{
    if (root == NULL){
        return;
    }
    printPath(root->parent);
    printMatrix(root->mat);
 
    printf("\n");
}

//function to check wheteher the step is possible or not
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

//function to check whether two matrices are equal or not
int checkmatrix(int olist[N][N],int child[N][N]){
    int count=0;
   
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(olist[i][j]==child[i][j]){
                count++;
            }
        }
    }
    if(count == 16){
        return 1;
    }
    else{ 
        return 0;
    }
}

//function to check whether the child node already exist in openlist and if it exists the function will return values based on comparison
int findinopenlist(Bstree *olist,Node *child){
    
    if(olist==NULL){
        return 0;
    }
    if(checkmatrix(olist->Slidenode->mat,child->mat)){
        if(olist->Slidenode->cost+ olist->Slidenode->level > child->cost + child->level){
            olist->Slidenode->cost=INT_MIN;
            return 1;
        }
        else{
            return 2;
        }
    }
    
    findinopenlist(olist->left,child);
    findinopenlist(olist->right,child);
}

//function to check whether the child node already exist in closedlist and if it exists the function will return values based on comparison
int findclosedlist(Bstree *clist,Node *child){
    if(clist==NULL){
        return 0;
    }
    if(checkmatrix(clist->Slidenode->mat,child->mat)){
        if(clist->Slidenode->cost+ clist->Slidenode->level > child->cost + child->level){
            clist->Slidenode->cost=INT_MIN;
            return 1;
        }
        else{
            return 2;
        }
    }
    findclosedlist(clist->left,child);
    findclosedlist(clist->right,child);
}

//function for solving the 15 slide puzzle 
void solve(int initial[N][N],int final[N][N])
{
    int x,y;
    //finding the blank node position
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(initial[i][j]==0){
                x=i;
                y=j;
            }
        }
    }

    // botton, left, top, right
    int row[] = { 1, 0, -1, 0 };
    int col[] = { 0, -1, 0, 1 };

    Bstree *pq=NULL;                     //open list
    Bstree *clist=NULL;                  //closed list

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);

    //push the source node into the open list 
    pq=push(pq,root);
    time++;
    heapify(pq);
    //while openlist not empty
    while(pq)
    {
        Node* min = pq->Slidenode;
        clist = push(clist,min);
        //add the parent node from the closed list
        //delete the parent node from the openlist
        pq=pop(pq);
        //if the goal state is reached then H(n)==0 then print the path of the matrix
        //also print the total no of nodes generated which are equal to total no child nodes  
        //also print the toatl no of nodes present in the memory which is equal to total no of nodes in the open list + total no of nodes in the closed list
        if (min->cost == 0)
        {
            printf("\n------------------------------------path---------------------------------\n");
            printPath(min);
            printf("\nnumber of nodes generated:%d\n",time);
            printf("\nnumber of nodes present in the memory:%d\n",pq->ton+clist->ton);
            return;
        }

        //for min node move the blank slide to all possible directions(max possible=4) and add the children to the open list if the conditions are satisfied
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                // botton, left, top, right
                //int row[] = { 1, 0, -1, 0 };
                //int col[] = { 0, -1, 0, 1 };

                //create a child node
                Node* child = newNode(min->mat, min->x,
                            min->y, min->x + row[i],
                            min->y + col[i],
                            min->level + 1, min);
                //calculate cost(h(n)) of the child node
                child->cost = calculateCost(child->mat, final);
                int ono=0,cno=0;

                //if pq not equal to null then check whether the child node exist in openlist or not
                if(pq!=NULL){
                    ono=findinopenlist(pq,child);
                }

                //if clist not equal to null then check whether the child node exist in closedlist or not
                if(clist!=NULL){
                    cno = findclosedlist(clist,child);
                }
                
                //For each child m of n Do
                //If m has a duplicate in openlist, retain the cheaper one in OPEN and through off the other.
                if(ono==1){
                    heapify(pq);
                    pq = pop(pq);
                    pq = push(pq,child);
                    time++;
                }
                else if(ono==2){
                    ono = 2;
                    time++;
                    //printf("node not generated\n");
                }

                //For each child m of n Do
                //if new m is cheaper than than n then through off that m which is in CLOSED and keep the new m with its cost in OPEN
                //If new m has more cost then through off new m
                if(cno==1){
                    heapify(clist);
                    clist = pop(clist);
                    pq = push(pq,child);
                    time++;
                }
                else if(cno==2){
                    cno=2;
                    time++;
                }
                //For each child m of n 
                //If m is entirely new, add to OPEN.
                if(ono == 0 && cno ==0){
                    pq=push(pq,child);
                    time++;
                }
            }
        }
        heapify(pq);
    }
    //if openlist is empty then solution doesn't exist
    printf("solution doesn't exist");
}
//main function
int main(){
    int initial[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d",&initial[i][j]);
        }
    }
    //expected matrix
    int final[N][N] ={{1, 2, 3,4},{5, 6, 7,8},{9, 10, 11,12},{13, 14, 15, 0}};

    if(isSolvable){
        printf("solvable\n");
        solve(initial,final);
	}
	else{
		printf("unsolvable");
	}
    return 0;
}

