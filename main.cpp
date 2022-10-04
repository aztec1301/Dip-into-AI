/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>
#include"glm/glm.hpp"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>
//map related
#include "MapObject.h"
#include "Nodes.h"
#include "NodeMap.h"
//agent related
#include "agent.h"
//MapObjects
#include "Gemstones.h"
#include "Lever.h"
#include "Princess.h"
//StateMachine related
#include "FSM.h"
#include "State.h"
//Decision Tree Related
#include "AorQDecision.h"
#include "AorBAnswersDecision.h"
#include "Decision.h"
//Behaviours
#include "GemHunt.h"
#include "LeverHunting.h"
#include "PrincessSaving.h"
#include "Dancing.h"
#include "Death.h"
#include "Attack.h"
#include "Guard.h"
#include "GoToPost.h"
//Conditions
#include "GemsCollected.h"
#include "LeverFlicked.h"
#include "PrincessSaved.h"
#include "IsDead.h"
#include "SeeOtherAgent.h"
#include "AtPost.h"

Node** GetStartPoint(NodeMap& nodeMap, int startingPoints)//used to create a node** of starting positions
{
    
    Node** startingPositions = new Node *[startingPoints];//create a node* array of starting positions
    for (int i = 0; i < startingPoints; i++)//laod them in from the nodemap
    {
        switch (i)
        {
        case 0:
            startingPositions[i] = nodeMap.GetNode(6, 0);//these are all the starting points
            break;

        case 1:
            startingPositions[i] = nodeMap.GetNode(21, 0);
            break;

        case 2:
            startingPositions[i] = nodeMap.GetNode(49, 4);
            break;

        case 3:
            startingPositions[i] = nodeMap.GetNode(49, 16);
            break;

        case 4:
            startingPositions[i] = nodeMap.GetNode(42, 28);
            break;

        case 5:
            startingPositions[i] = nodeMap.GetNode(10, 28);
            break;

        case 6:
            startingPositions[i] = nodeMap.GetNode(23, 28);
            break;

        case 7:
            startingPositions[i] = nodeMap.GetNode(0, 12);
            break;
        }
    }

    return startingPositions;
}

void DrawPath(std::vector<Node*> path, Color c)//Function to draw a line between each node in a given vector
{
    for (int i = 1; i < path.size(); ++i)//For each node inside the given vector
    {
        //Draw a line from this node to the node previously in the vector
        DrawLine((int)path[i]->position.x, (int)path[i]->position.y, (int)path[i - 1]->position.x, (int)path[i - 1]->position.y, c);
    }
}

void CreateFiniteStateMachine(Agent& hero)//create the finite state machine
{
    //FSM
    // Setup the finite state machine that will have control over our hero
    // ------------------------------------------------------------------------

    //conditions
    //Each of these will check to see if we can progress to the next state
    GemsCollected* collected = new GemsCollected(true);
    LeverFlicked* flicked = new LeverFlicked(false);
    PrincessSaved* saved = new PrincessSaved(false);
    IsDead* dying = new IsDead(false);

    //states
    //each state represents an action or set of actions the agent will follow
    State* gemHunting = new State(new GemHunt());
    State* leverHunting = new State(new LeverHunting());
    State* princessSaving = new State(new PrincessSaving());
    State* dance = new State(new Dancing());
    State* dead = new State(new Death());

//transitions
//The set of circumstances to move from one state to the next
    gemHunting->AddTransition(collected, leverHunting);
    gemHunting->AddTransition(dying, dead);
    leverHunting->AddTransition(flicked, princessSaving);
    leverHunting->AddTransition(dying, dead);
    princessSaving->AddTransition(saved, dance);

//FSM
//Create a FSM and add states to it
    FiniteStateMachine* fsm = new FiniteStateMachine(gemHunting);
    fsm->AddState(leverHunting);
    fsm->AddState(princessSaving);
    fsm->AddState(dance);
    fsm->AddState(dead);

    hero.SetBehavior(fsm);//assign it to our hero
    //------------------------------------------------------------------------
}

void CreateEnemyDecisionTree(std::vector<Agent*>& enemies)
{
    //Decision Tree for enemies
    //Setup the Decision tree our enemy agents will all use for their AI
    //-----------------------------------------------------------------------
    

    for (int i = 0; i < enemies.size(); ++i)//for every enemy
    {
        //Decisions
        //these dictate what happens to the decision making process dependent on the condition asigned to them
        //----------------------------------------------
        Decision* isDeadRootQ = new AorQDecision();
        Decision* seeAgentQ = new AorQDecision();
        Decision* atPostQ = new QAorBAnswersDecision();
        //----------------------------------------------

        //Behaviour setting
        // these are the behaviours that can result from certain lines of questioning
        //--------------------------------------
        isDeadRootQ->SetBehaviour(new Death());
        seeAgentQ->SetBehaviour(new Attack());
        atPostQ->SetBehaviour1(new Guard());
        atPostQ->SetBehaviour2(new GoToPost());
        //------------------------------------------

        //condition setting
        // these are the conditions that each Decision must ask, returning either true or false
        //------------------------------------------
        isDeadRootQ->SetCondition(new IsDead(false));
        seeAgentQ->SetCondition(new SeeOtherAgent(false));
        atPostQ->SetCondition(new AtPost(false));
        //------------------------------------------------

        //Next line of questioning
        // these are the questions to be asked after the first question is asked, and then the follow on from there
        //-----------------------------------------
        isDeadRootQ->SetNextQuestion(seeAgentQ);
        seeAgentQ->SetNextQuestion(atPostQ);
        //-------------------------------------------

        enemies[i]->SetRootDecision(isDeadRootQ);//assign it to the enemy
    }
    //------------------------------------------------------------------------
}


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 460;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    int heroHP = 20;//hp assigned to hero
    int enemyHP = 10;//hp assigned to enemy
    int agentSpeed = 80;//the speed at which an agent travels;
    int startingPoints = 8;//The 8 entrance points
    const int numberOfStones = 7;//maximum 7 (used to be 10, but I coded it so every gem will have 1 enemy, and you can only have a max of 7 enemies)
    int numberOfEnemies;//this will equal number of stones, one enemy for each stone

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    //Here we're creating the map and the nodemap. 
    //--------------------------------------
    MapObject* map = new MapObject("level0.map");
    NodeMap nodeMap = NodeMap();

    nodeMap.Initialise(map, "level0.map");
    //-------------------------------------


    //Loads in 8 valid starting positions into an array, then randomly picks one to
    // set the start point at
    //-----------------------------------
    int random = rand() % startingPoints;
    int pointUsed = random;
    Node* start = GetStartPoint(nodeMap, startingPoints)[pointUsed];
    
    //-----------------------------------

    //Creates an Array of gemstones equal to the specified number of gemstones
    //then asks the nodemap for a list of predetermined postions those gems can go
    //the gems are then provided wth one of those postions at random 
    //------------------------------------------------------------
    Gemstones gemstones[numberOfStones];
    
    std::vector<glm::vec2> positions = nodeMap.GetGemPositions();
    std::vector<int> numberCache;

    std::vector<Animation*> gemSprites;
    gemSprites.push_back(new Animation(Rectangle{ 0, 0, 15, 15 }, "DiamondSprite.txt"));
    gemSprites.push_back(new Animation(Rectangle{ 0, 0, 15, 15 }, "EmeraldSprite.txt"));
    gemSprites.push_back(new Animation(Rectangle{ 0, 0, 15, 15 }, "RubySprite.txt"));
    gemSprites.push_back(new Animation(Rectangle{ 0, 0, 15, 15 }, "SaphireSprite.txt"));

    for (int i = 0; i < numberOfStones; i++)
    {
        random = rand() % nodeMap.GetNumberofGemPositions();
        if (std::find(numberCache.begin(), numberCache.end(), random) == numberCache.end())
        {
            numberCache.push_back(random);
            gemstones[i].SetPosition(positions[random]);
            random = rand() % gemstones->GetNumberOfSprites();
            gemstones[i].SetAnimation(gemSprites[random]);
        }
        else
        {
            --i;
        }
    }
    //-----------------------------------------------------------------
    
    //create the only lever in the sim
    //---------------------------------------------------
    Lever* lever = new Lever();
    lever->SetPosition(nodeMap.GetLeverPosition());
    lever->SetAnimation(new Animation(Rectangle{ 0, 0, 10, 10 }, "Button.txt"));
    nodeMap.SetLever(lever);
    //---------------------------------------------------

    //create our princess
    //---------------------------------------------------
    Princess* princess = new Princess(new Animation(Rectangle{ 0, 0, 16, 16 }, "Princess.txt"));
    nodeMap.SetPrincess(princess);

    random = rand() % nodeMap.GetAmountOfPrincessSpawnPoints();

    princess->SetPosition(nodeMap.GetPrincessPositions()[random]);
    //-----------------------------------------------------


    //creates our Hero
    //------------------------------------------------
    Agent hero(new Animation(Rectangle{ 0,0,16,16 }, "HeroSpriteRun.txt"));
    hero.SetNode(start);//assign random start point
    hero.SetSpeed(agentSpeed);//assign base speed
    hero.SetHP(heroHP);//sets the hero's hp
    hero.SetGemNumber(numberOfStones);//tell the agent how many stones there are in the map
    hero.SetGemInfo(gemstones);//give the agent the information of each stone
    hero.SetNodeMap(nodeMap);//give the agent the nodemap to follow
    //------------------------------------------------

    //Creates enemies
    //-------------------------------------------------
    std::vector<Agent*> enemies;//make a vector to hold enemies
    numberCache.clear();//clear out the number cache we made before 
    numberCache.push_back(pointUsed);//make sure enemies can't spawn where the hero spawns
    numberOfEnemies = numberOfStones;//amount of enemies will always equal the same amount of gemstones on map
   
    for (int i = 0; i < numberOfEnemies; ++i)//for every enemy
    {
        random = rand() % startingPoints;//get a random start point

        if(std::find(numberCache.begin(), numberCache.end(), random) == numberCache.end())//if we haven't used it for another enemy
        {
            numberCache.push_back(random);//make sure that start point can no longer be used
            Agent* enemy = new Agent(new Animation(Rectangle{ 0, 0, 16, 16 }, "Slime.txt"));//give them sprite information
            start = GetStartPoint(nodeMap, startingPoints)[random];//set a Node* to that posiiton
            enemy->SetNode(start);//set the enemies position to te nodes position
            enemy->SetSpeed(agentSpeed);
            enemy->SetGemInfo(gemstones);
            enemy->SetHP(enemyHP);
            enemy->SetEnemy();
            enemy->SetGemToGuard(i);
            enemy->SetNodeMap(nodeMap);
            enemies.push_back(enemy);//put the enemy in the list
        }
        else //if we have already used it
        {
            --i;//ignore it
        }
    }
    //------------------------------------------------

    CreateFiniteStateMachine(hero);//create the finite state machine our hero will follow
    CreateEnemyDecisionTree(enemies);//create the decision tree our enemies will follow
    
    Color lineColor = { 255,0,0,255 };//Set a line Colour to be used for the hero
    Color enemyLineColor = { 0,0,255,255 };//Set a line Colour to be used for the hero

    // Main game loop
    float time = (float)GetTime();
    float deltaTime;//making some computer based time


    int mapChanged = 0;//used to check if the map has been changed

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        float fTime = (float)GetTime();
        deltaTime = fTime - time;
        time = fTime;
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        if (lever->IsFlipped() == true && mapChanged == 0)//if the lever is flipped but the map hasn't changed yet
        {
            map->InstantiateMap("level0b.map");//instantiate the new map object
            nodeMap.Initialise(map, "level0b.map");//initialise a new node map based on the new map
            hero.SetNodeMap(nodeMap);//give the hero a copy of the new node map
            ++mapChanged;//make sure we know ther maps been changed
        }
        if (princess->IsSaved() == true)//if the princess has been saved
        {
            for (Agent* a : enemies)//kill all the enmies, show off at least another state the decision tree has
            {
                a->SetHP(0);
            }
        }
        
        
        //Updating the hero
        //---------------------------------------------
      
        hero.Update(deltaTime);//the bulk of the agent's programming, taken care of by the agents state machine
        hero.TerrainCheck(nodeMap, agentSpeed);//checks what terrain we're on and sets speed accordingly
        //------------------------------------------------

        //updating the enemeies using their decision tree
        //----------------------------------------
        for (Agent* a : enemies)
        {
            a->Update(deltaTime);
            a->TerrainCheck(nodeMap, agentSpeed);
        }
        //----------------------------------------
       
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        map->Draw();//draw the map
        
        lever->Draw();//draw the lever
        princess->Draw();//draw the princess
        nodeMap.Draw();//draw the nodemap (can be commented out fot a cleaner look)
      
        for (int i = 0; i < numberOfStones; ++i)//if gemstone hasn't been collected, draw it
        {
            if (gemstones[i].IsCollected() == false)
            {
                gemstones[i].Draw();
            }
            
        }

        for (Agent* a : enemies)//draw the enemies
        {
            a->Draw();
            //DrawPath(a->GetPath(), enemyLineColor);//Draw a path along the enemeies projected travel (looks very messy, recomend leaving uncommented at higher numbers of enemies)
        }
      
        hero.Draw();//draw the hero
       
        DrawPath(hero.GetPath(), lineColor);//Draw a path along the hero's projected travel (can be commented out for a cleaner look)
        
       
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    
    map->~MapObject();
    nodeMap.~NodeMap();
    hero.~Agent();
    for (Agent* a : enemies)
    {
        a->~Agent();
    }
    for (Gemstones a : gemstones)
    {
        a.~Gemstones();
    }
    lever->~Lever();
    princess->~Princess();
    // 
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
