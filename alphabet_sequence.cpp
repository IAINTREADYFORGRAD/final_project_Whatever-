#include "struct.h"
#include "alphabet_sequence.h"
//sort by alphabet
//then the course sequence will be like
//biology-economics-PE-philosophy-physics

//count the how many courses have been registered
int count_courses(Course *head){
    Course *temp = head;
    int count=0;
    for (; temp->next != NULL; temp=temp->next){
        count++;
    }
    return count;
}

void insert_course(Course* head, Course* be_inserted, Course* to_insert){

    //keep the track of previous node so as to insert a new node
    Course *be_pre = head; //pre node of be_inserted node
    Course *to_pre = head;  //pre node of to_insert node

    //if the course a user intending to insert has existed in the record, do nothing 
    if (be_inserted==to_insert){ 
        return;
    }
    
    //to get previous nodes of both needed to be inserted and being inserted
    for (; be_pre->next != be_inserted; be_pre = be_pre->next) 
        continue;

    for (; to_pre->next!=to_insert; to_pre=to_pre->next)
        continue;

    //insert
    to_pre->next = to_insert->next;
    to_insert->next = be_inserted;
    be_pre->next = to_insert;
}

//to decide the order of courses
//course name a: physics
//course name b: philosophy
//philosophy will be listed before physics
int cmp_letter (Course* a, Course* b){
    char a_name[MAX_WORD];
    strcpy(a_name, a->course_name);
    char b_name[MAX_WORD];
    strcpy(b_name, b->course_name);
    int i = 0;

    //all convert to lowercase
    int a_len = strlen(a_name);
    for (int j = 0; j < a_len; j++)
    {
        a_name[j] = tolower(a_name[j]);
    }

    int b_len = strlen(b_name);
    for (int j = 0; j < b_len; j++)
    {
        b_name[j] = tolower(b_name[j]); 
    }

    //to find the different letter location
    //a_name: physics vs b_name: philosophy
    //to get a_name[i]=y, b_name[i]=i
    for (; i < MAX_WORD; i++)
    {
        if (a_name[i] != b_name[i]){
            break;
        }
    }

    //to compare letters at the location [i]
    if(a_name[i]>=b_name[i] || b_name[i]=='\r'){ // b_name will precede a_name 
        return 0;
    }

    else if (a_name[i]<b_name[i] || a_name[i]=='\r'){ // b_name will be after a_name
        return 1;
    }

    return 1;
}

//qsort
int binary_search(Course* head, int low, int high, Course* to_insert_node){
    //low: the 1st node of sorted list / the 1st node of sorted list that has not made comparison with node needing to be inserted
    //high: the last node of sorted list

    //head storing nothing. database starting at head->next
    Course *temp_mid = head->next; 

    int return_val; 

    //when ASCII code of to_insert_node's course name is greater than every node except for the last node in the sorted list
    //to make the comparison of to_insert_node & last node
    if (low >= high){   

        //get the last node of the sorted list
        Course *last_node = head->next;
        for (int i = 0; i < low; i++){
            last_node = last_node->next;
        }

        // if cmp_letter == 1, b_name will be after a_name
        // to_insert_node needs to be after last node of the sorted list
        if(cmp_letter(last_node, to_insert_node)){ 
            return low + 1;
        }

        else{
            return low;
        }
    }
    else{ 
        int mid = (low + high) / 2; 
        for (int i = 0; i < mid; i++){
            temp_mid = temp_mid->next;
        }

        //if cmp_letter = 0, b_name will precede a_name
        if(!cmp_letter(temp_mid, to_insert_node)){ 
            return_val=binary_search(head, low, mid - 1, to_insert_node);
        }

        if(cmp_letter(temp_mid, to_insert_node)){
            return_val=binary_search(head, mid + 1, high, to_insert_node);
        }
    }

    return return_val; //return the location to_insert_node need to be placed
}

void alphabet_sequence (Course *head){
    int count = count_courses(head);
    int loc;
    Course *to_insert_node, *temp;

    //insertion sort
    for (int i = 0; i < count-1; i++){
        to_insert_node=head->next; //head storing nothing. database starting at head->next
        for (int j = 0; j < i + 1; j++){ //to get the 1st node in the unsorted list
            to_insert_node = to_insert_node->next;
        }
        
        loc=binary_search(head, 0, i, to_insert_node); //get the location the course needing to insert into the sorted part of list
        temp = head->next; 
        for (int j = 0; j < loc; j++){
            temp = temp->next;
        }
        insert_course(head, temp, to_insert_node);
    }
}

