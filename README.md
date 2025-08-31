AVR Digital Clock with Alarm (ATmega32 + LCD + Buzzer)

This project implements a digital clock with alarm functionality using an ATmega32 microcontroller and a 16x2 LCD.

The clock allows you to:

Display the current time (hours, minutes, seconds).

Set the initial time from which the clock starts running.

Configure an alarm time (hours, minutes, seconds).

Activate/deactivate the alarm.

Trigger a buzzer (or LED) when the alarm goes off.

Turn off the buzzer manually.

🛠 Hardware Requirements

Microcontroller: ATmega32

LCD: 16x2 alphanumeric LCD (connected via alcd.h library)

Buttons (on PORTA):

PINA.0 → SET (switch between states)

PINA.1 → RIGHT (navigate settings / toggle alarm)

PINA.2 → UP (increment selected field or stop buzzer)

Buzzer/LED: connected to PORTD.6 for alarm output

Clock source: System clock (Timer0 used for 1ms ticks)

⚙️ Software Features
Main Functions:

Clock Mode (state1)

Displays the current time (HH:MM:SS).

Automatically increments time every second.

Time Setup Mode (state2–state4)

Allows setting Hours → Minutes → Seconds using the buttons.

Alarm Setup Mode (state5–state7)

Allows setting Alarm Hours → Alarm Minutes → Alarm Seconds.

Alarm Active Mode (state8)

Shows the running clock.

Displays A on the screen if the alarm is active.

When clock time matches alarm time, buzzer (PORTD.6) turns on.

The buzzer automatically turns off after 60 seconds if not stopped.

Alarm Off Mode (state9)

Buzzer (PORTD.6) is turned off manually.

Returns back to normal clock operation.
💻 Code Written using CodeVisionAVR.

📽️ Video YouTube video link: https://youtu.be/BkosUO_lfEA
