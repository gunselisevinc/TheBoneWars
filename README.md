# TheBoneWars
The Bone Wars: An Archeological Challenge

## Project Description
The Bone Wars (Great Dinasour Rush) is a board game that relies on an imaginary senario of famous archeologists Edward Drinker Cope (of the Academy of Natural Sciences of Philadelphia) and Othniel Charles Marsh (of the Peabody Museum of Natural History at Yale). 

In this game, assume that there are two players Cope, and Marsh that are positioned on opposite ends of an island in the ocean. The island is a square shape platform made of n x n elements. The archeologists strive to find all of the hidden bones. At the end of the game, the player with more bone score wins the game. The players start the game with the same energy. With each move, they spend one energy and require supplements such as food and water. Furthermore, in this initially peaceful looking island, unfortunately there are some hidden booby traps that would decrease the energy of the players. The energy of the player keeps on reducing in case they jump on a cell with a trap. Once the player hits a trap, in addition to usual one energy spent, an additional 0.25 unit is reduced until the player finds medical supplies. If one of the players dies (energy reaches 0) s/he can still win the game. The other player may still need to collect bones for a better score. Of course, in case one of the players collect more than half of the available bone score, the game ends with victory for this player.

### Hidden Elements
The hidden elements can be one of the following:
* Bones
* Traps
* Food
* Water
* Medical supplies

The size of the board for the game will be specified by the players; however, the board is always a square shape, and the size of the board should be at least 5 x 5. For this game, the program randomly hides 3 times floor division of n^2/25 many of bones, 2 times floor division of n^2/25 many of traps, 3 times floor division of n^2/25 many of food, 2 times floor division of n^2/25 many of water and a floor division of n^2/25 many of medical supply resources across the grid randomly. 

## Game Rules
The game begins by generating a random number between n and 2n, inclusive which indicates the initial energy of Cope and Marsh. At each turn, the current state of the game board should be displayed as well as the total score of bones for each player.
* At the beginning of each turn, the players should choose the x and y coordinates on the board.
* In case there is any kind of resource at the selected coordinate, all the cells which involve the resource will become visible.
* At each turn, the program should also generate a random number, between 1 and 6 (inclusive). This will be our dice effect.
  * If the dice value is 6, then the 8 neighbours (can be less than 8 on the leftmost and rightmost columns and top and bottom rows. Especially in the corners, we will have 3 neighbours) will be exposed to the player and all the resources will be gathered. In case there are traps, they will not be effective.
  * If the dice value is 1, in case the player has landed on a trap, it is not going to be effective.
  * The other outcomes will not have any special effects.
  The objective of the game is to score better bone points than the other player.

### Resources and Their Effects
On each grid, the resource types and coordinates will be assigned automatically (randomly). That is to say, in case there are 3 foods to be placed, the type (Burger, Chips, Nugets) and the location on the grid will be specified randomly. The same condition holds for types and coordinates of bones as well. The effects of each resource can be given as follows:

Resource | Effect | Size | Character Used for Representation
-------- | ------ | ---- | ---------------------------------
Bone (Full Body) | +100 bone score | 2 | F
Bone (Skull) | +50 bone score | 1 | S
Bone (Ordinary) | +20 bone score | 1 | O
Food Burger | +4 energy | 2 | B
Food Nuggets | +3 energy | 2 | N
Food Chips | +2 energy | 1 | C
Water | +1 energy | 1 | W
Medical Supplies | Stops Trap Effect | 1 | M
Trap | Bad News! | 1 | T

After the resources have been positioned, the game proceeds in a series of rounds. In each round, each player takes a turn to announce a target cell in the grid. The computer then announces the outcome of the random numbers and the actions to be followed. The grid is then updated accordingly.

## Implementation Details
A base abstract class "Resources" is created which has member variables for size and representing character. There are five sub-classes of resources (trap included) for five distinct types (Food and bones are further divided, but you are free in implementing these). The resources gathered by each player are held in a structure. In each turn, the structure used to keep the resources is traversed to calculate the total score, energy and current condition (is the player hurt from the trap and in need for medical attention or not). For each three Food items in the structure, the energy can be increased one point in each round since the archaeologist with a good diet would develop a stronger immune system to survive. An "Archeologist" class is created for each player. Each player has list of gathered resources. A "Grid" class is created, which is associated with the most up to date state of the island. Each player object has access to the same grid object.

### Deployment of Resources
The deploy_resources function of the grid will randomly deploy resources at the beginning of the game. The resources may be placed vertically, horizontally or diagonally.

### Gathering
Each player is gathered in turns. Before and after the choosing the coordinates, the last version of grids is shown. The program doesn't allow the players to gather from the same coordinates more than once.

If one of the player collects more than half of the available bone scores, the game ends and the program shows the winner and looser with the details of the resources gathered.
