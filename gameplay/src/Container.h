#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Control.h"
#include "Layout.h"

namespace gameplay
{

/**
 * A container is a UI control that can contain other controls.
 *
 * The following properties are available for containers:

 @verbatim
    container <containerID>
    {
         // Container properties.
         layout   = <Layout::Type>        // A value from the Layout::Type enum.  E.g.: LAYOUT_VERTICAL
         style    = <styleID>           // A style from the form's theme.
         alignment   = <Control::Alignment constant> // Note: 'position' will be ignored.
         position    = <x, y>    // Position of the container on-screen, measured in pixels.
         autoWidth   = <bool>
         autoHeight  = <bool>
         size        = <width, height>   // Size of the container, measured in pixels.
         width       = <width>   // Can be used in place of 'size', e.g. with 'autoHeight = true'
         height      = <height>  // Can be used in place of 'size', e.g. with 'autoWidth = true'
         scroll      = <Container::Scroll constant> // Whether scrolling is allowed and in which directions.
         scrollBarsAutoHide = <bool>    // Whether scrollbars fade out when not in use.
  
         // All the nested controls within this container.
         container 
         { 
             ...
         }

         label { }
         textBox { }
         button { }
         checkBox { }
         radioButton { }
         slider { }
    }
 @endverbatim
 */
class Container : public Control
{
public:

    /**
     * Constant used to auto-hide scrollbars.
     */
    static const int ANIMATE_SCROLLBAR_OPACITY = 8;

    /**
     * The definition for container scrolling.
     */
    enum Scroll
    {
        SCROLL_NONE        = 0,
        SCROLL_HORIZONTAL  = 0x01,
        SCROLL_VERTICAL    = 0x02,
        SCROLL_BOTH = SCROLL_HORIZONTAL | SCROLL_VERTICAL
    };

    /**
     * Get this container's layout.
     *
     * @return This container's layout object.
     */
    Layout* getLayout();

    /**
     * Add a control to this layout.
     * The control will be assigned the next available index.
     *
     * @param control The Control to add.
     *
     * @return The index assigned to the added Control.
     */
    unsigned int addControl(Control* control);

    /**
     * Insert a control at a specific index.
     *
     * @param control The control to add.
     * @param index The index at which to insert the control.
     */
    void insertControl(Control* control, unsigned int index);

    /**
     * Remove a control at a specific index.
     *
     * @param index The index from which to remove the control.
     */
    void removeControl(unsigned int index);

    /**
     * Remove a control with the given ID.
     *
     * @param id The ID of the control to remove.
     */
    void removeControl(const char* id);

    /**
     * Remove a specific control.
     *
     * @param control The control to remove.
     */
    void removeControl(Control* control);

    /**
     * Get the Control at a specific index.
     *
     * @param index The index at which to retrieve the Control.
     *
     * @return The Control at the given index.
     */
    Control* getControl(unsigned int index) const;

    /**
     * Get a Control with a specific ID that belongs to this Layout.
     *
     * @param id The ID of the Control to search for.
     */
    Control* getControl(const char* id) const;

    /**
     * Get the vector of controls within this container.
     *
     * @return The vector of the controls within this container.
     */
    const std::vector<Control*>& getControls() const;

    /**
     * Sets the allowed scroll directions for this container.
     *
     * @param scroll The allowed scroll directions for this container.
     */
    void setScroll(Scroll scroll);

    /**
     * Gets the allowed scroll directions for this container.
     *
     * @return The allowed scroll directions for this container.
     */
    Scroll getScroll() const;

    /**
     * Set whether scrollbars auto hidden when they become static.
     *
     * @param autoHide true to auto hide the scrollbars when they become static.
     */
    void setScrollBarsAutoHide(bool autoHide);

    /**
     * Whether scrollbars are always visible, or only visible while scrolling.
     *
     * @return Whether scrollbars are always visible.
     */
    bool isScrollBarsAutoHide() const;

    /**
     * @see AnimationTarget#getAnimation
     */
    Animation* getAnimation(const char* id = NULL) const;

    /**
     * @see AnimationTarget#getAnimationPropertyComponentCount
     */
    virtual unsigned int getAnimationPropertyComponentCount(int propertyId) const;

    /**
     * @see AnimationTarget#getAnimationProperty
     */
    virtual void getAnimationPropertyValue(int propertyId, AnimationValue* value);

    /**
     * @see AnimationTarget#setAnimationProperty
     */
    virtual void setAnimationPropertyValue(int propertyId, AnimationValue* value, float blendWeight = 1.0f);

protected:

    /**
     * Constructor.
     */
    Container();

    /**
     * Destructor.
     */
    virtual ~Container();

    /**
     * Create an empty container.  A container's layout type must be specified at creation time.
     *
     * @param type The container's layout type.
     *
     * @return The new container.
     */
    static Container* create(Layout::Type type);

    /**
     * Create a container with a given style and properties, including a list of controls.
     *
     * @param style The style to apply to this container.
     * @param properties The properties to set on this container, including nested controls.
     * @param theme The theme to search for control styles within.
     *
     * @return The new container.
     */
    static Container* create(Theme::Style* style, Properties* properties, Theme* theme);

    /**
     * Updates each control within this container,
     * and positions them according to the container's layout.
     *
     * @param container This container's parent container.
     * @param offset The offset.
     */
    virtual void update(const Control* container, const Vector2& offset);

    /**
     * Touch callback on touch events.  Controls return true if they consume the touch event.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @return Whether the touch event was consumed by a control within this container.
     *
     * @see Touch::TouchEvent
     */
    virtual bool touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
    
    /**
     * Keyboard callback on key events.  Passes key events on to the currently focused control.
     *
     * @param evt The key event that occured.
     * @param key If evt is KEY_PRESS or KEY_RELEASE then key is the key code from Keyboard::Key.
     *            If evt is KEY_CHAR then key is the unicode value of the character.
     * 
     * @see Keyboard::KeyEvent
     * @see Keyboard::Key
     */
    virtual void keyEvent(Keyboard::KeyEvent evt, int key);

    /**
     * Gets a Layout::Type enum from a matching string.
     *
     * @param layoutString The layout string to parse
     */
    static Layout::Type getLayoutType(const char* layoutString);

    /**
     * Returns whether this control is a container.
     * 
     * @return true if this is a container, false if not.
     */
    bool isContainer();

    /**
     * Returns whether this container or any of its controls have been modified and require an update.
     * 
     * @return true if this container or any of its controls have been modified and require an update.
     */
    virtual bool isDirty();

    /**
     * Adds controls nested within a properties object to this container,
     * searching for styles within the given theme.
     *
     * @param theme The them to add controls from
     * @param properties The properties to use.
     */
    void addControls(Theme* theme, Properties* properties);

    /**
     * Draws a sprite batch for the specified clipping rect .
     *
     * @param spriteBatch The sprite batch to use.
     * @param clip The clipping rectangle.
     * @param needsClear Whether it needs to be cleared.
     * @param cleared Whether it was previously cleared
     * @param targetHeight The targets height
     */
    virtual void draw(SpriteBatch* spriteBatch, const Rectangle& clip, bool needsClear, bool cleared, float targetHeight);

    /**
     * Update scroll position and velocity.
     */
    void updateScroll();

    /**
     * Applies touch events to scroll state.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @return Whether the touch event was consumed by scrolling within this container.
     *
     * @see Touch::TouchEvent
     */
    bool touchEventScroll(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

    /**
     * Get a Scroll enum from a matching string.
     *
     * @param scroll A string representing a Scroll enum.
     *
     * @return The Scroll enum value that matches the given string.
     */
    static Scroll getScroll(const char* scroll);

    /**
     * The container's layout.
     */
    Layout* _layout;
    /**
     * List of controls within the container.
     */
    std::vector<Control*> _controls;
    /**
     * Scrollbar top cap image.
     */
    Theme::ThemeImage* _scrollBarTopCap;
    /**
     * Scrollbar verticle image.
     */
    Theme::ThemeImage* _scrollBarVertical;
    /**
     * Scrollbar bottom cap image.
     */
    Theme::ThemeImage* _scrollBarBottomCap;
    /**
     * Scrollbar left cap image.
     */
    Theme::ThemeImage* _scrollBarLeftCap;
    /**
     * Scrollbar horizontal image.
     */
    Theme::ThemeImage* _scrollBarHorizontal;
    /**
     * Scrollbar horizontal image.
     */
    Theme::ThemeImage* _scrollBarRightCap;
    /** 
     * Flag representing whether scrolling is enabled, and in which directions.
     */
    Scroll _scroll;
    /** 
     * Scroll bar bounds
     */
    Rectangle _scrollBarBounds;
    /** 
     * How far this layout has been scrolled in each direction.
     */
    Vector2 _scrollPosition;
    /** 
     * Should the scrollbars auto hide. Default is false.
     */
    bool _scrollBarsAutoHide;
    /** 
     * Used to animate scrollbars fading out.
     */
    float _scrollBarOpacity;
    /** 
     * Whether the user is currently touching / holding the mouse down within this layout's container.
     */
    bool _scrolling;
    /** 
     * First scrolling touch x position
     */ 
    int _scrollingFirstX;
    /** 
     * First scrolling touch y position
     */ 
    int _scrollingFirstY;
    /** 
     * The last y position when scrolling
     */ 
    int _scrollingLastX;
    /** 
     * The last x position when scrolling
     */ 
    int _scrollingLastY;
    /** 
     * Time we started scrolling in the x
     */ 
    long _scrollingStartTimeX;
    /** 
     * Time we started scrolling in the y
     */ 
    long _scrollingStartTimeY;
    /** 
     * The last time we were scrolling
     */
    long _scrollingLastTime;
    /** 
     * Speed to continue scrolling at after touch release.
     */ 
    Vector2 _scrollingVelocity;
    /** 
     * Friction dampens velocity.
     */ 
    float _scrollingFriction;
    /** 
     * Are we scrolling to the right?
     */ 
    bool _scrollingRight;
    /** 
     * Are we scrolling down?
     */ 
    bool _scrollingDown;

private:

    /**
     * Constructor.
     */
    Container(const Container& copy);

    AnimationClip* _scrollBarOpacityClip;
    int _zIndexDefault;
};


/**
 * Sort funtion for use with _controls.sort(), based on Z-Order.
 * 
 * @param c1 The first control
 * @param c2 The second control
 * return true if the first controls z index is less than the second.
 */
bool sortControlsByZOrder(Control* c1, Control* c2);

}

#endif
