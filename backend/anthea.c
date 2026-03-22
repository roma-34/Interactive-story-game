#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char description[2000];
    char img[2000];
    struct Node *choice1;
    struct Node *choice2;
    struct Node *choice3;
} scene;

scene *Undo[100];
scene *Redo[100];
int top = -1;
int topredo = -1;

scene *array[24];
scene *save_point = NULL;

// Scene descriptions
char arr[24][2000] = {
    "Shadows over Anthea\\n\\n Anthea is a vibrant, bustling city with a rich history.\\n Queen Anthea rules with wisdom, but now a dangerous secret group called The Shadows is plotting to take over.\\n The city is safety depends on two brave soldiers-Valkyrie and Orion-who must uncover and stop these threats.\\n Are you ready to begin your adventure?\\n\\n1.Continue\\n\\n2.Exit\\n",

    "Character Selection\\n\\nChoose your hero:\\n\\n1. Valkyrie - A fearless soldier with sharp mind and combat skills.\\n\\n2. Orion - A calm strategist and expert fighter.\\n",

    "The Queen's Warning\\n\\nThe Queen has sent an urgent message. The Shadows plan to strike soon. Where do you want to start investigating?\\n\\n1. Old warehouse - Suspected hideout.\\n\\n2. City guards - Gather intelligence.\\n\\n3. Underground tunnels - Explore deeper.\\n",

    "Hidden Warehouse\\n\\nThe warehouse looks abandoned but might hide important clues.\\n\\n1. Search quietly for evidence.\\n\\n2. Set a trap and wait.",

    "Guards' Report\\n\\nA guard whispers that there might be a traitor working with The Shadows.\\n\\n1. Question the suspect directly.\\n\\n2. Follow the suspect secretly.",

    "Underground Tunnels\\n\\nThe tunnels are dark and filled with traps and enemies.\\n\\n1. Proceed carefully and look for signs.\\n\\n2. Light a fire to see better.",

    "The Evidence\\n\\nYou find clues pointing toward an impending attack.\\n\\n1. Alert the city guards.\\n\\n2. Search for the enemy's plan.",

    "Waiting Trap\\n\\nHours pass and no one appears. Your patience is tested.\\n\\n1. Keep waiting.\\n\\n2. Leave and report to the Queen.",

    "Direct Confrontation\\n\\nThe suspect is nervous but denies everything.\\n\\n1. Press for answers.\\n\\n2. Let go and watch.",

    "Secret Surveillance\\n\\nThe suspect leads you to a secret meeting of The Shadows.\\n\\n1. Interrupt now.\\n\\n2. Report and wait for backup.",

    "Careful Search\\n\\nYou find signs of recent activity in the tunnels.\\n\\n1. Follow the signs.\\n\\n2. Report to the Queen.",

    "Fire for Vision\\n\\nFire reveals enemies nearby. Battle is inevitable.\\n\\n1. Fight.\\n\\n2. Escape to regroup.",

    "Final Alert and Defense\\n\\nYou alert the city and prepare for battle as The Shadows advance.\\n\\n1. Lead the defense.\\n\\n2. Prepare a tactical retreat.",

    "Enemy's Plan\\n\\nYou uncover The Shadows' attack plan with times and locations.\\n\\n1. Intercept attackers early.\\n\\n2. Bolster city defenses.",

    "Confront The Shadows' Leader\\n\\nYou face the enemy leader in a decisive clash.\\n\\n1. Fight till end.\\n\\n2. Attempt negotiation.",

    "Victory or Loss\\n\\nThe clash with The Shadows reaches its peak. Your leadership has led to a fierce battle deciding the fate of Anthea.\\n\\n1. Celebrate the victory with your allies.\\n\\n2. Mourn the losses and vow to rebuild stronger.",

    "Tactical Retreat\\n\\nYou strategically retreat to save your people and gather strength for the next fight.\\n\\n1. Plan a counterattack.\\n\\n2. Seek allies in distant lands.",

    "Plan Counterattack\\n\\nYou mobilize your troops and plot a surprise strike against The Shadows.\\n\\n1. Launch the attack at dawn.\\n\\n2. Gather more intelligence before attacking.",

    "Seek Allies\\n\\nYour journey to find new allies brings you to ancient mountain tribes and mystical kingdoms willing to aid your cause.\\n\\n1. Visit the mountain tribes.\\n\\n2. Petition the Kingdom of Eldoria.",

    "Victory Celebration\\n\\nThe city of Anthea erupts in joy and celebration. Your bravery has restored peace.\\n\\n1. Restart adventure.\\n\\n2. Exit.",

    "Rebuild and Reflect\\n\\nThough the battle was costly, your leadership inspires hope. Together, Anthea begins healing and rebuilding.\\n\\n1. Restart.\\n\\n2. Exit.",

    "Intelligence Gathering\\n\\nYou gather new intelligence revealing weaknesses in The Shadows' plan.\\n\\n1. Move swiftly to attack.\\n\\n2. Strengthen defenses.",

    "Mountain Tribes\\n\\nThe mountain tribes welcome you as an ally. Their fierce warriors pledge loyalty.\\n\\n1. The story ends here with their support securing Anthea's safety.\\n\\n2. Restart or exit.",

    "Kingdom of Eldoria\\n\\nThe mystical kingdom of Eldoria grants your request for magical assistance.\\n\\n1. The story ends here with Eldoria's magical alliance ensuring hope.\\n\\n2. Restart or exit."};

// Image file names
char images[24][50] = {"1.jpg", "2.jpg", "3.jpg", "4.jpg",
                       "5.jpg", "6.jpg", "7.jpg", "8.jpg", "9.jpg",
                       "90.jpg", "91.png", "92.png", "93.png", "94.png",
                       "95.png", "96.png", "97.png", "98.png", "99.png",
                       "990.png", "991.png", "992.png", "993.png", "994.png"};

scene *create()
{
    for (int i = 0; i < 24; i++)
    {
        array[i] = (scene *)malloc(sizeof(scene));
        strcpy(array[i]->description, arr[i]);
        strcpy(array[i]->img, images[i]);
        array[i]->choice1 = NULL;
        array[i]->choice2 = NULL;
        array[i]->choice3 = NULL;
    }

    // Linking choices
    array[0]->choice1 = array[1];

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

    array[7]->choice1 = array[7];
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
    array[20]->choice1 = array[0];

    array[21]->choice1 = array[15];
    array[21]->choice2 = array[20];

    array[22]->choice1 = array[19];
    array[23]->choice1 = array[19];

    return array[0];
}

void pushUndo(scene *node)
{
    if (top < 99)
        Undo[++top] = node;
    topredo = -1;
}

scene *undo()
{
    if (top <= 0)
        return Undo[0];
    Redo[++topredo] = Undo[top--];
    return Undo[top];
}

scene *redo()
{
    if (topredo < 0)
        return Undo[top];
    Undo[++top] = Redo[topredo--];
    return Undo[top];
}

scene *gotoSave()
{
    if (save_point == NULL)
        return Undo[top];
    while (top > 0 && Undo[top] != save_point)
        top--;
    return Undo[top];
}

void displayProgress()
{
    printf("{\"history\":[");
    for (int i = 0; i <= top; i++)
    {
        printf("{\"description\":\"%s\",\"img\":\"%s\"}", Undo[i]->description, Undo[i]->img);
        if (i < top)
            printf(",");
    }
    printf("]}\n");
    fflush(stdout);
}

int main(void)
{
    scene *current = create();
    pushUndo(current);
    char cmd[10];
    printf("{\"description\":\"%s\",\"img\":\"%s\"}\n", current->description, current->img);
    fflush(stdout);
    while (fgets(cmd, sizeof(cmd), stdin))
    {
        cmd[strcspn(cmd, "\n")] = 0;

        int valid = 1;
        if (strlen(cmd) == 0)
        {
            continue;
        }
        else if (strcmp(cmd, "U") == 0)
        {
            current = undo();
        }
        else if (strcmp(cmd, "R") == 0)
        {
            current = redo();
        }
        else if (strcmp(cmd, "S") == 0)
        {
            save_point = current;
        }
        else if (strcmp(cmd, "G") == 0 && save_point)
        {
            current = gotoSave();
        }
        else if (strcmp(cmd, "D") == 0)
        {
            displayProgress();
            continue;
        }
        else if (strcmp(cmd, "E") == 0)
        {
            current = array[0];
            top = -1;
            topredo = -1;
            save_point = NULL;
            pushUndo(current);
            printf("{\"restart\":true,\"description\":\"%s\",\"img\":\"%s\"}\n", current->description, current->img);
            fflush(stdout);
            continue;
        }
        else if (strcmp(cmd, "1") == 0 && current->choice1)
        {
            current = current->choice1;
            pushUndo(current);
        }
        else if (strcmp(cmd, "2") == 0 && current->choice2)
        {
            current = current->choice2;
            pushUndo(current);
        }
        else if (strcmp(cmd, "3") == 0 && current->choice3)
        {
            current = current->choice3;
            pushUndo(current);
        }
        else
        {
            valid = 0;
        }

        if (!valid)
        {
            printf("{\"error\":\"Invalid choice! Please pick a valid option.\",\"description\":\"%s\",\"img\":\"%s\"}\n", current->description, current->img);
        }
        else
        {
            printf("{\"description\":\"%s\",\"img\":\"%s\"}\n", current->description, current->img);
        }
        fflush(stdout);
    }

    return 0;
}
