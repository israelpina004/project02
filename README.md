# Project 02 - Battleship

Names: Israel Pina, Esteak Shapin, Logan Ruzzier<br>
Period: 4

**Project Description:** We aimed to create a socket-based two-player game, specifically a recreation of Battleship. After the first player creates a single-use (non-forking) server he waits for a second player to connect to him, at which point there will be a continuous sharing of information between the two linked systems through a socket. Congruous with the original Battleship, each player has two boards to look at to help strategize their offensive and defensive game. Before the game begins, each player places their ships on the board, indicating the coordinates of their intended position. The players then take turns inputting a pair of coordinates to “fire." The program determines whether this shot was a hit or a miss. Both players will be immediately notified of the shot’s outcome, and the result will be indicated on each player’s pair of boards. The “firer” will see every square he has previously fired at, and whether this shot was a hit, on one of his boards (in this case the board devoid of ships). The “firee” will see every square that his opponent has fired at, and whether this shot was a hit, on one of his boards (in this case the board with the ships on it). After this, accordingly, the players switch roles. This cycle will repeat until one of the players has all of their ships “sunk” (this occurs when every square previously delineated to be part of a ship has been hit by the opponent), and their opponent wins. </br>

**User Interface:** The user interface is an SDL graphical window. Once the project file is run, the user is asked whether he wishes to “Create a game” or “Join a game,” which will decide whether the program follows the server- or client-side protocols for starting up. It waits for a connection before starting the game. Before any game-related communication takes place, the players must decide on the placement of their ships on the board. The program will prompt the player for the placement of one of the ships (i.e. “Please enter the desired coordinates of your submarine (3 spaces), followed by the desired orientation in the following format: “(X, N) Vertical/Horizontal”) before indicating on the player’s personal board the spaces this ship occupies. It must be checked before the ship is placed whether it does not fit on the board or overlaps another ship. Following the ship placement phase, the players will take turns sending coordinates to fire at (i.e. “Please enter the desired coordinates of your torpedo strike in the following format: “(X, N)”) and then receive the outcome of this shot. The hits/misses of your shots and the opponents will be indicated by varying colors on the squares of your graph-like board. Once one of the players wins by successfully hitting all of the opponents’ ships squares, they will receive a congratulatory message, followed by a prompt of whether they want a rematch (i.e. “Do you want to play again? “Y/N”). The opponent will receive a similar message, and should they both answer “Y,” the game will restart and they’ll pick spots for their ships once again.

**Technical Design:** This project relies on the use of sockets, similarly to how they were used in Work 23 (minus the forking server aspect). It also allocates memory to store the contents of the players' boards (2 each), and relies on 2-D array semantics to determine ship placements, hits, and displaying the board. For taking player inputs the program will need to handle files and stdin. It also relies on signal handling to provide the user with a more refined experience (you need to know when your opponent abandons the game!). The client may choose to leave at any point in the game for whatever reason. Israel and Logan focused on the socket-based communication and organizing the game, whereas Shapin accomplished the graphical points.

**Required Libraries:**<br>
-SDL

**How to install SDL:**<br>
For installing SDL through the Windows command line (MinGW), [this website provides a helpful tutorial in doing so.](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php)<br>
For macOS users, [use this tutorial.](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)<br>
For Linux users, [use this.](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php)<br>
If you have Ubunto, running "sudo apt-get install libsdl2-2.0" should install the SDL libraries.<br>

**Instructions:**<br>
-Users are prompted to set up or join a game when starting the program.<br>
-The one joining the game must type the host's IP address when asked to.<br>
-The host may NOT ctrl-C out of the game at any moment. Doing so will prevent future successful program runs.<br>
-Users are asked to place their ships prior to the game starting. The program asks for coordinates and if the user would like to orient their ship left, right, up, or down from those coordinates. Coordinates are formatted as (Letter)(Number) in this game, with the lowest letter being A and the highest being J. The lowest number is 1 and the highest is 9. More information on ship placement is available after pressing "2" on the startup menu.<br>
-Players attack by inputting coordinates when prompted to. The game ends if one of the player's ships have all sunken.

