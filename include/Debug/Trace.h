/*
 * Debug via printing to the serial port.
 *
 * The Freematics ONE+ A and B devices do not make GPIO pins 12 to 15 available
 * for JTAG debugging. Therefore we use Serial.println() and SerialBT.println()
 * to implement basic tracing.
 */

#ifndef DEBUG_TRACE_H_
#define DEBUG_TRACE_H_

#ifdef DEBUG
#define DEBUG_TRACE(message) \
  Serial.print(message);     \
  SerialBT.print(message);
#else
#define DEBUG_TRACE(x)
#endif

#endif
