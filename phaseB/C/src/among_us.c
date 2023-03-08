/***************************************************
 *                                                 *
 * file: among_us.c                                *
 *                                                 *
 * @Author  Skerdi Basha                           *
 * @Version 1-12-2020                              *
 * @email   sbash@csd.uoc.gr                       *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */

#include "among_us.h"

unsigned int primes_g[650] = { 
                                 179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
                                 233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
                                 283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
                                 353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
                                 419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
                                 467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
                                 547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
                                 607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
                                 661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
                                 739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
                                 811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
                                 877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
                                 947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013, 
                                1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069, 
                                1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151, 
                                1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223, 
                                1229,   1231,   1237,   1249,   1259,   1277,   1279,   1283,   1289,   1291, 
                                1297,   1301,   1303,   1307,   1319,   1321,   1327,   1361,   1367,   1373, 
                                1381,   1399,   1409,   1423,   1427,   1429,   1433,   1439,   1447,   1451, 
                                1453,   1459,   1471,   1481,   1483,   1487,   1489,   1493,   1499,   1511, 
                                1523,   1531,   1543,   1549,   1553,   1559,   1567,   1571,   1579,   1583, 
                                1597,   1601,   1607,   1609,   1613,   1619,   1621,   1627,   1637,   1657, 
                                1663,   1667,   1669,   1693,   1697,   1699,   1709,   1721,   1723,   1733, 
                                1741,   1747,   1753,   1759,   1777,   1783,   1787,   1789,   1801,   1811, 
                                1823,   1831,   1847,   1861,   1867,   1871,   1873,   1877,   1879,   1889, 
                                1901,   1907,   1913,   1931,   1933,   1949,   1951,   1973,   1979,   1987, 
                                1993,   1997,   1999,   2003,   2011,   2017,   2027,   2029,   2039,   2053, 
                                2063,   2069,   2081,   2083,   2087,   2089,   2099,   2111,   2113,   2129, 
                                2131,   2137,   2141,   2143,   2153,   2161,   2179,   2203,   2207,   2213, 
                                2221,   2237,   2239,   2243,   2251,   2267,   2269,   2273,   2281,   2287, 
                                2293,   2297,   2309,   2311,   2333,   2339,   2341,   2347,   2351,   2357, 
                                2371,   2377,   2381,   2383,   2389,   2393,   2399,   2411,   2417,   2423, 
                                2437,   2441,   2447,   2459,   2467,   2473,   2477,   2503,   2521,   2531, 
                                2539,   2543,   2549,   2551,   2557,   2579,   2591,   2593,   2609,   2617, 
                                2621,   2633,   2647,   2657,   2659,   2663,   2671,   2677,   2683,   2687, 
                                2689,   2693,   2699,   2707,   2711,   2713,   2719,   2729,   2731,   2741, 
                                2749,   2753,   2767,   2777,   2789,   2791,   2797,   2801,   2803,   2819, 
                                2833,   2837,   2843,   2851,   2857,   2861,   2879,   2887,   2897,   2903, 
                                2909,   2917,   2927,   2939,   2953,   2957,   2963,   2969,   2971,   2999, 
                                3001,   3011,   3019,   3023,   3037,   3041,   3049,   3061,   3067,   3079, 
                                3083,   3089,   3109,   3119,   3121,   3137,   3163,   3167,   3169,   3181, 
                                3187,   3191,   3203,   3209,   3217,   3221,   3229,   3251,   3253,   3257, 
                                3259,   3271,   3299,   3301,   3307,   3313,   3319,   3323,   3329,   3331, 
                                3343,   3347,   3359,   3361,   3371,   3373,   3389,   3391,   3407,   3413, 
                                3433,   3449,   3457,   3461,   3463,   3467,   3469,   3491,   3499,   3511, 
                                3517,   3527,   3529,   3533,   3539,   3541,   3547,   3557,   3559,   3571, 
                                3581,   3583,   3593,   3607,   3613,   3617,   3623,   3631,   3637,   3643, 
                                3659,   3671,   3673,   3677,   3691,   3697,   3701,   3709,   3719,   3727, 
                                3733,   3739,   3761,   3767,   3769,   3779,   3793,   3797,   3803,   3821, 
                                3823,   3833,   3847,   3851,   3853,   3863,   3877,   3881,   3889,   3907, 
                                3911,   3917,   3919,   3923,   3929,   3931,   3943,   3947,   3967,   3989, 
                                4001,   4003,   4007,   4013,   4019,   4021,   4027,   4049,   4051,   4057, 
                                4073,   4079,   4091,   4093,   4099,   4111,   4127,   4129,   4133,   4139, 
                                4153,   4157,   4159,   4177,   4201,   4211,   4217,   4219,   4229,   4231, 
                                4241,   4243,   4253,   4259,   4261,   4271,   4273,   4283,   4289,   4297, 
                                4327,   4337,   4339,   4349,   4357,   4363,   4373,   4391,   4397,   4409, 
                                4421,   4423,   4441,   4447,   4451,   4457,   4463,   4481,   4483,   4493, 
                                4507,   4513,   4517,   4519,   4523,   4547,   4549,   4561,   4567,   4583, 
                                4591,   4597,   4603,   4621,   4637,   4639,   4643,   4649,   4651,   4657, 
                                4663,   4673,   4679,   4691,   4703,   4721,   4723,   4729,   4733,   4751, 
                                4759,   4783,   4787,   4789,   4793,   4799,   4801,   4813,   4817,   4831, 
                                4861,   4871,   4877,   4889,   4903,   4909,   4919,   4931,   4933,   4937, 
                                4943,   4951,   4957,   4967,   4969,   4973,   4987,   4993,   4999,   5003, 
                                5009,   5011,   5021,   5023,   5039,   5051,   5059,   5077,   5081,   5087, 
                                5099,   5101,   5107,   5113,   5119,   5147,   5153,   5167,   5171,   5179,
                            };
                         
 struct Task *temp;
 int j=0;
 struct Player *find_player2;
 struct Task* task_temp;
 struct Task* prev;
int alien_count,crewmate_count;


/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    struct General_Tasks_HT* new_GL =(struct General_Tasks_HT*) malloc(sizeof(struct General_Tasks_HT));
    general_tasks_ht = new_GL;
    new_GL->count=0;
    int i;
    for(i=0; i<650; i++ ){
        if(max_tasks_g<primes_g[i]){
            p=primes_g[i];
            i=649;
        }
    }
    new_GL->tasks = (struct HT_Task**)malloc(sizeof(struct HT_Task)*p);

    struct Completed_Tasks_PQ* trash_task=(struct Completed_Tasks_PQ*) malloc(sizeof(struct Completed_Tasks_PQ));
    trash_task->size=0;
    completed_tasks_pq=trash_task;
    return 1;
}

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
    
    struct Player* new_player =(struct Player*) malloc(sizeof(struct Player));
    struct Player* temporary,*prev;
    
	new_player->pid=pid;
    new_player->is_alien=is_alien;
     
    if(players_tree == NULL){      //insert player at root
        players_tree = new_player;
        new_player->lc = NULL;
        new_player->rc = NULL;
        new_player -> parrent= NULL;
        return 1;
    }
    temporary = players_tree;
    
    while(temporary != NULL){  //traverse the tree to find null node
        prev = temporary;
        if(pid < temporary->pid){
            temporary = temporary->lc;
        }
        else if (pid > temporary->pid){
             temporary = temporary-> rc;
        }
    }

    if( new_player-> pid > prev-> pid){  //insert player at the leaf
        prev-> rc = new_player;
    }        
    else {
        prev->lc = new_player;
    }
    new_player->parrent = prev;  //doubly(set the prev player)
    players_count+=1;
    Player(players_tree);
    printf("DONE\n");
    return 1;
}


/**
 * @brief Insert Task in the general task hash table
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty) {
    struct HT_Task* new_task=(struct HT_Task*) malloc(sizeof(struct HT_Task*));
    struct General_Tasks_HT *temp = general_tasks_ht;
    struct HT_Task** temporary=temp->tasks;
    
    int call=0;
    call=h(tid);
    int position=0;
    position= call;
    
    temporary[p];

    new_task->tid = tid;
    new_task->difficulty = difficulty;

    if(temporary[position]==NULL){      //Insert tasks in General Hash Table
         temporary[position] = new_task;
    }
    else if (temporary+position !=NULL) {
        new_task->next = temporary[position];
        temporary[position]=new_task;
    }
    temp->count+=1;
    printf("DONE\n");
    return 1;
}   



/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() { 
    struct General_Tasks_HT* ht_head = general_tasks_ht;
    struct HT_Task *ht_temp;
    int i,metritis_task=0; 
    int thesi;
    struct Task *prev;
    struct Task* task_temp;

    for(i=0; i<p; i++){

        ht_temp = ht_head->tasks[i]; /*hold the first node of each chain stored in the hashtable*/
        while(ht_temp != NULL){

            thesi = metritis_task%players_count;     //Find the position for player to take the task//
            
            struct Task* distribute_task=(struct Task*) malloc(sizeof(struct Task));
            distribute_task->tid=ht_temp->tid;
            distribute_task->difficulty=ht_temp->difficulty;
            
            count=0;
            Inorder(players_tree,thesi);
            
            while(specific_player->is_alien==1 ){   //Check if the player was return if is alien find the next player
                if(thesi==players_count-1){
                    thesi=0;
                }
                count=0;
                thesi++;
                Inorder(players_tree,thesi);
            }
            if(specific_player->tasks==NULL){               //Distribute tasks in trees of players
                specific_player->tasks = distribute_task;
            }
            else{ 
                task_temp=specific_player->tasks;
                while(task_temp!=NULL){
                    prev=task_temp;
                    if(distribute_task->tid < task_temp->tid){
                       task_temp=task_temp->lc;
                    }
                    else {
                       task_temp=task_temp->rc;
                    }
                }
                if(distribute_task->tid < prev->tid){   
                prev->lc=distribute_task;
                prev->lcnt++; 
                }
                else {
                    prev->rc=distribute_task;
                }
            }
            distribute_given_tasks+=1;     
            metritis_task++;
            ht_temp= ht_temp->next; 
        }
    } 
    printf("DONE\n");
    return 1;
}


struct Task* minimumKey(struct Task *curr) {  //find minimum node in the right subtree 
        while(curr->lc!=NULL){
            curr=curr->lc;
        }
    return curr;
}


/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid) {
    struct Player* p_temporary=players_tree,*find_player;
    struct Task* t_temporary,*previous;
    struct Task *find_task;
    int flag=0,flag1=0;

    while(p_temporary!=NULL) {  //FIND THE PLAYER POU THA KANEI TO IMPLEMENT
        if(pid==p_temporary->pid){
            find_player=p_temporary;
            flag=1;
            break;
        }
        if(pid < p_temporary->pid){
            p_temporary=p_temporary->lc;
        }
        else if(pid > p_temporary->pid){
            p_temporary=p_temporary->rc;
        }
    }

    if(find_player->is_alien==1){  //CHECK IF THE FINDED PLAYER IS ALIEN
        return 1;
    }
    
    if(flag==0){  //Check if the player was not found!!!
        return 1;
    }
 
    if(find_player->tasks == NULL) {  //SE PERIPTOSI POU H TASK LIST TOU PLAYER EINAI NULL 
        return 1;
    }
    t_temporary=find_player->tasks;
    
    while(t_temporary!=NULL){              //Find the Task pou tha ginei implement
            if(tid==t_temporary->tid){
                find_task=t_temporary;
                flag1=1;
                break;
            }
            previous=t_temporary;
            if(tid < t_temporary->tid){
                t_temporary=t_temporary->lc;
            }
            else if(tid > t_temporary->tid){
                t_temporary=t_temporary->rc;
            } 
    }      
    
    if(flag1==0){ //Chceck if the task was not found!!!
        return 1;
    }

    struct HT_Task* new_trash=(struct HT_Task*) malloc(sizeof(struct HT_Task));
    new_trash->tid=find_task->tid;
    new_trash->difficulty=find_task->difficulty;

  /*if(completed_tasks->tasks[j]==NULL){
         completed_tasks->tasks[j] = new_trash;
    }
    else{
        completed_tasks->tasks[j++] = new_trash;
    }
    j++;
 */

    if(find_task->lc==NULL && find_task->rc==NULL){      //delete node without childs
       
        if (find_task != find_player->tasks) {
             printf("i dont have childs\n");
            if (previous->lc == find_task){
                previous->lc = NULL;
                free(find_task);
            }
            else{
                previous->rc = NULL;
                free(find_task);
            }  
            completed_tasks_pq->size++;  
        }
        // if tree has only root node, delete it and set root to null
        else{   
            printf("i dont have childs(ROOT)\n");      //Check for root
            find_player->tasks =NULL;
            free(find_player->tasks);
            completed_tasks_pq->size++;
        }
    }
    else if(find_task->rc==NULL && find_task->lc!=NULL){   //delete node with 1 child at the left 
           if(find_task!=find_player->tasks){
                if(find_task->rc!=NULL){
                    printf("i am on 1 left child(1)\n"); 
                    find_task=find_task->lc;
                    find_task->lc=NULL;
                    free(find_task->lc);
                    completed_tasks_pq->size++; 
                }
            }
            else if(find_task==find_player->tasks ){         //Check for root
                printf("i am on 1 left child and no others childs below(ROOT)\n");
                find_player->tasks=find_player->tasks->lc;
                find_task->lc=NULL;
                find_task=NULL;
                completed_tasks_pq->size++;
                free(find_task);
            }
    } 
   else if(find_task->rc!=NULL && find_task->lc==NULL){    //delete node with 1 child at the right
            if(find_task!=find_player->tasks){
                if(find_task->rc!=NULL){
                    printf("i am on 1 right child\n");
                    find_task=find_task->rc;
                    find_task->rc=NULL;
                    free(find_task->rc);
                    completed_tasks_pq->size++;
                }
            } 
            if(find_task==find_player->tasks ){          //check for root
                printf("i am on 1 right child and no others childs below(ROOT)\n");
                find_player->tasks=find_player->tasks->rc;
                find_player->tasks->rc=NULL;
                free(find_player->tasks->rc);
                completed_tasks_pq->size++;
            }
    } 
    else if(find_task->lc!=NULL && find_task->rc!=NULL){
        temp = minimumKey(find_player->tasks->rc);
        if(temp==NULL){
            return 1;
        }                     //check for internal node with 2 childs
        if(find_task!=find_player->tasks){
            if(temp->lc==NULL && temp->rc!=NULL){
                printf("i have 2 childs \n");
                find_task=temp;
                temp=temp->rc;
                temp->rc=NULL;
                free(temp->rc);
                completed_tasks_pq->size++;
            }
        }
        else if(find_task==find_player->tasks){            //check for root with 2 childs
            printf("i have 2 childs(ROOT)\n");
            if( temp->lc==NULL && temp->rc==NULL){
                find_player->tasks=temp;
                find_player->tasks->rc=NULL;
                free(find_player->tasks->rc);
                completed_tasks_pq->size++;
            }
        }
    } 
    print_double_tree();
    printf("DONE\n");
    return 1;
}


/**
 * @brief Eject Player
 * 
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2) {
    struct Player* p_temporary=players_tree,*find_player,*prev;
    struct Task* temp_task;
    int flag=0,flag1=0;

    while(p_temporary!=NULL) {  //FIND THE PLAYER POU THA GINEI EJECT
        if(pid_1==p_temporary->pid){
            find_player=p_temporary;
            flag=1;
            break;
        }
        prev=p_temporary;
        if(pid_1 < p_temporary->pid){
            p_temporary=p_temporary->lc;
        }
        else if(pid_1 > p_temporary->pid){
            p_temporary=p_temporary->rc;
        }
    }
    if(flag==0){        //Check if the player was not found!!!
        return 1;
    }

    temp_task=find_player->tasks;

  if(temp_task==NULL){
    if(find_player->lc==NULL && find_player->rc==NULL){      //delete node without childs
       
        if (find_player != players_tree) {
             printf("i dont have childs\n");
            if (prev->lc == find_player){
                prev->lc = NULL;
                free(find_player);
            }
            else{ 
                prev->rc = NULL;
                free(find_player);
            }  
        }
        // if tree has only root node, delete it and set root to null
        else{   
            printf("i dont have childs(ROOT)\n");      //Check for root
            players_tree =NULL;
            free(players_tree);
        }
    }
    else if(find_player->rc==NULL && find_player->lc!=NULL){ //delete node with 1 child at the left
        
            if(find_player!=players_tree){
                
                if(find_player->rc!=NULL){
                    printf("i am on 1 left child(1)\n"); 
                    struct Task *child = find_player->rc;
                    find_player=child;
                    child=NULL;
                    free(child);
                }
            }
            if(find_player==players_tree){         //Check for root
                printf("i am on 1 left child and no others childs below(ROOT)\n");
                players_tree=players_tree->lc;
                find_player->lc=NULL;
                find_player=NULL;
                free(find_player);
            }
    } 
   else if(find_player->rc!=NULL && find_player->lc==NULL){    //delete node with 1 child at the right
        struct Task *child = find_player->rc;
            if(find_player!=players_tree){
                if(find_player->rc!=NULL){
                    printf("i am on 1 right child\n");
                    players_tree->lc=find_player->rc;
                    find_player=find_player->rc;
                    child->rc=NULL;
                    free(child->rc);
                }
            } 
            if(find_player==players_tree){           //check for root
                printf("i am on 1 right child and no others childs below(ROOT)\n");
                players_tree=players_tree->rc;
                players_tree->rc=NULL;
                free(players_tree->rc);
            }
    } 
    else if(find_player->lc!=NULL && find_player->rc!=NULL){
        temp = minimumKey(find_player->tasks->rc);
        if(temp==NULL){
            return 1;
        }                             //check for internal node with 2 childs
        if(find_player!=players_tree){
            if(temp->lc==NULL && temp->rc!=NULL){
                printf("i have 2 childs \n");
                find_player=temp;
                temp=temp->rc;
                temp->rc=NULL;
                free(temp);
            }
        }
        else if(find_player==players_tree){                     //check for root with 2 childs
            printf("i have 2 childs and i have others childs\n");
            if( temp->lc==NULL && temp->rc==NULL){
                players_tree=temp;
                players_tree->rc=NULL;
                free(players_tree->rc);
            }
        }
    }
  } //END of the eject player if without tasks
  else{
      while(p_temporary!=NULL) {      //FIND THE PLAYER POU THA KANEI PAREI TA TASKS
        if(pid_2==p_temporary->pid){
            find_player2=p_temporary;
            flag1=1;
            break;
        }
        prev=p_temporary;
        if(pid_2 < p_temporary->pid){
            p_temporary=p_temporary->lc;
        }
        else if(pid_2 > p_temporary->pid){
            p_temporary=p_temporary->rc;
        }
    }
    if(flag1==0){
        return 1;
    }

    if(find_player2->tasks==NULL){          //if player with pid2 is without tasks then give the root of tasks from player with pid1
        find_player2->tasks=find_player->tasks;
        find_player->tasks=NULL;
    }
    else{
        task_temp=find_player2->tasks;
        traverseT1(find_player->tasks);  //call recursive function to merge trees
        if(find_player->lc==NULL && find_player->rc==NULL){      //delete node without childs
        if (find_player != players_tree) {
             printf("i dont have childs\n");
            if (prev->lc == find_player){
                prev->lc = NULL;
                free(find_player);
            }
            else{ 
                prev->rc = NULL;
                free(find_player);
            }  
        }
        // if tree has only root node, delete it and set root to null
        else{   
            printf("i dont have childs(ROOT)\n");      //Check for root
            players_tree =NULL;
            free(players_tree);
        }
    }
    else if(find_player->rc==NULL && find_player->lc!=NULL){ //delete node with 1 child at the left
            if(find_player!=players_tree){
                
                if(find_player->rc!=NULL){
                    printf("i am on 1 left child(1)\n"); 
                    struct Task *child = find_player->rc;
                    find_player=child;
                    child=NULL;
                    free(child);
                }
            }
            if(find_player==players_tree){         //Check for root
                printf("i am on 1 left child and no others childs below(ROOT)\n");
                players_tree=players_tree->lc;
                find_player->lc=NULL;
                find_player=NULL;
                free(find_player);
            }
    } 
   else if(find_player->rc!=NULL && find_player->lc==NULL){  //delete node with 1 child at the right
        struct Task *child = find_player->rc;
            if(find_player!=players_tree){
                if(find_player->rc!=NULL){
                    printf("i am on 1 right child\n");
                    players_tree->lc=find_player->rc;
                    find_player=find_player->rc;
                    child->rc=NULL;
                    free(child->rc);
                }
            } 
            if(find_player==players_tree){     //check for root
                printf("i am on 1 right child and no others childs below(ROOT)\n");
                players_tree=players_tree->rc;
                players_tree->rc=NULL;
                free(players_tree->rc);
            }
    } 
    else if(find_player->lc!=NULL && find_player->rc!=NULL){
        temp = minimumKey(find_player->tasks->rc);
        if(temp==NULL){
            return 1;
        }                          //check for internal node with 2 childs
        if(find_player!=players_tree){
            if(temp->lc==NULL && temp->rc!=NULL){
                printf("i have 2 childs \n");
                find_player=temp;
                temp=temp->rc;
                temp->rc=NULL;
                free(temp->rc);
            }
        }
        else if(find_player==players_tree){                     //check for root with 2 childs
            printf("i have 2 childs and i have others childs\n");
            if( temp->lc==NULL && temp->rc==NULL){
                players_tree=temp;
                players_tree->rc=NULL;
                free(players_tree->rc);
            }
        }
    }
   }

 }
    print_players();
    printf("DONE\n");
    return 1;
}

//Function to traverse pid_1_Tree and give tasks to pid_2_Tree
void traverseT1(struct Task* task) { 
     if (task == NULL) 
        return; 
  
    taskInorder(task->lc);          //Traverse the tree of player 1 and give the tasks to player 2

        while(task_temp!=NULL){
            prev=task_temp;
                if(task->tid < task_temp->tid){
                   task_temp=task_temp->lc;
                }
                else {
                   task_temp=task_temp->rc;
                }
        }
        if(task->tid < prev->tid){   
            prev->lc=task;
            prev->lcnt++; 
        }
        else {
            prev->rc=task;
        }
    taskInorder(task->rc); 
} 


/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 * 
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses){
    return 1;
}

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid) {
    return 1;
}

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence) {
    return 1;
}

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2) {
    return 1;
}


void countplayers(struct Player* player) { 
     if (player == NULL) 
          return; 
     /* first recursive on left child */
     countplayers(player->lc); 

    if(player->is_alien==1){
        alien_count+=1;
    }
    else{
        crewmate_count+=1;
    }
     /* now recursive on right child */
     countplayers(player->rc); 
} 

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {
    countplayers(players_tree);
    
    if(alien_count > crewmate_count){
        printf("Aliens Win. \n");
        return 1;
    }
    else if( alien_count==0 || alien_count < crewmate_count || distribute_given_tasks == completed_tasks_pq->size){
        printf("Crewmates Win. \n");
    }
    printf("\nDONE\n");
    return 1;
}

void Player(struct Player* player) {    //recursive function to print players
     
     if (player == NULL) 
          return; 

     /* first recur on left child */
     Player(player->lc); 

     /* then print the data of node */
     printf("player <%d : %d> ", player->pid,player->is_alien);   
     printf("\n");

     /* now recur on right child */
     Player(player->rc); 
} 

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
    Player(players_tree);
    printf("DONE\n");
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
    
    struct General_Tasks_HT* ht_head = general_tasks_ht;
    struct HT_Task* chain_head;
    int i;

    for(i=0; i<p; i++){

        chain_head = ht_head->tasks[i]; /*hold the first node of each chain stored in the hashtable*/

        printf("Index %d =" , i);

        while(chain_head != NULL){
            printf(" <%d:%d> ", chain_head->tid , chain_head->difficulty);
            chain_head = chain_head->next;
        }

        printf("\n");
        
    }
    // printf("Count = %d" , general_tasks_ht->count);
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
   /* int i=0;
    printf("Priority_Queue = ");
   	while (i < max_tasks_g) { 
        printf(" <%d,%d>, ",completed_tasks_pq->tasks[i]->,completed_tasks_pq->tasks[i]);
        i++;
    }
    printf("\nDone\n"); */
    printf("DONE\n");
    return 1;
}


void playerInorder(struct Player* player) {     //traverse players and in the same time the tasks of players
     if (player == NULL) 
          return; 

     /* first recur on left child */
     playerInorder(player->lc); 

     /* then print the data of node */
     printf("player %d = ", player->pid);   
     taskInorder(player->tasks);
     printf("\n");

     /* now recur on right child */
     playerInorder(player->rc); 
} 


void taskInorder(struct Task* task) {           //traverse tasks of player
     if (task == NULL) 
        return; 
  
     taskInorder(task->lc); 
     printf("<%d> <%d> ,", task->tid,task->difficulty);   
     taskInorder(task->rc); 
} 


/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
   printf("implemented tasks is : %d \n",completed_tasks_pq->size);
   playerInorder(players_tree);
   printf("DONE\n");
   return 1;
}


void freeplayer(struct Player* player) {    //recursive function to print players
     
     if (player == NULL) 
          return; 

     freeplayer(player->lc); 
     
     freeplayer(player->rc);
     player->is_alien=NULL;
     player->pid=NULL;
     free(player);
} 


/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int h(int tid) {            //algorithm for hashing
    int a=1;
    int b=0;
    int index=0;
    a= (rand()%((p-1)-1+1))+1;
    b= (rand()%((p-1)-0+1))+1;
    index=((a*tid+b) %p);
    return index;
}


void Inorder(struct Player* node,int thesi) {  //find the player in the specific position for distribute
    
    if (node == NULL) 
        return; 
    
    if (count <= thesi) {
        /* first recur on left child */
        Inorder(node->lc, thesi); 
    
        // when count = n then print element 
        if (count == thesi) {
            specific_player=node;
        }
        count++;
        /* now recur on right child */
        Inorder(node->rc, thesi); 
    }
} 



/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    printf("\n");
    printf("Free_All\n");
    struct General_Tasks_HT* ht_head = general_tasks_ht;
    struct HT_Task* chain_head;
    int i;
    struct Player* temporary=players_tree;

    for(i=0; i<p; i++){
        chain_head = ht_head->tasks[i];     //FREE HASH TABLE(GENERAL_LIST)
        ht_head->tasks[i]=NULL;
        free(ht_head->tasks[i]);
    }

    freeplayer(players_tree);
    players_tree=NULL;
   
    print_players();
    print_tasks();
    printf("DONE\n");
    return 1;
}