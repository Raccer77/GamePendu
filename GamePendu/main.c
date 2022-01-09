
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> 
#include <pthread.h>
#include <unistd.h>

#define TOTAL_VIE 5 
#define TRUE 1
#define FALSE 0

int timer = 0 ;

void println(char* str) {
    printf("%s\n", str) ;
}

void* ThreadTimer() {
    while(1){
        timer++ ;
        sleep(1) ;
    }
    return NULL ;
}

int main(int argc, char const *argv[])
{
    
    char* word = "DEVINER" ;
    char* lettres_utilisees = malloc(50) ;
    int vie = TOTAL_VIE ;
    int size = strlen(word) ;
    int place_lettre = 0 ;
    char* wordPlayer = malloc(size+1);
    wordPlayer[size] = '\0' ;

    int i;
    for(i=0 ; i<size ; i++) wordPlayer[i] = '_' ;

    char* input = malloc(2) ;

    pthread_t* thread_id ;
    pthread_create(thread_id, NULL, ThreadTimer, NULL) ;

    int find_word ;
    
    while(vie > 0){

        println("-----------------------------------------------------") ;
        println("") ;
        println("") ;
        printf("Mot à trouver : %s", wordPlayer) ;
        println("") ;
        printf("Liste des lettres utilisées : %s\n", lettres_utilisees) ;
        printf("Vies : %d/%d\n", vie, TOTAL_VIE) ;
        println("") ;

        int err = scanf("%s", input) ;
        int taille_input = strlen(input) ;
        char lettre = input[0] ;

        if(taille_input > 1){
            printf("Vous ne devez mettre qu'une seule lettre. La lettre comptée est donc %c\n", lettre) ;
        }

        if(err == -1){
            println("Erreur sur la saisie au clavier.") ;
            return 1 ;
        }

        int already_use = FALSE ;
        for(int j=0 ; j<size ;j++){
            if(lettres_utilisees[j] == lettre){
                printf("Vous avez déjà essayé cette lettre. Votre essai n'est pas comptabilisé.\n") ;
                println("") ;
                already_use = TRUE ;
                break ;
            }
        }
        if(already_use) continue ;

        int find_lettre = FALSE ;
        find_word = TRUE ;

        for(int j=0 ; j<size ; j++){
            if(word[j] == lettre) {
                wordPlayer[j] = lettre ;
                find_lettre = TRUE ;
            }
            if(wordPlayer[j] == '_') find_word = FALSE ;
        }

        strcat(lettres_utilisees, &lettre) ;
        strcat(lettres_utilisees, " ") ;

        if(find_lettre) printf("Vous avez trouvé une lettre !\n") ;
        else vie-- ;

        if(find_word) break ;

    } 
    
    println("") ;
    println("") ;
    println("-----------------------------------------------------") ;
    println("") ;

    if(find_word){
        printf("Félicitation ! Vous avez trouvé le mot %s !\n", word) ;
        printf("Il vous restait %d vies sur %d\n", vie, TOTAL_VIE) ;
    }
    else {
        printf("Dommage, vous avez perdu ! Le mot était : %s !\n", word) ;
        printf("Vous avez utilisé vos %d vies...\n", TOTAL_VIE) ;
    }

    int min = (int)(timer/60) ;
    int sec = timer%60 ;

    if(min == 0) printf("Vous avez mis %ds\n", sec) ;
    else printf("Vous avez mis %dm%d\n", min, sec) ;
            

    println("") ;
    println("") ;

    return 0;
}
