/***************************************************
 *                                                 *
 * file: among_us.c                                *
 *                                                 *
 * @Author  Antonios Peris                         *
 * @Version 20-10-2020                             *
 * @email   csdp1196@csd.uoc.gr                    *
 *                                                 *
 * @brief   Implementation of among_us.h           *
 *                                                 *
 ***************************************************
 */

#include "among_us.h"
int c1=0;
int c2=0;    
int c3=0;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    struct Head_GL* new_GL =(struct Head_GL*) malloc(sizeof(struct Head_GL));
    struct Head_Completed_Task_Stack* new_in_stack =(struct Head_Completed_Task_Stack*) malloc(sizeof(struct Head_Completed_Task_Stack));
    int k;
    for(k=0; k<3;k++){
        new_GL->tasks_count[k]=0;
    }    
    tasks_head=new_GL;

    tasks_stack = new_in_stack;
    tasks_stack->count=0;

    return 1;
}

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid,int is_alien) {
    struct Players* new_player =(struct Players*) malloc(sizeof(struct Players));
    if (new_player == NULL) { 
        return 0; 
    }

	new_player->pid=pid;
    new_player->is_alien=is_alien;

	if (players_head == NULL) {        //an einai adeia h lista
		new_player->next = new_player;
		new_player->prev = new_player;          //linking nodes
        players_head = new_player;
	}
	else {              //allios 
		new_player->next = players_head;           //mpainei kapou sti mesi h sto telos
		new_player->prev=players_head->prev;
		players_head->prev->next = new_player;         //linking nodes
        players_head->prev =new_player;
        
	}
    players_count+=1;
    print_players();
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid,int difficulty) {
    
    struct Tasks* new_task=(struct Tasks*) malloc(sizeof(struct Tasks));
    struct Tasks *temp=tasks_head->head;

    new_task->tid=tid;  
    new_task->difficulty=difficulty;

    if (new_task==NULL){    
        return 0;   
    }   
    if (temp == NULL || temp->difficulty >= new_task->difficulty) {  
        new_task->next = temp; 
        tasks_head->head= new_task;
    } 
    else { 
        while (temp->next != NULL && temp->next->difficulty < new_task->difficulty) { 
            temp = temp->next; 
        }
        new_task->next = temp->next; 
        temp->next = new_task;
    } 
    if(difficulty==1){
        c1 +=1;
    }
    else if(difficulty==2){
       c2+=1;
    }
    else if(difficulty==3){
       c3+=1;
    }
    tasks_head->tasks_count[0]=c1;
    tasks_head->tasks_count[1]=c2;
    tasks_head->tasks_count[2]=c3;  
    
    print_general_list();
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Distribute tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
    int position;
    struct Tasks* current=tasks_head->head;
    struct Tasks* t_head;
    struct Players* temporary;
    int metritis;
    int i=1;

    if(tasks_head==NULL){
        return 0;
    }
    else {
        while(current!=NULL){

            temporary = players_head;
            position=i%players_count;   //vrisko tin thesi tou player pou tha parei to task
            metritis=0;

            struct Tasks* new_task=(struct Tasks*) malloc(sizeof(struct Tasks));
            new_task->tid = current->tid;                                   //to new_task pairnei tis times pou tha dothoun sti task list tou player
            new_task->difficulty = current->difficulty;
           
            while(metritis<position){         //traverse mexri na ton vri
                temporary=temporary->next;
                metritis++;
            }
        
            while(temporary->is_alien==1){
                temporary=temporary->next;
            }
    
            t_head=temporary->tasks_head;   //pointer sto head tis listas ton tasks tou

            if (t_head == NULL || t_head->difficulty >= current->difficulty ) {  //ELEGXO AN TO TASK POU PSAXNO = EINAI STO HEAD TIS TASK LIST
                new_task->next = temporary->tasks_head; 
                temporary->tasks_head = new_task;
            }
            else{
                while (t_head->next != NULL && t_head->next-> difficulty < current->difficulty) { 
                     t_head = t_head->next;                                 //KANW TRAVERSE MEXRI TO TASK POU PSAXNO NA EINAI STIN MESI H STO TELOS TIS TASK LIST
                }
                new_task->next = t_head->next;              //KANW TO LINKING TON NODES
                t_head->next = new_task;
                //struct Tasks* new_sentinel=(struct Tasks*) malloc(sizeof(struct Tasks));
               /* if(t_head->next==NULL){
                    printf("GEIA SOU");
                    new_sentinel->tid=-1;
                    new_sentinel->difficulty=0;
                    new_sentinel=t_head->next;
                    new_sentinel->next=t_head;
                    temporary->tasks_sentinel=new_sentinel;
                }
                */
            }
            distribute_given_tasks++; 
            current=current->next;
            i++; 
        }
    }
    print_double_list();
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficuly
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int difficulty) {
    struct Tasks* new_trash=(struct Tasks*) malloc(sizeof(struct Tasks));
    struct Players* p_temporary=players_head;
    struct Tasks* t_temporary,*previous;
    struct Tasks* delete_node;
    tasks_stack->count+=1; 
    
    do {  //FIND THE PLAYER POU THA KANEI TO IMPLEMENT
        p_temporary = p_temporary->next;
    }while(p_temporary->pid != pid  && p_temporary!=players_head);


    t_temporary = p_temporary->tasks_head; //TO TEMPORARY TOU TASK TOU DINOUME TO HEAD TIS TASK LIST TOU PAIXTI

    if(p_temporary->tasks_head == NULL){  //SE PERIPTOSI POU H TASK LIST TOU PLAYER EINAI NULL
        print_double_list(); 
        return 1;
    } 
    //ELEGXO GIA TO HEAD STIN TASK LIST
    if ( t_temporary->difficulty == difficulty) {  //AN TO TEMPORARY EINAI TO HEAD STIN TASK LIST
        delete_node = t_temporary;      
        p_temporary->tasks_head = t_temporary->next;
      
    }
    else if (p_temporary->tasks_head->next==NULL){ //AN EINAI STIN ARXI ALLA PERIEXI KIALLA NODES...TOTE TO HEAD NA GINEI TO NEXT NODE
        delete_node = t_temporary;      
        p_temporary->tasks_head = t_temporary->next;
    }  
    else{                                                                               //ALLIOS
        while (t_temporary->next!= NULL && t_temporary->difficulty != difficulty){    //KANW TRAVERSE MEXRI TO TASK POU PSAXNO NA EINAI STIN MESI H STO TELOS TIS TASK LIST
           previous=t_temporary;
           t_temporary=t_temporary->next;
        }
        if(t_temporary!=NULL){                                //AFOU TO VRO ELEGXO AN TO TASK POU VRIKA EINAI ANISO NULL
            delete_node=t_temporary;                                    //  TO THETO SAN TON KOMVO POU THELW NA DIAGRAPSO 
            previous->next = t_temporary->next;     
        }
        else if(t_temporary== NULL) {                //AN AUTO POU VRIKA EINAI NULL..TOTE DEN VRETHIKE AUTOS POU PSAXNOUME...PERNOUME TON PROIGOUMENO
            delete_node=previous;                    // THETO SAN TON KOMVO POU THELW NA DIAGRAPSO TON PROIGOUMENO TOU                                                   
        }                                                                
    }
    
    new_trash->tid=delete_node->tid;                             //TO NODE NEW TRASH PAIRNEI TIS TIMES POU THA MPOUNE STIN STOIVA
    new_trash->difficulty=delete_node->difficulty;

    if(tasks_stack->head==NULL || tasks_stack->head!=NULL){
        new_trash->next = tasks_stack->head; 
        tasks_stack->head = new_trash;   //KANW TO HEAD NA DIXNI STO KAINOURIO NODE
    }

    free(delete_node);
    print_double_list(); 
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Eject Player
 * 
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid) {
    struct Players* player_temp=players_head;
    struct Tasks* task_temp,*tasks_peripatos,*tasks_pmin,*help_pointer,*previous;
    int counter;
    int counter_iso=0;
    int min=1000;
    int flag=0;
    struct Players *pid_min,*player_peripatos;

    //find the players with minimum tasks
        do {
            if (player_temp->pid==pid ) {
                player_peripatos=player_temp;
                flag=1;                                       //FLAG POU XRISIMOPOIO EKSO APO TIN DO WHILE
                tasks_peripatos=player_temp->tasks_head;
            }
            else if(player_temp->is_alien==1 ){
            }
            else if(player_temp->pid!=pid){
                counter=0;
                counter_iso=0;
                task_temp=player_temp->tasks_head;
                
                while(task_temp!=NULL){  //counting the tasks for every player
                    counter++;
                    counter_iso++;
                    task_temp = task_temp->next;
                }
                if(counter<=min){
                    min=counter;
                    pid_min=player_temp;  //player with minimum tasks
                }
            }
            
            player_temp=player_temp->next;
        } while(player_temp!=players_head); 

        if (flag==0){       //STIN PERIPTOSI POU ENAS PAIXTIS GINEI EJECT GIA PARADEIGMA KAI META TOU POUME NA KANEI IMPLEMENT AUTOS O PAIXTIS
            return 1;               //AN DEN IPIRXE AUTO O KODIKAS PAEI SE INFINITY LOOP
        }
    
    tasks_peripatos=player_peripatos->tasks_head;
    
    // Merge 2 lists
    while ((tasks_peripatos != NULL)) {
        help_pointer=tasks_peripatos->next;
        tasks_pmin=pid_min->tasks_head;

        if (pid_min->tasks_head == NULL || pid_min->tasks_head->difficulty >= tasks_peripatos->difficulty) {
            tasks_peripatos->next=tasks_pmin;               //AN MPEI STO HEAD TIS TASK LIST TOU PLAYER 
            pid_min->tasks_head=tasks_peripatos;
        } 
        else {
            while ( tasks_pmin != NULL && tasks_pmin-> difficulty  < tasks_peripatos-> difficulty) {          
                previous=tasks_pmin;                //AN MPEI STI MESI H STO TELOS TIS TASK LIST TOU PLAYER 
                tasks_pmin = tasks_pmin->next;
            }
                previous->next=tasks_peripatos;       //LINKING TA NODES
                tasks_peripatos->next = tasks_pmin;  
        }   
        tasks_peripatos = help_pointer;
    }
    //Delete from circular doubly link list
    if (player_peripatos == players_head) {  //AN O PLAYER POU THA FIGEI EINAI STO HEAD
        players_head = player_peripatos->next; 
        players_head->prev = player_peripatos->prev;    //LINKING TIS LISTAS
        player_peripatos->prev->next=players_head; 
    }
    else {  //ALLIOS AN EINAI KAPOU ALLOU STI LISTA TON PLAYER
        player_peripatos->prev->next = player_peripatos->next;          //LINKING TIS LISTAS
        player_peripatos->next->prev = player_peripatos->prev; 
    } 
    free(player_peripatos);
    print_double_list();
    printf("\nDONE\n"); 
    return 1;
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 * 
 * @param pid The crewmate's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses){

    eject_player(pid);     //kaloume tin eject gia na kanei eject ton pid player
    
    struct Players* task_player=players_head;

    do{        //traverse list of players as long we didnt find the pid_a
        task_player=task_player->next;

    }while(task_player!=players_head && task_player->pid!=pid_a);

    task_player->evidence +=number_of_witnesses;     //otan ton vroume tou dinoume to witness
    print_evidence();
    return 1;
}


/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabbotage(int number_of_tasks,int pid) {
    
    struct Players* task_player=players_head, *player_point, *player_next;
    struct Tasks *t_head;
    struct Tasks* new_trash;

    int counter_tasks=0;
    int metritis=0;
    int counter=0;
    int position;
    position=number_of_tasks/2;   

    do{                                         //FIND THE POINT PLAYER WITH PID
        task_player=task_player->next;
    }while(task_player!=players_head && task_player->pid!=pid);
    
    player_point=task_player; 
    
    do{                                        //PIGENE STIN LISTA PAIXTON KAI PIGENE ARISTERA OSO TO NUMBER_OF_TASKS/2
        player_point = player_point->prev;
        metritis++;   
    }while( metritis < position);

    player_next=player_point;

    while(tasks_stack->head!=NULL && counter < number_of_tasks){                            //OSO KANEIS TRAVERSE TIN STIVA
                         
            new_trash=tasks_stack->head;                          //TOTE TO NEW NODE NA PAREI TA STIXIA TOU
            tasks_stack->head = tasks_stack->head->next;            // Changed head
                
            if(player_next->is_alien==1){      //AN AUTOS POU PIGES ARISTERA HTAN ALIEN TOTE PIGENE DEKSIA MEXRI NA VREIS CREWMATE
                do{
                    player_next=player_next->next;
                }while(player_next->is_alien==1);
            } 
                t_head = player_next->tasks_head;                 //POINTER TIPOU TASK POU DIXNEI STI LISTA TON TASK TOU PAIXTI POU VRIKAME POU DEN EINAI ALIEN

                if (t_head == NULL || t_head->difficulty >= new_trash->difficulty ) {   //AN MPEI STO HEAD TIS TASK LIST TOU PLAYER POU DEN EINAI CREWMATE
                    new_trash->next = player_next->tasks_head; 
                    player_next->tasks_head = new_trash;
                }
                else{                                                           //ALLIOS AN THA MPEI STIN MESI H STO TELOS TIS TASK LIST TOU PLAYER POU DEN EINAI CREWMATE
                    while (t_head->next != NULL && t_head->next-> difficulty < new_trash->difficulty) { 
                        t_head = t_head->next;
                    }
                    new_trash->next = t_head->next;    //TO LINKING GIA TA NODES STIN TASK LIST TOU PLAYER
                    t_head->next = new_trash;
                }
        player_next=player_next->next;       //EPOMENOS PLAYER POU THA DOSEI TASK   ##EPANALAMVANETE AUTO MEXRI NA DWSEI OLA TA TASKS POU PREPI
        counter++;
        counter_tasks++;
    }            
    tasks_stack->count = tasks_stack->count - counter_tasks;   //AFAIRW APO TO COUNT TON IMPLEMENTS TASKS POU VRISKONTAI STIN STOIVA 

    print_double_list();
    printf("\nDONE\n");
    return 1;
}


/**
 * @brief Vote
 *
 * @param pid The player's id
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid, int vote_evidence) {
 
    struct Players* task_player=players_head, *evidence_player,*pid_max;
    int flag=0;
    int max=0;

    while(task_player->next!=players_head){ 
        if(task_player->pid==pid){
            evidence_player = task_player;
            flag =1;
            evidence_player->evidence = evidence_player->evidence + vote_evidence;
        }
        if(task_player->evidence > max){
            max = task_player->evidence;
            pid_max = task_player;
            
        } 
        task_player=task_player->next;
    }
    if(flag==0){
        return 1;
    }
    eject_player(pid_max->pid);
    print_evidence();
    return 1;
}


/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work() {

    struct Players* player_max,*player_min,*player_temp=players_head;
    int counter_min=1000, counter,counter_max=0;
    struct Tasks* task_temp,*new_trash,*t_head;
        do {       //kanoume traverse tin lista ton paixton 
            if(player_temp->is_alien==1 ){
            }
            else {
                counter=0;
                task_temp=player_temp->tasks_head;
                
                while(task_temp!=NULL){             //metrame ta task tou kathenos
                    counter++;
                    task_temp = task_temp->next;
                }
                printf("counter %d \n ",counter);
                if(counter>counter_max){            //vriskoume ton paixti me ta perissotera tasks
                    counter_max=counter;
                    player_max=player_temp;
                    printf(" max %d \n ",counter_max);
                }
                if(counter<counter_min){      //vriskoume ton paixti me ta ligotera
                    counter_min=counter;
                    player_min=player_temp;
                    printf(" min 1 %d \n ",counter_min);
                }  
            }
            player_temp=player_temp->next;
        } while(player_temp!=players_head); 

        int tasks=0,metritis=0;
        tasks=counter_max/2;

        while(player_max->tasks_head != NULL && metritis < tasks){     //traverse tin lista tou player_max
            new_trash=player_max->tasks_head;                          // TO NEW NODE NA PAREI TA STOIXEIA TOU PLAYER_MAX
            player_max->tasks_head = player_max -> tasks_head -> next;
            t_head=player_min->tasks_head;      //AYTO EINAI TO TEMP TOU PLAYER_MIN

            if (t_head == NULL || t_head->difficulty >= new_trash->difficulty ) {   //AN MPEI STO HEAD TIS TASK LIST TOU PLAYER_MIN
                new_trash->next = player_min->tasks_head; 
                player_min->tasks_head = new_trash;
            }
            else{                                                           //ALLIOS AN THA MPEI STIN MESI H STO TELOS TIS LISTAS ME TA TASKS TOU PLAYER_MIN
                while (t_head->next != NULL && t_head->next-> difficulty < new_trash->difficulty) { 
                    t_head = t_head->next;
                }
                new_trash->next = t_head->next;         //ETSI KANOUME TO LINKING STI LISTA
                t_head->next = new_trash;
            }
            metritis++;    
        }
    print_double_list();
    printf("\nDONE\n");  
    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {

    struct Players *player_temp=players_head;
    int alien_count=0,crewmate_count=0;

    do{     //KANW TRAVERSE TOUS PLAYERS
        if(player_temp->is_alien==1){
            alien_count++;
        }
        else if (player_temp->is_alien==0){
            crewmate_count++;
        }

        player_temp=player_temp->next;
    }while(player_temp!=players_head);
    
    if(alien_count > crewmate_count){
        printf("Aliens Win. \n");
        return 1;
    }
    else if( alien_count==0 || alien_count < crewmate_count || distribute_given_tasks == tasks_stack->count){
        printf("Crewmates Win. \n");

    }
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
    struct Players* tmp = players_head;
	printf("Players = ");
    do {
		printf("<%d:%d>, ",tmp->pid,tmp->is_alien);
		tmp = tmp->next;
	} while(tmp!=players_head);
    printf("\nDone\n");
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {

    struct Tasks *current = tasks_head->head;
     printf("List_Tasks = ");
   	while (current != NULL) {
        printf("<%d,%d>,",current->tid,current->difficulty);
        current = current->next;
    }
    printf("\nDone\n");
    return 1;
}

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack() {
    struct Tasks *current = tasks_stack->head;
    printf("Stack_Tasks = ");
   	while (current!= NULL) { 
        printf(" <%d,%d>, ",current->tid,current->difficulty);
        current = current->next;
    }
    printf("\nDone\n");
    return 1;
}

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list() {
    struct Players* player_temp=players_head;
    struct Tasks* task_temp;
    int counter=1;
    
    if(players_head==NULL){
        return 0;
    }
    else{
        do {
            task_temp=player_temp->tasks_head;
            printf("Player %d = ",counter);
            counter++;
            while(task_temp!=NULL){
                printf("<%d,%d>, ",task_temp->tid,task_temp->difficulty);
                task_temp = task_temp->next;
            }
            printf("\n");
            player_temp=player_temp->next;
        } while(player_temp!=players_head);
    }
    printf("\nDone\n");
    return 1;
}



/**
 * @brief Print Players & evidence of players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_evidence() {
    struct Players* player_temp=players_head;
    struct Tasks* task_temp;
    
    if(players_head==NULL){
        return 0;
    }
    else{
        do {
            task_temp=player_temp->tasks_head;
            printf("<%d,%d> = ",player_temp->pid,player_temp->evidence);
            while(task_temp!=NULL){
                printf("<%d,%d>, ",task_temp->tid,task_temp->difficulty);
                task_temp = task_temp->next;
            }
            printf("\n");
            player_temp=player_temp->next;
        } while(player_temp!=players_head);
    }
    printf("\nDone\n");
    return 1;
}


/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_general_list() {

    struct Tasks *current = tasks_head->head;
    printf("Tasks = ");
   	while (current != NULL) {
        printf("<%d,%d>,",current->tid,current->difficulty);
        current = current->next;
    }
    printf("\nDone\n");
    return 1;
}



/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    struct Players* player_peripatos=players_head;
    printf("\n");
    printf("FREE_ALL\n");

    struct Tasks* tmp;

    while (tasks_stack->head != NULL) {    //free memory for stack list
        tmp = tasks_stack->head;
        tasks_stack->head =tasks_stack->head->next;
        free(tmp);
    }
    free(tasks_stack);


    while (tasks_head->head != NULL) {       //free memory for general task list
        tmp = tasks_head->head;
        tasks_head->head = tasks_head->head->next;
        free(tmp);
    }
   
     do{
        while(player_peripatos->tasks_head!=NULL){
            player_peripatos->tasks_head= player_peripatos->tasks_head->next;
            free(player_peripatos->tasks_head);
        }
        if (player_peripatos == players_head) {  
            players_head = player_peripatos->next; 
            players_head->prev = player_peripatos->prev;    //LINKING TIS LISTAS
            player_peripatos->prev->next=players_head; 
        }
        player_peripatos=player_peripatos->next;
    }while(players_head->next!=players_head);

    print_stack();
    print_general_list();
    print_double_list();
    printf("\nDONE\n");
    return 1;
}

