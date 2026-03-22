#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char description[2000];
    struct Node* choice1;
    struct Node* choice2;
    struct Node* choice3;
    int visited;
} scene;


scene* Undo[100];
scene* Redo[100];

int top = -1;
int topredo = -1;

scene* array[100];

char arr[24][2000] = {
    "Shadows over Anthea\n\n Anthea is a vibrant, bustling city with a rich history.\n Queen Anthea rules with wisdom, but now a dangerous secret group called The Shadows is plotting to take over.\n The city is safety depends on two brave soldiers-Valkyrie and Orion-who must uncover and stop these threats.\n Are you ready to begin your adventure?\n\n1.Continue\n\n2.Exit\n",
    
    "Character Selection\n\nChoose your hero:\n\n1. Valkyrie - A fearless soldier with sharp mind and combat skills.\n\n2. Orion - A calm strategist and expert fighter.\n",
    
    "The Queen's Warning\n\nThe Queen has sent an urgent message. The Shadows plan to strike soon. Where do you want to start investigating?\n\n1. Old warehouse - Suspected hideout.\n\n2. City guards - Gather intelligence.",
    
    "Hidden Warehouse\n\nThe warehouse looks abandoned but might hide important clues.\n\n1. Search quietly for evidence.\n\n2. Set a trap and wait.",
    
    "Guards' Report\n\nA guard whispers that there might be a traitor working with The Shadows.\n\n1. Question the suspect directly.\n\n2. Follow the suspect secretly.",
    
    "Underground Tunnels\n\nThe tunnels are dark and filled with traps and enemies.\n\n1. Proceed carefully and look for signs.\n\n2. Light a fire to see better.",
    
    "The Evidence\n\nYou find clues pointing toward an impending attack.\n\n1. Alert the city guards.\n\n2. Search for the enemy's plan.",
    
    "Waiting Trap\n\nHours pass and no one appears. Your patience is tested.\n\n1. Keep waiting.\n\n2. Leave and report to the Queen.",
    
    "Direct Confrontation\n\nThe suspect is nervous but denies everything.\n\n1. Press for answers.\n\n2. Let go and watch.",
    
    "Secret Surveillance\n\nThe suspect leads you to a secret meeting of The Shadows.\n\n1. Interrupt now.\n\n2. Report and wait for backup.",
    
    "Careful Search\n\nYou find signs of recent activity in the tunnels.\n\n1. Follow the signs.\n\n2. Report to the Queen.",
    
    "Fire for Vision\n\nFire reveals enemies nearby. Battle is inevitable.\n\n1. Fight.\n\n2. Escape to regroup.",
    
    "Final Alert and Defense\n\nYou alert the city and prepare for battle as The Shadows advance.\n\n1. Lead the defense.\n\n2. Prepare a tactical retreat.",
    
    "Enemy's Plan\n\nYou uncover The Shadows' attack plan with times and locations.\n\n1. Intercept attackers early.\n\n2. Bolster city defenses.",
    
    "Confront The Shadows' Leader\n\nYou face the enemy leader in a decisive clash.\n\n1. Fight till end.\n\n2. Attempt negotiation.",
    
    "Victory or Loss\n\nThe clash with The Shadows reaches its peak. Your leadership has led to a fierce battle deciding the fate of Anthea.\n\n1. Celebrate the victory with your allies.\n\n2. Mourn the losses and vow to rebuild stronger.",
    
    "Tactical Retreat\n\nYou strategically retreat to save your people and gather strength for the next fight.\n\n1. Plan a counterattack.\n\n2. Seek allies in distant lands.",
    
    "Plan Counterattack\n\nYou mobilize your troops and plot a surprise strike against The Shadows.\n\n1. Launch the attack at dawn.\n\n2. Gather more intelligence before attacking.",
    
    "Seek Allies\n\nYour journey to find new allies brings you to ancient mountain tribes and mystical kingdoms willing to aid your cause.\n\n1. Visit the mountain tribes.2. Petition the Kingdom of Eldoria.",
    
    "Victory Celebration\n\nThe city of Anthea erupts in joy and celebration. Your bravery has restored peace.\n\n1. Restart adventure.\n\n2. Exit.",
    
    "Rebuild and Reflect\n\nThough the battle was costly, your leadership inspires hope. Together, Anthea begins healing and rebuilding.\n\n1. Restart.\n\n2. Exit.",
    
    "Intelligence Gathering\n\nYou gather new intelligence revealing weaknesses in The Shadows' plan.\n\n1. Move swiftly to attack.\n\n2. Strengthen defenses.",
    
    "Mountain Tribes\n\nThe mountain tribes welcome you as an ally. Their fierce warriors pledge loyalty.\n\n1. The story ends here with their support securing Anthea's safety.\n\n2. Restart or exit.",
    
    "Kingdom of Eldoria\n\nThe mystical kingdom of Eldoria grants your request for magical assistance.\n\n1. The story ends here with Eldoria's magical alliance ensuring hope.\n\n2. Restart or exit."
};

void run(scene* node) {
    if (!node) return;

    if (top == -1 || Undo[top] != node) {
        if (top < 99) {
            Undo[++top] = node; 
        } else {
            printf("Undo stack is full\n");
        }
    }

   
    topredo = -1;
}




scene* undo() {
    if (top <= 0) {
        printf("Nothing to undo\n");
        return Undo[0];
    }

    Redo[++topredo] = Undo[top--];  
    return Undo[top];              
}

scene* redo() {
    if (topredo < 0) {
        printf("Nothing to redo\n");
        return Undo[top];
    }

    Undo[++top] = Redo[topredo--];  
    return Undo[top];
}


void display() {
    if (top == 0) {
        printf("No Moves played\n");
        return;
    }

    printf("\nVisited Scenes:\n");
    for (int i = 0; i < top; i++) {
        printf("---------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", Undo[i]->description);
    }
}

scene* gotosave(scene* node) {
    if (!node) {
        printf("No saved node provided\n");
        return (top > 0) ? Undo[top - 1] : NULL;
    }

    while (top > 0 && Undo[top - 1] != node)
        top--;

    if (top == 0) {
        printf("Saved point not found in history\n");
        return node;
    }

    return Undo[top - 1];
}


scene* create() {
    scene* temp;
    for (int i = 0; i < 24; i++) {
        temp = (scene*)malloc(sizeof(scene));
        if (!temp) {
            printf("malloc failed at scene %d\n", i);
            exit(1);
        }
        int j = 0;
        while (arr[i][j] != '\0' && j < sizeof(temp->description) - 1) {
            temp->description[j] = arr[i][j];            j++;
        }
        temp->description[j] = '\0';
        temp->choice1 = NULL;
        temp->choice2 = NULL;
        temp->choice3 = NULL;
        temp->visited = 0;
        array[i] = temp;
    }
    
    array[0]->choice1 = array[1];
    array[0]->choice2 = NULL;
    array[1]->choice1 = array[2];
    array[1]->choice2 = array[2];
    array[2]->choice1 = array[3];
    array[2]->choice2 = array[4];
    array[2]->choice3 = array[5];
    array[3]->choice1 = array[6];
    array[3]->choice2 = array[7];
    array[4]->choice1 = array[8];
    array[4]->choice2 = array[9];
    array[5]->choice1 = array[10];
    array[5]->choice2 = array[11];
    array[6]->choice1 = array[12];
    array[6]->choice2 = array[13];
    array[7]->choice1 = array[2];
    array[7]->choice2 = array[2];
    array[8]->choice1 = array[12];
    array[8]->choice2 = array[9];
    array[9]->choice1 = array[14];
    array[9]->choice2 = array[12];
    array[10]->choice1 = array[9];
    array[10]->choice2 = array[2];
    array[11]->choice1 = array[15];
    array[11]->choice2 = array[16];
    array[12]->choice1 = array[15];
    array[12]->choice2 = array[16];
    array[13]->choice1 = array[15];
    array[13]->choice2 = array[16];
    array[14]->choice1 = array[15];
    array[14]->choice2 = array[16];
    array[15]->choice1 = array[19];
    array[15]->choice2 = array[20];
    array[16]->choice1 = array[17];
    array[16]->choice2 = array[18];
    array[17]->choice1 = array[15];
    array[17]->choice2 = array[21];
    array[18]->choice1 = array[22];
    array[18]->choice2 = array[23];
    array[19]->choice1 = array[0];
    array[19]->choice2 = NULL;
    array[20]->choice1 = array[0];
    array[20]->choice2 = NULL;
    array[21]->choice1 = array[15];
    array[21]->choice2 = array[20];
    array[22]->choice1 = array[19];
    array[22]->choice2 = NULL;
    array[23]->choice1 = array[19];
    array[23]->choice2 = NULL;
    return array[0];
}


int main() {
    
    scene* head,*save;
     head = create();
     save = NULL;
     char c;
     run(head);
   while (1) {
        system("cls");
        printf("--------------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", head->description);
        printf("--------------------------------------------------------------------------------------------------------------\n");
        printf("OPTIONS: ");
        printf("U : Undo    ");
        printf("R : Redo    ");
        printf("S : Save this point    ");
        printf("G : Go to saved point    ");
        printf("E : Exit game    ");
        printf("D : Display stack\n");
        printf("--------------------------------------------------------------------------------------------------------------\n");
        printf("Enter choice: ");
        scanf(" %c", &c); 
    
        switch (c) {
            case '1':
                if (head->choice1){
                    head = head->choice1;
                    run(head);
                }
                else
                    printf("No path for choice 1.\n");
                break;

            case '2':
               
                if (head->choice2){
                    head = head->choice2;
                      run(head);
            }
                else if (head == array[0]) {
                      printf("\nExiting the game. Goodbye!\n");
                     exit(0);
                }
                else
                    printf("No path for choice 2.\n");
                break;

            case '3':
                run(head);
                if (head->choice3)
                    head = head->choice3;
                else
                    printf("No path for choice 3.\n");
                break;

            case 'U':
                head = undo();
                break;

            case 'R':
                head = redo();
                break;

            case 'S':
                save = head;
                printf("SAVED the following scene.\n");
                break;

            case 'G':
                if (save)
                    head = gotosave(save);
                else
                    printf("No saved point found.\n");
                break;

            case 'D':
                display();
                break;

            case 'E':
                printf("\nExiting the game!\n");
                exit(0);

            default:
                printf("Invalid choice, try again.\n");
                break;
        }
        printf("Press Enter to Continue");
        getchar();
        getchar();
    }

    return 0;
}
