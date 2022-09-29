#include "struct.h"
#include "Base.h"
#include "advanced_search.h"

//purpose: in case of typo 
//registered courses: biology-economics-PE-philosophy-physics
//search: bi, bo, etc.
//result: biology

int max(int a, int b){
    if(a>=b)
        return a;
    else
        return b;
}

//LCS_num: how many letters cmp_course_name has identical to targeted_course_name
//course_name: cmp_course_name
struct a_found_course *create_node_for_tree(int LCS_num, char course_name_[MAX_WORD]){
    struct a_found_course *new_node = (struct a_found_course *)malloc(sizeof(struct a_found_course));
    new_node->LCS_num = LCS_num;
    strcpy(new_node->course_name, course_name_);
    new_node->left = new_node->right = NULL;
    return new_node;
}

void create_tree(struct a_found_course* root, int LCS_num, char course_name[MAX_WORD]){
    //LCS_num: how many letters cmp_course_name has are identical to targeted_course_name
    //course_name: cmp_course_name

    struct a_found_course* temp = root;

    if(temp==NULL){
        temp = create_node_for_tree(LCS_num, course_name);
    }

    //arranged by LCS_num
    else if(LCS_num<temp->LCS_num){
        return create_tree(temp->left, LCS_num, course_name);
    }
    
    else if(LCS_num>temp->LCS_num){
        return create_tree(temp->right, LCS_num, course_name);
    }    
    
    //when LCS_nums resemble, the order would be based on the length of the name of the course
    else{

        if(strlen(course_name) > strlen(temp->course_name)){
            if (temp->left != NULL){// insert
                new_->left = temp->left;
                temp->left = create_node_for_tree(LCS_num, course_name);;
            }
            else{
                temp->left = create_node_for_tree(LCS_num, course_name);;
            }
        }

        else{
            if (temp->right != NULL){
                new_->right = temp->right;
                temp->right = create_node_for_tree(LCS_num, course_name);;
            }
            else{
                temp->right = create_node_for_tree(LCS_num, course_name);;
            }
        }

    }
    *root = temp;
}

//reverse: to print out the most matched courses
char* inorder_traversal_reverse(struct a_found_course* root){
    struct a_found_course *temp = root;

    if(temp!=NULL){
        inorder_traversal_reverse(temp->right);
        if(inorder_traversal_reverse(temp->right)){
            return inorder_traversal_reverse(temp->right);
        }
        else
            return temp->course_name;
    }

    return NULL;
}

//targeted_course_name: users search for the details of the course, biology, but miss some letter, so it might be bi, bo, etc.
//find_course func: to search for the most matched course name according to targeted_course_name
//algo: LCS
char* find_courses(char* targeted_course_name, Course *head){
    int i, j; 
    int targeted_course_len = strlen(targeted_course_name);
    struct a_found_course *start = NULL;

    for (Course *temp = head->next; temp != NULL; temp=temp->next){ 
        int cmp_course_len = strlen(temp->course_name);
        char cmp_course_name[cmp_course_len]; //cmp_course_name: course name in the registered list. compare one by one
        strcpy(cmp_course_name, temp->course_name);

        //square[targeted_course_len][cmp_course_len] will turn out recording how many letters cmp_course_name has are identical to targeted_course_name
        //targeted_course_name: phs
        //cmp_course_name: physics
        //square[targeted_course_len][cmp_course_len]: 3 
        int square[targeted_course_len+1][cmp_course_len+1];

        for (i = 0; i < targeted_course_len+1; i++)
            square[i][0] = 0; //initialization
        for (j = 0; j < cmp_course_len+1; j++)
            square[0][j] = 0;

        for (i = 1; i < targeted_course_len+1; i++){
            for (j = 1; j < cmp_course_len+1; j++){
                if (tolower(targeted_course_name[i-1])==tolower(cmp_course_name[j-1])){ //course name upper case for example abbreviation
                    square[i][j] = square[i - 1][j - 1] + 1;
                }
                else {
                    square[i][j] = max(square[i][j - 1], square[i - 1][j]);
                }
            }
        }

        //put into a binary tree to find the most matched course name in the registered list
        //the binary tree is created according to the result of square[targeted_course_len][cmp_course_len]
        if(square[i-1][j-1]>0){
            create_tree(&start, square[i-1][j-1], cmp_course_name);
        }
    }

    //to get the most right child in the tree (to get the most matched course name in the registered list)
    //search: phs
    //result of LCS algo: physics & phiolophy
    //result of sorting: physics
    return inorder_traversal_reverse(start);
}
//review: just need to keep the the most match course name and the number of identical number

//to print out the most matched course name according to the input
//and ask if it is identical to user's target
Course* advanced_search(Course *head, char *targeted_course_name){
    char Y_N[3];
    char found[MAX_WORD];
    Course *p = NULL;
    p = search(head, targeted_course_name);

    //if the input is with typo or incomplete
    if (p == NULL && find_courses(targeted_course_name, head)!=NULL)
    {
        strcpy(found, find_courses(targeted_course_name, head));
        printf("did u mean: %s\n", found);
        printf("enter Y/N:");
        scanf("%s", Y_N);
        if (tolower(Y_N[0])=='y'){
            p = search(head, found);
            return p; 
        }
    }
    return p;
}
