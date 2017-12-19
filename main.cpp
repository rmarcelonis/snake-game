#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int widthTiles = 30, heightTiles = 30;
int size = 16;
int w = size * widthTiles;
int h = size * heightTiles;

int moveDir, snakeSize = 6;

struct Snake { int x,y; } s[100];

struct Fruit { int x,y; } f;

void Tick()
 {
    // snake movement
    for (int i = snakeSize; i > 0; --i)
    {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
    }

    // snake movement control
    switch(moveDir)
    {
        case 0: // down
            s[0].y++;
            break;
        case 1: // left
            s[0].x--;
            break;
        case 2: // right
            s[0].x++;
            break;
        case 3: // up
            s[0].y--;
            break;
        default:
            break;
    }

    // consume and regenerate fruit in random location
	if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        snakeSize++;
        f.x=rand() % widthTiles;
        f.y=rand() % heightTiles;
    }

    // relocate an out-of-bounds snake
    if (s[0].x>widthTiles)  { s[0].x = 0; }
    if (s[0].x<0)           { s[0].x = widthTiles; }
    if (s[0].y>heightTiles) { s[0].y = 0; }
    if (s[0].y<0)           { s[0].y = heightTiles; }

    // divide snake where the head intersects the body
    for (int i = 1; i < snakeSize; i++)
    {
       if (s[0].x==s[i].x && s[0].y==s[i].y) { snakeSize = i; }
    }
 }

int main()
{
	srand(time(0));

    RenderWindow window(VideoMode(w, h), "Simple Snake");

	Texture t1,t2,t3;
	t1.loadFromFile("assets/black.png");
	t2.loadFromFile("assets/red.png");
	t3.loadFromFile("assets/green.png");

	Sprite sprite1(t1), sprite2(t2), sprite3(t3);

	Clock clock;
    	float timer = 0, delay = 0.1;

	f.x = 0;
    	f.y = 0;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        	timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) { moveDir = 1; }
	    	if (Keyboard::isKeyPressed(Keyboard::Right)){ moveDir = 2; }
	    	if (Keyboard::isKeyPressed(Keyboard::Up))   { moveDir = 3; }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { moveDir = 0; }

		if (timer > delay)
        	{
            		timer = 0;
            		Tick();
        	}

    window.clear();
    // draw background
    for (int i = 0; i < widthTiles; i++)
    {
        for (int j = 0; j < heightTiles; j++)
        {
            	sprite1.setPosition(i*size, j*size);
            	window.draw(sprite1);
        }
    }

    // draw snake
    for (int i = 0; i < snakeSize; i++)
	{
	    	sprite3.setPosition(s[i].x*size, s[i].y*size);
	    	window.draw(sprite3);
	}

   // draw fruit
    sprite2.setPosition(f.x*size,  f.y*size);
    window.draw(sprite2);
    window.display();
	 
    }
	
    return 0;
}
