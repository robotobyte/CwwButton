// *****************************************************************************
//
// Button Class
// ------------
// Code by W. Witt; V1.00-beta-01; July 2016
//
// *****************************************************************************

#ifndef CwwButton_h
#define CwwButton_h

// *****************************************************************************

#include <Arduino.h>

// =============================================================================

class CwwButton {

  public:

    // Public Types:

    // Public Constants:

    // Public Variables:

    // Public Functions:

             CwwButton ( uint8_t pinOfButton, uint16_t debounceTimeMs = 10, boolean pinIsAnalog = false );
    virtual ~CwwButton ();

    boolean isLow        ( boolean debounce = false );
    boolean isHigh       ( boolean debounce = false );
    boolean hasChanged   ( boolean debounce = false );
    uint8_t currentState ( boolean debounce = false );

    boolean isLowStable        ();
    boolean isHighStable       ();
    boolean hasChangedStable   ();
    uint8_t currentStateStable ();

    boolean isStable        ();
    boolean isStableAtState ( uint8_t state );

    void     setDebounceTime     ( uint16_t debounceTimeMs );
    uint16_t valueOfDebounceTime ();

  private:

    // Private Constants:

    // Private Variables:

    uint8_t  pinOfButton;
    boolean  pinIsAnalog;
    uint16_t debounceTimeMs;
    uint8_t	 buttonStateLast;

    // Private Functions:

    uint8_t readPin ();

};

// *****************************************************************************

#endif

// *****************************************************************************
