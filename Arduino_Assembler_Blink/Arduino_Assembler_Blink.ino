/*
 * Demo sketch to show how to call a trivial assembler function from
 * within a standard Arduino sketch. This is a variant of the infamous
 * BLINK sketch for pin 13 of an UNO. Sorry about that.
 *
 * Ralph S Bacon October 2020 	www.youtube.com/ralphbacon
 *
 * I recommend that you fiddle about with either the sketch or asm code
 * to se how it all works - you can always download the original again
 * if you break it (easy to do).
 */

/*
 * We need this counter variable to be declared "volatile" so we
 * never read the value from some register, we always read the
 * memory location (it will be updated in the background via the
 * assembler routine)
 */
volatile uint16_t myCounter asm("counter") __attribute__ ((used)) = 10;

/*
 * The "used" attribute means that despite appearances, we're telling the
 * compiler not to omtimise it away and just use the fixed value of 0.
 *
 * We can, if required, change the symbolic name used in the assembler
 * function eg we use myCounter in the sketch but the assembler routine
 * uses the symbolic name "counter"
 */


/*
 * We must declare that certain functions are "elsewhere" not in this
 * sketch, and are "C" compatible. The linker will find them.
 */
extern "C" {
/*
 * function prototypes - the names declared here so we can
 * reference them in the code below without getting errors.
 */
void start();
void blink();
}

// Standard setup
void setup() {
	// As we want to display serial (debugging) messages, start the serial port
	Serial.begin(9600);

	// This routine (declared above as an external, C routine) now called
	start();

	// All done here
	Serial.println("Setup completed");
}

// Standard loop
void loop() {

	// This routine (declared above as an external, C routine) now called
	blink();

	// Progress message
	Serial.print("That's a blink:");

	// Now print the (updated, via the assembler routine) value
	Serial.println(myCounter);
}
