//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define height_brik 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
   initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    /**
 * MEGA MEGA LOOP FOREVER!!!!!!!!
 */
    // initial velocity
    double velocityx1 = 2.0;
    double velocityy = 2.0;
    
    // number of lives initially
    int lives = LIVES;
    
    // number of bricks initially
    int bricks = COLS * ROWS;
    
    // number of points initially
    int points = 0;
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);  
    
    updateScoreboard(window, label, points);
    
    waitForClick();
    
    
    
    // follow mouse forever and keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    
        // to store (with '\0'), we need <= 3 chars
        
        
                
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) /2;
                double y = 579;
                setLocation(paddle, x, y);
                if (getX(paddle) + getWidth(paddle) >= getWidth(window))
                    {
                        setLocation(paddle, (400-200), 579);
                    }

                // bounce off left edge of window
                else if (getX(paddle) <= 0)
                {
                    setLocation(paddle, (0), 579);
                }
            }
        }
                  
    
    
    
    // bounce forever
    
        // move ball along x-axis
        double velocityx=drand48()*velocityx1;
        move(ball,velocityx, velocityy);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityx1 = -velocityx1;
            
        }
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives-=1;
            velocityy = -velocityy;
            char s[2];
            // convert i from int to string
            sprintf(s, "Lives: %i", lives);
            

        // update label
        setLabel(label, s);

        // center label
        double x = (getWidth(window) - getWidth(label)) / 2-100;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);
        waitForClick();
            
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityx1 = -velocityx1;
        }
        else if (getY(ball) <= 0)
        {
            velocityy = -velocityy;
        }

        // linger before moving again
        pause(10);
        //cheking fore detect 
        GObject object = detectCollision(window, ball);
        
        if (object==paddle)
        {
            velocityy = -velocityy;
        }
        else if (object!= NULL)
        {
            if (strcmp(getType(object), "GRect")==0)
            {
                velocityy = -velocityy;
                removeGWindow(window,object);
                bricks-=1;
                points+=1;
                updateScoreboard(window, label, points);
                
            }
        }
        
        
    
        
        
        
        
        
        
    }

      
    

    

    // game over
         char s[2];
            // convert i from int to string
            sprintf(s, "GAME OVER. points: %i", points);
            

        // update label
        setLabel(label, s);

        // center label
        double x = (getWidth(window) - getWidth(label)) / 2;
        double y = (getHeight(window) - getHeight(label)) / 2;
        setLocation(label, x, y);
        waitForClick();
        
        
    
    // wait for click before exiting
    
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{

    int width_brik = ((WIDTH/COLS)-2);
    
    char* colors[5]={"RED","GREEN", "BLUE","YELLOW","BROWN" };
    
    
    for (int i=0;i<COLS;i++)
    
      {
          for (int j=0;j<ROWS;j++)
          {
                GRect brick = newGRect( (1 + i*(width_brik+2)), (10 + j*(height_brik+2)), width_brik, height_brik);
                setFilled(brick, true);
                setColor(brick, colors[j%5]);
                add(window, brick);
                
          
          }
      }
      
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */

GOval initBall(GWindow window)
{
    // instantiate ball
    GOval ball = newGOval((WIDTH-ROWS*(height_brik+2)-10)/2-RADIUS, WIDTH-RADIUS, 2*RADIUS, 2*RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
    
}


/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // "This program draws a red rectangle
      GRect paddle = newGRect(100, 579, 200, 20);
      setFilled(paddle, true);
      setColor(paddle, "BLACK");
      add(window, paddle);
      return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
       
}
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "point: %i",points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
