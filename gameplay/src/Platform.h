#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "Touch.h"
#include "Keyboard.h"

namespace gameplay
{

class Game;

/**
 * Defines a platform.
 */
class Platform
{
public:

    /**
     * Destructor.
     */
    ~Platform();

    /**
     * Creates a platform for the specified game which is will interacte with.
     *
     * @param game The game to create a platform for.
     * 
     * @return The created platform interface.
     */
    static Platform* create(Game* game);

    /**
     * Begins processing the platform messages.
     *
     * This method handles all OS window messages and drives the game loop.
     * It normally does not return until the application is closed.
     * 
     * @return The platform message pump return code.
     */
    int enterMessagePump();
    
    /**
     * This method informs the platform that the game is shutting down 
     * and anything platform specific should be shutdown as well or halted
     * This function is called automatically when the game shutdown function is called
     */
    static void signalShutdown();
    
    /**
     * Gets the display width.
     * 
     * @return The display width.
     */
    static unsigned int getDisplayWidth();
    
    /**
     * Gets the display height.
     * 
     * @return The display height.
     */
    static unsigned int getDisplayHeight();

    /**
     * Gets the absolute platform time starting from when the message pump was started.
     *
     * @return The absolute platform time. (in milliseconds)
     */
    static long getAbsoluteTime();

    /**
     * Sets the absolute platform time since the start of the message pump.
     *
     * @param time The time to set (in milliseconds).
     */
    static void setAbsoluteTime(long time);

    /**
     * Gets whether vertical sync is enabled for the game display.
     * 
     * @return true if vsync is enabled; false if not.
     */
    static bool isVsync();

    /**
     * Sets whether vertical sync is enable for the game display.
     *
     * @param enable true if vsync is enabled; false if not.
     */
    static void setVsync(bool enable);

    /**
     * Set if multi-touch is enabled on the platform
     */
    static void setMultiTouch(bool enabled);

   /**
    * Is multi-touch mode enabled.
    */
    static bool isMultiTouch();

    /**
     * Gets the platform accelerometer values.
     * 
     * @param pitch The accelerometer pitch.
     * @param roll The accelerometer roll.
     */
    static void getAccelerometerValues(float* pitch, float* roll);

    /**
     * Swaps the frame buffer on the device.
     */
    static void swapBuffers();
    
    /**
     * Shows or hides the virtual keyboard (if supported).
     *
     * @param display true when virtual keyboard needs to be displayed and false otherwise.
     */
    static void displayKeyboard(bool display);

    /**
     * Touch callback on touch events. This method handles passing the touch event to the form or to the game.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @see Touch::TouchEvent
     */
    static void touchEventInternal(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

    /**
     * Keyboard callback on keyPress events.
     *
     * @param evt The key event that occured.
     * @param key If evt is KEY_PRESS or KEY_RELEASE then key is the key code from Keyboard::Key.
     *            If evt is KEY_CHAR then key is the unicode value of the character.
     * 
     * @see Keyboard::KeyEvent
     * @see Keyboard::Key
     */
    static void keyEventInternal(Keyboard::KeyEvent evt, int key);

    /**
     * Sleeps synchronously for the given amount of time (in milliseconds).
     *
     * @param ms How long to sleep (in milliseconds).
     */
    static void sleep(long ms);

private:

    /**
     * Constructor.
     */
    Platform(Game* game);

    /**
     * Constructor.
     */
    Platform(const Platform& copy);

    Game* _game;                // The game this platform is interfacing with.
};

}

#endif
