/* Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdint.h>
#include <n76e003.h>

// 16Mhz clock
#define CLOCK 16000000L
// Divide by 12
#define T0CLOCK ((CLOCK)/12L)
// Per milisecond
#define T0_1MS ((T0CLOCK)/1000L)

static void msdelay(uint32_t count)
{
	uint16_t reload = -T0_1MS;

	// Input = Fsys/12
	SET_FIELD(CKCON, T0M, 0);
	// Mode 1
	SET_FIELD(TMOD,  T0M, 1);

	// Start
	TR0 = 1;
    while (count != 0)
    {
        TL0 = reload      & 0xFF;
        TH0 = reload >> 8 & 0xFF;;

        while(!TF0);
        TF0 = 0;

	    count--;
    }
    TR0 = 0;
}

void main() {
	// Set pins in old-skool Quasi Bidirectional mode
	P0M1 = 0;
	P0M2 = 0;
	P1M1 = 0;
	P1M2 = 0;
	P3M1 = 0;
	P3M2 = 0;

	for (;;) {
		int i;
		for (i = 0; i < 10; i++) {
			P12 = 0;
			msdelay(25);
			P12 = 1;
			msdelay(25);
		}
		msdelay(500);
	}
}
