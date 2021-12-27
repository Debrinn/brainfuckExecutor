#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
/////////////
/* Définition de types :
 * pgm -> contenant le programme à exécuter
 * memory, _memory -> la structure de la mémoire d'un BF (brainfuck)
 */
typedef char* pgm;
struct _memory {
    int size;
    int cur_ptr;
    char* content;
};
typedef struct _memory * memory;

void print_program_with_pos(pgm p, int pos){
    int i = 0;
    printf("%s\n",p);
    while (i!=pos){
        printf(" ");
        i=i+1;
    }
    printf("^\n");
}
void print_memory(memory m){
    int i = 0;
    while (m->content[i]==0){
        i=i+1;
    }
    while (m->content[i]!=0){
        if (i==m->cur_ptr){
            printf(">%d< ",m->content[i]);
        }else{
            printf("%d ",m->content[i]);
        }
        i = i+1;
    }
    printf("\n");
}
char global_mem[1000];

void init_g(){
    int i = 0;
    while (i!=1000){
        global_mem[i]=0;
        i=i+1;
    }
}
memory init_memory(){
    memory nouvelle;
    nouvelle->size= 1000;
    nouvelle->cur_ptr= 0;

    nouvelle->content = global_mem;
    return nouvelle;
}
void move_head_right(memory m){
    if (m->cur_ptr == 1000){
        printf("Erreur : la tête de lecture est déjà au maximum.\n");
    }else{
        m->cur_ptr = m->cur_ptr+1;
    }
}
void move_head_left(memory m){
    if (m->cur_ptr == 0){
        printf("Erreur la tête de lecture est au minimum de la mémoire : 0\n");
    }else{
        m->cur_ptr = m->cur_ptr-1;
    }
}
void incr_under_head(memory m){
    m->content[m->cur_ptr]= m->content[m->cur_ptr]+1;
}
void decr_under_head(memory m){
    m->content[m->cur_ptr]= m->content[m->cur_ptr]-1;
}
void read_under_head(memory m){
    char a_changer;
    scanf("%c",&a_changer);
    m->content[m->cur_ptr]= a_changer;
}
void write_under_head(memory m){
    printf("%c", m->content[m->cur_ptr]);
}

int matching_close(pgm p, int i){
    int reverse = 0;
    int position ;
    int k = 0;
    int size = strlen(p);
    while (i!=size){
        if (p[i]=='['){
            reverse=reverse+1;
        }
        else if (p[i]==']'){
            if (reverse==0 | reverse==1){
                return i;
            }
            else{
                reverse= reverse-1;
            }
        }
        i = i+1;
    }
    printf("Erreur : absence de crochet de fermeture ] \nSolution : renvoi de -1 en position");
    return -1;

}
int matching_open(pgm p, int i){
    int size = strlen(p)-1;
    int reverse=0;
    while (size!=-1){
        //printf("reverse : %c\n",p[size]);
        if (p[size]==']'){
            //printf("LE TEST FONCTIONNE");
            reverse=reverse+1;
        }
        else if (p[size]=='['){
            if (reverse!=0 && reverse!=1){
                //printf("EEFEFE");
                reverse=reverse-1;
            }else{
                //printf("BLOB");
                return size;
            }

        }
        size = size-1;
    }
    printf("Erreur : absence de crochet d'ouverture [");
    return size;
}
int step(int inst_ptr, pgm p, memory m){
    //printf("\nEn data :%c\n",inst_ptr);
    if (p[inst_ptr]=='>'){
        move_head_right(m);
        return (inst_ptr+1);
    } else if (p[inst_ptr]=='<'){
        move_head_left(m);
        return (inst_ptr+1);
    } else if(p[inst_ptr]=='.'){
        write_under_head(m);
        return (inst_ptr+1);
    } else if (p[inst_ptr]==','){
        read_under_head(m);
        return (inst_ptr+1);
    } else if (p[inst_ptr]=='+'){
        incr_under_head(m);
        return (inst_ptr+1);
    } else if (p[inst_ptr]=='-'){
        decr_under_head(m);
        return (inst_ptr+1);
    } else if (p[inst_ptr]==']'){
        //printf("\nvoila : -> %d\n", matching_close(p,inst_ptr));
        return (matching_open(p,inst_ptr));
    } else if (p[inst_ptr]=='['){
        int cas = m->content[m->cur_ptr];
        if (cas==0){

            return (matching_close(p,inst_ptr)+1);
        }else{
            return (inst_ptr+1);
        }
    }else{
        print_program_with_pos(p,inst_ptr);
        printf("\nErreur : caractère inconnu,\nRetour :-1\n");
        return -1;
    }
}
void exec(pgm p, memory m){

    int pointeur = 0;
    char carac;
    int sof_pgm= strlen(p);

    while (pointeur != sof_pgm){
        carac = p[pointeur];

        pointeur=step(pointeur,p,m);
        /*printf("\n");
        print_memory(m);
        printf("\n");*/
    }
    printf("\n");
}

void main(){
    init_g();
    printf("\n"
           "██████  ██████   █████  ██ ███    ██ ███████ ██    ██  ██████ ██   ██ \n"
           "██   ██ ██   ██ ██   ██ ██ ████   ██ ██      ██    ██ ██      ██  ██  \n"
           "██████  ██████  ███████ ██ ██ ██  ██ █████   ██    ██ ██      █████   \n"
           "██   ██ ██   ██ ██   ██ ██ ██  ██ ██ ██      ██    ██ ██      ██  ██  \n"
           "██████  ██   ██ ██   ██ ██ ██   ████ ██       ██████   ██████ ██   ██ \n"
           "                                                                      \n"
           "                                                                      \n"
           "███████ ██   ██ ███████  ██████ ██    ██ ████████  ██████  ██████     \n"
           "██       ██ ██  ██      ██      ██    ██    ██    ██    ██ ██   ██    \n"
           "█████     ███   █████   ██      ██    ██    ██    ██    ██ ██████     \n"
           "██       ██ ██  ██      ██      ██    ██    ██    ██    ██ ██   ██    \n"
           "███████ ██   ██ ███████  ██████  ██████     ██     ██████  ██   ██    \n"
           "                                                                      \n"
           "                                                                      ");
    printf("\nExécuteur codé par DRESER Matéo - Pour le Lycée Champollion - 2021\n""ENTREZ CODE : \n");
    pgm prog;
    printf("~# ");
    scanf("%s",prog);
    printf("\n");
    memory init_s= malloc(sizeof (struct _memory));
    init_s->cur_ptr=0;
    init_s->content=global_mem;
    init_s->size=1000;
    exec(prog,init_s);

}