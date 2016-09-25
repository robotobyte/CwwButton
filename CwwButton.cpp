// ****************************************************************************
//
// Button Class
// ------------
// Code by W. Witt; V1.00-beta-01; July 2016
//
// ****************************************************************************

#include <limits.h>
#include <Arduino.h>

#include <CwwButton.h>

// ============================================================================
// Constructors, Destructor
// ============================================================================

CwwButton::CwwButton (
  uint8_t  pinOfButton,
  uint16_t debounceTimeMs,
  boolean  pinIsAnalog
) {

  this->pinOfButton    = pinOfButton;
  this->pinIsAnalog    = pinIsAnalog;
  this->debounceTimeMs = debounceTimeMs;

  pinMode ( pinOfButton, INPUT );
  buttonStateLast = readPin ();

}

// ----------------------------------------------------------------------------

CwwButton::~CwwButton () {

}

// ============================================================================
// Public Functions
// ============================================================================

boolean CwwButton::isLow ( boolean debounce ) {

  return currentState ( debounce ) == LOW;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwButton::isHigh ( boolean debounce ) {

  return currentState ( debounce ) == HIGH;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwButton::hasChanged ( boolean debounce ) {

  uint8_t buttonStateReference;

  buttonStateReference = buttonStateLast;
  return buttonStateReference != currentState ( debounce );

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint8_t CwwButton::currentState ( boolean debounce ) {

  uint8_t       buttonStateStart;
  uint8_t       buttonStateNow;
  unsigned long debounceStartTimeMs;

  buttonStateStart = readPin ();

  if ( debounce ) {
    debounceStartTimeMs = millis ();
    while ( millis() - debounceStartTimeMs < debounceTimeMs ) {
      buttonStateNow = readPin ();
      if ( buttonStateNow != buttonStateStart ) {
        buttonStateStart = buttonStateNow;
        debounceStartTimeMs = millis ();
      }
    }
  }

  buttonStateLast = buttonStateStart;

  return buttonStateStart;

}

// ----------------------------------------------------------------------------

boolean CwwButton::isLowStable () {

  return currentState ( true ) == LOW;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwButton::isHighStable () {

  return currentState ( true ) == HIGH;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwButton::hasChangedStable () {

  return hasChanged ( true );

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint8_t CwwButton::currentStateStable () {

  return currentState ( true );

}

// ----------------------------------------------------------------------------

boolean CwwButton::isStable () {

  return isStableAtState ( readPin () );

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

boolean CwwButton::isStableAtState ( uint8_t state ) {
  
  unsigned long debounceStartTimeMs;
  boolean       timeHasExpired;
  uint8_t       buttonStateNow;
  boolean       buttonHasChanged;

  debounceStartTimeMs = millis ();
  do {
    buttonStateNow = readPin ();
    buttonHasChanged = buttonStateNow != state;
    timeHasExpired = millis() - debounceStartTimeMs < debounceTimeMs;
  } while ( ! buttonHasChanged && ! timeHasExpired );

  if ( ! buttonHasChanged ) buttonStateLast = state;

  return ! buttonHasChanged;

}

// ----------------------------------------------------------------------------

void CwwButton::setDebounceTime ( uint16_t ) {

  this->debounceTimeMs = debounceTimeMs;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint16_t CwwButton::valueOfDebounceTime () {

  return debounceTimeMs;

}

// ============================================================================
// Private Functions
// ============================================================================

uint8_t CwwButton::readPin () {

  uint8_t stateOfPin;

  if ( pinIsAnalog ) {
    stateOfPin = analogRead ( pinOfButton ) > ( 0x3ff >> 1 ) ? HIGH : LOW;
  }
  else {
    stateOfPin = digitalRead ( pinOfButton );
  }

  return stateOfPin;

}

// ****************************************************************************
