#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

int  board[8][8];
int selectedX = 0, selectedY = 0;
bool enterPressed = 0;
const int windowWidth = 1920;
const int windowHeight = 1080;
const int cellSize = windowWidth / 17;
const int gemSpacing = 5;
int score = 0;


//*************************************************(FUNCTION TO SWAP GEMS)******************************************************************

void swap_gems(int x1, int x2, int y1, int y2)
{
	int temp = board[x1][y1];
	board[x1][y1] = board[x2][y2];
	board[x2][y2] = temp;
}


//****************************************(FUNCTION TO CHECK IDENTICAL ADJACENT GEMS  )*****************************************************************

bool check_horizontal(int i, int j, int num)
{
	if (j > 1)
	{
		if (board[i][j - 1] != num && board[i][j - 2] != num)
			return true;
	}
	else
		return true;

	return false;
}


bool check_vertical(int i, int j, int num)
{
	if (i > 1)
	{
		if (board[i - 1][j] != num && board[i - 2][j] != num)
			return true;
	}
	else
		return true;

	return false;
}


//*************************************************(FUNCTION TO DRAW THE BOARD)******************************************************************
void drawBoard(RenderWindow& window, const int cellSize)
{
	bool isWhite = true; // For alternate colors in the grid
	RectangleShape box(Vector2f(cellSize, cellSize));

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (isWhite)
			{
				box.setFillColor(Color(255, 255, 255));
			}
			else
			{
				box.setFillColor(Color(128, 128, 128));
			}
			isWhite = !isWhite; // Toggle color for the next box
			box.setPosition((i + 0.1) * cellSize, (j + 0.1) * cellSize);
			window.draw(box);
		}
		// Flip the color for the next row
		isWhite = !isWhite;
	}
}


//*************************************************(FUNCTION TO SET BOARDS)******************************************************************
void set_board()
{
	srand(time(0));
	int num;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			num = rand() % 7 + 1;
			board[i][j] = num;
		}
	}
}



//*************************************************(FUNCTION TO DISPLAY GEMS ON CONSOLE)******************************************************************

void display_board()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j] << " ";

		}
		cout << endl;
	}
}


//*************************************************(FUNCTION TO Make move)******************************************************************

void make_move()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			//**************************************************(5 Match Destroy)******************************************************************

			// Check for horizontal five-match at the elbow

			if (j + 3 < 8 && i + 1 < 8 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i + 1][j])
			{
				board[i][j] = 8;
				board[i][j + 1] = rand() % 7 + 1;
				board[i][j + 2] = rand() % 7 + 1;
				board[i][j + 3] = rand() % 7 + 1;
				board[i + 1][j] = rand() % 7 + 1;
				score += 250;
			}

			// Check for vertical five-match at the elbow

			if (i + 3 < 8 && j + 1 < 8 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i][j + 1])
			{
				board[i][j] = 8;
				board[i + 1][j] = rand() % 7 + 1;
				board[i + 2][j] = rand() % 7 + 1;
				board[i + 3][j] = rand() % 7 + 1;
				board[i][j + 1] = rand() % 7 + 1;
				score += 250;
			}


			//**************************************************(4 Match Destroy)******************************************************************

			// Check for horizontal adjacent four-match

			if (j + 3 < 8 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3])
			{
				board[i][j] = 8;
				board[i][j + 1] = rand() % 7 + 1;
				board[i][j + 2] = rand() % 7 + 1;
				board[i][j + 3] = rand() % 7 + 1;
				score += 150;
			}

			// Check for vertical adjacent four-match

			if (i + 3 < 8 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j])
			{
				board[i][j] = 8;
				board[i + 1][j] = rand() % 7 + 1;
				board[i + 2][j] = rand() % 7 + 1;
				board[i + 3][j] = rand() % 7 + 1;
				score += 150;
			}



			//**************************************************(3 Match Destroy)******************************************************************

			// Checks for horizontal matches

			if (j + 2 < 8 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
			{
				board[i][j] = rand() % 7 + 1;
				board[i][j + 1] = rand() % 7 + 1;
				board[i][j + 2] = rand() % 7 + 1;
				score += 50;

			}

			// Check for vertical matches

			if (i + 2 < 8 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
			{
				board[i][j] = rand() % 7 + 1;
				board[i + 1][j] = rand() % 7 + 1;
				board[i + 2][j] = rand() % 7 + 1;
				score += 50;
			}

		}
	}
}


//**********************************************(FUNCTION TO DISPLAY THE SCORE)*********************************************************


void displayScore(RenderWindow& window)
{
	// Use SFML text object to display score
	Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		cout << "Failed to load file";
	}

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + to_string(score));
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(windowWidth - 400, 20);

	window.draw(scoreText);
}

//**********************************************(FUNCTION TO DISPLAY THE TIME)*********************************************************


void displayTime(RenderWindow& window, Time clock)
{
	// Use SFML text object to display score
	Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		cout << "Failed to load file";
	}

	int time = 60 - static_cast<int>(clock.asSeconds());

	Text timerText;
	timerText.setFont(font);
	timerText.setString("Time left: " + to_string(time) + "s");
	timerText.setCharacterSize(60);
	timerText.setFillColor(Color::White);
	timerText.setPosition(windowWidth - 400, 100);

	window.draw(timerText);
}


//**********************************************(THE MAIN FUNCTION OF THE GAME)*********************************************************


int main()
{
	set_board();
	make_move();
	display_board();

	Texture arr[9];
	Clock timer;
	Time clock;

	ifstream inFile("Highscore.txt");
	ofstream outFile("Score.txt");




	//**************************************************(TEXTURE ERROR HANDLING)*****************************************************************

	if (!arr[0].loadFromFile("images/l.jpg"))
	{
		cout << "Cannot load image";
	}

	if (!arr[1].loadFromFile("images/red.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[2].loadFromFile("images/irridecent.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[3].loadFromFile("images/yellow.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[4].loadFromFile("images/purple.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[5].loadFromFile("images/blue.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[6].loadFromFile("images/green.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[7].loadFromFile("images/orange.png"))
	{
		cout << "Cannot load image";
	}

	if (!arr[8].loadFromFile("images/special.png"))
	{
		cout << "Cannot load image";
	}

	//*************************************************(CREATING THE WINDOW OF THE GAME)***********************************************************

	RenderWindow window(VideoMode(windowWidth, windowHeight), "Bejewelled Blitz");


	//*************************************************(SETTING UP THE CURSOR)*****************************************************************

	float cursorRow = 0.1, cursorColumn = 0.1;
	RectangleShape cursor;
	cursor.setSize(Vector2f(cellSize, cellSize));
	cursor.setPosition((cursorRow)*cellSize, (cursorColumn)*cellSize);
	cursor.setFillColor(Color(255, 255, 255, 0));
	cursor.setOutlineThickness(8.0);
	cursor.setOutlineColor(Color::Magenta);

	//****************************************(LOADING TEXTURE OF GEMS)*****************************************************************
	Texture rectangleTexture, circleTexture, squareTexture, triangleTexture, diamondTexture, orangeTexture, greenTexture;
	rectangleTexture.loadFromFile("images/red.png");
	circleTexture.loadFromFile("images/irridecent.png");
	squareTexture.loadFromFile("images/yellow.png");
	triangleTexture.loadFromFile("images/purple.png");
	diamondTexture.loadFromFile("images/blue.png");
	orangeTexture.loadFromFile("images/orange.png");
	greenTexture.loadFromFile("images/green.png");

	//****************************************(CREATING SPRITES FOR GEMS)*****************************************************************

	Sprite rectangleSprite(rectangleTexture);
	Sprite circleSprite(circleTexture);
	Sprite squareSprite(squareTexture);
	Sprite triangleSprite(triangleTexture);
	Sprite diamondSprite(diamondTexture);
	Sprite orangeSprite(orangeTexture);
	Sprite greenSprite(greenTexture);

	//****************************************(HANDINLING SIZE OF GEMS)*****************************************************************

	rectangleSprite.setScale((float)cellSize / rectangleTexture.getSize().x, (float)cellSize / rectangleTexture.getSize().y);
	circleSprite.setScale((float)cellSize / circleTexture.getSize().x, (float)cellSize / circleTexture.getSize().y);
	squareSprite.setScale((float)cellSize / squareTexture.getSize().x, (float)cellSize / squareTexture.getSize().y);
	triangleSprite.setScale((float)cellSize / triangleTexture.getSize().x, (float)cellSize / triangleTexture.getSize().y);
	diamondSprite.setScale((float)cellSize / diamondTexture.getSize().x, (float)cellSize / diamondTexture.getSize().y);

	//****************************************(BACKGROUND COLOR OF WINDOW)*****************************************************************
	window.clear(Color::White);


	//****************************************(LOADING  GAME   ICON)*****************************************************************
	Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());



	//*************************************************(THIS IS THE GAME LOOP)******************************************************************

	score = 0;
	while (window.isOpen())
	{
		make_move();
		window.clear();
		drawBoard(window, cellSize);
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Sprite image;
				int s = board[i][j];
				image.setTexture(arr[s]);
				image.setPosition((i + 0.12) * cellSize, (j + 0.12) * cellSize); // Adjusting position based on cellSize
				image.setScale(((float)cellSize - 10) / arr[s].getSize().x, ((float)cellSize - 10) / arr[s].getSize().y);
				window.draw(image);
				float offsetX = (cellSize - image.getLocalBounds().width) / 2.0f;
				float offsetY = (cellSize - image.getLocalBounds().height) / 2.0f;

			}
		}


		window.draw(cursor);
		displayScore(window);
		displayTime(window, clock);


		//*************************************************(THIS THE EVENTS PART)******************************************************************

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == Keyboard::Enter)
				{
					enterPressed = 1;
				}
				if (event.key.code == Keyboard::Up && !enterPressed)
				{
					if (cursorColumn > 0.1)
					{
						// Ensure cursor doesn't go out of bounds
						cursorColumn--;
						cursor.setPosition(cursorRow * cellSize, cursorColumn * cellSize);
					}
					// Move selection up
					if (selectedY > 0)
						selectedY--;

				}
				if (event.key.code == Keyboard::Down && !enterPressed)
				{
					// Move the cursor down
					if (cursorColumn < 6.9)
					{
						// Ensure cursor doesn't go out of bounds
						cursorColumn++;
						cursor.setPosition(cursorRow * cellSize, cursorColumn * cellSize);
					}
					// Move selection down
					if (selectedY < 7)
						selectedY++;

				}
				if (event.key.code == Keyboard::Left && !enterPressed)
				{
					// Move the cursor left
					if (cursorRow > 0.1)
					{
						// Ensure cursor doesn't go out of bounds
						cursorRow--;
						cursor.setPosition(cursorRow * cellSize, cursorColumn * cellSize);
					}
					// Move selection left
					if (selectedY > 0)
						selectedX--;

				}
				if (event.key.code == Keyboard::Right && !enterPressed)
				{
					if (cursorRow < 6.9)
					{ // Ensure cursor doesn't go out of bounds
						cursorRow++;
						cursor.setPosition(cursorRow * cellSize, cursorColumn * cellSize);
					}
					// Move selection right
					if (selectedX < 7)
						selectedX++;
				}
				if (event.key.code == Keyboard::Up && enterPressed)
				{
					if (selectedY > 0)
					{
						swap(board[selectedX][selectedY], board[selectedX][selectedY - 1]);
					}
					enterPressed = 0;
					if (check_vertical(selectedX, selectedY, board[selectedX][selectedY]) || check_horizontal(selectedX, selectedY, board[selectedX][selectedY]))
					{
						make_move();
					}
				}

				if (event.key.code == Keyboard::Down && enterPressed)
				{
					if (check_vertical(selectedX, selectedY, board[selectedX][selectedY]) || check_horizontal(selectedX, selectedY, board[selectedX][selectedY]) && selectedY < 7)
					{
						swap(board[selectedX][selectedY], board[selectedX][selectedY + 1]);
						make_move();
					}
					enterPressed = 0;
				}

				if (event.key.code == Keyboard::Right && enterPressed)
				{
					if (selectedX < 7)
					{
						swap(board[selectedX + 1][selectedY], board[selectedX][selectedY]);
					}
					enterPressed = 0;
					if (check_vertical(selectedX, selectedY, board[selectedX][selectedY]) || check_horizontal(selectedX, selectedY, board[selectedX][selectedY]))
					{
						make_move();
					}
				}

				if (event.key.code == Keyboard::Left && enterPressed)
				{
					if (selectedX > 0)
					{
						swap(board[selectedX - 1][selectedY], board[selectedX][selectedY]);
					}
					enterPressed = 0;
					if (check_vertical(selectedX, selectedY, board[selectedX][selectedY]) || check_horizontal(selectedX, selectedY, board[selectedX][selectedY]))
					{
						make_move();
					}
				}
			}
		}
		clock = timer.getElapsedTime();
		window.display();
		int sec = static_cast<int>(clock.asSeconds());
		if (sec == 60)
		{
			window.close();
		}
	}
	outFile << "Highscore is: " << score;



	return 0;
}