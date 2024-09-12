#ifndef EVENT_WRAPPER_h
#define EVENT_WRAPPER_h

#include <SDL2/SDL.h>
#include <cstdint>

namespace SDL
{

using Event = SDL_Event;

bool PollEvent(Event& event);

enum class EventTypes : std::uint32_t
{
    FIRSTEVENT = SDL_FIRSTEVENT,     /**< Unused (do not remove) */

    /* Application events */
    QUIT = SDL_QUIT, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    APP_TERMINATING = SDL_APP_TERMINATING,        /**< The application is being terminated by the OS
                                                       Called on iOS in applicationWillTerminate()
                                                       Called on Android in onDestroy()
                                                  */
    APP_LOWMEMORY = SDL_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
                                                     Called on iOS in applicationDidReceiveMemoryWarning()
                                                     Called on Android in onLowMemory()
                                                */
    APP_WILLENTERBACKGROUND = SDL_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                                                Called on iOS in applicationWillResignActive()
                                                                Called on Android in onPause()
                                                           */
    APP_DIDENTERBACKGROUND = SDL_APP_DIDENTERBACKGROUND,   /**< The application did enter the background and may not get CPU for some time
                                                                Called on iOS in applicationDidEnterBackground()
                                                                Called on Android in onPause()
                                                           */
    APP_WILLENTERFOREGROUND = SDL_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                                                Called on iOS in applicationWillEnterForeground()
                                                                Called on Android in onResume()
                                                           */
    APP_DIDENTERFOREGROUND = SDL_APP_DIDENTERFOREGROUND,  /**< The application is now interactive
                                                               Called on iOS in applicationDidBecomeActive()
                                                               Called on Android in onResume()
                                                          */

    LOCALECHANGED = SDL_LOCALECHANGED,  /**< The user's locale preferences have changed. */

    /* Display events */
    DISPLAYEVENT = SDL_DISPLAYEVENT,  /**< Display state change */

    /* Window events */
    WINDOWEVENT = SDL_WINDOWEVENT,  /**< Window state change */
    SYSWMEVENT  = SDL_SYSWMEVENT,   /**< System specific event */

    /* Keyboard events */
    KEYDOWN         = SDL_KEYDOWN,          /**< Key pressed */
    KEYUP           = SDL_KEYUP,            /**< Key released */
    TEXTEDITING     = SDL_TEXTEDITING,      /**< Keyboard text editing (composition) */
    TEXTINPUT       = SDL_TEXTINPUT,        /**< Keyboard text input */
    KEYMAPCHANGED   = SDL_KEYMAPCHANGED,    /**< Keymap changed due to a system event such as an
                                                      input language or keyboard layout change.
                                            */
    TEXTEDITING_EXT = SDL_TEXTEDITING_EXT,  /**< Extended keyboard text editing (composition) */

    /* Mouse events */
    MOUSEMOTION     = SDL_MOUSEMOTION,      /**< Mouse moved */
    MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,  /**< Mouse button pressed */
    MOUSEBUTTONUP   = SDL_MOUSEBUTTONUP,    /**< Mouse button released */
    MOUSEWHEEL      = SDL_MOUSEWHEEL,       /**< Mouse wheel motion */

    /* Joystick events */
    OYAXISMOTION      = SDL_JOYAXISMOTION,      /**< Joystick axis motion */
    JOYBALLMOTION     = SDL_JOYBALLMOTION,      /**< Joystick trackball motion */
    JOYHATMOTION      = SDL_JOYHATMOTION,       /**< Joystick hat position change */
    JOYBUTTONDOWN     = SDL_JOYBUTTONDOWN,      /**< Joystick button pressed */
    JOYBUTTONUP       = SDL_JOYBUTTONUP,        /**< Joystick button released */
    JOYDEVICEADDED    = SDL_JOYDEVICEADDED,     /**< A new joystick has been inserted into the system */
    JOYDEVICEREMOVED  = SDL_JOYDEVICEREMOVED,   /**< An opened joystick has been removed */
    JOYBATTERYUPDATED = SDL_JOYBATTERYUPDATED,  /**< Joystick battery level change */

    /* Game controller events */
    CONTROLLERAXISMOTION                       = SDL_CONTROLLERAXISMOTION,          /**< Game controller axis motion */
    CONTROLLERBUTTONDOWN                       = SDL_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
    CONTROLLERBUTTONUP                         = SDL_CONTROLLERBUTTONUP,            /**< Game controller button released */
    CONTROLLERDEVICEADDED                      = SDL_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
    CONTROLLERDEVICEREMOVED                    = SDL_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
    CONTROLLERDEVICEREMAPPED                   = SDL_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */
    CONTROLLERTOUCHPADDOWN                     = SDL_CONTROLLERTOUCHPADDOWN,        /**< Game controller touchpad was touched */
    CONTROLLERTOUCHPADMOTION                   = SDL_CONTROLLERTOUCHPADMOTION,      /**< Game controller touchpad finger was moved */
    CONTROLLERTOUCHPADUP                       = SDL_CONTROLLERTOUCHPADUP,          /**< Game controller touchpad finger was lifted */
    CONTROLLERSENSORUPDATE                     = SDL_CONTROLLERSENSORUPDATE,        /**< Game controller sensor was updated */
    CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3 = SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
    CONTROLLERSTEAMHANDLEUPDATED               = SDL_CONTROLLERSTEAMHANDLEUPDATED,  /**< Game controller Steam handle has changed */

    /* Touch events */
    FINGERDOWN   = SDL_FINGERDOWN,
    FINGERUP     = SDL_FINGERUP,
    FINGERMOTION = SDL_FINGERMOTION,

    /* Gesture events */
    DOLLARGESTURE = SDL_DOLLARGESTURE,
    DOLLARRECORD  = SDL_DOLLARRECORD,
    MULTIGESTURE  = SDL_MULTIGESTURE,

    /* Clipboard events */
    CLIPBOARDUPDATE = SDL_CLIPBOARDUPDATE,  /**< The clipboard or primary selection changed */

    /* Drag and drop events */
    DROPFILE     = SDL_DROPFILE,      /**< The system requests a file open */
    DROPTEXT     = SDL_DROPTEXT,      /**< text/plain drag-and-drop event */
    DROPBEGIN    = SDL_DROPBEGIN,     /**< A new set of drops is beginning (NULL filename) */
    DROPCOMPLETE = SDL_DROPCOMPLETE,  /**< Current set of drops is now complete (NULL filename) */

    /* Audio hotplug events */
    AUDIODEVICEADDED   = SDL_AUDIODEVICEADDED,    /**< A new audio device is available */
    AUDIODEVICEREMOVED = SDL_AUDIODEVICEREMOVED,  /**< An audio device has been removed. */

    /* Sensor events */
    SENSORUPDATE = SDL_SENSORUPDATE, /**< A sensor was updated */

    /* Render events */
    RENDER_TARGETS_RESET = SDL_RENDER_TARGETS_RESET,  /**< The render targets have been reset and their contents need to be updated */
    RENDER_DEVICE_RESET  = SDL_RENDER_DEVICE_RESET,   /**< The device has been reset and all textures need to be recreated */

    /* Internal events */
    POLLSENTINEL = SDL_POLLSENTINEL,  /**< Signals the end of an event poll cycle */

    /** Events SDL_USEREVENT through SDL_LASTEVENT are for your use,
     *  and should be allocated with SDL_RegisterEvents()
     */
    USEREVENT = SDL_USEREVENT,

    /**
     *  This last event is only for bounding internal arrays
     */
    LASTEVENT = SDL_LASTEVENT
};

}

bool operator==(Uint32 type, SDL::EventTypes event_type);

#endif
